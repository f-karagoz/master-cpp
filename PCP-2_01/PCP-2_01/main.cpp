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

int soup_servings = 10;
std::mutex show_cooker_lid;

void hungry_person(int id)
{
    int put_lid_back = 0;       // to track n times lid put back
    while (soup_servings > 0)
    {
        //v pick up the slow cooker lid
        std::unique_lock<std::mutex> lid_lock(show_cooker_lid);
        //v is it your turn to take the soup?
        if ((id == soup_servings % 2) && (soup_servings > 0))
        {
            soup_servings--;    // it's your turn take soup:
        }
        else
        {
            // it's not your turn. put lid back.
            put_lid_back++;
        }
    }
    printf("Person %d put the lid back %u times.\n", id, put_lid_back);
}

int main (void)
{
    std::thread hungry_threads[2];
    
    for (int i=0; i < 2; ++i)
        hungry_threads[i] = std::thread(hungry_person, i);
        
    for (auto& ht : hungry_threads)
        ht.join();
    
    return 0;
}

/* OUTPUT: without condition vaiable
 Person 0 put the lid back 1401 times.
 Person 1 put the lid back 1162 times.
 Program ended with exit code: 0
 */
