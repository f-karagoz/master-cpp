//
//  main.cpp
//  PCP_13
//
//  Created by Furkan Karagöz on 26.12.2022.
//  Starvation
//  Two philosophers, thinking and eating sushi

#include <thread>
#include <mutex>
#include <array>

int sushi_count = 5000;

void philosopher(std::mutex &chopsticks)
{
    int sushi_eaten = 0;
    while (sushi_count > 0)
    {
        std::scoped_lock lock(chopsticks);
        if (sushi_count)
        {
            sushi_count--;
            sushi_eaten++;
        }
    }
    printf("Philosopher %d ate %d.\n", std::this_thread::get_id(), sushi_eaten);
}

int main (void)
{
    std::mutex chopsticks;
//    std::thread barron(philosopher, std::ref(chopsticks));
//    std::thread olivia(philosopher, std::ref(chopsticks));
    std::array<std::thread, 200> philosophers;
    for (unsigned i = 0; i < philosophers.size(); ++i)
        philosophers[i] = std::thread(philosopher, std::ref(chopsticks));
//    barron.join();
//    olivia.join();
    for (unsigned i = 0; i < philosophers.size(); ++i)
        philosophers[i].join();
    
    printf("The philosophers are done eating.\n");
    return 0;
}


/* PROGRAM OUTPUT:
 (when there is two thread every thread can access to some extent of resources)
 
 Philosopher 2269184 ate 1850.
 Philosopher 1732608 ate 3150.
 The philosophers are done eating.
 Program ended with exit code: 0
 */

/* PROGRAM OUTPUT:
 (for 200 threads)
 (all threads have the same default priority but some never executed)
 Philosopher 59744256 ate 0.
 Philosopher 58671104 ate 0.
 Philosopher 62963712 ate 0.
 Philosopher 64036864 ate 0.
 Philosopher 58134528 ate 89.
 Philosopher 59207680 ate 0.
 Philosopher 60280832 ate 0.
 Philosopher 52232192 ate 551.
 Philosopher 65646592 ate 0.
 Philosopher 56524800 ate 387.
 Philosopher 66183168 ate 0.
 Philosopher 57061376 ate 1.
 Philosopher 52768768 ate 865.
 Philosopher 54915072 ate 361.
 Philosopher 68329472 ate 0.
 Philosopher 57597952 ate 102.
 Philosopher 68866048 ate 0.
 Philosopher 54378496 ate 374.
 Philosopher 61890560 ate 0.
 Philosopher 62427136 ate 0.
 Philosopher 69402624 ate 0.
 Philosopher 69939200 ate 0.
 Philosopher 53305344 ate 486.
 Philosopher 63500288 ate 0.
 Philosopher 55988224 ate 9.
 Philosopher 66719744 ate 0.
 Philosopher 71012352 ate 0.
 Philosopher 71548928 ate 0.
 Philosopher 53841920 ate 585.
 Philosopher 67792896 ate 0.
 Philosopher 55451648 ate 55.
 Philosopher 72622080 ate 0.
 Philosopher 73158656 ate 0.
 Philosopher 51695616 ate 1135.
 Philosopher 64573440 ate 0.
 Philosopher 65110016 ate 0.
 Philosopher 60817408 ate 0.
 Philosopher 67256320 ate 0.
 Philosopher 72085504 ate 0.
 Philosopher 61353984 ate 0.
 Philosopher 70475776 ate 0.
 Philosopher 74768384 ate 0.
 Philosopher 75304960 ate 0.
 Philosopher 73695232 ate 0.
 Philosopher 74231808 ate 0.
 Philosopher 75841536 ate 0.
 Philosopher 76378112 ate 0.
 Philosopher 76914688 ate 0.
 Philosopher 77451264 ate 0.
 Philosopher 77987840 ate 0.
 Philosopher 78524416 ate 0.
 Philosopher 79060992 ate 0.
 Philosopher 79597568 ate 0.
 Philosopher 80134144 ate 0.
 Philosopher 80670720 ate 0.
 Philosopher 81207296 ate 0.
 Philosopher 81743872 ate 0.
 Philosopher 82280448 ate 0.
 Philosopher 82817024 ate 0.
 Philosopher 83353600 ate 0.
 Philosopher 83890176 ate 0.
 Philosopher 84426752 ate 0.
 Philosopher 84963328 ate 0.
 Philosopher 85499904 ate 0.
 Philosopher 86036480 ate 0.
 Philosopher 86573056 ate 0.
 Philosopher 87109632 ate 0.
 Philosopher 87646208 ate 0.
 Philosopher 88182784 ate 0.
 Philosopher 88719360 ate 0.
 Philosopher 89255936 ate 0.
 Philosopher 89792512 ate 0.
 Philosopher 90329088 ate 0.
 Philosopher 90865664 ate 0.
 Philosopher 91402240 ate 0.
 Philosopher 91938816 ate 0.
 Philosopher 92475392 ate 0.
 Philosopher 93011968 ate 0.
 Philosopher 93548544 ate 0.
 Philosopher 94085120 ate 0.
 Philosopher 94621696 ate 0.
 Philosopher 95158272 ate 0.
 Philosopher 95694848 ate 0.
 Philosopher 96231424 ate 0.
 Philosopher 96768000 ate 0.
 Philosopher 97304576 ate 0.
 Philosopher 97841152 ate 0.
 Philosopher 98377728 ate 0.
 Philosopher 98914304 ate 0.
 Philosopher 99450880 ate 0.
 Philosopher 99987456 ate 0.
 Philosopher 100524032 ate 0.
 Philosopher 101060608 ate 0.
 Philosopher 101597184 ate 0.
 Philosopher 102133760 ate 0.
 Philosopher 102670336 ate 0.
 Philosopher 103206912 ate 0.
 Philosopher 103743488 ate 0.
 Philosopher 104280064 ate 0.
 Philosopher 104816640 ate 0.
 Philosopher 105353216 ate 0.
 Philosopher 105889792 ate 0.
 Philosopher 106426368 ate 0.
 Philosopher 106962944 ate 0.
 Philosopher 107499520 ate 0.
 Philosopher 108036096 ate 0.
 Philosopher 108572672 ate 0.
 Philosopher 109109248 ate 0.
 Philosopher 109645824 ate 0.
 Philosopher 110182400 ate 0.
 Philosopher 110718976 ate 0.
 Philosopher 111255552 ate 0.
 Philosopher 111792128 ate 0.
 Philosopher 112328704 ate 0.
 Philosopher 112865280 ate 0.
 Philosopher 113401856 ate 0.
 Philosopher 113938432 ate 0.
 Philosopher 114475008 ate 0.
 Philosopher 115011584 ate 0.
 Philosopher 115548160 ate 0.
 Philosopher 116084736 ate 0.
 Philosopher 116621312 ate 0.
 Philosopher 117157888 ate 0.
 Philosopher 117694464 ate 0.
 Philosopher 118231040 ate 0.
 Philosopher 118767616 ate 0.
 Philosopher 119304192 ate 0.
 Philosopher 119840768 ate 0.
 Philosopher 120377344 ate 0.
 Philosopher 120913920 ate 0.
 Philosopher 121450496 ate 0.
 Philosopher 121987072 ate 0.
 Philosopher 122523648 ate 0.
 Philosopher 123060224 ate 0.
 Philosopher 123596800 ate 0.
 Philosopher 124133376 ate 0.
 Philosopher 124669952 ate 0.
 Philosopher 125206528 ate 0.
 Philosopher 125743104 ate 0.
 Philosopher 126279680 ate 0.
 Philosopher 126816256 ate 0.
 Philosopher 127352832 ate 0.
 Philosopher 127889408 ate 0.
 Philosopher 128425984 ate 0.
 Philosopher 128962560 ate 0.
 Philosopher 129499136 ate 0.
 Philosopher 130035712 ate 0.
 Philosopher 130572288 ate 0.
 Philosopher 131108864 ate 0.
 Philosopher 131645440 ate 0.
 Philosopher 132182016 ate 0.
 Philosopher 132718592 ate 0.
 Philosopher 133255168 ate 0.
 Philosopher 133791744 ate 0.
 Philosopher 134328320 ate 0.
 Philosopher 134864896 ate 0.
 Philosopher 135401472 ate 0.
 Philosopher 135938048 ate 0.
 Philosopher 136474624 ate 0.
 Philosopher 137011200 ate 0.
 Philosopher 137547776 ate 0.
 Philosopher 138084352 ate 0.
 Philosopher 138620928 ate 0.
 Philosopher 139157504 ate 0.
 Philosopher 139694080 ate 0.
 Philosopher 140230656 ate 0.
 Philosopher 140767232 ate 0.
 Philosopher 141303808 ate 0.
 Philosopher 141840384 ate 0.
 Philosopher 142376960 ate 0.
 Philosopher 142913536 ate 0.
 Philosopher 143450112 ate 0.
 Philosopher 143986688 ate 0.
 Philosopher 144523264 ate 0.
 Philosopher 145059840 ate 0.
 Philosopher 145596416 ate 0.
 Philosopher 146132992 ate 0.
 Philosopher 146669568 ate 0.
 Philosopher 147206144 ate 0.
 Philosopher 147742720 ate 0.
 Philosopher 148279296 ate 0.
 Philosopher 148815872 ate 0.
 Philosopher 149352448 ate 0.
 Philosopher 149889024 ate 0.
 Philosopher 150425600 ate 0.
 Philosopher 150962176 ate 0.
 Philosopher 151498752 ate 0.
 Philosopher 152035328 ate 0.
 Philosopher 152571904 ate 0.
 Philosopher 153108480 ate 0.
 Philosopher 153645056 ate 0.
 Philosopher 154181632 ate 0.
 Philosopher 154718208 ate 0.
 Philosopher 155254784 ate 0.
 Philosopher 155791360 ate 0.
 Philosopher 156327936 ate 0.
 Philosopher 156864512 ate 0.
 Philosopher 157401088 ate 0.
 Philosopher 157937664 ate 0.
 Philosopher 158474240 ate 0.
 */
