//  main.cpp
//  PCP_02
//
//  Created by Furkan Karagöz on 25.12.2022.
//
//  Execution Scheduling demo
//      Two threds chopping vegetables

#include <thread>
#include <chrono>

bool chopping = true;

void vegetable_chopper(const char* name)
{
    unsigned vegetable_count = 0;
    while (chopping)
        vegetable_count++;
    printf("%s chopped %u vegetables.\n", name, vegetable_count);
}

int main (void)
{
    std::thread olivia(vegetable_chopper, "Olivia");
    std::thread barron(vegetable_chopper, "Barron");
    
    printf("Barron and Olivia are chopping vegetables...\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    chopping = false;
    barron.join();
    olivia.join();
    return 0;
}

// Scheduling differs from run to run.
// So programs should not be relying on the scheduler for correntness.
/*
 Barron and Olivia are chopping vegetables...
 Olivia chopped 453979077 vegetables.
 Barron chopped 455196076 vegetables.
 Program ended with exit code: 0
 */
/*
 Barron and Olivia are chopping vegetables...
 Olivia chopped 460289300 vegetables.
 Barron chopped 459173854 vegetables.
 Program ended with exit code: 0
 */
