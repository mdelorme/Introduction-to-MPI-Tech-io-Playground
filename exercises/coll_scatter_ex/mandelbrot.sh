#!/bin/bash

echo -e "Compiling"
cd coll_scatter_ex
rm -rf mandelbrot
mpicxx -std=c++11 -O3 -o mandelbrot mandelbrot.cpp 2> err_log

rc=$?
if [[ $rc != 0 ]]; then
    echo -e "Error : mpicxx returned"
    cat err_log
    echo "TECHIO> success false"
    rm -rf out
    exit $rc
fi
echo "Compilation is OK"

NP=4

echo -e "Running example 1 ... "
mpirun -mca btl tcp,sm,self -np $NP ./mandelbrot -2.0 1.0 -1.5 1.5 50 > ex1

echo -e "Running example 2 ... "
mpirun -mca btl tcp,sm,self -np $NP ./mandelbrot -0.749 -0.750 -0.0605 -0.0615 1024 > ex2

echo -e "Running example 3 ... "
mpirun -mca btl tcp,sm,self -np $NP ./mandelbrot -1.45 -1.35 -0.05 0.05 128 > ex3

echo -e "Running example 4 ... "
mpirun -mca btl tcp,sm,self -np $NP ./mandelbrot -1.30 -1.15 0.25 0.40 128 > ex4

echo -e "Plotting ..."
python display.py

echo -e "Done !"
rm -rf mandelbrot out


