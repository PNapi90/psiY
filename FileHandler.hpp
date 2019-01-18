#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <mutex>


class FileHandler
{
private:

    bool locked,binary;

    void UnlockException();

    std::mutex MUTEX;

public:
    FileHandler(bool _binary);
    ~FileHandler();

    void Load_d12(std::vector<std::vector<double>> &DataX, int d0, int d12);
    void Load_E(std::vector<std::vector<double>> &DataE, int Eg);

    void Write(std::vector<std::vector<double>> &DataEX, std::string FileName);
};



#endif