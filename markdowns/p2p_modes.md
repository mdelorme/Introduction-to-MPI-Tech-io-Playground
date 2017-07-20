# Communication modes

We have seen almost everything important about point-to-point communication. There is one thing I have not talked about yet and that might be interesting to understand regarding MPI.

If you have experimented a bit yet, you might have remarked something awkward when doing blocking communications. Sometimes, it seems that the blocking communication is not blocking, while at other times, it seems to be. How strange.

For those of you who have not stumbled across that strange behaviour, here is a small example to convince you :

@[Blocking awkwardness]({"stubs" : ["p2p_modes/p2p_modes.cpp"], "command": "bash p2p_modes/p2p_modes.sh"})

This example shows two blocking-communication. One is performed on a small buffer (50 elements) while the second is performed on a large buffer (100000 elements). Process 0, only sends the buffers, and prints when the send has been performed as well as the time the send as taken to be completed. Process 1 is going to wait (to demonstrate the blocking properties) then receive and warn the user when the receive has been completed.

You can easily notice the awkward behaviour : the first send is completed way before the first receive, while for the large buffer, both operation seem to be happening at the same time.

The reason for that is that the first send is performed in **synchronous** mode while the second is not. There are actually four different communication modes you can trigger while communicating : **standard**, **buffered**, **synchronous** and **ready**. Each of these mode has a corresponding `Send` function (The `Recv` function will always be the same). 

The **standard** mode (`MPI_Send`) is actually a "non-mode" that lets the MPI implementation choose which communication mode is preferable. This might be heavily dependent on the implementation. In OpenMPI, the observed behaviour is that for short messages, the send is automatically buffered while for long messages, the message will be sent using a mode somewhat close to the synchronous mode.

The **buffered** mode (`MPI_Bsend`) stores all the data to be sent in a temporary buffer and returns to the execution, just as a non-blocking send would do. The advantage here is that execution continues immediatly even if the corresponding blocking `Recv` has not been called yet. On the other hand, buffered mode copies all the data of your buffer into another region of memory, duplicating the data. This might be dangerous memory wise if you are transferring large amounts of data.

The **ready** mode (`MPI_Rsend`) can start only if the corresponding receive has already been called. This allows your program to gain time from some additional overhead in the initialization of messages. If the corresponding `Recv` has not yet been called, the message that will be received //might// be ill-defined so you have to make sure that the receiving process has asked for a `Recv` **before** calling the ready mode.

Finally, the **synchronous** mode (`MPI_Ssend`) will wait for the corresponding `Recv` to complete. The data transfer will occur at that exact moment, ensuring that both processes are ready for transfer.

Try to play a bit with these mode and the previous example to see the difference in times to return to the program.



