# Custom communicators and groups

In this chapter we are going to talk about communicators. Communicators are a complex subject in MPI and the standard documentation of MPI dedicates a full chapter to them and to related concepts. In this course, we will only see the basics of custom communicators, mainly what they are and how to create them easily. We will also see a way to create a cartesian topology, which is one of the most common topologies to communicate for grid based codes.

## Definitions

There are a lot of levels of subtlety in communicators in MPI and if you are interested in the full detail, I would advise you to read the specifications in the [standard](http://mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf). Without entering too much into details, here are a few terms that are needed to understand what communicators are :

* **Group** : A group is an ordered collection of process. These process are ordered via their **rank**.
* **Context** : A context can be seen as a tag that provides a safe-space for communication. This "tag" labels the communication and links it to its context, providing additional semantics.
* **Intra-communicator** : An intra-communicator is the reunion of a group and a context. Until now, we have been using `MPI_COMM_WORLD` as a communicator. `MPI_COMM_WORLD` is an intra-communicator.

Now you understand that a communicator limits its communications to a specific group of processes. But we can also define the notion of **inter-communicators** that allow to pass message between two non-overlapping groups. An inter-communicator is the reunion of TWO groups and a context.

Finally, there is one last concept that we need to define : a **topology** is a way to provide a mapping between a specified disposition of processes and their actual ranks. The most classical example is the cartesian topology where instead of addressing a process by its rank, we will address it by a coordinate in a grid. We will see more about topology in a short while !

## What's useful in all of this ?

In the following lessons, we won't be talking anymore about inter-communicators. These communicators can be important, but they don't belong in an introduction course. If you are really interested in reading about them, you will find more information in the MPI standard, as well as a brief example [here](http://mpi-forum.org/docs/mpi-1.1/mpi-11-html/node114.html).

As for the rest, we will now be vague and get back to calling intra-communicators by simply communicators. Please bear in mind thought that, everytime there is a mention to a communicator in MPI, it can be either intra or inter communicators.

This chapter will be pretty short. In the next lesson we will see how to create and split communicators followed by an exercise. Then, in the following lesson we will learn about cartesian topologies and apply them to an exercise.



