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

### Emission :

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

### Reception :

The function to call to receive data from a process is very similar from the one to send but has an additional parameter :

```cpp
int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
```

As you can see, there is an additional `status` parameter. The `MPI_Status` is a struct that you can access if necessary to have more information on the message you just received :

```cpp
struct MPI_Struct {
  int MPI_SOURCE;
  int MPI_TAG;
  int MPI_ERROR;
  int _cancelled;
  size_t _ucount;
};
```

`MPI_SOURCE` indicates where the message comes from, `MPI_TAG` the tag of the message, and `MPI_ERROR` if an error has occured during the reception of the message. The two last attributes are not supposed to be used, or, as the OpenMPI developers put it in the source code :

```cpp
/* The following two fields are internal to the Open MPI
       implementation and should not be accessed by MPI applications.
       They are subject to change at any time.  These are not the
       droids you're looking for. */
```

Now you might wonder why we would need the source and the tag when we already know it, since we have to specify these values in the `MPI_Recv` call. Well in fact, there are two wildcards you are allowed to use when calling `MPI_Recv` : `MPI_ANY_SOURCE` and `MPI_ANY_TAG`. These allow the incoming messages to be of any source or any tag when specified.

You might not want to use the information provided by `MPI_Status`. In this case you can replace the status parameter by `MPI_STATUS_IGNORE` in which case no information will be retrieved.

Let's see a few example calls to `MPI_Recv` :


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

**Receiving a table of 5 doubles from process 1, 2 or 3 with tag 4:**

```cpp
double values[5];
MPI_Status status;
MPI_Recv(&values, 5, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, &status);
std::cout << "Received from process " << status.MPI_SOURCE
          << "; with tag " << status.MPI_TAG << std::endl;
```




