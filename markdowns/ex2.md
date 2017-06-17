# Point-to-point communications, exercise 1

It is time to code something a bit fancier than just printing your rank id on the screen. Let's have an actual communication between two processes. The objective of the exercise is as follows : The program will be run with two processes. You will have first to get your rank on `MPI_COMM_WORLD` and read an integer on `stdin`. Then, depending on your id, you will have to have different behaviours :

**Process #0**

* Send your integer to Process #1
* Receive the integer of Process #1
* Sum the two values
* Write the result on `stdout`.

** Process #1**

* Receive the integer of Process #0
* Send your integer to Process #0
* Subtract the two values
* Write the result on `stdout`.
