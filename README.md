A "librarian" Unix command line program taken from the note-taking app idea outlined in [Hacking: The Art of Exploitation](https://www.amazon.co.uk/Hacking-Art-Exploitation-Jon-Erickson/dp/1593271441) (file access program that accounts for uids).

## Help:

Arguments:

* use -h to print out the help file (this section of the README.md).
* use -a to add a record (requires arguments).
* use -r to remove a record (requires argument).
* use -p to print out all records.
* Adding and removing records requires a string format comma-seperated list of information (title, author, page count, isbn) at least one additional argument is required.

e.g: 

./libtep -a "Operating Systems, Arpaci-Dusseau, 675"

./libtep -r "Operating Systems, Arpaci-Dusseau"


#### Note:

I had originally thought of using a endless loop to add records into a dynamic array of vectors (OSTEP homework assignment, hence the name) - however, as time progressed it seemed obvious to just use file access and an array of strings (arguments taken from the cl). 