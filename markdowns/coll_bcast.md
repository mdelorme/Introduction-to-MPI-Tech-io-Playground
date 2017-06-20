# Broadcasting

Broadcasting happens when one process wants to send the same information to every other process. We have seen in the previous lesson an example of broadcasting. Broadcast is a non blocking operation, so processes continue running as soon as the information has been sent/received.

After the operation, all process will have a copy of the data from the **root** process in their buffers.

You might wonder the advantages of a broadcasting operations compared to a sequence of send. Aside from the actual elegance of not having an if-statement and having to pick between Send and Receive operations, a Broadcast is a lot more effective than a list of send receives. It is always a bit tricky to talk about performances and collective operations because efficiency and speed is highly dependant on the implementation. Let's compare two possible algorithms for broadcasting an array of integers elements from the process 0 to 8 other processes.

The first implementation is the P2P version described in the previous lesson. The root sends information to all the other processes in turn, which makes the complexity of this implementation $`O(N)`$.

![Broadcast using linear implementation](/img/bcast_p2p.gif)

The second implementation is dynamic and relies on a tree structure. Basically, a process that already has received information will send to other processes in turn : Process 0 is going to send its data to process 1. Then, simultaneously, process 0 is going to transmit to process 2, and process 1 to process 3, etc. The following animation describes the sequence of communications. This animations makes things a bit clearer :

![Broadcast using tree implementation](/img/bcast_tree.gif)

As you can see, the first implementation requires 8 steps while the second only 4. More generally, the tree algorithm has a complexity in $`O(log n)`$.

These are two examples of implementation for a broadcast algorithm. Now the beauty of the implementations such as OpenMPI is that they have [decision algorithms](https://www.open-mpi.org/papers/workshop-2006/tue_07_coll_and_topo.pdf) running on top of your calls, that choose which algorithm to apply depending on your bandwidth, quantity of data and processes. As per OpenMPI, it is also possible to include your [own implementation](https://www.open-mpi.org/papers/ics-2004/ics-2004.pdf) in the code if you feel like your code would benefit from a very specific algorithm.

As for actual quantitative comparisons, [MPI Tutorial](http://mpitutorial.com/tutorials/mpi-broadcast-and-collective-communication/) has a very nice comparison program between the first version and whatever your implementation of MPI will use for broadcasting an array. It is really interesting to take a look at the code and play a bit with it locally.

Now that we have seen what a broadcast is and why it's interesting to use a dedicated function of the implementation, let's move to a small exercise to code our first broadcast in MPI.