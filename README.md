 ostep-vectors
Potential solution to homework question #14:8 from the [OSTEP book](http://pages.cs.wisc.edu/~remzi/OSTEP/) in the form of a command line librarian program. 

## Help:

Arguments:

* use -h to print out the help file (this section of the README.md).
* use -a to add a record (requires arguments).
* use -r to remove a record (requires argument).
* use -p to print out all records.
* Adding and removing records requires a subsequent comma-seperated list of information (title, author, page count, isbn) at least one additional argument is required.

e.g: 

./program -a Operating Systems, Arpaci-Dusseau, 675, 198508649

./program -r Operating Systems, Arpaci-Dusseau


## todo:
1. Get initial memory allocation and initalisation working and passing in _valgrind_ [X].
2. Create procedures for adding new entries to the struct, reallocating the memory in the vector array and initalising this new entry within each element [-].
3. Add command line parsing [-].
4. Remove keyboard input code [].
5. Add tests, fix bugs [].
