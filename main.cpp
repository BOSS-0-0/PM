#include "Process.h"
#include "ProcessC.h"
#include "ProcessCon.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>

bool compareByMemory(const Process& a, const Process& b) {
    return a.memoryUse > b.memoryUse;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    ProcessC collector;
    ProcessCon controller;

    int choice;

    do {
        std::cout << "\n=== Менеджер процессов ===" << std::endl;
        std::cout << "1. Показать все процессы" << std::endl;
        std::cout << "2. Показать топ-10 по памяти" << std::endl;
        std::cout << "3. Завершить процесс по PID" << std::endl;
        std::cout << "4. Выйти" << std::endl;
        std::cout << "Выберите действие: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Некорректный ввод" << std::endl;
            continue;
        }

        switch (choice) {
        case 1: {
            std::vector<Process> processes = collector.collectProcesses();
            std::cout << "\nНайдено процессов: " << processes.size() << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            for (const auto& p : processes) {
                p.print();
            }
            break;
        }
        case 2: {
            std::vector<Process> processes = collector.collectProcesses();
            std::sort(processes.begin(), processes.end(), compareByMemory);
            std::cout << "\nТоп-10 процессов по памяти:" << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            int count = std::min(10, static_cast<int>(processes.size()));
            for (int i = 0; i < count; i++) {
                std::cout << (i + 1) << ". ";
                processes[i].print();
            }
            break;
        }
        case 3: {
            DWORD pid;
            std::cout << "Введите PID: ";
            if (std::cin >> pid) {
                int confirm;
                std::cout << "Вы уверены? (1 - да, 0 - нет): ";
                std::cin >> confirm;
                if (confirm == 1) {
                    controller.terminateProcess(pid);
                } else {
                    std::cout << "Отменено" << std::endl;
                }
            } else {
                std::cout << "Некорректный PID" << std::endl;
            }
            break;
        }
        case 4:
            std::cout << "Выход..." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор" << std::endl;
        }
    } while (choice != 4);

    return 0;
}