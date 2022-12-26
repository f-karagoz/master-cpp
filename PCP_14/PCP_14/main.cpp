//
//  main.cpp
//  PCP_14
//
//  Created by Furkan Karagöz on 26.12.2022.
//  Livelock
//  Two philosophers, thinking and eating sushi

#include <thread>
#include <mutex>

int sushi_count = 5000;

void philosopher(std::mutex &first_chopstick, std::mutex &second_chopstick)
{
    while (sushi_count > 0)
    {
        first_chopstick.lock();
        if (!second_chopstick.try_lock())
        {
            // second is already lock. unlock the first one.
            first_chopstick.unlock();
            std::this_thread::yield(); // will reschedule the thread
        }
        else
        {
            if (sushi_count)
                sushi_count--;
            second_chopstick.unlock();
            first_chopstick.unlock();
        }
    }
}

int main (void)
{
    std::mutex chopstick_a, chopstick_b;
    std::thread barron(philosopher, std::ref(chopstick_a), std::ref(chopstick_b));
    std::thread olivia(philosopher, std::ref(chopstick_b), std::ref(chopstick_a));
    std::thread steve(philosopher, std::ref(chopstick_a), std::ref(chopstick_b));
    std::thread nikki(philosopher, std::ref(chopstick_b), std::ref(chopstick_a));
    barron.join();
    olivia.join();
    steve.join();
    nikki.join();
    printf("The philosophers are done eating.\n");
    return 0;
}

// std::this_thread::yield will reschedule the thread opeartion
// to allow other threads to run

/* PROGRAM OUTPUT:
 The philosophers are done eating.
 Program ended with exit code: 0
 */
