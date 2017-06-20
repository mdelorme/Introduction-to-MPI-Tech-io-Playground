#!/bin/bash

echo -e "Compiling"
cd examples/p5_1
rm -rf bcast_p2p
mpicxx -o bcast_p2p bcast_p2p.cpp 2> err_log

rc=$?
if [[ $rc != 0 ]]; then
    echo -e "Error : mpicxx returned"
    cat err_log
    echo -e "Please do not modify the provided code. They are not exercises but mere examples."
    echo "TECHIO> success false"
    rm -rf out
    exit $rc
fi
echo "Compilation is OK"
echo -e "Execution ... "
mpirun -mca btl sm,tcp,self -np 5 ./bcast_p2p
rm -rf out

echo "TECHIO> success true"

ompi_info



