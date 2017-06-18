# Collective communications

We have learnt how to send a message from a specific process to another specific process. But sometimes, the applications require more global solutions. Let's take an obvious example. Let's imagine we have 10 different processes. Process 0 has an information to dispatch to every other processes. With what we just learnt, the way we would do this would be something like :

@[Collective example 1]({"stubs": ["examples/p5_1/bcast_p2p.cpp"], "command": "bash examples/p5_1/p5_1.sh"})

If you run this code, you will see that the buffer has been dispatched to every process.

Now this might seem acceptable if you don't know about collective communications, but there is a proper, easier and more straightforward way of doing this :

@[Collective example 2]({"stubs": ["examples/p5_2/bcast_collective.cpp"], "command": "bash examples/p5_2/p5_2.sh"})

This does the exact same thing, but as you can see, there is only one simpler call to a MPI function.