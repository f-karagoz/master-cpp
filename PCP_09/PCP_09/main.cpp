//
//  main.cpp
//  PCP_08
//
//  Created by Furkan Karagöz on 26.12.2022.
//  Try lock
//  Two shoppers adding items to a shared notepad

#include <thread>
#include <mutex>
#include <chrono>

unsigned items_on_notepad = 0;
std::mutex pencil;

void shopper(const char* name)
{
    int items_to_add = 0;
    while (items_on_notepad <= 20)
    {
        // add item(s) to shared items_on_notepad
        // left side of the if statement will be executed first
        if (items_to_add && pencil.try_lock())
        {
//            pencil.lock();
            items_on_notepad += items_to_add;
            printf("%s added %u item(s) to notepad.\n", name, items_to_add);
            items_to_add = 0;
            // intended time spent writing is 300 ms
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            pencil.unlock();
        }
        else
        {
            // intended time spent searching
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            items_to_add++;
            printf("%s found something else to buy.\n", name);
        }
    }
}

int main (void)
{
    auto start_time = std::chrono::steady_clock::now();
    std::thread barron(shopper, "Barron");
    std::thread olivia(shopper, "Olivia");
    barron.join();
    olivia.join();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count();
    printf("Elapsed Time: %.2f seconds\n", elapsed_time/1000.0);
    
    return 0;
}


/*
 Olivia found something else to buy.
 Olivia added 1 item(s) to notepad.
 Barron found something else to buy.
 Barron added 1 item(s) to notepad.
 Olivia found something else to buy.
 Olivia added 1 item(s) to notepad.
 Barron found something else to buy.
 Barron added 1 item(s) to notepad.
 Olivia found something else to buy.
 Olivia added 1 item(s) to notepad.
 Barron found something else to buy.
 Barron added 1 item(s) to notepad.
 Olivia found something else to buy.
 Olivia added 1 item(s) to notepad.
 Barron found something else to buy.
 Barron added 1 item(s) to notepad.
 Olivia found something else to buy.
 Olivia added 1 item(s) to notepad.
 Barron found something else to buy.
 Barron added 1 item(s) to notepad.
 Olivia found something else to buy.
 Olivia added 1 item(s) to notepad.
 Barron found something else to buy.
 Barron added 1 item(s) to notepad.
 Olivia found something else to buy.
 Olivia added 1 item(s) to notepad.
 Barron found something else to buy.
 Barron added 1 item(s) to notepad.
 Olivia found something else to buy.
 Olivia added 1 item(s) to notepad.
 Barron found something else to buy.
 Barron added 1 item(s) to notepad.
 Olivia found something else to buy.
 Olivia added 1 item(s) to notepad.
 Barron found something else to buy.
 Barron added 1 item(s) to notepad.
 Olivia found something else to buy.
 Olivia added 1 item(s) to notepad.
 Barron found something else to buy.
 Barron added 1 item(s) to notepad.
 Olivia found something else to buy.
 Olivia added 1 item(s) to notepad.
 Barron found something else to buy.
 Elapsed Time: 6.46 seconds
 */


/*
 Olivia found something else to buy.
 Olivia added 1 item(s) to notepad.
 Barron found something else to buy.
 Barron found something else to buy.
 Barron found something else to buy.
 Barron found something else to buy.
 Barron added 4 item(s) to notepad.
 Olivia found something else to buy.
 Olivia found something else to buy.
 Olivia found something else to buy.
 Olivia found something else to buy.
 Olivia added 4 item(s) to notepad.
 Barron found something else to buy.
 Barron found something else to buy.
 Barron found something else to buy.
 Barron found something else to buy.
 Barron added 4 item(s) to notepad.
 Olivia found something else to buy.
 Olivia found something else to buy.
 Olivia found something else to buy.
 Olivia found something else to buy.
 Olivia added 4 item(s) to notepad.
 Barron found something else to buy.
 Barron found something else to buy.
 Barron found something else to buy.
 Barron found something else to buy.
 Barron added 4 item(s) to notepad.
 Olivia found something else to buy.
 Elapsed Time: 2.14 seconds
 Program ended with exit code: 0
 */
