#! /bin/bash

echo -e "\033[1mCompiling\033[0m"
cd 01_hello_world
rm -rf out hw
mpicxx -o hw hello_world.cpp 2> err_log
ls
mkdir out
rc=$?
if [[ $rc != 0 ]]; then
    echo -e "\033[1mError\033\0m : mpicxx returned"
    cat err_log
    echo "TECHIO> success false"
    rm -rf out
    exit $rc
fi
echo "Compilation is OK"

rm -rf out/*
rc=0

echo -e "\033[1mExecution\033[0m"
mpirun -np 4 -output-filename out/out ./hw

for f in `ls out`; do
    echo " **** Output of $f : ****"
    cat out/$f

echo "TECHIO> success true"

rm -rf out

