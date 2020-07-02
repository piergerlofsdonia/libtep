#!/bin/bash
gcc libtep.c -o libtep.o -c
gcc filehandler.c -o filehandler.o -c
gcc -o libtep libtep.o filehandler.o
valgrind --track-origins=yes ./libtep -a "Algorithms to Live By, Christian & Griffiths, 353"
echo Complete!
