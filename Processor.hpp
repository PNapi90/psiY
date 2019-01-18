#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Merger.hpp"
#include "FileHandler.hpp"

class Processor
{
private:
    
    int d0_start,d0_end,EnergyBin,thrNum;

    std::vector<int> d12s;
    std::vector<double> Maxima;
    std::vector<std::vector<double>> HistX,Merge;

    Merger MERGER;
    FileHandler *FILES;

public:
    Processor(std::vector<int> &d0_Range,
              std::vector<int> &Binning,
              int EnergyBin,
              FileHandler *FILES,
              int _thrNum);
    ~Processor();

    void PROCESS(std::vector<std::vector<double>> &HistE);
};

#endif