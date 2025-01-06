.. title: Using YAML for Configuration
.. slug: cpp-yaml
.. date: 2021-12-10
.. tags:
.. category: cpp:libraries
.. link:
.. description:
.. type: text
.. has_math: true
.. priority: 4

At some point, a program might require more arguments on startup than a command line call can manage without complications. In that case it can help to work with configuration files, which are passed to the binary when starting it. This can be done in many ways, including plain text files or markup languages like XML, Markdown, JSON or others.

The examples in this module use `YAML <https://yaml.org/>`_ for passing configuration data.
YAML is human-readable and easy to edit, which allows quick changes to configurations.

-----

The YamlMan Class
-----------------

The YAML manager class ``YamlMan`` is used in all following examples which make use of YAML for parsing configuration parameters in adapted versions.

The Constructor
===============

The constructor of the class is passed a file path to a YAML file as argument:

.. code-block:: cpp

  YamlMan::YamlMan(std::string filepath)

The following behavior is specific for each example, storing the values from the YAML file to member variables:

.. code-block:: cpp

  YAML::Node config = YAML::LoadFile(filepath);

  // access YAML nodes:
  param1 = config["param1"].as<std::string>();
  param2 = config["param2"].as<int>();
  param3 = config["param3"].as<double>();
