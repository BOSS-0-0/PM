#include "ProcessC.h"
#include <windows.h>
#include <psapi.h>
#include <isotream>
#include <vector>
#pragma comment(lib,"psapi.lib")

using namespace std;
vector<Process> ProcessC::collectProcess(){
    vector<Process> processes;
    DWORD processIDs[1024];
    DWORD baitReturned;
    if(!EnumProcesses(processIDs, sizeof(processIDs), &baitReturned)){
        cerr<<"Ошибка при получени списка процессво" <<endl;
        return processes;
    }
    DWORD numProcesses =baitReturned / sizeof(DWORD);

    for (DWORD i = 0; i < numProcesses; i++) {
        if(processIDs[i] !=0){
            Process info = getProcess(processIDs[i]);
            if (info.pid != 0){
                processes.push_back(info);
            }
        }
    }
    return porceeses;
}

PRocess ProcessC::getProcess(DWORD porcessId){
    Process info;

    HANDLE hProcess = OpenPRocess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (hProcess == NULL){
        return info;
    }
    HMODULE hMod;
    DWORD cdNeeded;
    if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cdNeeded)){
        char processName[MAX_PATH];
        GetModuleBaseNameA(hProcess, hMod, processName, sizeof(processName));
        info.name = processName;
    }
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
        info.memoryUsage = pmc.WorkingSetSize;
    }
    info.pid = processID; 
    info.status = "Running";
    CloseHandle(hProcess);
    return info;
}