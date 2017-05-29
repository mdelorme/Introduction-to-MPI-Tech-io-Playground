# Hello World

Let's start diving in the code.
First of all, MPI must always be initialised and finalised. Both operations must be the first and last calls of your code, always. The corresponding commands are `MPI_Init` and `MPI_Finalize`. `MPI_Init` always takes a reference to the command line arguments, while `MPI_Finalize` does not.

If you remember, in the previous lesson we talked about *rank* and *size*. The way to obtain these, is to use the following calls :

```cpp
int size, rank;
MPI_Comm_Size(MPI_COMM_WORLD, &size);
MPI_Comm_Rank(MPI_COMM_WORLD, &rank);
```

Note the `MPI_COMM_WORLD`, that indicates that the operation is done on the communicator `WORLD`, which is a MPI-specific constant indicating that we are looking at every single processes ran at the same time. We will see later what communicators are and how to create them to create groups of processes. For the moment, we will stick with calling MPI on the `WORLD` communicator. 

## Instructions
Now the first exercise will be to write a program which does the following steps :

* Initialises MPI.
* Reads the size of `MPI_COMM_WORLD` and the rank of the current process.
* Prints `Hello world, from process #<RANK OF THE PROCESS`.
* Finalizes MPI and exits.

@[Hello World]({"stubs": ["01_hello_world/hello_world.cpp"], "command": "sh exercises/01_hello_world/hello_world.sh"})