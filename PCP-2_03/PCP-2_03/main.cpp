//
//  main.cpp
//  PCP-2_03
//
//  Created by Furkan Karagöz on 05.02.2022.
//  Topic:      Smaphore
//  Example:    10 phones getting charged on 4 ports

#include <thread>
#include <semaphore>        // C++20
#include <chrono>

std::counting_semaphore<4> charger(4);

void cell_phone (int id)
{
    charger.acquire();
    printf("Phone %d is charging...\n", id);
    srand(id);              // Random time to charge
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000 + 1000));
    printf("Phone %d DONE charging!\n", id);
    charger.release();
}

int main (void)
{
    std::thread phones[10];
    for (int i = 0; i < 10; ++i)
        phones[i] = std::thread(cell_phone, i);
    for (auto& p : phones)
        p.join();
    return 0;
}

/* OUTPUT:
 Phone 0 is charging...
 Phone 2 is charging...
 Phone 1 is charging...
 Phone 3 is charging...
 Phone 3 DONE charging!
 Phone 8 is charging...
 Phone 1 DONE charging!
 Phone 7 is charging...
 Phone 0 DONE charging!
 Phone 9 is charging...
 Phone 2 DONE charging!
 Phone 4 is charging...
 Phone 8 DONE charging!
 Phone 6 is charging...
 Phone 9 DONE charging!
 Phone 5 is charging...
 Phone 7 DONE charging!
 Phone 6 DONE charging!
 Phone 4 DONE charging!
 Phone 5 DONE charging!
 Program ended with exit code: 0
 */
