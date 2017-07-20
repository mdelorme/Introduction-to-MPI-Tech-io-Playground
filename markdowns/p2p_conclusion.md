# P2P Conclusion

That's it ! We are finished with point-to-point communications !
By now you should know all the basics to send and receive messages from one specific process to another specific process. With that, you can already do a lot of different funky things in parallel !

In the next chapter, we will talk about collective communications, when you want to reach more than just one process in a communication. In the meantime, you can practice what you have learnt by answering this quizz :

?[What is the default communicator that encapsulate all processes ?]
-[ ] MPI_COMM_ALL
-[ ] MPI_COMM_DEFAULT
-[X] MPI_COMM_WORLD
-[ ] MPI_COMM_DEF

?[Which of these situations is/are a race condition ?](multiple)
-[ ] When the send buffer is not filled fast enough for the receive to be completed properly.
-[ ] When there is a large difference in sending time between two processes with the same buffers.
-[X] When the sending process modifies its buffer before the receiving process has read from it.

?[What is a deadlock ?]
-[ ] When a process blocks its buffer so that no receive can modify it
-[ ] A mode of communication, that waits for a receive to be completed before sending
-[X] When multiple processes are waiting for each-other without being able to continue
-[ ] When a non-blocking receive is not followed by a wait.

?[What are the four modes of communication ?]
-[X] Standard, buffered, ready and synchronous.
-[ ] Standard, buffered, deadlocked and synchronous.
-[ ] Default, standard, buffered and ready
-[ ] Default, standard, buffered and synchronous.

?[The buffered mode is fundamentally similar to a non-blocking send]
-[X] True
-[ ] False

?[What can we use probing for ?](multiple)
-[X] To know if a message is waiting to be delivered to a process
-[X] To know the tag of an incoming message
-[X] To know the id of the process sending a message
-[X] To know the number of elements in an incoming message

?[In non-blocking communications, which function must necessarily be called at some point after a receive or a send ?]
-[ ] `MPI_Test`
-[ ] `MPI_Barrier`
-[X] `MPI_Wait`
-[ ] `MPI_Probe`

