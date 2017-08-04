# Broadcasting - exercise 1

## Statement

In this exercise, we are going to setup a simple program with 3 processes. Each process will have a different role. Process #0 will read data (a buffer of doubles) on stdin, and send this data to the other processes. This will be done in two steps : first the process will send the number of elements it read from `stdin`, then the actual buffer. We do this, so processes #1 and #2 are able to create the reception buffers with the right size. Then every process will sum some elements and print the resulting value on `stdout` :

* Process 0 will sum and display all the elements of the buffer
* Process 1 will sum and display the positive elements
* Process 2 will sum and display the negative elements

## Broadcasting

The basic broadcasting function in MPI is `MPI_Bcast`, which is defined as follows :

```cpp
int MPI_Bcast(void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);
```

There is also a non-blocking version that works as the non-blocking p2p communications (and that should be followed by `MPI_Test` and `MPI_Wait`)

```cpp
int MPI_Ibcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request)
```
All parameters to these functions should be pretty obvious now. `root` is the id of the process sending the data, all other processes will be receivers and, as such, the values in `buffer` will be overwritten.

@[Broadcasting, exercise 1]({"stubs": ["coll_bcast_ex1/bcast.cpp"], "command": "bash coll_bcast_ex1/bcast.sh", "layout": "aside"})

