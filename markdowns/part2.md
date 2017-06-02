# MPI_COMM_WORLD, size and ranks

Before starting any coding, we need a bit of context. When a program is ran with MPI all the processes are grouped in what we call a communicator. You can see a communicator as a box grouping processes together, allowing them to communicate. Every communication is linked to a communicator, allowing the communication to reach different processes. Communications can be either of two types :

* Point-to-Point : Two processes in the same communicator are going to communicate.
* Collective : All the processes in a communicator are going to communicate together.

![MPI_COMM_WORLD](/img/MPI_COMM_WORLD.png "MPI_COMM_WORLD is a communicator holding every single processes ran at the same time")

The default communicator is called `MPI_COMM_WORLD`. It basically groups all the processes started at the same time on the command line. If you take a look at the example below, you see a depiction of a program ran with five processes. Every process is connected and can communicate inside this communicator. 

![MPI_COMM_CUSTOM](/img/MPI_COMM_CUSTOM.png "Custom communicators allow processes to be grouped differently, allowing finer communications between them")

`MPI_COMM_WORLD` is not the only communicator in MPI. It is possible to create custom communicators and we will see how to do this in a future chapter. On the example image, we have created three communicators on top of `MPI_COMM_WORLD`. `CUSTOM_COMM_1` groups processes 0, 1 and 2. `CUSTOM_COMM_2` groups processes 3 and 4, and `CUSTOM_COMM_3` groups processes 1 and 2. 

What that means in practice is that, it is impossible, when communicating on `CUSTOM_COMM_1`, to make a communication that is going to reach process #3. With the same logic, we see that it is impossible to create a Point-to-Point communication from #3 to #1 on `CUSTOM_COMM2` but possible to create such a Point-to-Point communication on `MPI_COMM_WORLD`. Although communicators might seem a bit obscure at the moment, their utility will become clear a bit later. For now, let's only concentrate on `MPI_COMM_WORLD`, which holds every single process ran from the command line. 

When a communicator is created, two fundamental properties are determined :

1- The communicator **size**, which indicates how many processes are grouped in this communicator
2- Every process has a **rank**, a unique id in the communicator used to communicate.

If you take a look at the annotated version of the previous figure :

![MPI_COMM_CUSTOM2](/img/MPI_COMM_CUSTOM2.png "The ranks of every process has been added, with respect to their communicators (matching colors)")

The rank of every process, on a communicator is given next to the process, in the color matcing the communicator. So you see that process number 2 on `MPI_COMM_WORLD` is process 2 on `COMM_CUSTOM_1` and process 0 on `COMM_CUSTOM_3`. There is no implicit way of knowing the rank of a process on a communicator. For this, we need to query the communicator using the function `MPI_Comm_rank`. Same for the size of a communicator, you can find it by calling the function `MPI_Comm_size`. We will use `MPI_Comm_rank` in a practical example in the next lesson. But now, let's test your understanding of the subject :

?[What is the size of COMM_CUSTOM_2 ?]
-[x] 2 processes
-[ ] 3 processes
-[ ] 4 processes

?[On which communicator(s) can we make a collective communication to reach P1 and P3 ?](multiple)
-[ ] COMM_CUSTOM_1
-[ ] COMM_CUSTOM_2
-[ ] COMM_CUSTOM_3
-[x] MPI_COMM_WORLD
-[ ] None

?[On which communicator(s) can we make a collective communication to reach ONLY P1 and P3 ?](multiple)
-[ ] COMM_CUSTOM_1
-[ ] COMM_CUSTOM_2
-[ ] COMM_CUSTOM_3
-[ ] MPI_COMM_WORLD
-[x] None

?[On which communicator(s) can we make a Point-to-Point communication between P2 and P3 ?](multiple)
-[ ] COMM_CUSTOM_1
-[ ] COMM_CUSTOM_2
-[x] COMM_CUSTOM_3
-[x] MPI_COMM_WORLD
-[ ] None


