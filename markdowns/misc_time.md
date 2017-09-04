## Measuring Time with MPI

In many cases, taking the time to develop a parallel application with MPI implicitly means that you want to increase your performances (that is not the only reason to use MPI, another one being to distribute a huge dataset on many machines that could not hold it in entirely on one node). Assessing the performance of a program, when dealing with parallel applications is usually what we call measuring the scalability of the program (does the program scales well with the number of processes ?). Scalability is out of the scope here so we won't go too much into details here, but what you have to remember as a general principle is that if you want to measure scalability, you will have to know how long your program, or certain sections of it, run for.

For that, you will have to use chronometers. There are a lot of ways to measure time in computer science, but as a general rule of thumb, you should always use a clock that measures the [Elapsed real time](https://en.wikipedia.org/wiki/Elapsed_real_time) or **wall time**. Fortunately, all MPI implementations provide you with such a clock : `MPI_Wtime`. As a matter of fact, you might remember that we have been using this function a few lessons back when trying to measure the difference between blocking and non-blocking communications !

`MPI_Wtime` is a really simple function, so there will be no exercise with this lesson. Calling it returns a double storing the time in seconds since an arbitrary point in the past. So, if you want to measure the time between two points of your code, you should do something like :

```cpp
double start = MPI_Wtime();

// Do something here

double end = MPI_Wtime();

std::cout << "The process took " << end - start << " seconds to run." << std::endl;
```

As sometimes, your code will be consisting of lots of loops and you might want to measure only the time spend in some very specific parts of these loops, you can also implement a time counter based on `MPI_Wtime` :

```cpp
double counter = 0.0;

for (int i=0; i < N; ++i) {
  for (int j=0; j < M; ++j) {
    // Do something that we don't want to measure

    // Subtract the current time value to the counter
    counter -= MPI_Wtime()

    // Do something that we want to measure

    // Add the current time value to the counter -> Only the elapsed time will be stored
    counter += MPI_Wtime()
  }
}

std::cout << "Measured work took " << counter << " seconds to run." << std::endl;
```



