#!/bin/sh

g++ -Wall -std=c++11 src/main.cpp src/gain_example.cpp src/oscman.cpp -ljack -llo -o gain_example
