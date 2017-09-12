# Introduction to distributed computing with MPI

**Message Passing Interface** (MPI) is a standardized message-passing  library interface specification. A mouthful to say that MPI is a very abstract description on how messages can be exchanged between different processes. MPI is only a standard. That means that, as for C++, the standard is a completely abstract list of features and concepts that will be **implemented**. And as for C++ with g++/clang and icpc, MPI has multiple implementations. The two principal are OpenMPI, an open-source implementation and MPICH from which derives all the high competitive implementations for supercomputers (such as Intel MPI, Bull MPI, Cray MPI). In this course, we will use the OpenMPI implementation. But regardless of the implementation, all of them follow the same standard and provide the same functionalities.

## Why should I care about MPI ?

MPI is good at a few things that could interest any computer scientist. Since MPI handles the passing of messages between different processes, it is usually good for parallelism and high performance computing. In a very straightforward approach you can parallelise a code to do SIMD parallelism : Single Instruction, Multiple Data. That means all of your process will be applying the same treatment on a big pool of data that will be distributed among them. But since MPI does not force you to launch only one program, it is also very convenient when trying to do MIMD parallelism : Multiple Instruction, Multiple Data. A very common example of these kind of programs are consumer/producers programs where the producer creates information for the consumers to treat.

## Distributed computing

Where MPI really shines is for distributed computing. MPI has become since the early 90's the most used standard for message passing between different nodes on connected architectures. This proves to be invaluable in scientific computing for instance, where numerical simulation often requires hundreds to thousands of interconnected nodes to have sufficient memory. This holds for any application using multiple interconnected computers such as rendering farms.

Let's take a very simple example to explain why distributed computing might be necessary in scientific simulations. If you try to simulate the way stars move in a galaxy (and only stars), you will have to compute the movement of 100 billion particles. If you imagine that you will need sufficient precision for these stars and that all values will be stored as doubles, then every single value for a star will weight around 8 bytes. How many values do we need to store per star ? 3 doubles for position, 3 doubles for velocity, 1 double for the mass, and possibly more for other properties. So, at least 7 doubles per star, which amounts to roughly 5 terabytes of data. And that's just for stars, but usually such simulations will also incorporate other types of particles, grids for fluid dynamics, etc. The total is usually tremendous and so, if you want to have realistic simulations of what is happening in such a system, you definitely can't use a single computer : you need distributed memory so that all of this data is partitioned and sent to different nodes, each with a reasonable amount of memory to treat it.  

![The French supercomputer Curie](/img/curie.png "The French supercomputer Curie")
*The French supercomputer Curie. Supercomputers like this one are heavy users of MPI programs. Distributed computing is necessary when you have to run a simulation using multiple terabytes of memory on thousands of CPUs*

When talking about parallelisation it is interesting to note that the actual programs using MPI can still use other means of parallelism. As such, there is nothing preventing a user to combine MPI with GPU parallelism, vectorisation or shared-memory parallelism (such as OpenMP).

## Which version of MPI ?

MPI in its first version is really simple and straightforward. With the advance of high performance computing, new versions of MPI have been released (MPI-2 and 3) including more and more possibilities such as Parallel I/Os, dynamic process management or shared-memory operations. This tutorial will primarily focus on the basics of MPI-1 : Communicators, point-to-point and collective communications, and custom datatypes.

If you choose to try MPI on your computer, the latest versions of OpenMPI (version 2.1.1 as this tutorial is written) are fully MPI-3 compliant. So everything you read on the net on the standard should be doable in such a version.

## What will I learn ?

The whole tutorial is designed as a hands on session where we will see concepts and will use them at the same time. We won't go too much into the details of the standard or the implementations, but mostly on the big picture, the concepts to know and to use to design your first distributed program.

The next lessons will be dedicated on simple initialisation and blocking point-to-point communications. After that, we will see collective communications, non-blocking point-to-point operations and finally how to create communicators and derived datatypes.

## What are the requirements ?

It is recommended that you already know a bit of C/C++. The examples will be given in C++ and the exercises will be compiled with g++ so that you can use C or C++. It is necessary that you know basic C/C++ syntax such as control and conditional statements, how to print on stdout. It is also necessary that you understand the basics of memory management in C/C++. MPI being a library heavily manipulating data in memory and transfering buffers, it is better to understand what pointers are and how to manipulate them to complete the course.

Please note that C and C++ are not the only languages that can be used to do distributed computing with MPI. Most notably, every MPI implementation is also compatible with Fortran. On top of that, lots of interpreted languages have libraries allowing their developers to use mpi in an indirect way. For instance, Python users can use the library mpi4py.

## Can I use MPI on my local computer ?

Yes, it is possible. You need to install an implementation of MPI. If you are using Linux or MacOS, then the simplest way to get an implementation of MPI is to install the latest packages of OpenMPI. If you are using Windows, you can use Cygwin to use OpenMPI or you can install MS-MPI, the Microsoft version. This tutorial is based on OpenMPI, but this should not make any noticeable difference in the commands.

## Contribute to the course !

This course is an eternal work in progress. The choice of topics and the angle they are attacked from is a completely subjective choice and might be subject to discussion. It is my understanding that we should all collaborate to make these kind of resources better, so if you have any comment, suggestion, addition to make to the course, feel free to contact me or even better, to fork the [github](https://github.com/mdelorme/Introduction-to-MPI-Tech-io-Playground) repo and make your pull requests :)

## References

There are a few references that are good to always have bookmarked when dealing with MPI.
* First of all, the latest reference of the [MPI standard](http://mpi-forum.org/docs/). It is huge and hard to read but indispensible if you want to understand what lies beyond the surface of the API (a lot of things which will not be covered here).

* Another necessary tool is the API reference of your implementation. Here's [OpenMPI's](https://www.open-mpi.org/doc/current/) and [MPICH's](https://www.mpich.org/static/docs/v3.1/www3/) (MS-MPI is based on MPICH, so this will be the API documentation for Windows users). These API references are usually ... pretty coarse to say the least, but provide every function signature as well as some additional information.

* The [MPI Tutorial](http://mpitutorial.com) website is the starting point of many MPI developers. It is extremely useful and provides lots of very clear examples for everything MPI-1 related. This tutorial only aims at reaching such a level of pedagogical information. To be completely honest, this tutorial would not exist if MPI Tutorial was an interactive website such as tech.io.

* [MPIP2P](https://cvw.cac.cornell.edu/MPIP2P/), a tutorial part of the Cornell Virtual Workshop. It explains very well all the subtleties behind Point-to-Point communications and has very good diagrams, especially for the communication modes.

With these resources and this interactive course, you should be ready to take on the world of distributed computing !
