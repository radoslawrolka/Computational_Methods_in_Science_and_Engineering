#include "task3.h"

int main() {
    compare_partial_sums();
    return 0;
}

both_sums riemann_sum(float s, int n, bool forward) {
    both_sums sums{0,0};
    if (forward) {
        for (int i = 1; i < n+1; i++) {
            sums.fsum += 1.0f / (pow(i, s));
            sums.dsum += 1.0 / (pow(i, s));
        }
    } else {
        for (int i = n; i > 0; i--) {
            sums.fsum += 1.0f / (pow(i, s));
            sums.dsum += 1.0 / (pow(i, s));
        }
    }
    return sums;
}

both_sums dirichlet_sum(float s, int n, bool forward) {
    both_sums sums{0,0};
    if (forward) {
        for (int i = 1; i < n+1; i++) {
            sums.fsum += pow(-1, i - 1) * (1 / pow(i, s));
            sums.dsum += pow(-1, i - 1) * (1 / pow(i, s));
        }
    } else {
        for (int i = n; i > 0; i--) {
            sums.fsum += pow(-1, i - 1) * (1 / pow(i, s));
            sums.dsum += pow(-1, i - 1) * (1 / pow(i, s));
        }
    }
    return sums;
}

void compare_partial_sums() {
    using namespace std;
    cout << setprecision(20);
    float s[]{2, 3.6667, 5, 7.2, 10};
    int n[]{50, 100, 200, 500, 10000};
    sum_func funcs[] = {riemann_sum, dirichlet_sum};
    enum direction {forward=0, backward=1};

    for (float si : s) {
        for (int ni : n) {
            for (sum_func f : funcs) {
                for (int d : {forward, backward}) {
                    both_sums r = f(si, ni, d);
                    cout << "s: " << si << ", n: " << ni << endl;
                    cout << "f: " << (f == riemann_sum ? "riemann" : "dirichlet") << ", d: " << (d == forward ? "forward" : "backward") << endl;
                    cout << "float:  " << r.fsum << endl;
                    cout << "double: " << r.dsum << endl;
                }
            }
        }
    }
}
