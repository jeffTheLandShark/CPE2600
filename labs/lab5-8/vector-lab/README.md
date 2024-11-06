# CPE2600 Vector Lab

## Description
This program is a simple vector calculator that can perform basic operations on vectors.

The vectors are stored in a dynamic array of `struct Vect` objects. The program uses dynamic memory to store the vectors and their components. The program will automatically resize the array when the number of vectors exceeds the current capacity. A vector will be redefined if a new vector is named the same as an existing vector.

## Build
To build the program, simply run `make`. The makefile will compile the program and create an executable named `matlab-clone.exe`. 

## Run
To run the program, execute the following command:
```
./matlab-clone.exe
```
The program will display a prompt `>`. You can then enter commands to perform operations on vectors.

The program supports the following command line options:
- `-h` or `--help`: Display help message
- `-f`: Load vectors from a file

## Commands
The program can perform the following operations:
- Assignment: `varname = x y z`
- Display: `varname`
- Addition: `varname = var1 + var2`
- Subtraction: `varname = var1 - var2`
- Scalar Multiplication: `varname = var1 * num`
- Operation plus assignment: `varname = var1 + var2`
- Dot product: `varname = var1 . var2`
- Cross product: `varname = var1 x var2`
- Clear list: `clear`
- Display list: `list`
- Load from file: `load filename`
- Save to file: `export filename`

## Using Dynamic Memory
My program uses dynamic memory to store the vectors and their components, and for file I/O.
- The vectors are stored in a dynamic array of `struct Vect` objects. The program will automatically resize the array to double the current size when the number of vectors exceeds the current capacity. 
- The input file is read line by line, and the program closes the file after reading the data. 