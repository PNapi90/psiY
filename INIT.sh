#!bin/bash

mkdir ComptonHists
mkdir d0_Hists
mkdir Histograms

for i in {0..1000}
do
    mkdir Histograms/EGamma_${i}
    for j in {0..599}
    do
        if [ $(($j % 4)) -eq 0 ]
        then
            mkdir Histograms/EGamma_${i}/d0_${j}
        fi
    done
    echo Histograms/EGamma_${i} created
done