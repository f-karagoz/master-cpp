//
//  main.cpp
//  PCP-2_01
//
//  Created by Furkan Karagöz on 02.02.2022.
//  Topic:      Condition Variable
//  Example:    Two hungry threads, anxiously waiting for their turn to take soup

#include <thread>
#include <queue>

class ServingLine
{
public:
    void serve_soup(int i)
    {
        soup_queue.push(i);
    }
    
    int take_soup(void)
    {
        int bowl = soup_queue.front();
        soup_queue.pop();
        return bowl;
    }
    
private:
    std::queue<int> soup_queue;
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

/* C++ library is not thread safe:
 exit;
 zsh: segmentation fault
 */
