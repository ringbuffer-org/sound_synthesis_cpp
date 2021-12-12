#!/bin/bash
g++ -Wall -L/usr/lib src/yamlman.cpp src/main.cpp src/karplus_strong_example.cpp src/oscman.cpp src/midiman.cpp -ljack -llo -lyaml-cpp -lsndfile -lrtmidi -o karplus_strong
