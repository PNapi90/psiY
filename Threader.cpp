#include "Threader.hpp"

//---------------------------------------------------------

Threader::Threader(int _thrNum,
                   FileHandler *FILES,
                   std::vector<int> &d0_Range,
                   std::vector<int> &_Binning,
                   int EnergyBin,
                   std::vector<std::vector<double>> &_HistE)
    : thrNum(_thrNum),
      Process(d0_Range, _Binning, EnergyBin, FILES, _thrNum)
{

    std::string threadString = (thrNum > 9) ? std::to_string(thrNum) : "0"+std::to_string(thrNum);

    std::cout << "Created Thread # " << threadString;
    std::cout << " with d0 in [" << d0_Range[0] << "," << d0_Range[1] << ")";
    std::cout << std::endl;

    HistE = std::vector<std::vector<double>>(_HistE.size(), std::vector<double>(_HistE[0].size(), 0));
    for(int i = 0;i < HistE.size();++i)
    {
        for(int j = 0;j < HistE[0].size();++j) HistE[i][j] = _HistE[i][j];
    }
}

//---------------------------------------------------------

Threader::~Threader()
{}

//---------------------------------------------------------

void Threader::DoIt()
{
    Process.PROCESS(HistE);
}

//---------------------------------------------------------

std::thread Threader::threading()
{
    return std::thread([=]{DoIt();}); 
}

//---------------------------------------------------------