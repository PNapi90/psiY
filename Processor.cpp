#include "Processor.hpp"

//---------------------------------------------------------

Processor::Processor(std::vector<int> &d0_Range,int EnergyBin,
                     FileHandler *FILES) : MERGER()
{
    d0_start = d0_Range[0];
    d0_end = d0_Range[1];

    this->EnergyBin = EnergyBin;
    this->FILES = FILES;

    HistX = std::vector<std::vector<double>>(150,std::vector<double>(101,0));
    d12s = std::vector<int>(150,0);

    Merge = std::vector<std::vector<double>>(175,std::vector<double>(180,0));
    Maxima = std::vector<double>(175,0);

    for(int i = 0;i < 150;++i) d12s[i] = i*4;
}

//---------------------------------------------------------

Processor::~Processor()
{
    FILES = nullptr;
}

//---------------------------------------------------------

void Processor::PROCESS(std::vector<std::vector<double>> &HistE)
{
    int d0 = d0_start;
    std::string Name;
    for(int i = d0_start;i < d0_end;++i)
    {
        d0 += 4;
        for(auto d12 : d12s)
        {
            //load d0_d12 histograms from file into HistX
            FILES->Load_d12(HistX,d0,d12);

            //Merge HistE and HistX regarding cos(psi)
            MERGER.MERGE(HistE,HistX,Merge,Maxima);

            Name = "Histograms/EGamma_" + std::to_string(EnergyBin) + "/d0_";
            Name += std::to_string(d0) + "/d12_" + std::to_string(d12);

            //write merged Histogram into file E_i/d0_j/d12_k
            FILES->Write(Merge,Name);
        }
        
    }
}

//---------------------------------------------------------