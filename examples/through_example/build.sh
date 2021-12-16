#!/bin/sh

g++ -std=c++11 gain_example.cpp oscman.cpp -ljack -llo -o gain_example
