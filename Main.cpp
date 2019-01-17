#include <iostream>
#include <fstream>
#include <vector>
#include <memory>


#include "FileHandler.hpp"
#include "Threader.hpp"


int main()
{

    int nthr = 20;

    int Egamma = 661;

    std::vector<std::vector<int>> d0_Range(175,std::vector<int>(2,0));

    int Divisor = 600/nthr;
    
    for(int i = 0;i < d0_Range.size();++i)
    {
        d0_Range[i][0] = i*Divisor;
        d0_Range[i][1] = (i+1)*Divisor;
    }

    std::vector<std::vector<double>> HistE(175,std::vector<double>(101,0));

    FileHandler FILES;
    FILES.Load_E(HistE,Egamma);

    std::vector<std::shared_ptr<Threader>> Threads;
    Threads.reserve(nthr);

    for(int i = 0;i < nthr;++i)
    {
        Threads.push_back(std::make_shared<Threader>(i, &FILES, d0_Range[i], Egamma,HistE));
    }

    std::thread t[nthr];
    for(int i = 0;i < nthr;++i) t[i] = Threads[i]->threading();
    for (int i = 0; i < nthr; ++i) t[i].join();

    return 0;
}

