## Custom types - exercise

In the previous lesson, we have seen how to create very basic contiguous datatypes. This way of creating datatypes does not help us when we want to create datatypes that mix different basice types. For instance, in the previous lesson's example, we have seen a custom structure used to store the data :

```cpp
struct CustomData {
  int n_values;
  double dbl_values[10];
};
```

To represent this using the type/displacement formalism, our datatype would look something like :

```
[(int, 0), (double, 4), (double, 12), (double, 20), (double, 28), (double, 36), (double, 44), (double, 52), (double, 60), (double, 68), (double, 76)]
```

To simplify everything, we can convert everyone of these couples as a triplet : (type, start, number of elements). Thus our list simplifies to :

```
[(int, 0, 1), (double, 4, 10)]
```

MPI provides us with a special function to actually convert such a list in a datatype :

```cpp
int MPI_Type_create_struct(int count, const int block_length[], const MPI_Aint displacement[], const MPI_Datatype types[], MPI_Datatype *new_type);
```

Let's see these arguments one by one. `count` is the number of elements in your list, in our case we have two entries, so `count` will be 2.

`block_length` is an array of integers, indicating, for entry `i`, the number of contiguous elements of that type. That will be the third value of our triplet : 1 in the `int` case, 10 in the `double` case.

`displacement` is an array of `MPI_Aint`. We have never seen this type, but let's forget immediatly about it, and consider this to be an array of integers. `MPI_Aint` stands for `Address integer`. These are just a specific MPI type for integers. In our case, that's the second element of each triplet.

`types` is an array of `MPI_Datatypes`. This should be pretty obvious by now : it's an array of all the different sub-types we are going to use in the custom type.

Finally, we store the resulting datatype in `new_type`.

Knowing this, you are ready to optimise the example code we gave in last lesson, especially, removing all the copies in memory and transferring all the data using only one gather communication.

@[Custom struct datatype]({"stubs": ["misc_custom_types/create_struct.cpp"], "command": "bash misc_custom_types/create_struct.sh"})



