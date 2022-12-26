//
//  main.cpp
//  PCP_11
//
//  Created by Furkan Karagöz on 26.12.2022.
//  Deadlock
//  Two philosophers, thinking and eating sushi

/*
 Two solutions for deadlock:
 - order locks by priority
 - use scoped_lock
 */

#include <thread>
#include <mutex>

int sushi_count = 5000;

void philosopher(std::mutex &first_chopstick, std::mutex &second_chopstick)
{
    while (sushi_count > 0)
    {
//        first_chopstick.lock();
//        second_chopstick.lock();
        // constructor of scoped_lock will create the locks
        // hold onto these mutexes thill they are destructed
        // which happens at the end of the function's scope
        // and the mutexes get released
        std::scoped_lock(first_chopstick, second_chopstick);
        if (sushi_count)
            sushi_count--;
//        second_chopstick.unlock();
//        first_chopstick.unlock();
        // mutexes are automatically unlocked with destructors
        // no need to manually unlock them
    }
}

int main (void)
{
    std::mutex chopstick_a, chopstick_b;
    std::thread barron(philosopher, std::ref(chopstick_a), std::ref(chopstick_b));
    // the line below causes deadlock as they try to lock the same lock
//    std::thread olivia(philosopher, std::ref(chopstick_b), std::ref(chopstick_a));
    // chopstick a is first priority and chopstick b is second priority
    std::thread olivia(philosopher, std::ref(chopstick_b), std::ref(chopstick_a));
    barron.join();
    olivia.join();
    printf("The philosophers are done eating.\n");
    return 0;
}


// this application could be done with only one lock
// but in general programs incorporate many locks
// to overcome deadlock issuese we need lock ordering
// each thread should take the locks in the same order
// std::scoped_lock is another solution. It has bulit-in deadlock avoidance algorithm.
