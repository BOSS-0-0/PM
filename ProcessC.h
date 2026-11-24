#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <cstdint>
#include <iostream>
#include <iomanip>

struct Process {
    uint32_t pid;
    std::string name;
    std::string fullPath;
    uint64_t memoryUse;
    double cpuUse;
    int threadCount;
    int prioritet;
    std::string status;

    Process() : pid(0), name(), fullPath(), memoryUse(0), cpuUse(0.0),
                threadCount(0), prioritet(0), status("Unknown") {}

    void print() const {
        double memoryMB = memoryUse / (1024.0 * 1024.0);
        std::cout << "PID: " << pid << " | "
                  << "Name: " << name << " | "
                  << "Memory: " << std::fixed << std::setprecision(2) << memoryMB << " MB | "
                  << "CPU: " << cpuUse << "% | "
                  << "Threads: " << threadCount << " | "
                  << "Status: " << status << std::endl;
    }
};

#endif