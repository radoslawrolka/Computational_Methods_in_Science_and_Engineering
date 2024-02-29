#ifndef MOWNIT_TASK1_H
#define MOWNIT_TASK1_H

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

//prototypes
float rand_float(float min, float max);
typedef void (*func_ptr)(int, float, bool);
std::chrono::duration<double> count_time(func_ptr func, int n=10e7, float v=0);

//task 1.1 & 1.2 & 1.3
void sum_n_floats(int n=10e7, float v=0, bool step_print=false);
//task 1.4 & 1.5
void recursive_sum_n_floats(int n=10e7, float v=0);
// task 1.6
void compare_2_sums(int n=10e7, float v=0);

#endif //MOWNIT_TASK1_H
