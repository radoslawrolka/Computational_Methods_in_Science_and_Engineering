import numpy as np
import matplotlib.pyplot as plt

# recursive logistic mapping
def logistic_mapping(r, x):
    return r * x * (1 - x)

# count logistic mapping
def count(r_min, r_max, x0, n, dtype=np.float32):
    r = np.linspace(r_min, r_max, n, dtype=dtype)
    x = np.zeros(n, dtype=dtype)
    x[0] = x0
    for i in range(1, n):
        x[i] = logistic_mapping(r[i], x[i-1])
    return r, x

# count logistic mapping until zero
def count_until_zero(r, x0, dtype=np.float32):
    x = np.array([x0], dtype=dtype)
    while x[-1] > 0.01:
        x = np.append(x, logistic_mapping(r, x[-1]))
    return [r for _ in range(len(x))], list(x)

# plot bifurcation diagram
def bifurcation_diagram(results):
    n = len(results)
    if n == 1:
        plt.figure(figsize=(10, 6))
        plt.scatter(results[0][1], bifurcation_data[:,1], s=0.1, c='black')
        plt.xlabel('r')
        plt.ylabel('x')
        plt.title(f"Bifurcation diagram [r={r[0]:.2f}-{r[-1]:.2f}, x0={x[0]:.2f}]")

        plt.show()
        return
    fig, axs = plt.subplots(1, n, figsize=(5*n, 5))
    for i, (r, x) in enumerate(results):
        axs[i].scatter(r, x, s=0.1, c='black', marker='o')
        axs[i].set_xlabel('r')
        axs[i].set_ylabel('x')
        axs[i].set_title(f"Bifurcation diagram [r={r[0]:.2f}-{r[-1]:.2f}, x0={x[0]:.2f}]")
    plt.tight_layout()
    plt.show()

# task 4.1
def task4_1(n=10000):
    r_min, r_max = 1, 4
    data = []
    for x0 in [0.1, 0.5, 0.9]:
        data.append(count(r_min, r_max, x0, n))
    bifurcation_diagram(data)

# task 4.2
def task4_2(n=10000):
    r_min, r_max = 3.75, 3.8
    for x0 in [0.1, 0.5, 0.9]:
        data = [count(r_min, r_max, x0, n, dtype) for dtype in [np.float32, np.float64]]
        bifurcation_diagram(data)

# task 4.3
def task4_3():
    r = 4
    for x0 in [0.1, 0.5, 0.9]:
        data = [count_until_zero(r, x0)]
        print(f"x0={x0}, r={r} -> len(x)={len(data[0][1])}")
        print(data)
        bifurcation_diagram(data)

if __name__ == "__main__":
    task4_1()
    #task4_2()
    #task4_3()
