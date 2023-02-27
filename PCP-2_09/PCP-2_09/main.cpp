//
//  main.cpp
//  PCP-2_09
//
//  Created by Furkan Karagöz on 27.02.2022.
//  Topic:      Divide an conquer
//  Example:    Recursively sum range of numbers
#include <cstdio>

unsigned long long recursive_sum(unsigned int lo, unsigned int hi)
{
    if (hi - lo <= 100) // base case threshold
    {
        unsigned long long sum = 0;
        for (auto i=lo; i<hi; ++i)
            sum += i;
        return sum;
    }
    else    // divide and conquer
    {
        auto mid = (hi + lo) / 2;
        auto left = recursive_sum(lo, mid);
        auto right = recursive_sum(mid, hi);
        return left + right;
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
