#include <iostream>
#include <random>

#include "task2.h"
#include "task1.h"

/*
int main() {
    using namespace std;
    compare_3_sums();
    return 0;
}
*/

//task 2.0 & 2.1
void Kahan_sum_floats(int n, float v) {
    using namespace std;
    cout << "task.2.0 & 2.1:\n";
    v==0 ? v = rand_float(0.1f, 0.9f) : v;
    float sum = 0;
    float err = 0;
    for (int i = 0; i < n; ++i) {
        float y = v - err;
        float temp = sum + y;
        err = (temp - sum) - y;
        sum = temp;
    }
    double ground_truth = v * n;

    cout << "v:              " << v << "\n";
    cout << "Sum:            " << sum << endl;
    cout << "Ground truth:   " << ground_truth << endl;
    cout << "Error:          " << abs(ground_truth - sum) << endl;
    cout << "Relative error: " << abs(ground_truth - sum) / ground_truth << endl;
}

//task 2.2
void compare_3_sums(int n, float v) {
    using namespace std;
    cout << "task.2.3:\n";
    v==0 ? v = rand_float(0.1f, 0.9f): v;
    auto result1 = count_time(sum_n_floats, n, v).count();
    cout << "Normal sum:     " << result1 << " seconds" << endl;
    auto result2 = count_time(reinterpret_cast<func_ptr>(recursive_sum_n_floats), n, v).count();
    cout << "Recursive sum:  " << result2 << " seconds" << endl;
    auto result3 = count_time(reinterpret_cast<func_ptr>(Kahan_sum_floats), n, v).count();
    cout << "Kahan sum:      " << result3 << " seconds" << endl;
}
