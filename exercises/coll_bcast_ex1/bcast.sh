#!/bin/bash

echo -e "Compiling"
cd coll_bcast_ex1
rm -rf out bcast
mpicxx -o bcast bcast.cpp 2> err_log

rc=$?
if [[ $rc != 0 ]]; then
    echo -e "Error : mpicxx returned"
    cat err_log
    echo "TECHIO> success false"
    rm -rf out
    exit $rc
fi
echo "Compilation is OK"
mkdir out
rc=0

echo -e "Execution ... "

mpirun -mca btl sm,tcp,self -output-filename out/out -np 3 ./bcast < input
python check_bcast.py
rm -rf out




