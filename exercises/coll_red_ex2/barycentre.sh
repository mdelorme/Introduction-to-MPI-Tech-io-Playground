#!/bin/bash

echo -e "Compiling"
cd coll_red_ex2
rm -rf barycentre
mpicxx -std=c++11 -O0 -o barycentre main.cpp 2> err_log

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

mpirun -mca btl tcp,self -np 10 ./barycentre < input.txt | sort -n > norm
diff norm out.txt > log
rc=$?
if [[ $rc != 0 ]]; then
    echo -e "Error : output is wrong !"
    echo "TECHIO> success false"
    rm norm
    exit $rc
fi
rm -rf clt

echo "The computed distances are correct ! Congratulations !"
echo "TECHIO> success true"

