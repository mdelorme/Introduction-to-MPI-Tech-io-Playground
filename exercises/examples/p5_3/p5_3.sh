#!/bin/bash

cd examples/p5_3

echo "Compiling the p2p version"
mkdir out
rm -rf bcast_p2p
mpicxx -o bcast_p2p bcast_p2p.cpp 2> err_log

rc=$?
if [[ $rc != 0 ]]; then
    echo "Error : mpicxx returned"
    cat err_log
    echo "Please do not modify the provided code. They are not exercises but mere examples."
    echo "TECHIO> success false"
    rm -rf out
    exit $rc
fi
echo "Compilation is OK"

echo "Compiling the collective version"
rm -rf bcast_collective
mpicxx -o bcast_collective bcast_collective.cpp 2> err_log

rc=$?
if [[ $rc != 0 ]]; then
    echo "Error : mpicxx returned"
    cat err_log
    echo "Please do not modify the provided code. They are not exercises but mere examples."
    echo "TECHIO> success false"
    rm -rf out
    exit $rc
fi
echo "Compilation is OK"
echo "Running P2P version ... "
time mpirun -mca btl tcp,self -output-filename out/out -np 1000 ./bcast_collective
rm -rf out

echo "TECHIO> success true"




