import matplotlib.pyplot as plt
import numpy as np


def make_sphere(points=20, radius=1, center=(0, 0, 0)):
    sphere = []
    for i in range(points):
        theta = 2 * np.pi * i / points
        for j in range(points):
            phi = np.pi * j / points
            x = radius * np.sin(phi) * np.cos(theta) + center[0]
            y = radius * np.sin(phi) * np.sin(theta) + center[1]
            z = radius * np.cos(phi) + center[2]
            sphere.append([x, y, z])
    return np.array(sphere)


def plot_3d(matrix, fig=None, color='b'):
    if fig is None:
        fig = plt.axes(projection='3d')
    fig.scatter(matrix[0], matrix[1], matrix[2], c=color, marker='o')
    return fig


def random_matrix(low=0, high=1):
    return np.random.uniform(low=low, high=high, size=(3, 3))


def main():
    sphere = make_sphere()
    canvas = plot_3d(np.transpose(sphere))
    for color in ['r', 'g', 'y']:
        matrix = random_matrix()
        elipse = np.matmul(sphere, matrix)
        plot_3d(np.transpose(elipse), fig=canvas, color=color)
    plt.show()



if __name__ == '__main__':
    main()
