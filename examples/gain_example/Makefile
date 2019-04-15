# define the compiler
CC      = g++

# path(s) to include files
CFLAGS  = -I.

# libraries to link
LDFLAGS = -ljack -llo -lyaml-cpp

SRCS = main.cpp gain_example.cpp oscman.cpp yamlman.cpp
DEPS = oscman.h gain_example.h yamlman.h

all: gain_example

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

gain_example: main.o gain_example.o oscman.o yamlman.o
	$(CC) -o gain_example main.o gain_example.o oscman.o yamlman.o $(LDFLAGS)


clean:
	rm *.o gain_example
