# Splitting - exercise

We are now going to practice splitting. This exercise will be a toy exercise with no real purpose other than splitting a single communicator into multiple ones. We are going to reproduce the example in the previous lesson.

![Comm splitting, exercise](/img/splitting_p4.png)

For this, as we described in the previous lesson, you will have to split `MPI_COMM_WORLD` twice. Once to create `CUST_COMM1` and `CUSTOM_COMM2`, and a second time to create `CUSTOM_COMM3`. Then, the program will test your new communicators and check that everything is correct.

## Splitting

`MPI_Comm_split`, the splitting function is a blocking call. That means that all the processes on the original communicator will have to call the function for it to return. The splitting function in MPI is prototyped as follows :

```cpp
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm);
```

This requires a bit of explanation. The first parameter `comm` is the communicator we want to split. In our case, it is going to be `MPI_COMM_WORLD`. The `color` parameter corresponds to what we have said before : Every process gets a color depending on which communicator they will be. Same color process will end up on the same communicator. Let's skip the `key` parameter for the moment, and just skip to `newcomm`. `newcomm` is a pointer to your new communicator.

## Rank ordering

The `key` parameter is an indication of the rank each process will get on the new communicator. The process with the lowest key value will get rank 0, the process with the second lowest will get rank 1, and so on. By default, if you don't care about the order of the processes, you can simply pass their rank in the original communicator as `key`, this way, the processes will retain the same order.

## What about process 7 ?

You are right ! Process 7 in the first split, and processes 1, 2, 3, 5, 6, 7 in the second split will not end up in a new communicator. By using `MPI_UNDEFINED` as a color in `MPI_Comm_split`, the processes won't end up on any communicator. More precisely, the communicator that will be returned in `newcomm` will be `MPI_COMM_NULL` which corresponds to a null pointer.

## Statement

It's your turn to play. Note that, there are multiple ways of doing this properly. For this exercise, try to have only two calls to MPI_Comm_split in total in your code.

Your splitting is going to be validated with various broadcasts on the new communicators. If a problem arises, MPI will crash and give a message on the command line indicating the problem. If the crash message indicates that something is wrong with `MPI_Bcast` that might indicate that the processes have been assigned to the wrong communicators.

@[Splitting communicators]({"stubs": ["comm_splitting_ex/splitting.cpp"], "command": "bash comm_splitting_ex/splitting.sh", "layout": "aside"})