#!/bin/bash

echo -e "Compiling"
cd coll_red_ex1
rm -rf central_limit
mpicxx -std=c++11 -O0 -o central_limit central_limit.cpp 2> err_log

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

mpirun -mca btl tcp,self -np 100 ./central_limit
rm -rf central_limit


