//
//  main.cpp
//  PCP-2_09
//
//  Created by Furkan Karagöz on 27.02.2022.
//  Topic:      Divide an conquer
//  Example:    Recursively sum range of numbers

#include <cstdio>
#include <future>

unsigned long long recursive_sum(unsigned int lo, unsigned int hi, unsigned int depth=0)
{
    if (depth > 3) // base case threshold
    {
        unsigned long long sum = 0;
        for (auto i=lo; i<hi; ++i)
            sum += i;
        return sum;
    }
    else    // divide and conquer
    {
        auto mid = (hi + lo) / 2;
        auto left = std::async(std::launch::async, recursive_sum, lo, mid, depth+1);
        auto right = recursive_sum(mid, hi, depth+1);
        return left.get() + right;
    }
}

int main ()
{
    unsigned long long total = recursive_sum(0, 1000000000);
    printf("Total: %llu\n", total);
}

/* Result-1:
 Total: 499999999500000000
 Program ended with exit code: 0
 */

/* Result-2:
 Total: 499999999500000000
 Program ended with exit code: 0
 */

// We have limited the number threads can be createad with 'depth' variable
// When we pass the depth of 3 we sum the numbers
// Therefore divide the problem to depth of 3 at max
