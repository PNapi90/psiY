#include "Merger.hpp"

//---------------------------------------------------------

Merger::Merger() 
{}

//---------------------------------------------------------

Merger::~Merger()
{}

//---------------------------------------------------------

void Merger::MERGE(std::vector<std::vector<double>> &HistE,
                   std::vector<std::vector<double>> &HistX,
                   std::vector<std::vector<double>> &Merge,
                   std::vector<double> &Maxima)
{
    double Max = 0,Val = 0;

    int HistE_Size = HistE.size();
    int HistX_Size = HistX.size();
    int HistE_psi_Size = HistE[0].size();
    int HistX_psi_Size = HistX[0].size();

    if(HistE_psi_Size != HistX_psi_Size)
    {
        std::cerr << "HistX size = " << HistX_psi_Size << " not equal to HistE size = " << HistE_psi_Size << std::endl;
        exit(1);
    }
   
    for(int i = 0;i < HistE_Size;++i)
    {
        Max = 0;
        for(int j = 0;j < HistX_Size;++j)
        {
            Merge[i][j] = 0;
            for (int k = 0; k < HistE_psi_Size; ++k)
            {
                //prevent overfilled bins
                if(HistX[j][k] < 1)
                {
                    Val = Min(HistE[i][k], HistX[j][k]);
                    Merge[i][j] += Val;
                }
            }
            Max = (Max <= Merge[i][j]) ? Merge[i][j] : Max;
        }
        Maxima[i] = Max;
        if (Max > 0)
        {
            for (int j = 0; j < HistX_Size; ++j)
                Merge[i][j] /= Max;
        }
    }
}

//---------------------------------------------------------

inline double Merger::Min(double a,double b)
{
    return (a <= b) ? a : b;
}

//---------------------------------------------------------