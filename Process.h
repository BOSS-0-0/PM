#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H
#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>

struct Process{
    uint32_t pid; // уникальное имя для процесса
    std::string name;
    std::string fullPath; //полный путь файла
    uint64_t memoryUse;
    double cpuUse;
    int threadCount;//скеолько потоков используеться в процессе
    int prioritet;
    std:: string status;

    Process() : pid(0),memoryUse(0),cpuUse(0),threadCount(0),prioritet(0),status("Unknown"){}
    void print () const{
        double memoryMB = memoryUse / (1024.0 * 1024.0);
        std::cout << "Pid:" << pid << "|" <<"Name:" <<name <<"|"<<"Memory MB:" << std::fixed << std::setprecision(2) << memoryMB << "|" << "CPU:" << cpuUse << "|" << "Threads:" << threadCount << "|" << "Status:" << status <<std::endl;
    }
};
#endif