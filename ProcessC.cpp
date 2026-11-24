#include "ProcessC.h"
#include <psapi.h>
#include <iostream>

#pragma comment(lib, "psapi.lib")

std::vector<Process> ProcessC::collectProcesses() {
    std::vector<Process> processes;
    DWORD processIDs[1024];
    DWORD bytesReturned;

    if (!EnumProcesses(processIDs, sizeof(processIDs), &bytesReturned)) {
        std::cerr << "Ошибка при получении списка процессов" << std::endl;
        return processes;
    }

    DWORD numProcesses = bytesReturned / sizeof(DWORD);

    for (DWORD i = 0; i < numProcesses; i++) {
        if (processIDs[i] != 0) {
            Process info = getProcess(processIDs[i]);
            if (info.pid != 0) {
                processes.push_back(info);
            }
        }
    }

    return processes;
}

Process ProcessC::getProcess(DWORD processID) {
    Process info;

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (hProcess == NULL) {
        return info;
    }

    HMODULE hMod;
    DWORD cbNeeded;
    if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
        char processName[MAX_PATH];
        GetModuleBaseNameA(hProcess, hMod, processName, sizeof(processName));
        info.name = processName;
    }

    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
        info.memoryUse = pmc.WorkingSetSize;
    }

    info.pid = processID;
    info.status = "Running";

    CloseHandle(hProcess);
    return info;
}