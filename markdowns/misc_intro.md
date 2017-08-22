# Additional features

Until now we have seen all the basic commands to communicate between process grouped on `MPI_COMM_WORLD`. This last chapter treats of additional topics that would not fit in a proper chapter by themselves. The choice to put all these topic here is entirely subjective and could be considered arbitrary. Now as this course aims at giving you a first taste of MPI and the right tools to be able to develop a complete program from scratch and understanding the basic mechanisms of MPI, it felt less necessary to have an in-depth covering of communicators or custom-types. This is why they are quickly covered in this section. Further explanation of these topics might be the subject of a future advanced MPI-course.

This section will cover three topics :

* Communicator splitting
* Time measurement
* Custom type definition

The section ends with a list of interesting features of MPI that we have not covered in this course.



## Communicators

As you might remember from the introduction, it is possible to create your own communicators in MPI. That's what we are going to see in this chapter. Now communicators are a complex subject in MPI and the standard documentation of MPI dedicates a full chapter to them and to related concepts, so bear in mind that we will only be scratching the surface of a very complex and advanced topic.

In this course, we will only see the basics of custom communicators, mainly what they are and how to create them. We will also see what topologies are and how we can benefit from them.

### Definitions

There are a lot of levels of subtlety in communicators in MPI and if you are interested in the full detail, I would advise you to read the specifications in the [standard](http://mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf). Without entering too much into details, here are a few terms that are needed to understand what communicators are :

* **Group** : A group is an ordered collection of process. These processes are ordered via their **rank**.
* **Context** : A context can be seen as a tag that provides a safe-space for communication. This "tag" labels the communication and links it to its context, providing additional semantics.
* **Intra-communicator** : An intra-communicator is the reunion of a group and a context. Until now, we have been using `MPI_COMM_WORLD` as a communicator : it actually is an intra-communicator.

Now you understand that a communicator limits its communications to a specific group of processes but not only : if you have two communicators on the same group, their context will be different and the messages that will be sent will be virtually separated from each other.

Aside from intra-communicators we can also define the notion of **inter-communicators** that allow to pass message between two non-overlapping groups. An inter-communicator is the reunion of TWO groups and a context.

Finally, there is one last concept that we need to define : a **topology** is a way to provide a mapping between a specified disposition of processes and their actual ranks. The most classical example is the cartesian topology where instead of addressing a process by its rank we will address it by a coordinate in a grid. We will see more about topology in a short while !

### What's useful in all of this ?

In the following lessons, we won't be talking anymore about inter-communicators. These communicators can be important, but they don't belong in an introduction course. If you are really interested in reading about them, you will find more information in the MPI standard, as well as a brief example [here](http://mpi-forum.org/docs/mpi-1.1/mpi-11-html/node114.html).

As for the rest, we will now be vague and get back to calling intra-communicators by simply communicators. Please bear in mind though that everytime there is a mention to a communicator in MPI, it can be either intra or inter communicators.

This chapter will be pretty short. In the next lesson we will see how to split a communicators followed by an exercise. Then, in the following lesson we will learn a more general way of creating communicators.

### But why would I want to use other communicators?

That a totally legitimate question to ask and there are multiple answers to that but the most straightforward one has to do with what is called [Flynn's taxonomy](https://en.wikipedia.org/wiki/Flynn%27s_taxonomy). Under this very simple taxonomy, you can divide any program in four categories.

Sequential (non-parallel) programs are usually **SISD** programs : Single Instruction, Single Data. Note that, SISD is never used anywhere, the term sequential is preferred.

Until now most of what we have been aiming for in the parallel course is what we call **SIMD** : Single Instruction Multiple Data. Basically, we have a bunch of data and we want to apply the same treatment to all of them.

**MISD** means Multiple Instruction, Single Data. It basically means that you have different programs exploiting the same set of data. These programs can be parallelised in which case you will have a dedicated communicator for each program, and then a communicator between the two processes.

The final paradigm : **MIMD** for Multiple Instruction, Multiple Data is exactly the same as MISD but on top of that, the different programs will be working on different sets of data.

