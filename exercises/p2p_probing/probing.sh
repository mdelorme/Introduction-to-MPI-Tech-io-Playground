#!/bin/bash

echo -e "Compiling"
cd p2p_probing
rm -rf probing
mpicxx -std=c++11 -o probing probing.cpp 2> err_log

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
mkdir out

mpirun -mca btl sm,tcp,self -np 2 ./probing
rm -rf probing


