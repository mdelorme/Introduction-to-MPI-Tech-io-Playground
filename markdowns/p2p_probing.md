# Probing incoming communications

For very simple examples as we have seen previously, with very few processes and small communications, everything looks pretty simple and straightforward. On the other hand, in real-life applications, the amount of data communicated can be really big, and in such a case, optimising the size of the messages sent have a real influence on the performance of the system. As a general rules of thumb, there are two points you should always obey when it comes to MPI communications :

* Try to group as many data as possible in one communication. Sending $`N`$ communications of $`M`$ bytes will always be more costly than one communication of $`N\times M`$ bytes.
* Try to send the exact amount of data you are storing in your buffer and no more.

This first point will be detailed later and is mainly subject to communication overhead/latency. The second point might seem obvious, but it can happen sometimes that before a transfer, the receiving process has actually no idea of the quantity of data that is being transferred to it. In such a case, there are three solutions :

* Sending everything in two communications : first sending the quantity of data you are going to send (1 int), then another communication with the actual buffer of N elements. This tends to go against rule #1.
* Sending a nominal amount of data : always sending the maximum amount in the buffer. That goes against rule #2.
* **Probing** the message. Basically asking MPI to give you the size of the message.

Probing is actually very useful, it serves many purposes such as getting the count of elements we are about to receive, the id and tags of the processes we are receiving from or if we are actually receiving anything or not.

There are two functions used to probe : `MPI_Probe` and `MPI_IProbe`. As you can guess by now, the first one is a blocking call, while the second one is not. Now `MPI_Probe` is only going to give you the `MPI_Status` associated with the next message received corresponding to a certain tag and id. As before, it is possible to use `MPI_ANY_SOURCE` and `MPI_ANY_TAG` if you want to probe the reception of any kind of message or from any source. Then, it is possible to use the resulting `MPI_Status` object in conjunction with other functions to get more information. Let's see a quick example of how that works :

@[Probing example]({"stubs": ["p2p_probing/probing.cpp"], "command": "bash p2p_probing/probing.sh"})

In the example, you can see that we probe the arrival of a message on process 1. The probing is blocking so process 1 is going to wait for a message from process 0. As soon as the message arrives, the execution resumes. But unlike a blocking receive, no information is actually transferred to the process. The probing only informs that the process is ready to receive a communication. Then, we use `MPI_Get_count` on the received status to retrieve the information we want : the number of elements in the communication. This way, we can allocate only the right number of elements and transfer the exact amount.

Note that, in terms of performance, this example is really a toy problem. In a real situation it would not be wise to reallocate the communication buffer for each call. Although every code should be taylored to the situations they are handling, one good rule to avoid superfluous overhead is to allocate once one or two buffers for communication (typically, either one universal buffer, or one for sending and one for receiving). This way, allocation is done only once, but communication can be probed to avoid sending too much information.

## Memory layout warning
If you choose the last solution you have to be extremely careful about the layout in memory of your buffers. Consider for instance, your program is handling and communicating 3-vectors. If you allocate a buffer in C++ the layout you choose might be bug-prone. Consider the two following codes :


**Version 1**
```cpp
float vectors[100][3]; // A 100 vector table

int n_to_send = 10;
fill_in_vectors(vectors, n_to_send);

MPI_Send(vectors, n_to_send*3, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
```

**Version 2**
```cpp
float vectors[3][100]; // Same but inverted layout

int n_to_send = 10;
fill_in_vectors(vectors, n_to_send);

MPI_Send(vectors, n_to_send*3, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
```

Take a few minutes and try to undertand what will happen in both cases.

?[Which code is actually sending 10 vectors to process 1 ?]
-[X] Version 1
-[ ] Version 2
-[ ] Both
-[ ] None

Funny trivia : If you are using Fortran, then the answer to this question is actually the opposite !