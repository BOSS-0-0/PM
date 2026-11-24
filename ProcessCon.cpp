#include "ProcessCon.h"
#include <windows.h>
#include <iostream>

bool ProcessCon::terminateProcess(DWORD processID) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processID);
    if (hProcess == NULL) {
        std::cerr << "Не удалось открыть процесс с PID " << processID << std::endl;
        return false;
    }
    
    bool success = TerminateProcess(hProcess, 0);
    if (success) {
        std::cout << "Процесс " << processID << " успешно завершен" << std::endl;
    } else {
        std::cerr << "Ошибка при завершении процесса" << std::endl;
    }

    CloseHandle(hProcess);
    return success;
}
bool ProcessCon::suspendProcess(DWORD processID) {
    std::cout << "Приостановка процессов требует дополнительных прав" << std::endl;
    return false;
}