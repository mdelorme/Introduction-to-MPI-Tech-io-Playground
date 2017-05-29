# Introduction

**Message Passing Interface** (MPI) is a standardized message-passing  library interface specification. A mouthful to say that MPI is a very abstract description on how messages can be exchanged between different processes. MPI is only a standard. That means that, as for C++, the standard is a completely abstract list of features and concepts that will be **implemented**. And as for C++ with g++/clang and icpc, MPI has multiple implementations. The two principal are OpenMPI, an open-source implementation and MPICH from which derives all the high competitive implementations for supercomputers (such as Intel MPI, Bull MPI, Cray MPI). In this course, we will use the OpenMPI implementation. But regardless of the implementation, all of them follow the same standard and provide the same functionalities.

## Flynn's taxonomy

MPI is a way of making communicate processes together. There are different ways of using this. For instance, 


