#!/bin/bash
gcc libtep.c -o libtep.o -c
gcc filehandler.c -o filehandler.o -c
gcc -o libtep libtep.o filehandler.o
valgrind --track-origins=yes ./libtep -a "Input Title, Input Author, 2000"
echo Complete!
