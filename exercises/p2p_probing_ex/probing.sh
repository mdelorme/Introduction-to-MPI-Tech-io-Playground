#!/bin/bash

echo -e "Compiling"
cd p2p_probing_ex
rm -rf probing
mpicxx -std=c++11 -O0 -o probing main.cpp 2> err_log

rc=$?
if [[ $rc != 0 ]]; then
    echo -e "Error : mpicxx returned"
    cat err_log
    echo -e "WARNING : The files modified in the stub are included in other files, the line numbers indicated at compilation might be wrong".
    echo "TECHIO> success false"
    rm -rf out
    exit $rc
fi
echo "Compilation is OK"
echo -e "Execution ... "

rm -rf res.txt error.txt

mpirun -mca btl tcp,self -np 3 ./probing > res.txt 
python check_probing.py
rm -rf probing


