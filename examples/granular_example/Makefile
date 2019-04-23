# define the compiler
CC      = g++

# path(s) to include files
CFLAGS  = -I.

# libraries to link
LDFLAGS = -ljack -llo -lsndfile

SRCS = main.cpp granular_example.cpp oscman.cpp singlesample.cpp grainplayer.cpp triangularwindow.cpp
DEPS = granular_example.h oscman.h singlesample.h grainplayer.h triangularwindow.h

all: granular_example

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

granular_example: main.o granular_example.o oscman.o singlesample.o grainplayer.o triangularwindow.o
	$(CC) -o granular_example main.o granular_example.o oscman.o singlesample.o grainplayer.o triangularwindow.o $(LDFLAGS)

clean:
	rm *.o granular_example
