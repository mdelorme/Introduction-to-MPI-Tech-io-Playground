# Collective communications

We have learnt how to send a message from a specific process to another specific process. But sometimes, the applications require more global solutions. Let's take an obvious example. Let's imagine we have 10 different processes. Process 0 has an information to dispatch to every other processes. With what we just learnt, the way we would do this would be something like :

@[Collective example 1]({"stubs": ["examples/p5_1/bcast_p2p.cpp"], "command": "bash examples/p5_1/p5_1.sh"})

If you run this code, you will see that the buffer has been dispatched to every process.

Now this might seem acceptable if you don't know about collective communications, but there is a proper, easier and more straightforward way of doing this :

@[Collective example 2]({"stubs": ["examples/p5_2/bcast_collective.cpp"], "command": "bash examples/p5_2/p5_2.sh"})

This does the exact same thing, but as you can see, there is only one simpler call to a MPI function.

## Types of collective communications

Collective communications allow us to exchange more easily information across all processes (of a communicator). But collective communications are not only useful for this, there are different types of collective communications suited for very different objectives. Let's review the ones we are going to see in this tutorial :

* **Broadcast** : One process sends a message to every other process
* **Reduction** : One process gets data from all the other processes and applies an operation on it (sum, minimum, maximum, etc.)
* **Scatter** : A single process partitions the data to send pieces to every other process
* **Gather**  : A single process assembles the data from different process in a buffer
* **All to all** : Every process sends data to every other process.

In the next lessons, we are going to see more deeply each of these types of collective communications and examples of how to use them in applications.