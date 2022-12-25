/**
 * Threads that waste CPU cycles
 * Every operating system have their own way of implementing threads
 * As we use standard library of c++ our program should be portable
 */
#include <thread>
#include <chrono>
#include <unistd.h>

// a simple function that wastes CPU cycles "forever"
void cpu_waster() {
    printf("CPU Waster Process ID: %d\n", getpid());
    printf("CPU Waster Thread ID %d\n", std::this_thread::get_id());
    while(true) continue;
}

int main() {
    printf("Main Process ID: %d\n", getpid());
    printf("Main Thread ID: %d\n", std::this_thread::get_id());
    std::thread thread1(cpu_waster);
    std::thread thread2(cpu_waster);

    while(true) { // keep the main thread alive "forever"
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

/*
 Main Process ID: 68989
 Main Thread ID: 640512
 CPU Waster Process ID: 68989
 CPU Waster Process ID: 68989
 CPU Waster Thread ID 21823488
 CPU Waster Thread ID 22360064
*/


