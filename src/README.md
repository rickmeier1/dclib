# CLI in C++ to simulate a fictional public library

```text
Usage:
  dclib [OPTION...]

 main options:
  -l, --list            List books in library
  -c, --create          Create a new book, see create options [-t,-a required]
  -r, --retrieve title  Retrieve info on a book
  -u, --update title    Update a book, use create options -t,-a,-s,-i to indicate update fields
  -d, --delete title    Delete a book

 create options:
  -t, --title title      Book title
  -a, --author author    Book author
  -s, --summary summary  Book summary
  -i, --isbn isbn        Book ISBN

```
