#!/bin/bash

echo -e "Compiling"
cd p2p_race_conditions
rm -rf no_wait out
mpicxx -std=c++11 -o no_wait no_wait.cpp 2> err_log

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

mpirun -mca btl sm,tcp,self -np 2 ./no_wait
rm -rf no_wait


