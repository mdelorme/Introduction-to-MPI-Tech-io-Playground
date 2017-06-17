# Point-to-point communications, exercise 1

## The statement

It is time to code something a bit fancier than just printing your rank id on the screen. Let's have an actual communication between two processes. The objective of the exercise is as follows : The program will be run with two processes. You will have first to get your rank on `MPI_COMM_WORLD` and read an integer on `stdin`. Then, depending on your id, you will have to have different behaviours :

**Process #0**

* Send your integer to Process #1
* Receive the integer of Process #1
* Sum the two values
* Write the result on `stdout`.

** Process #1**

* Receive the integer of Process #0
* Send your integer to Process #0
* Subtract the two values
* Write the result on `stdout`.

Note the order of the first two operations that are inverted on the two processes ? That is so we avoid one of the most frequent problems with blocking communications : a **deadlock**. Blocking communications, are their name implies, block the processes while the communication is not finished. So if process #0 waits for process #1 to send it a message, and process #1 waits for process #0 to send it a message, both process will be blocked in an endless wait : the deadlock.

## Sending and receiving

Here are the two new functions you are going to be using for this exercise : `MPI_Send` and `MPI_Recv`.

### `MPI_Send`

You can send information to a process using the command `MPI_Send` :

```cpp
MPI_Send(void *buf, int count , MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
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

**Sending a table of doubles to process 10 with a specific tag 6:**

```cpp
double values[3] = {1e25, -0.0, M_PI};
MPI_send(values, 3, MPI_DOUBLE, 10, 6, MPI_COMM_WORLD);
```

### `MPI_Recv`


