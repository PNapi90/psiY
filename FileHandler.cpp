#include "FileHandler.hpp"

//---------------------------------------------------------

FileHandler::FileHandler(bool _binary)
    : binary(_binary)
{}

//---------------------------------------------------------

FileHandler::~FileHandler()
{}

//---------------------------------------------------------

void FileHandler::Load_d12(std::vector<std::vector<double>> &DataX,
                           int d0, int d12)
{

    std::lock_guard<std::mutex> LOCK(MUTEX);

    std::string d012Name = "d0_Hists/d0s_5_4/d0_" + std::to_string(d0) + "/d12_" + std::to_string(d12);

    std::ifstream DATA;
    if(binary)
        DATA.open(d012Name, std::ios::in | std::ios::binary);
    else
        DATA.open(d012Name);

    if (DATA.fail())
    {
        std::cerr << "Could not find " << d012Name << std::endl;
        exit(1);
    }

    std::vector<double> TVec(DataX[0].size(), 0);

    if(binary)
    {
        for (int i = 0; i < DataX.size(); ++i)
        {
            DATA.read(reinterpret_cast<char *>(&TVec[0]),
                      TVec.size() * sizeof(TVec[0]));

            for (int j = 0; j < TVec.size(); ++j)
                DataX[i][j] = TVec[j];
        }
    }
    
    else
    {
        for (int i = 0; i < DataX.size(); ++i)
        {
            for (int j = 0; j < DataX[0].size(); ++j)
                DATA >> DataX[i][j];
        }
    }
}

//---------------------------------------------------------

void FileHandler::Load_E(std::vector<std::vector<double>> &DataE,int Eg)
{
    std::lock_guard<std::mutex> LOCK(MUTEX);

    std::string EName = "ComptonHists/ComptonHist_" + std::to_string(Eg);
    
    std::ifstream DATA;
    if (binary)
        DATA.open(EName, std::ios::in | std::ios::binary);
    else
        DATA.open(EName);

    if(DATA.fail())
    {
        std::cerr << "Could not find " << EName << std::endl;
        exit(1);
    }

    std::vector<double> TVec(DataE[0].size(),0);

    if(binary)
    {
        for (int i = 0; i < DataE.size(); ++i)
        {
            DATA.read(reinterpret_cast<char *>(&TVec[0]),
                      TVec.size() * sizeof(TVec[0]));

            for (int j = 0; j < TVec.size(); ++j)
                DataE[i][j] = TVec[j];
        }
    }
    else
    {
        for (int i = 0; i < DataE.size(); ++i)
        {
            for (int j = 0; j < DataE[0].size(); ++j)
                DATA >> DataE[i][j];
        }
    }
}

//---------------------------------------------------------

void FileHandler::Write(std::vector<std::vector<double>> &DataEX,std::string FileName)
{
    std::lock_guard<std::mutex> LOCK(MUTEX_W);

    std::ofstream DATA;
    if (binary)
        DATA.open(FileName, std::ios::out | std::ios::binary);
    else
        DATA.open(FileName);

    if(DATA.fail())
    {
        std::cerr << "Could not open Output file " << FileName << std::endl;
        exit(1);
    }

    if(binary)
    {
        for (auto V : DataEX)
        {
            DATA.write(reinterpret_cast<char *>(&V[0]),
                       V.size() * sizeof(V[0]));
        }
    }
    
    else
    {
        for(auto DVec : DataEX)
        {
            for(auto V : DVec)
                DATA << V << " ";
            DATA << std::endl;
        }
    }
    
    DATA.close();
}

//---------------------------------------------------------

void FileHandler::UnlockException()
{
    std::cerr << "Mutex unlocked!" << std::endl;
    exit(1);
}

//---------------------------------------------------------