import numpy as np
import matplotlib.pyplot as plt

fig, axes = plt.subplots(1,2)
name = 'sol.txt'

mat = np.genfromtxt(name)

im1 = axes[0].imshow(mat, cmap = 'inferno', origin ='lower')

Lx = 10
Ly = 10
step = 1

x = np.arange(0,Lx+1,step)
y = np.arange(0,Ly+1,step)
mat2 = []

for i in range(Ly*step+1):
    for j in range(Lx*step+1):
        mat2.append(np.sin(np.pi * i / Lx) * np.sinh(np.pi * j / Lx) / np.sinh(np.pi * Ly / Lx))

mat2 = np.asarray(mat2)
print(mat2)
mat2 = np.reshape(mat2, (Lx*step+1, Ly*step+1))

im2 = axes[1].imshow(mat2.T, cmap = 'inferno', origin ='lower')

plt.show()