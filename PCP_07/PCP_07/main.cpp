//
//  main.cpp
//  PCP_05
//
//  Created by Furkan Karagöz on 25.12.2022.
//  Data race
//  Two shoppers adding items to a shared notepad
// simpler solution for this problem is atomic types
// encapsulates a value and synchonizes access to it
// prevents data race

#include <thread>
#include <atomic>

std::atomic<unsigned> garlic_count(0);

void shopper()
{
    for (int i=0; i<10000000; ++i)
        garlic_count++;
}

int main (void)
{
    std::thread barron(shopper);
    std::thread olivia(shopper);
    barron.join();
    olivia.join();
    printf("We should buy %u garlic\n", garlic_count.load());
    return 0;
}

/* PROGRAM OUTPUT:
 We should buy 20000000 garlic
 Program ended with exit code: 0
 */

/* Cpp Reference:
 Each instantiation and full specialization of the std::atomic template defines an atomic type. If one thread writes to an atomic object while another thread reads from it, the behavior is well-defined (see memory model for details on data races).

 In addition, accesses to atomic objects may establish inter-thread synchronization and order non-atomic memory accesses as specified by std::memory_order.

 std::atomic is neither copyable nor movable.
 */
