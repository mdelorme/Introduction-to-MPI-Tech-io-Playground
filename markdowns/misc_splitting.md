## Communicator splitting

As you might remember from the introduction, it is possible to create your own communicators in MPI and use them instead of `MPI_COMM_WORLD`. That's what we are going to see in this lesson. Communicators are a complex subject in MPI and the standard documentation of MPI dedicates a full chapter to them and to related concepts so bear in mind that we will only be scratching the surface of a very broad and advanced topic. Here, we will limit ourselves at the most straightforward way of creating a new communicator : splitting.

### Definitions

There are a lot of levels of subtlety in communicators in MPI and if you are interested in the full detail, I would advise you to read the specifications in the [standard](http://mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf). Without entering too much into details, here are a few terms that are needed to understand what communicators are :

* **Group** : A group is an ordered collection of process. These processes are ordered via their **rank**.
* **Context** : A context can be seen as a tag that provides a safe-space for communication. This "tag" labels the communication and links it to its context, providing additional semantics.
* **Intra-communicator** : An intra-communicator is the reunion of a group and a context. Until now, we have been using `MPI_COMM_WORLD` as a communicator : it actually is an intra-communicator.

Now you understand that a communicator limits its communications to a specific group of processes but not only : if you have two communicators on the same group, their context will be different and the messages that will be sent will be virtually separated from each other.

Aside from intra-communicators we can also define the notion of **inter-communicators** that allow to pass message between two non-overlapping groups. An inter-communicator is the reunion of TWO groups and a context.

Finally, there is one last concept that we need to define although we won't really need it here : a **topology** is a way to provide a mapping between a specified disposition of processes and their actual ranks. The most classical example is the cartesian topology where instead of addressing a process by its rank we will address it by a coordinate in a grid. Thge topology can be *virtual* (mapping the processes ranks in some custom way) or *physical* (mapping the processes ranks so they correspond to the actual core organization on the machine).

### What's useful in all of this ?

In the following examples, we won't be talking anymore about inter-communicators. These communicators can be important, but they don't belong in an introduction course. If you are really interested in reading about them, you will find more information in the MPI standard, as well as a brief example [here](http://mpi-forum.org/docs/mpi-1.1/mpi-11-html/node114.html).

As for the rest, we will now be vague and get back to calling intra-communicators by simply communicators. Please bear in mind though that everytime there is a mention to a communicator in MPI, it can be either intra or inter communicators.

### But why would I want to use other communicators?

That a totally legitimate question to ask and there are multiple answers to that but the most straightforward one has to do with what is called [Flynn's taxonomy](https://en.wikipedia.org/wiki/Flynn%27s_taxonomy). Under this very simple taxonomy, you can divide any program in four categories.

Sequential (non-parallel) programs are usually **SISD** programs : Single Instruction, Single Data. Note that, SISD is never used anywhere, the term sequential is preferred.

Until now most of what we have been aiming for in the parallel course is what we call **SIMD** : Single Instruction Multiple Data. Basically, we have a bunch of data and we want to apply the same treatment to all of them.

**MISD** means Multiple Instruction, Single Data. It basically means that you have different programs exploiting the same set of data. These programs can be parallelised in which case you will have a dedicated communicator for each program, and then a communicator between the two processes.

The final paradigm : **MIMD** for Multiple Instruction, Multiple Data is exactly the same as MISD but on top of that, the different programs will be working on different sets of data.


## Communicators creation

There are various ways of creating new communicators in MPI. A new communicator is always created from another so every communicator derives from `MPI_COMM_WORLD`. There are two easy ways of doing things : either you create a new group and derive a communicator from it, or you **split** an existing communicators into sub-communicators. In this lesson, we are going to explore the latest.

### Communicator splitting

To explain splitting, let's take an example. Consider we have a program with 8 processes. At the beginning, all of these processes are grouped inside `MPI_COMM_WORLD`.

![Comm splitting, part 1](/img/splitting_p1.png)

Now, let's imagine that we want to make two new communicators. One will group processes 0, 1, 2 and 3. The other will group processes 4, 5 and 6. Process 7 will stay only be in `MPI_COMM_WORLD`. Now assigning a process to another communicator does not mean that the process leaves the original communicator. So all these processes will stay in `MPI_COMM_WORLD`.

Splitting is the action of taking an existing communicator and distributing all of its processes to new communicators. The way we do it is by assigning every process a number that will tell in which communicator it will end after the splitting. That number is called a **colour**.

![Comm splitting, part2](/img/splitting_p2.png)

As you can see, we assign processes 0, 1, 2 and 3 the color 0, and the color 1 to processes 4, 5 and 6. Process 7 has no colour. There is a way in MPI to indicate that you don't want the process to be placed in any new communicator. Then, we act the splitting, and create the new communicators.

![Comm splitting, part3](/img/splitting_p3.png)

Now the processes 0 to 6 are belonging to two communicators. Processes 0, 1, 2 and 3 are in `MPI_COMM_WORLD` and in `CUSTOM_COMM1` while processes 4, 5 and 6 in `MPI_COMM_WORLD` and `CUSTOM_COMM2`. A very important thing to understand is that every communicator has its own size. Thus the size of `MPI_COMM_WORLD` is 8, the size of `CUSTOM_COMM1` is 4 and the one of `CUSTOM_COMM2` is 3.

Also note that, as stated in the introduction, the rank of a process in a communicator will always start from 0. Thus, process 0 in `MPI_COMM_WORLD` is still process 0 in `COMM_CUSTOM1`, but also process 4 in `MPI_COMM_WORLD` is process 0 in `COMM_CUSTOM2`. Bear in mind that the rank of a process only has a meaning with respect to a specific communicator.

The ordering of the processes in the communicator can also be defined when we split, but we will see this during the next exercise.

One last thing before practicing : nothing prevents you to create subsequent communicators. After doing this first split, you can do another split, either on `MPI_COMM_WORLD`, on `CUSTOM_COMM1` or on `CUSTOM_COMM2`. Let's imagine that now we want to create a third custom communicator `CUSTOM_COMM3` grouping processes 0 and 4 of `MPI_COMM_WORLD`. Then we can split `MPI_COMM_WORLD` again, and create that new communicator.

![Comm splitting, part4](/img/splitting_p4.png)