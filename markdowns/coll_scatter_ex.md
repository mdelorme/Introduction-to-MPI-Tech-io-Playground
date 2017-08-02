# Scattering and Gathering - exercise

We have now enough knowledge about MPI to start doing some funky code. For this exercise, you will help parallelise a code that computes Mandelbrot sets.

## Mandelbrot sets

Mandelbrot sets are very famous examples of fractal sets. It is not necessary to understand perfectly the principle to compute these but if you are interested, you can find more information on the [wikipedia page](https://en.wikipedia.org/wiki/Mandelbrot_set) (as usual).

The general algorithm is the following :

```
For every complex point c in an image
  z = 0
  iteration = 0
  while iteration < max_iterations
    z = z * z + c
    if modulus(z) > 2.0
      break

    iteration += 1

  if iteration == max_iteration
    value[c] = -1
  else
    value[c] = iteration
```

Once we have computed this for every point, we plot, for each couple (x,y) the value corresponding to the complex point c = x + iy. This value is colour-scaled so -1 = dark blue and max_iteration = bright red. 

If we take every point on $`x \in [-2.0, 1.0]`$ and $`y \in [-1.5, 1.5]`$ and `max_iteration=50`, we get the following image :

![Mandelbrot set](/img/mandelbrot.png "The whole Mandelbrot set")

## Statement

The exercise here is going to be a bit more difficult that usual because you will have to adapt a program that runs on one process, to a program that runs with any number of process. The goal is to adapt the program (not completely change it) so it can benefit from distributed computing. For this, you will have to call two collective communications and tranform bits and pieces of the code. The two collective communications will be :

* A scatter to distribute the set of points to every process so that only a fraction is treated by every process
* A gather that will regroup all the final data on one process.

Now, since the exercise might be a bit tedious, here are a few hints :

* You should allocate and initialise the array `points` only on one process and then distribute these values to the other processes.
* Don't forget that, as for reduction, scattering and gathering cannot be done in the same buffers. So you will have to add a buffer for reception of the points, and a buffer for the reception of the results.
* Verify that, in the end, you print all the values and not only the subset of process #0.
* The code works by default on one process, so you can run it to see what the result should be, before starting the modifications.

## Scattering and Gathering

Let's talk about the two operations. You can scatter by calling `MPI_Scatter` which prototype is :

```cpp
int MPI_Scatter(void *sendbuf, int sendcount, MPI_Datatype sendtype,
                void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
                MPI_Comm comm);
```

A handful of parameters ! You see that we can divides these in three groups : the ones for sending, the ones for receiving, and the global parameters of the communication. There is a lot of redundancy here, so bear with me :

* `sendbuf` is the buffer that ONE process will dispatch to all the other processes
* `sendcount` is the number of elements the process will send to ONE other process
* `sendtype` is the type of the data to be sent
* `recvbuf` is the buffer where every process will receive their slice of the cake
* `recvcount` is the number of elements the process will receive
* `recvtype` is the type of the data to be received
* `root` is the rank of the process that will be sending its data
* `comm` is the communicator on which the communication will be done

Now, it seems that `sendcount` and `recvcount` are the same thing. The same can be said for `sendtype` and `recvtype`. Actually it is a bit more complicated. I have already mentioned in the past lessons that in MPI, it is possible to define your own datatypes. Then, it can be sensible for your application to send a certain datatype, and receive another. The data won't change but the way you store them on the receiving end might. Note that, this exercise would be an ideal case to try out defining custom datatypes (for complex numbers), but we won't be doing this now.

The gathering will be done calling `MPI_Gather`, which has a very similar prototype :

```cpp
int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
               void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
               MPI_Comm comm);
```

No need to explain again the meaning of the parameters, they should all be obvious now !

Note that both of these function exist in non-blocking flavours with `MPI_Iscatter` and `MPI_Igather`. As for the others, they must be followed by `MPI_Test` and `MPI_Wait`. You can find their proper prototypes [here](https://www.open-mpi.org/doc/v1.8/man3/MPI_Gather.3.php) and [here](https://www.open-mpi.org/doc/v1.8/man3/MPI_Gather.3.php).

Another useful thing to know about gathering : you might need to gather the data and then broadcast it to every process so that each of them has a copy of all the data. This can be done in one step using the function `MPI_Allgather`. You will find more information on this function [here](https://www.open-mpi.org/doc/v1.10/man3/MPI_Allgather.3.php)

Finally, there is two additional versions of these functions : `MPI_Scatterv` and `MPI_Gatherv`. Without entering in too much data, these functions are used to scatter and gather the data when all the process do not hold the same quantities of data. If you feel like process 2 should have less data than process 0 and 1 but still want to use a scatter function, these are the functions you need to use. You will find more information on these [here](https://www.open-mpi.org/doc/current/man3/MPI_Scatterv.3.php) and [here](https://www.open-mpi.org/doc/v1.10/man3/MPI_Gatherv.3.php).

## The exercise

Well, now you know what to do ! So go ahead and make this program parallel !

@[Mandelbrot sets]({"stubs": ["coll_scatter_ex/mandelbrot.cpp"], "command": "bash coll_scatter_ex/mandelbrot.sh", "layout": "aside"})

