# define the compiler
CC      = g++

# path(s) to include files
CFLAGS  = -I.

# libraries to link
LDFLAGS = -lrtmidi

SRCS = main.cpp midiman.cpp
DEPS = datatypes.h midiman.h

all: midi_tester

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

midi_tester:  main.o midiman.o
	$(CC) -o midi_tester main.o midiman.o $(LDFLAGS)

clean:
	rm *.o midi_tester
