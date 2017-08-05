#!/bin/bash

echo -e "Compiling"
cd comm_splitting_ex
rm -rf splitting
mpicxx -std=c++11 -O3 -o splitting main.cpp 2> err_log

rc=$?
if [[ $rc != 0 ]]; then
    echo -e "Error : mpicxx returned"
    cat err_log
    echo "TECHIO> success false"
    rm -rf out
    exit $rc
fi
echo "Compilation is OK"

mpirun -mca btl tcp,sm,self -np 8 ./splitting
rc=$?

if [[ $rc != 0 ]]; then
    echo "TECHIO> success false"
fi
