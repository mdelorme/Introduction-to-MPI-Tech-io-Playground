# Reductions - exercise 1 : The central limit theorem

The [central limit theorem](https://en.wikipedia.org/wiki/Central_limit_theorem) is a very famous theorem in statistics and probability. Very roughly, the CLT states that if you add multiple independant random variable together and repeat this process a certain number of times, the ending distribution will be close to a normal distribution (a bell shaped curve). We propose to illustrate this using a parallel program that will generate random numbers and add them !

![CLT figure](/img/normal_distribution.png)
//A normal distribution follows the famous bell-shaped Gaussian curve//

For this, we will consider $`M`$ process that will manage $`N`$ random variables. The basic algorithm will be the following : every process ($`M\approx 100`$) will draw a high number ($`N\approx 100000`$) of random variables. These variables will be based on the [uniform generator](http://www.cplusplus.com/reference/random/) of C++. Once every process has generated all these random variables, we will use a reduction operation to sum all the independent variables on one process. At the end of the operation, the process 0 should be left with a summed table of $`N`$ elements. The rest of the stub and the runner will take care of checking the result of your computation.

To improve the quality of the result, the first process is repeated over $`K \approx 100`$ times internally for every process in order to generate more variables. You will only have to find the right command for the reduction.

## Reduction

The reduction is done using the `MPI_Reduce` call. The prototype of this function is :

```cpp
int MPI_Reduce(void* send_data, void* recv_data, int count, MPI_Datatype type, MPI_Op op, int root, MPI_Comm communicator); 
```
Remember that the root is the process on which the reduction result will be stored. The operation is either `MPI_PROD`, `MPI_SUM`, `MPI_MIN` or `MPI_MAX` (should be obvious by now).

Your turn to play :

@[Central limit theorem]({"stubs": ["coll_red_ex1/central_limit.cpp"], "command": "bash coll_red_ex1/central_limit.sh"})

