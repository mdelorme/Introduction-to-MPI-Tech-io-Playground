# Point-to-point communication, part 1

In the previous exercise, we have seen how to initialise MPI, get a process' rank and the size of a communicator. But for the moment, we did not have a chance to make processes communicate, which is the whole point of MPI.

As explained in lesson 2, there are two types of communications, point-to-point (that we are going to call P2P from now on), and collective. P2P communications are divided in two operations : **Send** and **Receive**, which names are pretty self-explanatory.

The most basic forms of P2P communication are called **blocking** or **synchronous** communications. The process sending a message will be waiting until the process receiving has finished receiving all the information. This is the easiest form of communications but not necessarily the fastest as we will see in the following lessons.

## Sending messages

A send operation, sends a buffer of data of a certain type to another process. A P2P message has the following properties :

* A reference to a buffer
* A datatype
* A number of elements
* A tag
* A destination id
* A communicator

Let's go over every element one by one an detail what they are.

**A reference to a buffer**

The reference will always be a pointer to a buffer. This array will hold the data that you wish to send from the current process to another.

**A datatype**

The datatype must correspond precisely to the data stored in the buffer. For this, MPI has predefined types that can be used. Most common types and their C counterparts are :

C Type | MPI Type
-------|---------
`char` | `MPI_CHAR`
`int` | `MPI_INT`
`float` | `MPI_FLOAT`
`double` | `MPI_DOUBLE`

There are lots of other types, that you can find in the official [MPI standard documentation](http://mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf). We will see later that it is also possible to create your own custom datatypes.

**A number of elements**

This one is pretty self-explanatory. The number of elements in the buffer that you want to send to the destination.

**A tag**

The tag is a simple integer that identifies the "type" of communication. This is a completely informal value that you put yourself. We will come back on the tag in the section about reception.

**A destination id**

The rank of the process you want to send the data to.

**A communicator**

The communicator on which to send the data to. Remember that the rank of processes might change depending on the communicator you are chosing.


All these information are necessary to send a P2P message. 


## Receiving messages

The receiving of a message works in the exact same way as the send operation. However, instead of a destination id, the call will require a source id : the identification of the process from which you are waiting a message. On top of that, depending if you are using blocking or non-blocking communications, you will need additional arguments, but we will cover them in time and place. Let's have a small hands-on now.