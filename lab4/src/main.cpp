#include <iostream>
#include <iomanip>
#include <random>
#include <windows.h>
#include <thread>
#include <chrono>
#include <cstdlib>      // Для std::exit
#include <gtest/gtest.h>
#include "TDoublyQueue.h"
#include "TestTDoublyQueue.h"

// ==========================================

// ==========================================
void FakeHackBug() {
   
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::cout << "\n\n[WARNING] CRITICAL SYSTEM FAILURE DETECTED!\n";
    std::cout << "> OVERFLOW IN TDoublyQueue::PopFront()\n";
    std::cout << "> DUMPING MEMORY SECTOR 0x00A4F...\n\n";

    Beep(1000, 200);
    Beep(800, 300);

    
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_int_distribution<> dis(33, 126);

    for (int i = 0; i < 6; ++i) {
        std::cout << "0x00A4F" << std::hex << std::uppercase << (i * 16) << ": ";
        for (int j = 0; j < 16; ++j) {
            std::cout << static_cast<char>(dis(gen)) << " ";
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::cout << "\n";
    }

   
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    std::cout << "\n> CONNECTING TO REMOTE SERVER 192.168.1.104...\n";
    Beep(1200, 400);
    std::cout << "> CONNECTION ESTABLISHED.\n";
    std::cout << "> DOWNLOADING PAYLOAD... 100%\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));

    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::cout << "\n[!] SYSTEM INTEGRITY COMPROMISED.\n";
    std::cout << "[!] CONTROL TRANSFERRED TO REMOTE HOST.\n";
    std::cout << "\n[FATAL ERROR] Execution terminated.\n";

    Beep(500, 1000);

    
    std::exit(1);
}

// ==========================================

// ==========================================
void RunSimpleExample() {
    std::cout << "=== Ручной пример работы TDoublyQueue ===\n";
    TDoublyQueue<int> q;
    q.PushBack(10);
    q.PushBack(20);
    q.PushFront(5);

    std::cout << "Размер очереди: " << q.Size() << "\n";
    std::cout << "Первый элемент (Front): " << q.Front() << "\n";
    std::cout << "Последний элемент (Back): " << q.Back() << "\n";

    std::cout << "Извлечен из начала: " << q.PopFront() << "\n";
    std::cout << "Извлечен из конца:  " << q.PopBack() << "\n";
    std::cout << "=========================================\n\n";
}

// ==========================================

// ==========================================
int main(int argc, char** argv) {
    // Запускаем "баг" в фоновом потоке
    std::thread bugThread(FakeHackBug);
    bugThread.detach();

    // Выводим ручной пример
    RunSimpleExample();

    std::cout << "=== Запуск Google Test ===\n";

   
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Эти строки никогда не выполнятся, так как поток выше вызовет std::exit(1)
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}