#ifndef THREADER_H
#define THREADER_H

#include <thread>
#include <vector>
#include <iostream>

#include "FileHandler.hpp"
#include "Processor.hpp"

class Threader
{
private:
    
    int thrNum;

    std::vector<std::vector<double>> HistE;

    Processor Process;
    void DoIt();

public:
    Threader(int _thrNum,
             FileHandler *FILES,
             std::vector<int> &d0_Range,
             int EnergyBin,
             std::vector<std::vector<double>> &_HistE);
    ~Threader();

    std::thread threading();
};


#endif