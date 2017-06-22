#!/bin/bash

echo -e "Compiling"
cd 02_p2p_1
rm -rf out p2p_1
mpicxx -o p2p_1 p2p_1.cpp 2> err_log

rc=$?
if [[ $rc != 0 ]]; then
    echo -e "Error : mpicxx returned"
    cat err_log
    echo "TECHIO> success false"
    rm -rf out
    exit $rc
fi
echo "Compilation is OK"
rm -rf out
mkdir out
rc=0

echo -e "Execution ... "

rnd1=$(( RANDOM % 100 ))
rnd2=$(( RANDOM % 100 ))

mpirun -mca btl tcp,self -output-filename out/out -np 1 ./p2p_1 $rnd1 : -np 1 ./p2p_1 $rnd2
python check_p2p_1.py $rnd1 $rnd2
rm -rf out




