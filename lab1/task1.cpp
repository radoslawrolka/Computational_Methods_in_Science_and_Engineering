#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "task1.h"

/*
int main() {
    compare_2_sums();
    return 0;
}
*/

float rand_float(float min, float max) {
    srand(time(nullptr));
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

std::chrono::duration<double> count_time(func_ptr func, int n, float v) {
    auto start = std::chrono::high_resolution_clock::now();
    func(n, v, false);
    auto end = std::chrono::high_resolution_clock::now();
    return end - start;
}

//task 1.1 & 1.2 & 1.3
void sum_n_floats(int n, float v, bool step_print) {
    using namespace std;
    cout << "task.1.1 & 1.2 & 1.3:\n";

    float sum = 0;
    v==0 ? v = rand_float(0.1f, 0.9f): v;
    for (int i = 0; i < n; i++) {
        sum += v;
        if (step_print && i%25000==0) {
            cout << "Relative error for " << i << " : " << abs(v*i - sum) / (v*i) << endl;
        }
    }
    float ground_truth = v * n;

    cout << "v:              " << v << "\n";
    cout << "Sum:            " << sum << endl;
    cout << "Ground truth:   " << ground_truth << endl;
    cout << "Error:          " << abs(ground_truth - sum) << endl;
    cout << "Relative error: " << abs(ground_truth - sum) / ground_truth << endl;
}

//task 1.4 & 1.5
void recursive_sum_n_floats(int n, float v) {
    using namespace std;
    cout << "task.1.4 & 1.5:\n";

    v==0 ? v = rand_float(0.1f, 0.9f) : v;
    vector<float> arr(n, v);
    vector<float> buff{};

    while (arr.size() > 1) {
        for (int i = 0; i < arr.size(); i += 2) {
            buff.push_back(arr[i] + arr[i + 1]);
        }
        arr = buff;
        buff.clear();
    }
    float sum = arr[0];
    float ground_truth = v * n;

    cout << "v:              " << v << "\n";
    cout << "Sum:            " << sum << endl;
    cout << "Ground truth:   " << ground_truth << endl;
    cout << "Error:          " << abs(ground_truth - sum) << endl;
    cout << "Relative error: " << abs(ground_truth - sum) / ground_truth << endl;
}

// task 1.6
void compare_2_sums(int n, float v) {
    using namespace std;
    cout << "task.1.6:\n";
    v==0 ? v = rand_float(0.1f, 0.9f): v;
    auto result1 = count_time(sum_n_floats, n, v).count();
    cout << "Normal sum:     " << result1 << " seconds" << endl;
    auto result2 = count_time(reinterpret_cast<func_ptr>(recursive_sum_n_floats), n, v).count();
    cout << "Recursive sum:  " << result2 << " seconds" << endl;
}
