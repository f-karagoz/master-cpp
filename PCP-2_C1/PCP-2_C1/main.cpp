//
//  main.cpp
//  PCP-2_C1
//
//  Created by Furkan Karagöz on 1.03.2022.
//  Topic:      Challenge : Matric mutiply
//  Example:    Product of two matrices

// Description:
// matrix[row][column]
// Multiplication is possible if first matrix # colum
// is equal to second matrix's # row.
// Product dimensions are [row-1][row-2]

#include <future>
#include <thread>
#include <cmath>

/* sequential implementation of matrix multiply */
void sequential_matrix_multiply(long ** A, size_t num_rows_a, size_t num_cols_a,
                                long ** B, size_t num_rows_b, size_t num_cols_b,
                                long ** C) {
    for (size_t i=0; i<num_rows_a; i++) {
        for (size_t j=0; j<num_cols_b; j++) {
            C[i][j] = 0; // initialize result cell to zero
            for (size_t k=0; k<num_cols_a; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void chunk_work(long ** A, size_t num_rows_a, size_t num_cols_a,
                  long ** B, size_t num_rows_b, size_t num_cols_b,
                  long ** C, size_t start_row, size_t end_row) {
    
    for (size_t i=start_row; i<end_row; i++)
    {
        for (size_t j=0; j<num_cols_b; j++) {
            C[i][j] = 0; // initialize result cell to zero
            for (size_t k=0; k<num_cols_a; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


void parallel_matrix_multiply(long ** A, size_t num_rows_a, size_t num_cols_a,
                        long ** B, size_t num_rows_b, size_t num_cols_b,
                        long ** C) {
    
    size_t n_threads = std::thread::hardware_concurrency();
    size_t n_lines_per_thread = ceil( (float)num_rows_a / n_threads );
    
    std::thread chunk_workers[n_threads];
    
    for (size_t i=0; i<n_threads; i++)
    {
        size_t chunk_start = i * n_lines_per_thread;
        size_t chunk_end = std::min( (i+1) * n_lines_per_thread, num_rows_a);
        
        chunk_workers[i] = std::thread(chunk_work,
                                        A, num_rows_a, num_cols_a,
                                        B, num_rows_b, num_cols_b,
                                        C, chunk_start, chunk_end);
    }
    for (auto& t: chunk_workers)
    {
        t.join();
    }
}


int main() {
    const int NUM_EVAL_RUNS = 3;
    const size_t NUM_ROWS_A = 100;
    const size_t NUM_COLS_A = 100;
    const size_t NUM_ROWS_B = NUM_COLS_A;
    const size_t NUM_COLS_B = 100;

    // intialize A with values in range 1 to 100
    long ** A = (long **)malloc(NUM_ROWS_A * sizeof(long *));
    if (A == NULL) {
        exit(2);
    }
    for (size_t i=0; i<NUM_ROWS_A; i++) {
        A[i] = (long *)malloc(NUM_COLS_A * sizeof(long));
        if (A[i] == NULL) {
            exit(2);
        }
        for (size_t j=0; j<NUM_COLS_A; j++) {
            A[i][j] = rand() % 100 + 1;
        }
    }

    // intialize B with values in range 1 to 100
    long ** B = (long **)malloc(NUM_ROWS_B * sizeof(long *));
    if (B == NULL) {
        exit(2);
    }
    for (size_t i=0; i<NUM_ROWS_B; i++) {
        B[i] = (long *)malloc(NUM_COLS_B * sizeof(long));
        if (B[i] == NULL) {
            exit(2);
        }
        for (size_t j=0; j<NUM_COLS_B; j++) {
            B[i][j] = rand() % 100 + 1;
        }
    }

    // allocate arrays for sequential and parallel results
    long ** sequential_result = (long **)malloc(NUM_ROWS_A * sizeof(long *));
    long ** parallel_result = (long **)malloc(NUM_ROWS_A * sizeof(long *));
    if ((sequential_result == NULL) || (parallel_result == NULL)) {
        exit(2);
    }
    for (size_t i=0; i<NUM_ROWS_A; i++) {
        sequential_result[i] = (long *)malloc(NUM_COLS_B * sizeof(long));
        parallel_result[i] = (long *)malloc(NUM_COLS_B * sizeof(long));
        if ((sequential_result[i] == NULL) || (parallel_result[i] == NULL)) {
            exit(2);
        }
    }

    printf("Evaluating Sequential Implementation...\n");
    std::chrono::duration<double> sequential_time(0);
    sequential_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A, B, NUM_ROWS_B, NUM_COLS_B, sequential_result); // "warm up"
    for (int i=0; i<NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        sequential_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A, B, NUM_ROWS_B, NUM_COLS_B, sequential_result);
        sequential_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    sequential_time /= NUM_EVAL_RUNS;

    printf("Evaluating Parallel Implementation...\n");
    std::chrono::duration<double> parallel_time(0);
    parallel_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A, B, NUM_ROWS_B, NUM_COLS_B, parallel_result); // "warm up"
    for (int i=0; i<NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        parallel_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A, B, NUM_ROWS_B, NUM_COLS_B, parallel_result);
        parallel_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    parallel_time /= NUM_EVAL_RUNS;
    
    // verify sequential and parallel results
    for (size_t i=0; i<NUM_ROWS_A; i++) {
        for (size_t j=0; j<NUM_COLS_B; j++) {
            if (sequential_result[i][j] != parallel_result[i][j]) {
                printf("ERROR: Result mismatch at row %ld, col %ld!\n", i, j);
            }
        }
    }
    printf("Average Sequential Time: %.2f ms\n", sequential_time.count()*1000);
    printf("  Average Parallel Time: %.2f ms\n", parallel_time.count()*1000);
    printf("Speedup: %.2f\n", sequential_time/parallel_time);
    printf("Efficiency %.2f%%\n", 100*(sequential_time/parallel_time)/std::thread::hardware_concurrency());
}

/* Result-1:
 const int NUM_EVAL_RUNS = 3;
 const size_t NUM_ROWS_A = 1000;
 const size_t NUM_COLS_A = 1000;
 const size_t NUM_ROWS_B = NUM_COLS_A;
 const size_t NUM_COLS_B = 1000;
 -----------------------------------
 Evaluating Sequential Implementation...
 Evaluating Parallel Implementation...
 Average Sequential Time: 11133.27 ms
   Average Parallel Time: 2319.12 ms
 Speedup: 4.80
 Efficiency 60.01%
 */

/* Result-2:
 const int NUM_EVAL_RUNS = 3;
 const size_t NUM_ROWS_A = 10000;
 const size_t NUM_COLS_A = 1000;
 const size_t NUM_ROWS_B = NUM_COLS_A;
 const size_t NUM_COLS_B = 1000;
 -----------------------------------
 Evaluating Sequential Implementation...
 Evaluating Parallel Implementation...
 Average Sequential Time: 113457.73 ms
   Average Parallel Time: 29320.77 ms
 Speedup: 3.87
 Efficiency 48.37%
 */

/* Result-3:
 const int NUM_EVAL_RUNS = 3;
 const size_t NUM_ROWS_A = 1000;
 const size_t NUM_COLS_A = 10000;
 const size_t NUM_ROWS_B = NUM_COLS_A;
 const size_t NUM_COLS_B = 1000;
 -----------------------------------
 Evaluating Sequential Implementation...
 Evaluating Parallel Implementation...
 Average Sequential Time: 194606.47 ms
   Average Parallel Time: 44937.40 ms
 Speedup: 4.33
 Efficiency 54.13%
 */

/* Result-4:
 const int NUM_EVAL_RUNS = 3;
 const size_t NUM_ROWS_A = 100;
 const size_t NUM_COLS_A = 100;
 const size_t NUM_ROWS_B = NUM_COLS_A;
 const size_t NUM_COLS_B = 100;
 -----------------------------------
 Evaluating Sequential Implementation...
 Evaluating Parallel Implementation...
 Average Sequential Time: 3.19 ms
   Average Parallel Time: 1.08 ms
 Speedup: 2.96
 Efficiency 36.99%
 */
