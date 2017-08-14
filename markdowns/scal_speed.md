# Measuring execution speed

To be able to indicate how well a program performs, we need to find a way to measure the elapsed time computing. You might recall that we used a function to do this in a [previous lesson](/markdowns/p2p_non_blocking.md) : `MPI_Wtime`.

`MPI_Wtime` is a function that returns the time elapsed since an arbitrary point in the past. Of course, in case you were wondering, this arbitrary point in the past is the same for all calls to `MPI_Wtime` in the program. This method is not the only available method to measure time. However, it is strongly advised that you use `MPI_Wtime` when using MPI.

