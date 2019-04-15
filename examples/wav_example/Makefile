# define the compiler
CC      = g++

# path(s) to include files
CFLAGS  = -I.

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    DBFLAGS = -g -Wall -Werror
else
    DBFLAGS = 
endif


# libraries to link
LDFLAGS = -ljack -llo -lsndfile

SRCS = wav_example.cpp oscman.cpp singlesample.cpp
DEPS = oscman.h gain_example.h

all: wav_example

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

wav_example: wav_example.o oscman.o singlesample.o
	$(CC) $(DBFLAGS) -o wav_example wav_example.o oscman.o singlesample.o  $(LDFLAGS)


clean:
	rm *.o wav_example
