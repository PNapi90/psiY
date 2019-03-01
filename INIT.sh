#!bin/bash

mkdir ComptonHists
mkdir d0_Hists
mkdir Histograms

for i in {0..0}#1000}
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

mkdir Histograms/TmpEGamma_661

for j in {0..599}
    do
        if [ $(($j % 4)) -eq 0 ]
        then
            mkdir Histograms/TmpEGamma_661/d0_${j}
        fi
    done
    echo Histograms/TmpEGamma_661 created

mkdir Histograms/ExpEGamma_661

for j in {0..599}
    do
        if [ $(($j % 4)) -eq 0 ]
        then
            mkdir Histograms/ExpEGamma_661/d0_${j}
        fi
    done
    echo Histograms/ExpEGamma_661 created

mkdir Histograms/TmpEGamma2_661

for j in {0..599}
    do
        if [ $(($j % 4)) -eq 0 ]
        then
            mkdir Histograms/TmpEGamma2_661/d0_${j}
        fi
    done
    echo Histograms/TmpEGamma2_661 created