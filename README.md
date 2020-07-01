A "librarian" Unix command line program demonstrating methods outlined in the [OSTEP book](http://pages.cs.wisc.edu/~remzi/OSTEP/) (basic vector array data structure using malloc/realloc) and [Hacking: The Art of Exploitation](https://www.amazon.co.uk/Hacking-Art-Exploitation-Jon-Erickson/dp/1593271441) (file access program that accounts for uids).

## Help:

Arguments:

* use -h to print out the help file (this section of the README.md).
* use -a to add a record (requires arguments).
* use -r to remove a record (requires argument).
* use -p to print out all records.
* Adding and removing records requires a string format comma-seperated list of information (title, author, page count, isbn) at least one additional argument is required.

e.g: 

./program -a "Operating Systems, Arpaci-Dusseau, 675"

./program -r "Operating Systems, Arpaci-Dusseau"


## todo:

TBD.

## Notes:
... Currently working on a full multi-file reformat based around a file-access structure (e.g. read from file, write to file, re-write file, super simple). The vector array problem outlined in OSTEP is going to be framed around a secondary file which is read in every time the program runs, this holds the 'changed' files - allowing a user to undo an add or remove action.