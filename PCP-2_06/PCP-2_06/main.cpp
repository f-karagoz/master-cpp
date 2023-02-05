//
//  main.cpp
//  PCP-2_05
//
//  Created by Furkan Karagöz on 05.02.2022.
//  Topic:      Barrier
//  Example:    Deciding how many bags of chips to buy for the party
//                  Olivia threads do their addition first, then barron threads multiply

#include <thread>
#include <mutex>
#include <latch>

unsigned int bags_of_chips = 1;     // Start with one bag on the list
std::mutex pencil;
// Constructer #threads need to wait at the barrier before release
// There are 5 olivia threads need to be executed first
std::latch fist_bump(5);


void cpu_work(unsigned long workUnits)
{
    unsigned long x = 0;
    for (unsigned long i = 0; i < workUnits * 1000000; ++i)
        x++;
    return;
}

void barron_shopper()
{
    cpu_work(1);                    // do a bit of work fist
    fist_bump.wait();               // Latched. Wait till counter reaches zero.
    std::scoped_lock<std::mutex> lock(pencil);
    bags_of_chips *= 2;
    printf("Barron DOUBLED bags of chips.\n");
}

void olivia_shopper()
{
    cpu_work(1);                    // do a bit of work fist
    {
        std::scoped_lock<std::mutex> lock(pencil);  // Lock is scoped to critical section
        bags_of_chips += 3;
    }
    printf("Olivia ADDED 3 bags of chips.\n");
    fist_bump.count_down();          // Decrease latch value
}

int main (void)
{
    std::thread shoppers[10];
    for (int i = 0; i < 10; i+=2)
    {
        shoppers[i] = std::thread(barron_shopper);
        shoppers[i+1] = std::thread(olivia_shopper);
    }
    
    for (auto& s : shoppers)
        s.join();
    
    printf("We need to buy %u bags of chips.\n", bags_of_chips);
    
    return 0;
}

/* RESULT: (same result different mechanism)
 Olivia ADDED 3 bags of chips.
 Olivia ADDED 3 bags of chips.
 Olivia ADDED 3 bags of chips.
 Olivia ADDED 3 bags of chips.
 Olivia ADDED 3 bags of chips.
 Barron DOUBLED bags of chips.
 Barron DOUBLED bags of chips.
 Barron DOUBLED bags of chips.
 Barron DOUBLED bags of chips.
 Barron DOUBLED bags of chips.
 We need to buy 512 bags of chips.
 Program ended with exit code: 0
 */
