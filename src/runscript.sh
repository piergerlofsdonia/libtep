#!/bin/bash
gcc libtep.c -o libtep.o -c
gcc filehandler.c -o filehandler.o -c
gcc -o libtep libtep.o filehandler.o
valgrind ./libtep -p
./libtep -a "Game Engine Black Book: Wolfenstein 3D, Sanglard, 375"
./libtep -a "Algorithms To Live By, Christian & Griffiths, 265"
./libtep -p
./libtep -r "Algorithms To Live By"
./libtep -h
echo Complete!
