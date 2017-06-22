#!/bin/bash

echo -e "Compiling"
cd p2p_non_blocking
rm -rf b_vs_nb
mpicxx -std=c++11 -o b_vs_nb main.cpp 2> err_log

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

mpirun -mca btl sm,tcp,self -np 2 ./b_vs_nb | tee out.txt
#python check_non_blocking.py
cat out.txt
rm -rf b_vs_nb


