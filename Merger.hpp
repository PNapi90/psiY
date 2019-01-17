#ifndef MERGER_H
#define MERGER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

class Merger
{
private:

    inline double Min(double a,double b);

public:
    Merger();
    ~Merger();

    void MERGE(std::vector<std::vector<double>> &HistE,
               std::vector<std::vector<double>> &HistX,
               std::vector<std::vector<double>> &Merge,
               std::vector<double> &Maxima);
};




#endif