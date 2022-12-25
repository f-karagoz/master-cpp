//
//  main.cpp
//  PCP_04
//
//  Created by Furkan Karagöz on 25.12.2022.
//  Detached thread
//  Barron finishes cooking while Olivia cleans

#include <thread>
#include <chrono>

void kitchen_cleaner()
{
    while (true)
    {
        printf("Olivia cleaned the kitchen.\n");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(void)
{
    std::thread olivia(kitchen_cleaner);
    olivia.detach();
    
    for (int i = 0; i < 3; ++i)
    {
        printf("Barron is cooking...\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }
    
    printf("Barron is done!\n");
//    olivia.join();
    
    return 0;
}

// no detached thread
/*
 Barron is cooking...
 Olivia cleaned the kitchen.
 Barron is cooking...
 Olivia cleaned the kitchen.
 Barron is cooking...
 Barron is done!
 Olivia cleaned the kitchen.
 Olivia cleaned the kitchen.
 Olivia cleaned the kitchen.
 Olivia cleaned the kitchen.
 Olivia cleaned the kitchen.
 Olivia cleaned the kitchen.
 Olivia cleaned the kitchen.
 Program ended with exit code: 9
 */

// If the child thread is deatched
// the child thread is for sure to be terminated
// after the parent thread is terminated

/* Detached thread
 Barron is cooking...
 Olivia cleaned the kitchen.
 Barron is cooking...
 Olivia cleaned the kitchen.
 Barron is cooking...
 Barron is done!
 Program ended with exit code: 0
 */
