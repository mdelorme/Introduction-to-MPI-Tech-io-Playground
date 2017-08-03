# Communicators creation

There are various ways of creating new communicators in MPI. A new communicator is always created from another so every communicator derives from `MPI_COMM_WORLD`. There are two easy ways of doing things : either you create a new group and derive a communicator from it, or you **split** an existing communicators into sub-communicators. In this lesson, we are going to explore the latest.

## Communicator splitting

To explain splitting, let's take an example. Consider we have a program with 8 processes. At the beginning, all of these processes are grouped inside `MPI_COMM_WORLD`.

![Comm splitting, part 1](/img/splitting_p1.png)

Now, let's imagine that we want to make two new communicators. One will group processes 0, 1, 2 and 3. The other will group processes 4, 5 and 6. Process 7 will stay only be in `MPI_COMM_WORLD`. Now assigning a process to another communicator does not mean that the process leaves the original communicator. So all these processes will stay in `MPI_COMM_WORLD`.

Splitting is the action of taking an existing communicator and distributing all of its processes to new communicators. The way we do it is by assigning every process a number that will tell in which communicator it will end after the splitting. That number is called a **colour**.

![Comm splitting, part2](/img/splitting_p2.png)

As you can see, we assign processes 0, 1, 2 and 3 the color 0, and the color 1 to processes 4, 5 and 6. Process 7 has no colour. There is a way in MPI to indicate that you don't want the process to be placed in any new communicator. Then, we act the splitting, and create the new communicators.

![Comm splitting, part3](/img/splitting_p3.png)

Now the processes 0 to 6 are belonging to two communicators. Processes 0, 1, 2 and 3 are in `MPI_COMM_WORLD` and in `CUSTOM_COMM1` while processes 4, 5 and 6 in `MPI_COMM_WORLD` and `CUSTOM_COMM2`. A very important thing to understand is that every communicator has its own size. Thus the size of `MPI_COMM_WORLD` is 8, the size of `CUSTOM_COMM1` is 4 and the one of `CUSTOM_COMM2` is 3.

Also note that, as stated in the introduction, the rank of a process in a communicator will always start from 0. Thus, process 0 in `MPI_COMM_WORLD` is still process 0 in `COMM_CUSTOM1`, but also process 4 in `MPI_COMM_WORLD` is process 0 in `COMM_CUSTOM2`. Bear in mind that the rank of a process only has a meaning with respect to a specific communicator.

The ordering of the processes in the communicator can also be defined when we split, but we will see this during the next exercise.

One last thing before practicing : nothing prevents you to create subsequent communicators. After doing this first split, you can do another split, either on `MPI_COMM_WORLD`, on `CUSTOM_COMM1` or on `CUSTOM_COMM2`. Let's imagine that now we want to create a third custom communicator `CUSTOM_COMM3` grouping processes 0 and 4 of `MPI_COMM_WORLD`. Then we can split `MPI_COMM_WORLD` again, and create that new communicator.

![Comm splitting, part4](/img/splitting_p4.png)