#!/bin/bash

echo -e "Compiling"
cd misc_custom_types
rm -rf create_struct types_example
mpicxx -std=c++11 -o types_example types_example.cpp 2> err_log
mpicxx -std=c++11 -o create_struct create_struct.cpp 2> err_log

rc=$?
if [[ $rc != 0 ]]; then
    echo -e "Error : mpicxx returned"
    cat err_log
    echo "TECHIO> success false"
    rm -rf out
    exit $rc
fi
echo "Compilation is OK"
rc=0

echo -e "Execution ... "

mpirun -mca btl sm,tcp,self -np 5 ./types_example > ref
mpirun -mca btl sm,tcp,self -np 5 ./create_struct > out

python check.py


