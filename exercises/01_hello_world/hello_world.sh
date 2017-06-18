#!/bin/bash

echo -e "Compiling"
cd 01_hello_world
rm -rf out hw
mpicxx -o hw hello_world.cpp 2> err_log
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
mpirun -mca btl tcp,self -np 4 -output-filename out/out ./hw
python check_hw.py
rm -rf out

