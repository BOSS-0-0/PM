#ifndef PROCESS_CONTROLLER_H
#define  PROCESS_CONTROLLER_H
#include <windows.h>

class ProcessCon{
    public:
    bool terminateProcess(DWORD processID);
    bool suspendProcess(DWORD processID);

};
#endif