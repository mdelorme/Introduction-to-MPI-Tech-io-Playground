#!/bin/bash

echo -e "Compiling"
cd coll_red_ex1
rm -rf clt
mpicxx -std=c++11 -O0 -o clt central_limit.cpp 2> err_log

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

mpirun -mca btl tcp,self -np 20 ./clt > norm
python check_clt.py
rm -rf clt


