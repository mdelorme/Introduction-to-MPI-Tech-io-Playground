# MPI_COMM_WORLD, size and ranks

Before starting any coding, we need a bit of context. When a program is ran with MPI all the processes are grouped in what we call a **communicator**. You can see a communicator as a box grouping processes together, allowing them to communicate. Every communication is linked to a communicator, allowing the communication to reach different processes. Communications can be either of two types :

* **Point-to-Point** : Two processes in the same communicator are going to communicate.
* **Collective** : All the processes in a communicator are going to communicate together.

The default communicator is called `MPI_COMM_WORLD`. It basically groups all the processes when the program started. If you take a look at the example below, you see a depiction of a program ran with five processes. Every process is connected and can communicate inside this communicator.

![MPI_COMM_WORLD](/img/MPI_COMM_WORLD.png "MPI_COMM_WORLD is a communicator holding every single processes ran at the same time")

`MPI_COMM_WORLD` is not the only communicator in MPI. We will see in a future chapter how to create custom communicators, but for the moment, let's stick with `MPI_COMM_WORLD`. In the following lessons, every time communicators will be mentionned, just replace that in your head by `MPI_COMM_WORLD`.

The number in a communicator does not change once it is created. That number is called the **size** of the communicator. At the same time, each process inside a communicator has a unique number to identify it. This number is called the **rank** of the process. In the previous example, the size of `MPI_COMM_WORLD` is 5. The rank of each process is the number inside each circle. The rank of a process always ranges from $`0`$ to $`size-1`$.

Now that we have stated this very basic information about communicators, let's try and make our first program, a very simple Hello World.