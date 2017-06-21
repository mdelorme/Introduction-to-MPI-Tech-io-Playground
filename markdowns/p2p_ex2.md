# Non-blocking communications - exercise

Now it is time to dig deeper in non-blocking communications and try to code our first version of the algorithm presented in last section. Let's see again this algorithm for both processes :

```
if rank == 0 then
  Work for 3 seconds
  Initialise the send to process 1
  Work for 6 seconds
    Every milli-second, test if process 1 is ready to communicate
  Send the second batch of data to process 1
  Wait for process 1 to receive the data
else if rank == 1 then
  Work for 5 seconds
  Initialise receive from process 0
  Wait for a communication from process 0
  Work for 3 seconds
  Initialise receive from process 0
  Wait for a communication from process 0
```

Note the words we have been using in this example. For the moment, you know how to send and receive. But you don't know how to **initialise a send** **initialise a receive**, **test** or **wait**. That's what we are going to see now :

## Non-Blocking send and receive

The command when you want to send data in a non-blocking way is called `MPI_Isend` and define as :

```cpp
int MPI_Isend(void *buffer, int count, MPI_Datatype datatype, int dest, int tag, MPI_Communicator comm, MPI_Request *request);
```

Something we haven't seen before : `MPI_Request`. Unlike `MPI_Status` though, `MPI_Request` is a complex object and we won't elaborate here. See it that way : `MPI_Isend` is preparing a **request**. This request is going to be executed when both processes are ready to synchronise. This command only sets up the send, but actually does not transfer anything to the destination process, only prepares it.

Once this request has been prepared, it is necessary to complete it. There are two ways of completing a request : **wait** and **test**. But before looking at these, let's talk a vit about the non-blocking equivalent to `MPI_Recv`.

As you can already imagine, the non-blocking call to receive is the function `MPI_Irecv` :

```cpp
int MPI_Irecv(void *buffer, int count, MPI_Datatype datatype, int source, int tag, MPI_Communicator comm, MPI_Request *request);
```

As for its sending equivalent, `MPI_Irecv` returns a `MPI_Request` object. The request must then be completed by either waiting or testing.


## Waiting

Waiting forces the process to go in "blocking mode". The sending process will simply wait for the request to finish. If your process waits right after `MPI_Isend`, the send is the same as calling `MPI_Send`. There are two ways to wait `MPI_Wait` and `MPI_Waitany`.

```cpp
int MPI_Wait(MPI_Request *request, MPI_Status *status);
int MPI_Waitany(int count, MPI_Request array_of_requests[], int *index, MPI_Status *status);
```

The former, `MPI_Wait` just waits for the completion of the given request. As soon as the request is complete an instance of `MPI_Status` is returned in `status`.

The latter, `MPI_Waitany` waits for the first completed request in an array of requests to continue. As soon as a request completes, the value of `index` is set to store the index of the completed request of `array_of_requests`. The call also stores the status of the completed request.

As for the blocking communications, it is possible to replace the pointer to a `MPI_Status` instance by `MPI_STATUS_IGNORE` if you don't want to keep track of this information.

## Testing

Testing is a little bit different. As we've seen right before, waiting blocks the process until the request (or a request) is fulfilled. Testing checks if the request can be completed. If it can, the request is automatically completed and the data transferred. As for wait, there are two waits of testing : `MPI_Test` and `MPI_Testany`. They can be called as follow :

```cppp
int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status);
int MPI_Testany(int count, MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status);
```

Let's start with `MPI_Test`. As for `MPI_Wait`, the parameters `request` and `status` hold no mystery. Now remember that testing is non-blocking, so in any case the process continues execution after the call. The variable `flag` is there to tell you if the request was completed during the test or not. If `flag != 0` that means the request has been completed.

`MPI_Testany` should now be completely obvious. It sets `flag` to a non-zero value if any request is fulfillable. If so, `status` and `index` are also given a value.

## Examples

All of this is a lot of information, so here are a few examples, showing you how to use all of these calls. We consider two or three processes. The data is stored in a variable called `buffer`, defined as an array of `int` of size `buffer_count`.

**Two processes, waiting and testing on only one request**

```cpp
MPI_Request request;
MPI_Status  status;
int 	    request_complete = 0;

// Rank 0 sends, rank 1 receives
if (rank == 0) {
  MPI_Isend(buffer, buffer_count, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);

  // Here we do some work while waiting for process 1 to be ready
  while (has_work) {
    do_work();

    // We only test if the request is not already fulfilled
    if (!request_complete)
       MPI_Test(&request, &request_complete, &status);
  }

  // No more work, we wait for the request to be complete if it's not the case
  if (!request_complete)
    MPI_Wait(&request, &status);
}
else {
  MPI_IRecv(buffer, buffer_count, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);

  // Here we just wait for the message to come
  MPI_Wait(&request, &status);
}
```

**Three processes, waiting and testing on multiple requests**

```cppp
MPI_Requests request[2];
MPI_Status   status;
int          requests_left

