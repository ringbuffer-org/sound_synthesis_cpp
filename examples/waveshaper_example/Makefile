# define the compiler
CC      = g++

# path(s) to include files
CFLAGS  = -I.

# libraries to link
LDFLAGS = -ljack -llo -lsndfile -lyaml-cpp

SRCS = main.cpp waveshaper.cpp oscman.cpp yamlman.cpp transferfunction.cpp sinefolder.cpp tangentshaper.cpp
DEPS = oscman.h waveshaper.h yamlman.h transferfunction.h sinefolder.h tangentshaper.h

all: waveshaper

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

waveshaper: main.o waveshaper.o oscman.o yamlman.o transferfunction.o sinefolder.o tangentshaper.o
	$(CC) -o waveshaper main.o waveshaper.o oscman.o yamlman.o transferfunction.o sinefolder.o tangentshaper.o $(LDFLAGS)

clean:
	rm *.o waveshaper
