# Reductions

Reductions are among the most useful MPI operations you can use. Reductions are basically a very simple operation that will be applied on all the buffers the processes. The operation can be either user-specified (we will not cover this here) or from the list of pre-defined operations. Usually, the predefined operations are largely sufficient for any application. Let's take, once again, a very simple (and very inefficient) example. Consider a system where you have $`N`$ processes. The goal of the game is to compute the dot product of two $`N`$-vectors in parallel. Now the dot product of two vectors $`\mathbf{u}`$ and $`\mathbf{v}`$, for those who forgot, is the following operation :

```math
\mathbf{u}\dot \mathbf{v} = u_1 \times v_1 + u_2 \times v_2 + ... + u_N \times v_N
```

As you can imagine, this is highly parallelizable. If you have $`N`$ processes, each process $`i`$ can compute the intermediate value $`u_i \times v_i`$. Then, the program needs to find a way to sum all of these values. This is where the reduction comes into play. We can ask MPI to sum all those value and store them either on only one process (for instance process 0) or to redistribute the value to every process. Here is how we would do it in C++ :

@[Reduction example]({"stubs": ["coll_red/red.cpp"], "command": "bash coll_red/red.sh"})

As for broadcasting, reduction also provides optimised implementation that will be much better than any naive solution you could come up with p2p communications.

## Operations

In the example, you see that we indicate we want to sum all the values using the `MPI_SUM` flag. There are other predefined flags that allow you to do diverse operations on your data. You can find a precise list of there predefined flags if you look at the manual of `MPI_Reduce`. This list is reproduced below :

Operator | Operation
---------|--------
`MPI_MAX` | maximum value
`MPI_MIN` | minimum value
`MPI_SUM` | sum
`MPI_PROD` | product
`MPI_LAND` | logical and
`MPI_BAND` | bit-wise and
`MPI_LOR` | logical or
`MPI_BOR` | bit-wise or
`MPI_LXOR` | logical xor
`MPI_BXOR` | bit-wise xor
`MPI_MAXLOC` | max value and location
`MPI_MINLOC` | min value and location

For the following, we will only concentrate on the first four. The logical/bitwise operators are pretty obvious and should be used in a straightforward manner. As for the last two, they are really useful but require some datatype we have not seen (and won't see), so we will not cover these. You can find more information and examples on `MPI_MAXLOC` and `MPI_MINLOC` in the manual of `MPI_Reduce`.

## Operations on arrays

Now, everything should be pretty obvious when each process is dealing with a single value as we have shown on the example. But what happens when processes have buffers ? How does the sum behaves for instance ? Will it give us a single scalar at the end, or will sum the various buffers together.

The answer is : the operations are computed **element-wise**. So if you apply `MPI_MAX`, `MPI_MIN` or `MPI_SUM` on a buffer with five elements in a five-processes program, you will get five values as result :

Process   | `buf[0]` | `buf[1]` | `buf[2]` | `buf[3]` | `buf[4]`
----------|----------|----------|----------|----------|---------
0         | 4.0      | 12.0     | -1.0     | 7.2      | -23.0
1         | 0.0      | 0.0      | 0.0      | 0.0      | 0.0
2         | -1.0     | 2.0      | -3.0     | 4.0      | -5.0
3         | 7.3      | -5.0     | -12.0    | -3.2     | 1.23
4         | -1.0     | -1.0     | -1.0     | -1.0     | -1.0
          |          |          |          |          |
`MPI_MIN` | -1.0     | -5.0     | -12.0    | -3.2     | -23.0
`MPI_MAX` | 7.3      | 12.0     | 0.0      | 7.2      | 1.23
`MPI_SUM` | 9.3      | 8.0      | -17.0    | 7.0      | -27.77

## Reducing on all processes

There are multiple flavours of reduction. The example above shows us `MPI_Reduce` in which the reduction operation takes place on only one process (in this case process 0). In our case, the reception buffer (`result`) is only valid for process 0. The other processes will not have a valid value stored in `result`. Sometimes, you might want to have the result of the reduction stored on all processes, in which case `MPI_Reduce` is not suited. In such a case, you can use `MPI_Allreduce` to store the result on every process. So, if we had used `MPI_Allreduce` instead of `MPI_Reduce` in the example, all processes would have a valid value in `result` and could be using this value after the communication.

These two are not the only ways of doing reductions. You can find more information by looking at the MPI standard and the MPI implementation APIs.

## Buffer matters

You might wonder why, in the example, we bother using a different variable for storing the intermediate value, and the final result. After all, we could directly use :

```cpp
MPI_Reduce(&tmp, &tmp, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
```

This will invariably produce garbage in your result buffer. Do **NOT** use the same buffer for sending and receiving in a reduction. It is possible in some cases to use the same buffer, but to avoid bugs and improve the semantics and readability of your code, it is strongly suggested you use different buffers for sending and receiving data.

Let's try to apply this in two exercises now !