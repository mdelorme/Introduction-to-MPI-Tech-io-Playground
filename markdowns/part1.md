# MPI

**Message Passing Interface** (MPI) is a standardized message-passing  library interface specification. A mouthful to say that MPI is a very abstract description on how messages can be exchanged between different processes. MPI is only a standard. That means that, as for C++, the standard is a completely abstract list of features and concepts that will be **implemented**. And as for C++ with g++/clang and icpc, MPI has multiple implementations. The two principal are OpenMPI, an open-source implementation and MPICH from which derives all the high competitive implementations for supercomputers (such as Intel MPI, Bull MPI, Cray MPI). In this course, we will use the OpenMPI implementation. But regardless of the implementation, all of them follow the same standard and provide the same functionalities.

## Why should I care about MPI ?

MPI is good at a few things that could interest any computer scientist. Since MPI handles the passing of messages between different processes, it is usually good for parallelism and high performance computing. In a very straightforward approach you can parallelise a code to do SIMD parallelism : Single Instruction, Multiple Data. That means all of your process will be applying the same treatment on a big pool of data that will be distributed among them. But since MPI does not force you to launch only one program, it is also very convenient when trying to do MIMD parallelism : Multiple Instruction, Multiple Data. A very common example of these kind of programs are consumer/producers programs where the producer creates information for the consumers to treat.

Where MPI really shines is for distributed computing. MPI has become since the early 90's the most used standard for message passing between different nodes on connected architectures. This proves to be invaluable in scientific computing for instance, where numerical simulation often requires hundreds to thousands of interconnected nodes to have sufficient memory. This holds for any application using multiple interconnected computers such as rendering farms. 

![The French supercomputer Curie](img/curie.png "The French supercomputer Curie")
*The French supercomputer Curie. Supercomputers are heavy users of MPI programs*

When talking about parallelisation it is interesting to note that the actual programs using MPI can still use other means of parallelism. As such, there is nothing preventing a user to combine MPI with GPU parallelism, vectorisation or shared-memory parallelism (such as OpenMP).

## Which version of the standard ?

MPI in its first version is really simple and straightforward. With the advance of high performance computing, new versions of MPI have been released (MPI-2 and 3) including more and more possibilities such as Parallel I/Os, dynamic process management or shared-memory operations. This tutorial will primarily focus on the basics of MPI-1 : Communicators, point-to-point and collective communications, and custom datatypes.

The whole tutorial is designed as a hands on session where we will see concepts and will use them at the same time. We won't go too much into the details of the standard or the implementations, but mostly on the big picture, the concepts to know and to use to design your first distributed program.






