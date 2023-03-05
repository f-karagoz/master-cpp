//
//  main.cpp
//  PCP-2_C3
//
//  Created by Furkan Karagöz on 05.03.2022.
//  Topic:      Challenge : Download Images
//  Example:    Download images from internet and return total number of bytes

#include <thread>
#include <future>
#include <list>
#include <cstring>
#include <cmath>
#include <curl/curl.h> // curl support https://curl.haxx.se/

// Curl library provides access to the internet

/* declarations for download_image helper function */
size_t download_image(int image_num);
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);

/* sequential implementation of image downloader */
size_t sequential_image_downloader(int num_images) {
    size_t total_bytes = 0;
    for (int i=1; i<=num_images; i++) {
        total_bytes += download_image(i);
    }
    return total_bytes;
}

size_t indexed_image_downloader(int first_i, int last_i) {
    size_t total_bytes = 0;
    for (int i=first_i; i<=last_i; i++) {
        total_bytes += download_image(i);
    }
    return total_bytes;
}

/* parallel implementation of image downloader */
size_t parallel_image_downloader(int num_images) {
    size_t total_bytes = 0;
    int n_threads = std::thread::hardware_concurrency();
    int n_images_per_thread = ceil( (float)num_images / n_threads );
    std::list<std::future<size_t>> downloaders;
    
    for (int i=0; i < n_threads; ++i)
    {
        int first_i = i * n_images_per_thread;
        int last_i = std::min( (i+1)*n_images_per_thread, num_images);
        downloaders.push_back(std::async(std::launch::async, indexed_image_downloader, first_i, last_i));
    }
    for (int i=0; i < n_threads; ++i)
    {
        total_bytes += downloaders.front().get();
        downloaders.pop_front();
    }
    
    return total_bytes;
}

/* helper function to download a single image and return size in bytes */
size_t download_image(int image_num) {
    char url[] = "http://699340.youcanlearnit.net/imageXXX.jpg";
    sprintf(url, "http://699340.youcanlearnit.net/image%03d.jpg", ((image_num % 50) + 1));

    CURLcode res;
    curl_off_t num_bytes = 0;
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        res = curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T, &num_bytes);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_getinfo() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
    return num_bytes;
}

/* support function for the download_image helper function */
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    return size * nmemb;
}

int main() {
    const int NUM_EVAL_RUNS = 3;
    const int NUM_IMAGES = 50;

    printf("Evaluating Sequential Implementation...\n");
    std::chrono::duration<double> sequential_time(0);
    size_t sequential_result = sequential_image_downloader(NUM_IMAGES); // "warm up"
    for (int i=0; i<NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        sequential_image_downloader(NUM_IMAGES);
        sequential_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    sequential_time /= NUM_EVAL_RUNS;

    printf("Evaluating Parallel Implementation...\n");
    std::chrono::duration<double> parallel_time(0);
    size_t parallel_result = parallel_image_downloader(NUM_IMAGES); // "warm up"
    for (int i=0; i<NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        parallel_image_downloader(NUM_IMAGES);
        parallel_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    parallel_time /= NUM_EVAL_RUNS;
    
    // display sequential and parallel results for comparison
    if (sequential_result != parallel_result) {
        printf("ERROR: Result mismatch!\n  Sequential Result = %zd\n  Parallel Result = %zd\n", sequential_result, parallel_result);
    }
    printf("Average Sequential Time: %.2f ms\n", sequential_time.count()*1000);
    printf("  Average Parallel Time: %.2f ms\n", parallel_time.count()*1000);
    printf("Speedup: %.2f\n", sequential_time/parallel_time);
    printf("Efficiency %.2f%%\n", 100*(sequential_time/parallel_time)/std::thread::hardware_concurrency());
}

/* Use curl for xCode 14.2 :
 1. Project settings (click on the project in the project navigator windows)
 2. Navitage to Build Phases tab
 3. Under the Link Binary With Libraries click on the + icon
 4. Seach for libcurl.tbd
 */

/* Result: NUM_IMAGES = 10
 Average Sequential Time: 9856.91 ms
   Average Parallel Time: 4262.07 ms
 Speedup: 2.31
 Efficiency 28.91%
 */

/* Result: NUM_IMAGES = 50
 Average Sequential Time: 49382.24 ms
   Average Parallel Time: 11310.53 ms
 Speedup: 4.37
 Efficiency 54.58%
 */
