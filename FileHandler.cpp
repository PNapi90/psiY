#include "FileHandler.hpp"

//---------------------------------------------------------

FileHandler::FileHandler()
{}

//---------------------------------------------------------

FileHandler::~FileHandler()
{}

//---------------------------------------------------------

void FileHandler::Load_d12(std::vector<std::vector<double>> &DataX,
                           int d0, int d12)
{

    std::lock_guard<std::mutex> LOCK(MUTEX);


    locked = true;

    if (!locked)
        UnlockException();

    std::string d012Name = "d0_" + std::to_string(d0) + "/d12_" + std::to_string(d12);

    std::ifstream DATA(d012Name, std::ios::in | std::ios::binary);

    if (DATA.fail())
    {
        std::cerr << "Could not find " << d012Name << std::endl;
        exit(1);
    }

    std::vector<double> TVec(DataX[0].size(), 0);

    for (int i = 0; i < DataX.size(); ++i)
    {
        DATA.read(reinterpret_cast<char *>(&TVec[0]),
                  TVec.size() * sizeof(TVec[0]));

        for (int j = 0; j < TVec.size(); ++j)
            DataX[i][j] = TVec[j];
    }

    if (!locked)
        UnlockException();

    locked = false;
}

//---------------------------------------------------------

void FileHandler::Load_E(std::vector<std::vector<double>> &DataE,int Eg)
{
    std::lock_guard<std::mutex> LOCK(MUTEX);

    locked = true;

    if (!locked)
        UnlockException();

    std::string EName = "ComptonHist_" + std::to_string(Eg);
    std::ifstream DATA(EName,std::ios::in | std::ios::binary);

    if(DATA.fail())
    {
        std::cerr << "Could not find " << EName << std::endl;
        exit(1);
    }

    std::vector<double> TVec(DataE[0].size(),0);

    for (int i = 0; i < DataE.size(); ++i)
    {
        DATA.read(reinterpret_cast<char *>(&TVec[0]),
                 TVec.size() * sizeof(TVec[0]));

        for (int j = 0; j < TVec.size(); ++j)
            DataE[i][j] = TVec[j];
    }

    if (!locked)
        UnlockException();

    locked = false;
}

//---------------------------------------------------------

void FileHandler::Write(std::vector<std::vector<double>> &DataEX,std::string FileName)
{
    std::lock_guard<std::mutex> LOCK(MUTEX);

    locked = true;

    if (!locked) UnlockException();

    std::ofstream DATA(FileName,std::ios::out | std::ios::binary);
    
    if(DATA.fail())
    {
        std::cerr << "Could not open Output file " << FileName << std::endl;
        exit(1);
    }

    for (auto V : DataEX)
    {
        DATA.write(reinterpret_cast<char *>(&V[0]),
                   V.size() * sizeof(V[0]));
    }

    if (!locked)
        UnlockException();

    DATA.close();

    if (!locked)
        UnlockException();

    locked = false;
}

//---------------------------------------------------------

void FileHandler::UnlockException()
{
    std::cerr << "Mutex unlocked!" << std::endl;
    exit(1);
}

//---------------------------------------------------------