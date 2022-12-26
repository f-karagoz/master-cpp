//
//  main.cpp
//  PCP_08
//
//  Created by Furkan Karagöz on 26.12.2022.
//  Shared mutex
//  Several users reading a callender, but only few users updating it

#include <thread>
#include <mutex>
#include <chrono>
#include <array>
#include <shared_mutex>     // requires c++17

char WEEKDAYS[7][10] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
int today = 0;
//std::mutex marker;
std::shared_mutex marker;

void calender_reader(const int id)
{
    for (int i = 0; i < 7; i++)
    {
//        marker.lock();
        marker.lock_shared();
        printf("Reader-%d sees today is %s\n", id, WEEKDAYS[today]);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//        marker.unlock();
        marker.unlock_shared();
    }
}

void calender_writer(const int id)
{
    for (int i = 0; i < 7; i++)
    {
        marker.lock();
        today = (today + 1) % 7;
        printf("Writer-%d updated date to %s\n", id, WEEKDAYS[today]);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        marker.unlock();
    }
}

int main ()
{
    // use for loop to create 10 reader thred and 2 writer thread
    std::array<std::thread, 10> readers;
    for (unsigned i = 0; i < readers.size(); ++i)
        readers[i] = std::thread(calender_reader, i);
    
    std::array<std::thread, 2> writers;
    for (unsigned i = 0; i < writers.size(); ++i)
        writers[i] = std::thread(calender_writer, i);
    
    // wait for reader and writers to join
    for (unsigned i = 0; i < readers.size(); ++i)
        readers[i].join();
    
    for (unsigned i = 0; i < writers.size(); ++i)
        writers[i].join();
    
    return 0;
}

/* Cpp Reference: std::shared_mutex
 The shared_mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads. In contrast to other mutex types which facilitate exclusive access, a shared_mutex has two levels of access:

 shared - several threads can share ownership of the same mutex.
 exclusive - only one thread can own the mutex.
 */

// readers read the same value till a writer comes and changes it
/* PROGRAM OUTPUT: (without shared mutex)
 Reader-0 sees today is Sunday
 Reader-0 sees today is Sunday
 Reader-0 sees today is Sunday
 Reader-0 sees today is Sunday
 Reader-0 sees today is Sunday
 Reader-0 sees today is Sunday
 Reader-0 sees today is Sunday
 Reader-7 sees today is Sunday
 Reader-8 sees today is Sunday
 Reader-8 sees today is Sunday
 Reader-8 sees today is Sunday
 Reader-8 sees today is Sunday
 Reader-8 sees today is Sunday
 Reader-8 sees today is Sunday
 Reader-8 sees today is Sunday
 Reader-4 sees today is Sunday
 Reader-4 sees today is Sunday
 Reader-4 sees today is Sunday
 Reader-4 sees today is Sunday
 Reader-4 sees today is Sunday
 Reader-4 sees today is Sunday
 Reader-4 sees today is Sunday
 Reader-2 sees today is Sunday
 Reader-2 sees today is Sunday
 Reader-2 sees today is Sunday
 Reader-2 sees today is Sunday
 Reader-2 sees today is Sunday
 Reader-2 sees today is Sunday
 Reader-2 sees today is Sunday
 Writer-0 updated date to Monday
 Writer-0 updated date to Tuesday
 Writer-0 updated date to Wednesday
 Writer-0 updated date to Thursday
 Writer-0 updated date to Friday
 Writer-0 updated date to Saturday
 Reader-7 sees today is Saturday
 Reader-7 sees today is Saturday
 Reader-7 sees today is Saturday
 Reader-7 sees today is Saturday
 Reader-7 sees today is Saturday
 Reader-7 sees today is Saturday
 Reader-6 sees today is Saturday
 Reader-6 sees today is Saturday
 Reader-6 sees today is Saturday
 Reader-6 sees today is Saturday
 Reader-6 sees today is Saturday
 Reader-6 sees today is Saturday
 Reader-6 sees today is Saturday
 Writer-0 updated date to Sunday
 Reader-9 sees today is Sunday
 Reader-9 sees today is Sunday
 Reader-9 sees today is Sunday
 Reader-9 sees today is Sunday
 Reader-9 sees today is Sunday
 Reader-9 sees today is Sunday
 Reader-9 sees today is Sunday
 Reader-3 sees today is Sunday
 Reader-3 sees today is Sunday
 Reader-3 sees today is Sunday
 Reader-3 sees today is Sunday
 Reader-3 sees today is Sunday
 Reader-3 sees today is Sunday
 Reader-3 sees today is Sunday
 Reader-5 sees today is Sunday
 Reader-5 sees today is Sunday
 Reader-5 sees today is Sunday
 Reader-5 sees today is Sunday
 Reader-5 sees today is Sunday
 Reader-5 sees today is Sunday
 Reader-5 sees today is Sunday
 Writer-1 updated date to Monday
 Writer-1 updated date to Tuesday
 Writer-1 updated date to Wednesday
 Writer-1 updated date to Thursday
 Writer-1 updated date to Friday
 Writer-1 updated date to Saturday
 Writer-1 updated date to Sunday
 Reader-1 sees today is Sunday
 Reader-1 sees today is Sunday
 Reader-1 sees today is Sunday
 Reader-1 sees today is Sunday
 Reader-1 sees today is Sunday
 Reader-1 sees today is Sunday
 Reader-1 sees today is Sunday
 Program ended with exit code: 0
 */

// reader does not lock up
// program finished much quicker
/* PROGRAM OUTPUT: (with shared mutex)
 Reader-0 sees today is Sunday
 Reader-3 sees today is Sunday
 Reader-2 sees today is Sunday
 Reader-4 sees today is Sunday
 Reader-5 sees today is Sunday
 Reader-1 sees today is Sunday
 Reader-6 sees today is Sunday
 Reader-8 sees today is Sunday
 Reader-7 sees today is Sunday
 Reader-9 sees today is Sunday
 Writer-0 updated date to Monday
 Reader-2 sees today is Monday
 Reader-1 sees today is Monday
 Writer-0 updated date to Tuesday
 Reader-0 sees today is Tuesday
 Reader-4 sees today is Tuesday
 Reader-2 sees today is Tuesday
 Writer-0 updated date to Wednesday
 Reader-8 sees today is Wednesday
 Reader-6 sees today is Wednesday
 Writer-0 updated date to Thursday
 Writer-0 updated date to Friday
 Reader-0 sees today is Friday
 Reader-4 sees today is Friday
 Writer-1 updated date to Saturday
 Reader-6 sees today is Saturday
 Reader-7 sees today is Saturday
 Writer-1 updated date to Sunday
 Reader-8 sees today is Sunday
 Writer-1 updated date to Monday
 Reader-5 sees today is Monday
 Reader-0 sees today is Monday
 Reader-7 sees today is Monday
 Writer-1 updated date to Tuesday
 Reader-8 sees today is Tuesday
 Reader-1 sees today is Tuesday
 Writer-1 updated date to Wednesday
 Reader-3 sees today is Wednesday
 Reader-7 sees today is Wednesday
 Reader-2 sees today is Wednesday
 Writer-1 updated date to Thursday
 Reader-9 sees today is Thursday
 Reader-6 sees today is Thursday
 Writer-1 updated date to Friday
 Reader-1 sees today is Friday
 Reader-4 sees today is Friday
 Reader-5 sees today is Friday
 Reader-3 sees today is Friday
 Reader-7 sees today is Friday
 Writer-0 updated date to Saturday
 Writer-0 updated date to Sunday
 Reader-6 sees today is Sunday
 Reader-4 sees today is Sunday
 Reader-8 sees today is Sunday
 Reader-2 sees today is Sunday
 Reader-5 sees today is Sunday
 Reader-3 sees today is Sunday
 Reader-7 sees today is Sunday
 Reader-9 sees today is Sunday
 Reader-0 sees today is Sunday
 Reader-1 sees today is Sunday
 Reader-4 sees today is Sunday
 Reader-3 sees today is Sunday
 Reader-6 sees today is Sunday
 Reader-2 sees today is Sunday
 Reader-5 sees today is Sunday
 Reader-7 sees today is Sunday
 Reader-8 sees today is Sunday
 Reader-1 sees today is Sunday
 Reader-0 sees today is Sunday
 Reader-9 sees today is Sunday
 Reader-3 sees today is Sunday
 Reader-4 sees today is Sunday
 Reader-5 sees today is Sunday
 Reader-2 sees today is Sunday
 Reader-8 sees today is Sunday
 Reader-6 sees today is Sunday
 Reader-1 sees today is Sunday
 Reader-0 sees today is Sunday
 Reader-9 sees today is Sunday
 Reader-5 sees today is Sunday
 Reader-9 sees today is Sunday
 Reader-3 sees today is Sunday
 Reader-9 sees today is Sunday
 Program ended with exit code: 0
 */
