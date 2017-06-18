#!/bin/bash

echo -e "Compiling"
cd examples/p5_2
rm -rf bcast_collective
mpicxx -o bcast_collective bcast_collective.cpp 2> err_log

rc=$?
if [[ $rc != 0 ]]; then
    echo -e "Error : mpicxx returned"
    cat err_log
    echo "TECHIO> success false"
    rm -rf out
    exit $rc
fi
echo "Compilation is OK"
echo -e "Execution ... "
mpirun -mca btl tcp,self -np 5 ./bcast_collective
rm -rf out

echo "TECHIO> success true"




