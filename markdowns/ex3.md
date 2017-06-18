The `MPI_Status` is a struct that you can access if necessary to have more information on the message you just received :

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

Now you might wonder why we would need the source and the tag when we already know it, since we have to specify these values in the `MPI_Recv` call. Well in fact, there are two wildcards you are allowed to use when calling `MPI_Recv` : `MPI_ANY_SOURCE` and `MPI_ANY_TAG`. These allow the incoming messages to be of any source or any tag when specified.

You might not want to use the information provided by `MPI_Status`. In this case you can replace the status parameter by `MPI_STATUS_IGNORE` in which case no information will be retrieved.

**Receiving a table of 5 doubles from process 1, 2 or 3 with no tag:**

```cpp
double values[5];
MPI_Status status;
MPI_Recv(&values, 5, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, &status);
std::cout << "Received from process " << status.MPI_SOURCE
          << "; with tag " << status.MPI_TAG << std::endl;
```

