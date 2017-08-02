# Collective communications : conclusion

We have now finished to see the basics of collective communications ! The next chapter concentrates on communicators. By now you should already be able to craft advanced MPI programs with non-blocking communications, reductions, scattering, gathering or broadcasting.

There are a few things we have not seen in terms of collective communications such as [All to all](https://www.open-mpi.org/doc/v2.0/man3/MPI_Alltoall.3.php) communications or composite operations such as Reduce-scatter operations. These operations might be the subject of a future tech-io playground on advanced MPI, but they are not really the subject of an introduction course.

But for now, let's test your knowledge of collective communications to see if you have understood everything :

?[Broadcasting is the operation that ...]
-[ ] ... splits the data on one process and send pieces to all the others.
-[X] ... sends the same message from one process to all the others.
-[ ] ... sends a message from all process to all the other processes.

?[Is it possible to do a broadcast in non-blocking mode ?]
-[X] Yes
-[ ] No

?[Why is there two different parameters to MPI_Scatter for sending count and receiving count ?]
-[ ] To allow the sending different amounts of data to different processes.
-[ ] They are a redundancy and should always be the same.
-[X] To account for different data types.

?[A reduction with MPI_PROD called on an array of 5 values over 10 processes will return]
-[X] An array of 5 values.
-[ ] A single value.
-[ ] An array of 10 values.

?[What function should be used to gather and broadcast the result to all processes ?]
-[ ] MPI_Gather
-[ ] MPI_Gatherv
-[ ] MPI_Igather
-[X] MPI_Allgather

?[Consider the code below the question. How many elements will be copied in the receiving buffer ?]
-[ ] None, this will produce an error
-[ ] 1000
-[X] 5
-[ ] 100
-[ ] 20

```cpp
int* send_buf;
int recv_buf[1000];

if (rank == 0) {
   send_buf = new int[100];
   init_send_buf(send_buf);
}

MPI_Scatter(send_buf, 5, MPI_INT, recv_buf, 5, MPI_INT, 0, MPI_COMM_WORLD);
```

