# Reductions - exercise 1 : The central limit theorem

The central limit theorem is something we can easily illustrate using reductions and mpi communications. You can have a look at the wikipedia page on the central limit theorem if you want a deep explanation of the phenomenon, but in substance the theorem says that any sum of a sufficient number of uniform random distributions will tend to a normal (gaussian law).

We can illustrate that using $`N`$ processing drawing $`M`$ random variables from a uniform distribution. Then summing all over these $`N`$ processes. The result of the reduction should then be a distribution of $`M`$ normal variables. This should be simple enough to code very simply with only one global communication, which is what you have to do. The rest of the program will handling all the accessory tests to show that the distribution you created is indeed drawn from a normal law.

@[Central limit theorem]({"stubs": ["coll_red_ex1/central_limit.cpp"], "command": "bash coll_red_ex1/central_limit.sh"})

