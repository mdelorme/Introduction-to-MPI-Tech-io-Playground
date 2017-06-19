# Point-to-point communications, the `MPI_Status` structure

You might remember that, in the previous exercise, we overlooked the `MPI_Status` value when receiving. The `MPI_Status` is a struct that you can access if necessary to have more information on the message you just received. For instance, when receiving a message with `MPI_ANY_SOURCE` or `MPI_ANY_TAG` you disregard the origin and tag of the sender. However, you might still want to get this information to post-process the data you just received. The `MPI_Status` struct is defined as followed in OpenMPI :

```cpp
struct MPI_Struct {
  int MPI_SOURCE;
  int MPI_TAG;
  int MPI_ERROR;
  int _cancelled;
  size_t _ucount;
};
```

`MPI_SOURCE` indicates where the message comes from, `MPI_TAG` the tag of the message, and `MPI_ERROR` if an error has occured during the reception of the message. The two last attributes are not supposed to be used, or, as the OpenMPI developers put it in the source code :

```cpp
/* The following two fields are internal to the Open MPI
       implementation and should not be accessed by MPI applications.
       They are subject to change at any time.  These are not the
       droids you're looking for. */
```

Here is an example of reception of 5 doubles from any process, with any tag, but using the `MPI_Status` structure to retrieve the information :

```cpp
double values[5];
MPI_Status status;
MPI_Recv(&values, 5, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, &status);
std::cout << "Received from process " << status.MPI_SOURCE
          << "; with tag " << status.MPI_TAG << std::endl;
```

We will see later in this chapter how to use the `MPI_STATUS` information to get access to more information. For instance, the status can be used to probe how many elements are/were being sent in a communication before even receiving it.

