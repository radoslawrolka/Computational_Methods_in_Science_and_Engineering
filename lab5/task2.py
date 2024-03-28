import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import sys

# A = SUM_{i=1}^{r} sigma_i * u_i * v_i^T


fname = 'lenna.png'
image = Image.open(fname).convert('L') # greyscale

A = np.asarray(image) # image to array
BREAK = min(max(A.shape), 10) # max size r iterations

u, s, v = np.linalg.svd(A) # svd decomposition
B = np.zeros(A.shape) # compressed image

for i in range(min(A.shape[0], A.shape[1])): # photo size (k iterations) k << r
    B += s[i] * np.outer(u.T[i], v[i]) # count sigma
    if i == BREAK:
        break

fig, ax = plt.subplots()
fig.subplots_adjust(top=0.85)  # Adjust top margin to make space for title
fig_image = ax.imshow(B, cmap='gray')  # Display the compressed image
ax.set_title(f'abs(I - I_{BREAK}) = {np.linalg.norm(A-B)}', fontsize=14, y=1.05)
plt.show()