#!/bin/bash

g++ -std=c++11 -Wall -o zerr main.cpp  zerr.cpp -ljack -lfftw3 -lm
