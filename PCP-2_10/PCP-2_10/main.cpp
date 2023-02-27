//
//  main.cpp
//  PCP-2_10
//
//  Created by Furkan Karagöz on 27.02.2022.
//  Topic:      Measure speedup
//  Example:    Recursively sum range of numbers - sequential vs parallel

#include <future>
#include <chrono>

unsigned long long sequential_sum(unsigned int lo, unsigned int hi)
{
    unsigned long long sum = 0;
    for (auto i=lo; i<hi; ++i)
        sum += i;
    return sum;
}

unsigned long long parallel_sum(unsigned int lo, unsigned int hi, unsigned int depth=0)
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
        auto left = std::async(std::launch::async, parallel_sum, lo, mid, depth+1);
        auto right = parallel_sum(mid, hi, depth+1);
        return left.get() + right;
    }
}

int main ()
{
    const int NUM_EVAL_RUNS = 10;
    const int SUM_VALUE = 100000;    // 100 mil
    
    printf("Evaluating Sequential Implementation...\n");
    std::chrono::duration<double> sequential_time(0);
    auto sequential_result = sequential_sum(0, SUM_VALUE);  // warm-up
    for(int i=0; i<NUM_EVAL_RUNS; ++i)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        sequential_sum(0, SUM_VALUE);
        sequential_time += std::chrono::high_resolution_clock::now() - start_time;
    }
    sequential_time /= NUM_EVAL_RUNS;
    
    printf("Evaluating Parallel Implementation...\n");
    std::chrono::duration<double> parallel_time(0);
    auto parallel_result = parallel_sum(0, SUM_VALUE);  // warm-up
    for(int i=0; i<NUM_EVAL_RUNS; ++i)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        parallel_sum(0, SUM_VALUE);
        parallel_time += std::chrono::high_resolution_clock::now() - start_time;
    }
    parallel_time /= NUM_EVAL_RUNS;
    
    // Display sequential and parallel run results for comparison
    if (sequential_result != parallel_result)
        printf("ERROR: Result mismatch!\n Sequential Result = %lld\n"
               " Parallel Result = %lld\n", sequential_result, parallel_result);
    printf("Average Sequential Time: %.1f ms\n", sequential_time.count()*1000);
    printf("  Average Parallel Time: %.1f ms\n", parallel_time.count()*1000);
    printf("Speedup: %.2f\n", sequential_time/parallel_time);
    printf("Efficiency %.2f%%\n", 100*(sequential_time/parallel_time)
           / std::thread::hardware_concurrency());
}

/* Result-1 - 100 mil SUM_VALUE:
 Evaluating Sequential Implementation...
 Evaluating Parallel Implementation...
 Average Sequential Time: 258.4 ms
   Average Parallel Time: 63.7 ms
 Speedup: 4.06
 Efficiency 50.72%
 */

/* Result-2 - 100k SUM_VALUE:
 Evaluating Sequential Implementation...
 Evaluating Parallel Implementation...
 Average Sequential Time: 0.3 ms
   Average Parallel Time: 0.3 ms
 Speedup: 0.77
 Efficiency 9.56%
 */

// The parallel program becomes less efficient than the sequential olgorithm
// This is due to the additional overhead needed to span multiple threads
