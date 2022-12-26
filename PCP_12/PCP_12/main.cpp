//
//  main.cpp
//  PCP_12
//
//  Created by Furkan Karagöz on 26.12.2022.
//  Abandoned lock
//  Two philosophers, thinking and eating sushi

#include <thread>
#include <mutex>

int sushi_count = 5000;

void philosopher(std::mutex &chopsticks)
{
    while (sushi_count > 0)
    {
//        chopsticks.lock();
        std::scoped_lock lock(chopsticks);
        if (sushi_count)
            sushi_count--;
        if (sushi_count == 10)
        {
            printf("This philosopher has had enough!\n");
            break;          // will break out of the loop without unlocking the mutex
            // scoped lock destructor unlocks
        }
//        chopsticks.unlock();
    }
}

int main (void)
{
    std::mutex chopsticks;
    std::thread barron(philosopher, std::ref(chopsticks));
    std::thread olivia(philosopher, std::ref(chopsticks));
    barron.join();
    olivia.join();
    printf("The philosophers are done eating.\n");
    return 0;
}

/* PROGRAM OUTPUT:
 This philosopher has had enough!
 The philosophers are done eating.
 Program ended with exit code: 0
 */
