# Non-blocking communications

For the moment, we have only seen **blocking** point-to-point communication. That means that when a process sends or receive information, it has to [wait](https://cvw.cac.cornell.edu/MPIP2P/rendezvous.html) (Animation from Cornell virtual workshop) for the transmission to end to get back to what it was doing. In some applications, this can be terribly limiting. Let's take a first example to figure out why :

![Blocking limit 1](/img/blocking_non_blocking.png)

In this case, process 0 has some information to send to process 1. But both are working on very different things and, as such, take different time to finish their computations. Process 0 is ready to send its data first, but since process 1 has not finished its own computations, process 0 has to wait for process 1 to be ready before getting back to its own work. Process 1 finishes treating the data really quickly and now waits for process 0 to finish for getting new data. This way of sending messages is possible in MPI and called **non-blocking** communications.

Now this is an ideal case where process 0 could be informed that process 1 is available for discussion as soon as it is. Unfortunately in computer science terms, it would mean you have an additional process running in the background and monitoring the availability of both processes, which is not very efficient.

Instead, you can see non-blocking communications as a way to prepare everything for the communication, and once in a while, both process check their availability to do a transfer. This might be a bit obscure so let's work an example together. First in pseudo-code and then in C++. Let's imagine that process 0 has first to work for 3 seconds, then for 6. At the same time, process 1 has to work for 5 seconds, then for 3. They must synchronise some time in the middle, and at the end.

## Blocking version

In terms of pseudo-code, the blocking version will give us the following :

**Process 0**

```
Work for 3 seconds
Blocking-send data to process 1
Work for 6 seconds
Blocking-send data to process 1
```

** Process 1**

```
Work for 5 seconds
Blocking-receive data from process 0
Work for 3 seconds
Blocking-receive data from process 0
```

You can easily see from that example that the blocking communication will force process 0 into waiting for process 1. To get to the first communication, both programs will have to wait for 5 seconds. Then, to get to the second communication, both will have to wait for 6 more additional seconds. That means that in total, the program will take at least 11 seconds to run. A little more than that because of the overhead of actually sending/receiving the data.

In C++, if we "simulate" the work by making the processes sleep, the following code will do the job :

```cpp
if (rank == 0) {
    sleep(3);
    MPI_Send(buffer, buffer_count, MPI_INT, 1, 0, MPI_COMM_WORLD);
    sleep(6);
    MPI_Send(buffer, buffer_count, MPI_INT, 1, 1, MPI_COMM_WORLD);
  }
  else {
    sleep(5);
    MPI_Recv(buffer, buffer_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    sleep(3);
    MPI_Recv(buffer, buffer_count, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
```

Please note that we use a different tag to denote the two different communications.

## Non-blocking version

We can do better than this by using non-blocking communications. Instead of process 0 waiting for process 1 for the first communication, process 0 can continue to work and only probe if process 1 is ready for communication every millisecond. To be honest, this is a toy-example. In real-life application, the probing will be done at very specific points of your code. There are no real specificities here, so you will have to decide how the probing and synchronisation is done.

Here is the pseudo-code of the non-blocking version :

** Process 0**
```
Work for 3 seconds
Initialise the send to process 1
Work for 6 seconds
  Every 1ms, probe process 1 and communicate if necessary
Initialise the second send to process 1
Wait for process 1 to receive the data
```

** Process 1**
```
Work for 5 seconds
Initialise receive from process 0
Wait for a communication from process 0
Work for 3 seconds
Initialise receive from process 0
Wait for a communication from process 0
```

It makes the code a little bit more complex. Also, note that we are sort of cheating. Since we already know the time taken by both processes in the work phases, we make things a bit easier by forcing process 1 to wait for the data. The important part is in process 0 where the probing is done every millisecond.

What's next ? I suppose you are expecting the C++ code ? Well, this one you will have to write in the exercise that is coming next !
