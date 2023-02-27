//
//  main.cpp
//  PCP-2_05
//
//  Created by Furkan Karagöz on 27.02.2022.
//  Topic:      Thread pool
//  Example:    Copping vegetables with a thread pool
#include <boost/asio.hpp>

void vegetable_chopper(int vegetable_id)
{
    printf("Thread %d chopped vegetables %d.\n", std::this_thread::get_id(), vegetable_id);
}

int main()
{
    boost::asio::thread_pool pool(4);    // Constructor takes optional n of threads
    for (int i = 0; i < 100; ++i)
        // Wrap the chopper function in an lambda expression as a token we are submitting pool to execute
        boost::asio::post(pool, [i](){vegetable_chopper(i);});
    
    pool.join();
}

/* Result-1:
 Thread 152350720 chopped vegetables 0.
 Thread 154497024 chopped vegetables 4.
 Thread 155570176 chopped vegetables 6.
 Thread 152887296 chopped vegetables 1.
 Thread 156643328 chopped vegetables 8.
 Thread 155033600 chopped vegetables 5.
 ...
 */

/* Result-2: Now were using 4 threads instead of 100.
 Thread 177188864 chopped vegetables 0.
 Thread 177188864 chopped vegetables 1.
 Thread 177188864 chopped vegetables 2.
 Thread 177188864 chopped vegetables 3.
 Thread 177188864 chopped vegetables 4.
 Thread 177188864 chopped vegetables 6.
 Thread 177188864 chopped vegetables 7.
 Thread 178262016 chopped vegetables 8.
 ...
 */

/* To add the boost library this steps followed:
1. Download latest boost boost_1_81_0.tar.gz and unarchive it
 (now there boost_1_81_0 folder with boost)
2. Copy boost_1_72_0 folder inside project folder, so it is located aside of my_project_name.xcodeproj
3. In the xCode naviagate to the project's build settings.
4. In Search Paths section select Header Search Path, double click on value area and enter ${SRCROOT}/boost_1_81_0 (leave non-recursive flag)
5. Build & Run > Success
 */
