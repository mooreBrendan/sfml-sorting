# sfml-sorting

This repository serves as test code for me to learn sfml coding before further working on my [Catan](https://github.com/mooreBrendan/Catan/issues) repository.

This project creates a window to display various different sorting algorithms.  It currently implements insertion sort, bubble sort, merge sort, and quick sort.

To build this project, install sfml from the [website](https://www.sfml-dev.org/) and build the code.  Change the Makefile in this project to point the variable "SFMLPath" to the path that sfml is installed at on your computer.  Additionally, add the sfml dll's to this project folder.  After that, either build the project normally with "make" or "debug" if you want to include debug output.  Additionally, "make remake" and "make remake-debug" are included for convenience.

This will create an output program called "Sorting.exe" that will run the compiled code.
