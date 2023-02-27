//
//  main.cpp
//  PCP-2_05
//
//  Created by Furkan Karagöz on 27.02.2022.
//  Topic:      Thread pool
//  Example:    Copping vegetables with a thread pool
#include <thread>

void vegetable_chopper(int vegetable_id)
{
    printf("Thread %d chopped vegetables %d.\n", std::this_thread::get_id(), vegetable_id);
}

int main()
{
    std::thread choppers[100];
    for (int i = 0; i < 100; ++i)
        choppers[i] = std::thread(vegetable_chopper, i);
    
    for (auto& c : choppers)
        c.join();
}

/* Result:
 Thread 152350720 chopped vegetables 0.
 Thread 154497024 chopped vegetables 4.
 Thread 155570176 chopped vegetables 6.
 Thread 152887296 chopped vegetables 1.
 Thread 156643328 chopped vegetables 8.
 Thread 155033600 chopped vegetables 5.
 ...
 */
