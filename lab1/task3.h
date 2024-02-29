#ifndef MOWNIT_TASK3_H
#define MOWNIT_TASK3_H

#include <iostream>
#include <cmath>
#include <iomanip>

struct both_sums {
    float fsum;
    double dsum;
};
typedef both_sums (*sum_func)(float, int, bool);

//task.3
both_sums riemann_sum(float s, int n, bool forward);
both_sums dirichlet_sum(float s, int n, bool forward);
void compare_partial_sums();

#endif //MOWNIT_TASK3_H
