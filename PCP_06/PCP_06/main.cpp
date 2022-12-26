//
//  main.cpp
//  PCP_05
//
//  Created by Furkan Karagöz on 25.12.2022.
//  Data race
//  Two shoppers adding items to a shared notepad

#include <thread>
#include <mutex>
#include <chrono>

unsigned garlic_count = 0;
std::mutex pencil;          // mutex created


void shopper()
{
    for (int i=0; i<5; ++i)
    {
        printf("Shopper %d is thinking...\n", std::this_thread::get_id());
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        // we only need to protect the critical section of the code
        // which accesses the memory
        pencil.lock();
        garlic_count++;
        pencil.unlock();
    }
}

int main (void)
{
    std::thread barron(shopper);
    std::thread olivia(shopper);
    barron.join();
    olivia.join();
    printf("We should buy %u garlic\n", garlic_count);
    return 0;
}

/*
 Shopper 125042688 is thinking...
 Shopper 125042688 is thinking...
 Shopper 125042688 is thinking...
 Shopper 125042688 is thinking...
 Shopper 125042688 is thinking...
 Shopper 124506112 is thinking...
 Shopper 124506112 is thinking...
 Shopper 124506112 is thinking...
 Shopper 124506112 is thinking...
 Shopper 124506112 is thinking...
 We should buy 10 garlic
 Program ended with exit code: 0
 */

/*
 Shopper 115671040 is thinking...
 Shopper 116207616 is thinking...
 Shopper 115671040 is thinking...
 Shopper 116207616 is thinking...
 Shopper 115671040 is thinking...
 Shopper 116207616 is thinking...
 Shopper 116207616 is thinking...
 Shopper 115671040 is thinking...
 Shopper 116207616 is thinking...
 Shopper 115671040 is thinking...
 We should buy 10 garlic
 Program ended with exit code: 0
 */
