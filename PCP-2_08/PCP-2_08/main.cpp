//
//  main.cpp
//  PCP-2_08
//
//  Created by Furkan Karagöz on 27.02.2022.
//  Topic:      Future
//  Example:    Check how many vegetables are in the pantry

#include <future>

int how_many_vegetables()
{
    printf("Olivia is counting vegetables...\n");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 42;
}

int main()
{
    printf("Barron asks Olivia how many vegetables are in the pantry.\n");
    std::future<int> result = std::async(std::launch::async, how_many_vegetables);
    printf("Barron can do other things while he waits for the result...\n");
    // Future's get function will return the result or
    // blocks the execution until the result is ready
    printf("Olivia responded with %d.\n", result.get());
    
    return 0;
}

/* Result:
 Barron asks Olivia how many vegetables are in the pantry.
 Barron can do other things while he waits for the result...
 Olivia is counting vegetables...
 Olivia responded with 42.
 Program ended with exit code: 0
 */
