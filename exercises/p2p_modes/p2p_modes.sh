#!/bin/bash

echo -e "Compiling"
cd p2p_modes
rm -rf modes
mpicxx -std=c++11 -O0 -o modes p2p_modes.cpp 2> err_log

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

mpirun -mca btl tcp,self -np 2 ./modes
rm -rf modes


