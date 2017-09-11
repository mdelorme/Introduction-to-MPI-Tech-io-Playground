## The rest of MPI

This course is approaching its end now. Before we finish, let's have a peek at what we have been missing in this course that might be of certain interest to you :

### MPI-1 :

What we have seen here comes from the MPI-1 norm. As stated in the introduction, the current norm is MPI-3, and there are a lot of features that have been introduced since MPI-1. Let's see a few things that we missed in the MPI-1 norm. You will find, as usual, a lot more information about these in the [official norm document](http://mpi-forum.org/docs/mpi-1.3/mpi-report-1.3-2008-05-30.pdf) :

 * It is possible to cancel a pending communication, via `MPI_Cancel`
 * It is possible to combine a send and a receive in a single call using `MPI_Sendrecv`
 * When specifying a destination process in a send or a receive, you can use the wildcard `MPI_PROC_NULL` as destination or sender to ignore the call. That's very convenient when dealing with whole domains sends and boundary conditions
 * There are a lot of other functions you can call to define your own derived datatypes. For instance `MPI_Type_vector` and `MPI_Type_indexed` are two very useful functions.
 * You can use `MPI_Alltoall` to combine scatter and gather at the same time, distributing portion of all processes elements to all other processes.
 * It is possible to create custom reduction operations using `MPI_Op_create`.
 * There are a lot of different ways of creating communicators aside from splitting. It is, for instance, possible to create groups and convert them to communicators.
 * It is possible to map processes rank to custom topologies. Either in a cartesian fashion (for instance, mapping all processes ranks to a 2d grid) or in a more complex fashion (following any sort of graph).
 * It is also possible to create inter-communicators, specific communicators that will discuss between intra-communicators. That means having communicators not resting on one single group of processes.
 * When creating communicators, it is possible to attach to them attributes (under the form of a pair key/value). This way you can store information that is not relevant to a single process but the group of processes contained in the communicator.

### MPI-2 and MPI-3 :

The MPI-2 and 3 norms introduce more functionalities. Most of them are too advanced to be of any benefit in this course, but might be of interest when you make progress in your learning of MPI. To give you an idea of the amount of data we are dealing with, the MPI-1.3 official norm pdf is roughly 250 pages long and was approved in 2008. Four years later, the MPI-3 standard is 850 pages long. Of course this difference is not explained solely by the addition of features. Lots of parts in the specification have been made clearer and more precise. Also there are more information on the language bindings and the features that have been deprecated since the developement of MPI-1.

Although this might be subject to debate, we feel the principal new features in MPI-2 and 3 are the management of parallel IOs and the introduction of one-sided communications.

**Parallel IOs** allow you to make use of parallel file-systems as well as defining data-types so that different processes can access the same file in memory without having to reparse everything manually. We will not go more into detail here, this might be the subject of a future course on more advanced topic in MPI.

**One-sided communications** are a new type that allows communications to be made in a highly asynchronous way by defining windows of memory where every process can write and or read from. All of these revolve around the idea of **Remote Memory Access** (RMA). Traditional p2p or collective communications basically work in two-steps : first the data is transferred from the original(s) process(es) to the destination(s). The the sending and receiving processes are synchronised in some way (be it blocking synchronisation or by calling `MPI_Wait`). RMA allows us to decouple these two steps. One of the biggest implications of this, is the possibility to define shared-memory that will be used by many processes (cf `MPI_Win_allocate_shared`). Although shared-memory might seem out of the scope of MPI which was initially made for distributed memory, it makes sense to include such functionalities to allow processes sharing the same [NUMA](https://en.wikipedia.org/wiki/Non-uniform_memory_access) nodes for instance. All of these functionalities are grouped under the name of "One-sided communications", since they imply you don't need to have more than one process to store or load information in a shared-memory buffer. You can find a good example on [Intel's website](https://software.intel.com/sites/default/files/managed/eb/54/An_Introduction_to_MPI-3.pdf).


