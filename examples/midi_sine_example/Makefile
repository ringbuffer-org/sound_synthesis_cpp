# define the compiler
CC      = g++

# path(s) to include files
CFLAGS  = -I.

# libraries to link
LDFLAGS = -ljack -llo -lrtmidi

SRCS = main.cpp midi_sine_example.cpp midiman.cpp sinusoid.cpp
DEPS = midi_sine_example.h midiman.h sinusoid.h

all: midi_sine_example

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

midi_sine_example:  main.o midi_sine_example.o midiman.o sinusoid.o
	$(CC) -o midi_sine_example main.o midi_sine_example.o midiman.o sinusoid.o $(LDFLAGS)

clean:
	rm *.o midi_sine_example
