//
//  main.cpp
//  PCP-2_01
//
//  Created by Furkan Karagöz on 02.02.2022.
//  Topic:      Condition Variable
//  Example:    Two hungry threads, anxiously waiting for their turn to take soup

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

class ServingLine
{
public:
    void serve_soup(int i)
    {
        std::unique_lock<std::mutex> ladle_lock(ladle);
        soup_queue.push(i);
        ladle_lock.unlock();
        soup_served.notify_one();
    }
    
    int take_soup(void)
    {
        std::unique_lock<std::mutex> ladle_lock(ladle);
        while (soup_queue.empty())
        {
            // Release the ladle_lock and wait here
            // until a procuder thread adds a soup and releases the ladle_lock
            soup_served.wait(ladle_lock);   // Condition variable only accepts unique lock
        }
        int bowl = soup_queue.front();
        soup_queue.pop();
        return bowl;
    }
    
private:
    std::queue<int> soup_queue;
    std::mutex ladle;
    std::condition_variable soup_served;
};

ServingLine serving_line = ServingLine();

void soup_procuder(void)
{
    for (int i = 0; i < 10000; ++i)
    {
        serving_line.serve_soup(1);     // serve 10,000 bowls of soup
    }
    serving_line.serve_soup(-1);        // indicare no more soup
    printf("Producer done serving soup!\n");
}

void soup_consumer(void)
{
    int soup_eaten = 0;
    while (true)
    {
        int bowl = serving_line.take_soup();
        if (bowl == -1)                 // check for last soup
        {
            printf("Consumer ate %d bowls of soup.\n", soup_eaten);
            serving_line.serve_soup(-1);    // put back last soup for another consumer
            return;
        }
        else
        {
            soup_eaten += bowl;         // eat the soup
        }
    }
}

int main (void)
{
    std::thread olivia(soup_procuder);
    std::thread barron(soup_consumer);
    std::thread steve(soup_consumer);
    
    olivia.join();
    barron.join();
    steve.join();
    
    return 0;
}

/* RESULT: C++ library is not thread safe:
 exit;
 zsh: segmentation fault
 */

/* RESULT: After implementing condition variable and mutex, total of 10k soup consumed
 Producer done serving soup!
 Consumer ate 4672 bowls of soup.
 Consumer ate 5328 bowls of soup.
 Program ended with exit code: 0
 */

// By default C++ queue is not multi-thread safe.
// We can implement out own solution depending on the schenario.
// When Creating as single thread application queue's simplicity
// prevents the unnecessaty overhead.
// Check: boost::lockfree::queue for thread sage queue
