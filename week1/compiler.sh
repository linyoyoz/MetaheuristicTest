#!/bin/bash
g++ -c ExhaustiveSearch.cpp  HillClimbing.cpp
g++ -o search ExhaustiveSearch.o HillClimbing.o search.cpp
