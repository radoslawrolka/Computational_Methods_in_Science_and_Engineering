#ifndef MOWNIT_TASK2_H
#define MOWNIT_TASK2_H

//task 2.0 & 2.1
void Kahan_sum_floats(int n=10e7, float v=0);
//task 2.2
/*
 * Sum jest względnie duże w porównaniu z y co powoduje utratę bitów mniej znaczących liczby y.
 * (temp - sum) odzyskuje wyższe bity y; odjęcie y odzyskuje -(niższe bity y)
 * W następnej iteracji utracone niższe bity zostaną dodane do y
 */
//task 2.3
void compare_3_sums(int n=10e7, float v=0);

#endif //MOWNIT_TASK2_H
