//
//  main.cpp
//  PCP-2_01
//
//  Created by Furkan Karagöz on 02.02.2022.
//  Topic:      Condition Variable
//  Example:    Two hungry threads, anxiously waiting for their turn to take soup

//#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int soup_servings = 10;
std::mutex show_cooker_lid;
std::condition_variable soup_taken;

void hungry_person(int id)
{
    int put_lid_back = 0;                   // to track n times lid put back
    while (soup_servings > 0)
    {
        //v pick up the slow cooker lid
        std::unique_lock<std::mutex> lid_lock(show_cooker_lid);
        //v is it NOT your turn to take the soup?
        if ((id != soup_servings % 5) && (soup_servings > 0))
        {
            put_lid_back++;                 // Tracks the number of times waited for lock to be released
            soup_taken.wait(lid_lock);      // We pass the lock to the conditional vaiable
        }
        if (soup_servings > 0 )
        {
            soup_servings--;                // it's your turn take soup:
            lid_lock.unlock();
            soup_taken.notify_all();        // Operation finished. Wakes up other thread.
        }
    }
    printf("Person %d put the lid back %u times.\n", id, put_lid_back);
}

int main (void)
{
    std::thread hungry_threads[5];
    
    for (int i=0; i < 5; ++i)
        hungry_threads[i] = std::thread(hungry_person, i);
        
    for (auto& ht : hungry_threads)
        ht.join();
    
    return 0;
}

/* OUTPUT: without condition vaiable (2 threads)
 Person 0 put the lid back 1401 times.
 Person 1 put the lid back 1162 times.
 Program ended with exit code: 0
 */

/* OUTOUT: with condition variables (2 threads)
 Person 1 put the lid back 4 times.
 Person 0 put the lid back 5 times.
 Program ended with exit code: 0
 */

/* OUTOUT: with condition variables (5 threads)
 Person 0 put the lid back 2 times.
 Person 2 put the lid back 2 times.
 Person 1 put the lid back 3 times.
 Person 4 put the lid back 1 times.
 Person 3 put the lid back 3 times.
 Program ended with exit code: 0
 */
