//
//  main.cpp
//  PCP_05
//
//  Created by Furkan Karagöz on 25.12.2022.
//  Data race
//  Two shoppers adding items to a shared notepad

/*
 Computer is performing 3 step READ MODIFY WRITE operation
 for each inrementation. Sometimes the thread state is changed when this
 incrementation operation is not finished
 Deatecting data race is hard job
 */

#include <thread>

unsigned garlic_count = 0;

void shopper()
{
//    for (int i=0; i<10; ++i)
    for (int i=0; i<10000000; ++i)
        garlic_count++;
}

int main (void)
{
    std::thread barron(shopper);
    std::thread olivia(shopper);
    barron.join();
    olivia.join();
    printf("We should buy %u garlic\n", garlic_count);
    return 0;
}

/*
 We should buy 20 garlic
 Program ended with exit code: 0
 */

/*
 We should buy 10371184 garlic
 Program ended with exit code: 0
 */

/*
 We should buy 9914688 garlic
 Program ended with exit code: 0
 */
