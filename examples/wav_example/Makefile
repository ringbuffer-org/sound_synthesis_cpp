# define the compiler
CC      = g++

# path(s) to include files
CFLAGS  = -I.


# libraries to link
LDFLAGS = -ljack -llo -lsndfile

SRCS = main.cpp wav_example.cpp oscman.cpp singlesample.cpp
DEPS = oscman.h gain_example.h

all: wav_example

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

wav_example: main.o wav_example.o oscman.o singlesample.o
	$(CC) -o wav_example main.o wav_example.o oscman.o singlesample.o  $(LDFLAGS)


clean:
	rm *.o wav_example
