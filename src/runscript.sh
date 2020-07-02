#!/bin/bash
gcc libtep.c -o libtep.o -c
gcc filehandler.c -o filehandler.o -c
gcc -o libtep libtep.o filehandler.o
valgrind --track-origins=yes ./libtep -a "Algorithms To Live By, Christian & Griffiths, 275"
./libtep -a "Operating Systems, Arpaci-Dusseau, 675"
./libtep -r "Operating Systems"
./libtep -p
echo Complete!
