# Point-to-point communications, exercise 1

## Statement

It is time to code something a bit fancier than just printing your rank id on the screen. Let's have an actual communication between two processes. The objective of the exercise is as follows : The program will be ran with two processes. Your program will be given two random integers on the command line and read into a variable `local_value`. Then, depending on the id of the process, your program will have different behaviours :

**Process #0**

* Send your integer to Process #1
* Receive the integer of Process #1
* Write the sum of the two values on `stdout`

** Process #1**

* Receive the integer of Process #0
* Send your integer to Process #0
* Write the product of the two values on `stdout`

Note the order of the first two operations that are inverted on the two processes ? That is so we avoid one of the most frequent problems with blocking communications : a **deadlock**. Blocking communications, are their name implies, block the processes while the communication is not finished. So if process #0 waits for process #1 to send it a message, and process #1 waits for process #0 to send it a message, both process will be blocked in an endless wait : the deadlock.

## Emission :

You can send information to a process using the command `MPI_Send` :

```cpp
int MPI_Send(void *buf, int count , MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
```

Now these parameters should be almost obvious if you have followed the previous lesson. You can see that the first parameter is a void pointer, that means you just have to provide a pointer to a variable (if you send only one value) or an array (if you send multiple values).

Here are a few examples of sends :

**Sending an integer to process 2 :**

```cpp
int my_val = 10;
MPI_Send(&my_val, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
```

**Sending a table of integer to process 1 :**

```cpp
int values[5] = {1, 2, 3, 4, 5};
MPI_Send(values, 5, MPI_INT, 1, 0, MPI_COMM_WORLD);
```

**Sending a table of doubles to process 10 with a specific tag 6 :**

```cpp
double values[3] = {1e25, -0.0, M_PI};
MPI_send(values, 3, MPI_DOUBLE, 10, 6, MPI_COMM_WORLD);
```

The function also returns an integer. This value is an error code, telling if the communication was successful and in the case it was not, what happened. In case of an error however, you will not be able to directly use this information. By default, MPI sets up an error handler that will catch every error before exiting the calls. The default handler stops the program in case of an error. We will see in a future lesson how to setup the error handler and be more lenient on the send errors. For the moment, let's move on to reception of message.

## Reception :

The function to call to receive data from a process is very similar from the one to send but has an additional parameter :

```cpp
int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
```

As you can see, there is an additional `status` parameter. Let's ignore this by putting the value `MPI_STATUS_IGNORE` for the moment, we'll see more about this in the next exercise.

On top of the usual parameters, there are two wildcards that can be used. `MPI_ANY_SOURCE` instead of a precise id for the source of the message indicates you are ready to receive a message from any source. `MPI_ANY_TAG` has the same meaning, but for any tag.

Finally, the `count` parameter represents the **maximum** number of elements you are expecting to receive in the communication. The actual number received can thus be less or equal. If you receive more elements, an error will be triggered.

Let's now see a few example calls to `MPI_Recv` :


**Receiving an integer from process 5 with tag 0 :**

```cpp
int value;
MPI_Recv(&value, 1, MPI_INT, 5, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
```

**Receiving a table of 10 integer from process 3 with no tag :**

```cpp
int values[10];
MPI_Recv(&values, 10, MPI_INT, 3, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
```

**Receiving a table of 3 doubles from any process with any tag :**

```cpp
double values[3];
MPI_Recv(&values, 3, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
```

## A note on tags :

It is always tempting to go the easy way and always use `MPI_ANY_TAG` or just a tag 0 for all your messages. But as your application grows more and more complex, having specific tags for every type of communication helps you debug, ensure the synchronisations are done correctly, and gives more semantics to your code. Do hesitate to use constants to give more meaning to your tags.

@[P2P part 1]({"stubs": ["02_p2p_1/p2p_1.cpp"], "command": "bash 02_p2p_1/p2p_1.sh", "layout": "aside"})

