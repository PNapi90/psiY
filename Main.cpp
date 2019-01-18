#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>


#include "FileHandler.hpp"
#include "Threader.hpp"

//---------------------------------------------------------

struct FlagsAndValues
{
    int nthr = 1;
    int Egamma = 661;

    bool helpCalled = false;
    bool binary = false;

};

//---------------------------------------------------------

void ProcessFlags(int argc,char** argv,FlagsAndValues &F);
void PrintWelcome(FlagsAndValues &F);
void PrintHelp();

//---------------------------------------------------------

int main(int argc,char** argv)
{

    FlagsAndValues F;

    ProcessFlags(argc,argv,F);

    if(F.helpCalled)
    {
        PrintHelp();
        return 0;
    }


    PrintWelcome(F);

    int nthr = F.nthr;
    int Egamma = F.Egamma;



    std::vector<std::vector<int>> d0_Range(175,std::vector<int>(2,0));

    int Divisor = 600/nthr;
    
    for(int i = 0;i < d0_Range.size();++i)
    {
        d0_Range[i][0] = i*Divisor;
        d0_Range[i][1] = (i+1)*Divisor;
    }

    std::vector<std::vector<double>> HistE(175,std::vector<double>(101,0));

    FileHandler FILES(F.binary);
    FILES.Load_E(HistE,Egamma);

    std::vector<std::shared_ptr<Threader>> Threads;
    Threads.reserve(nthr);

    for(int i = 0;i < nthr;++i)
    {
        Threads.push_back(std::make_shared<Threader>(i, &FILES, d0_Range[i], Egamma,HistE));
    }

    std::cout << "-------------------------------------" << std::endl;

    std::thread t[nthr];
    for(int i = 0;i < nthr;++i) t[i] = Threads[i]->threading();
    for (int i = 0; i < nthr; ++i) t[i].join();

    return 0;
}

//---------------------------------------------------------

void ProcessFlags(int argc,char** argv,FlagsAndValues &F)
{

    bool threadBool = false,EnergyBool = false;

    std::string Flag;
    for(int i = 0;i < argc;++i)
    {
        Flag = std::string(argv[i]);
        
        if(Flag == "-t")
        {
            threadBool = true;
            continue;
        }
        if(threadBool)
        {
            F.nthr = std::stoi(Flag);
            threadBool = false;
            continue;
        }

        if (Flag == "-E")
        {
            EnergyBool = true;
            continue;
        }
        if (EnergyBool)
        {
            F.Egamma = std::stoi(Flag);
            EnergyBool = false;
            continue;
        }
        if (Flag == "-h")
        {
            F.helpCalled = true;
            continue;
        }
        if (Flag == "-b")
        {
            F.binary = true;
            continue;
        }
    }
}

//---------------------------------------------------------

void PrintHelp()
{
    std::cout << "\n------------------------------------------------------" << std::endl;
    std::cout << "Welcome to help of psiY" << std::endl;
    std::cout << "\nPossible Flags:\n" << std::endl;

    std::cout << "\t -t n \t set n as number of threads" << std::endl;
    std::cout << "\t -E n \t set n as bin of E\u03B3 in keV" << std::endl;
    std::cout << "\t -b \t load/write binary input files" << std::endl;
    std::cout << "\t -h \t prints this message" << std::endl;
    std::cout << "------------------------------------------------------\n" << std::endl;
}

//---------------------------------------------------------

void PrintWelcome(FlagsAndValues &F)
{
    std::string t_name = F.nthr == 1 ? "thread" : "threads";

    std::cout << "\n******************************************************" << std::endl;
    std::cout << "\nWelcome to the E(\u03B8)-X(\u03D1)-cos(\u03C8) merger psiY" << std::endl;
    std::cout << "\n======================================================" << std::endl;
    std::cout << "Running program with " << F.nthr << " " << t_name << std::endl;
    std::cout << "Incident photon energy E\u03B3 = " << F.Egamma << " keV" << std::endl;
    if(F.binary) std::cout << "Reading/writing binary input files" << std::endl;
    else std::cout << "Reading/writing text input files" << std::endl;
    std::cout << "======================================================" << std::endl;
} 

//---------------------------------------------------------