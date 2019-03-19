# define the compiler
CC      = g++

# path(s) to include files
CFLAGS  = -I.

# libraries to link
LDFLAGS = -ljack -llo

SRCS = gain_example.cpp oscman.cpp
DEPS = oscman.h gain_example.h

all: gain_example

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

gain_example: gain_example.o oscman.o 
	$(CC) -o gain_example gain_example.o oscman.o $(LDFLAGS)


clean:
	rm *.o gain_example
