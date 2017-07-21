# Probing information - exercise

In this exercise, we are going to use the probing mechanism to find out which process with which tag are trying to communicate pwith process 0. Your goal will be to handle process 0, the rest of the program will be hidden so you have no way of knowing which process is communicating what.

For this, you will need to use the `MPI_Probe` function, whose prototype is :

```cpp
int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status);
```

Remember that `source` (resp. `tag`) can be `MPI_ANY_SOURCE` (resp. `MPI_ANY_TAG`). The tag and source will be stored in the `status` variable.

## Exercise

You must fill in the function so that the process receives a message from any process. Then writes to stdout `Received a message from process ## with tag ##`. Then, if tag is 0, receive the message as a single integer and add it to `int_sum`. Else, if the tag is 1, receive the message as a single float and add it to the `float_sum` variable.

@[Probing]({"stubs": ["p2p_probing_ex/probing.cpp"], "command": "bash p2p_probing_ex/probing.sh", "layout": "aside"})