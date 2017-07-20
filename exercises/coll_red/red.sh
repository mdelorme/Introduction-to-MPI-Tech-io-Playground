#!/bin/bash

echo -e "Compiling"
cd coll_red
rm -rf red
mpicxx -std=c++11 -O0 -o red red.cpp 2> err_log

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

mpirun -mca btl tcp,self -np 10 ./red
rm -rf red


