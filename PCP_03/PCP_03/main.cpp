//
//  main.cpp
//  PCP_03
//
//  Created by Furkan Karagöz on 25.12.2022.
//  Thread life cycle
//  Two threads cooking soup

#include <thread>
#include <chrono>

void chef_olivia ()
{
    printf("Olivia started and waiting for sausage to thaw...\n");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    printf("Olivia is done cutting sausage.\n");
}

int main (void)
{
    printf("Barron requests Olivia's help.\n");
    // in cpp the thread will begin immediately after
    // the thread objects is instantiated
    std::thread olivia(chef_olivia);
    // joinable is the only way in cpp to gather
    // information about the state of the thread
    printf("\tOlivia is joinable? %s\n", olivia.joinable() ? "true" : "false");
    
    printf("Barron continues cooking soup.\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    printf("\tOlivia is joinable? %s\n", olivia.joinable() ? "true" : "false");
    
    printf("Barron patiently waits for Olivia to finish and join...\n");
    olivia.join();
    printf("\tOlivia is joinable? %s\n", olivia.joinable() ? "true" : "false");
    
    printf("Barron and Olivia are both done.\n");
    return 0;
}

/*
 Barron requests Olivia's help.
 Barron continues cooking soup.
 Olivia started and waiting for sausage to thaw...
 Barron patiently waits for Olivia to finish and join...
 Olivia is done cutting sausage.
 Barron and Olivia are both done.
 Program ended with exit code: 0
 */


/*
 Barron requests Olivia's help.
     Olivia is joinable? true
 Barron continues cooking soup.
 Olivia started and waiting for sausage to thaw...
     Olivia is joinable? true
 Barron patiently waits for Olivia to finish and join...
 Olivia is done cutting sausage.
     Olivia is joinable? false
 Barron and Olivia are both done.
 Program ended with exit code: 0
 */
