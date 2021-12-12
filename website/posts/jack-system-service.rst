.. title: Starting JACK Projects as System Service
.. slug: jack-system-service
.. date: 2020-05-07 09:27:37 UTC
.. tags: 
.. category: cpp:system
.. link: 
.. description: 
.. type: text


In some applications, like headless or embedded systems,
it can be helfpul to autostart the jack server,
followed by additional programs for sound processing.
In this way, a system can boot into the desired configuration
without additional user interaction.
There are several ways of achieving this. The following example
uses ``systemd`` services for a user named ``student``.

-----

The JACK Service
================

The JACK service needs to be started before the
clients. It is a system service and needs just a few
entries. This is a minimal example - depending on the application and hardware settings,
the arguments after ``ExecStart=/usr/bin/jackd`` need to be adjusted.


.. code-block:: sh

    [Unit]
    Description=Jack audio server 

    [Install]
    WantedBy=multi-user.target

    [Service]
    Type=simple
    PrivateTmp=true
    Environment="JACK_NO_AUDIO_RESERVATION=1"
    ExecStart=/usr/bin/jackd -d alsa
    User=student

    
The above content needs to be placed in the following file (root privileges are required for doing that):

.. code-block:: sh
		
 /etc/systemd/system/jack.service

Afterwards, the service can be started and stopped via the command line:

.. code-block:: sh
		
 $ sudo systemctl start jack.service 
 $ sudo systemctl stop jack.service 

In order to start the service on every boot, it needs to be enabled:

.. code-block:: sh
		
 $ sudo systemctl enable jack.service 

If desired, the service can also be deactivated:

.. code-block:: sh
		
 $ sudo systemctl disable jack.service 


-----
 
The Client Service(s)
=====================

Once the JACK service is enabled, 
client software can be started.
A second service is created, which
is executed after the JACK service.
This is ensured by the additional
entries in the ``[Unit]`` section.
The example service launches a Puredata
patch without GUI:

.. code-block:: sh

    [Unit]
    Description=Synthesis Software 
    After=jack.service
    Requires=jack.service

    [Install]
    WantedBy=multi-user.target

    [Service]
    Type=idle
    PrivateTmp=true
    ExecStartPre=/bin/sleep 1
    ExecStart=/usr/bin/puredata -nogui -jack ~/PD/test.pd
    User=student

The above content needs to be placed in the following file:

    
.. code-block:: sh
		
 /etc/systemd/system/synth.service

The service can now be controlled with the above introduced
``systemctl`` commands. When enabled, it starts on every boot
*after* the JACK server has been started:


.. code-block:: sh
		
 $ sudo systemctl enable synth.service 
