#!/bin/bash

echo -e "Compiling"
cd misc_custom_types
rm -rf vecetor_example
mpicxx -std=c++11 -o vector_example vector_example.cpp 2> err_log

rc=$?
if [[ $rc != 0 ]]; then
    echo -e "Error : mpicxx returned"
    cat err_log
    echo "TECHIO> success false"
    rm -rf out
    exit $rc
fi
echo "Compilation is OK"
mkdir out
rc=0

echo -e "Execution ... "

mpirun -mca btl sm,tcp,self -np 2 ./vector_example
rm -rf out




