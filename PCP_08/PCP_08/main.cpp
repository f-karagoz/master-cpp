//
//  main.cpp
//  PCP_08
//
//  Created by Furkan Karagöz on 26.12.2022.
//  Recursive mutex
//  Two shoppers adding garlic and potatoes to a shared notepad

#include <thread>
#include <mutex>

unsigned garlic_count = 0;
unsigned potato_count = 0;
// recursive mutex allows multiple locks to be put on the same mutex
// to unlock the mutex we need to unlock it the number of times locked
std::recursive_mutex pencil;

void add_garlic()
{
    pencil.lock();
    garlic_count++;
    pencil.unlock();
}

void add_potato()
{
    pencil.lock();
    potato_count++;
    add_garlic();           // mutex locked and unlocked multiple times
    pencil.unlock();
}

void shopper()
{
    for (int i = 0; i < 10000; ++i)
    {
        add_garlic();
        add_potato();
    }
}

int main (void)
{
    std::thread barron(shopper);
    std::thread olivia(shopper);
    barron.join();
    olivia.join();
    printf("We should buy %u garlic.\n", garlic_count);
    printf("We should buy %u potatoes.\n", potato_count);
    return 0;
}

/* PROGRAM OUTPUT:
 We should buy 40000 garlic.
 We should buy 20000 potatoes.
 Program ended with exit code: 0
 */
