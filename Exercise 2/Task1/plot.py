import numpy as np
import matplotlib.pyplot as plt
"""
fig, axes = plt.subplots(1,2)
name = 'sol.txt'

mat = np.genfromtxt(name)

im1 = axes[0].imshow(mat, cmap = 'inferno', origin ='lower')

Lx = 200
Ly = 100
step = 1

x = np.arange(0,Lx+1,step)
y = np.arange(0,Ly+1,step)
mat2 = []

for i in range(Ly*step+1):
    for j in range(Lx*step+1):
        mat2.append(np.sin(np.pi * j / Lx) * np.sinh(np.pi * i / Lx) / np.sinh(np.pi * Ly / Lx))

mat2 = np.asarray(mat2)
print(mat2)
mat2 = np.reshape(mat2, (Ly*step+1, Lx*step+1))

im2 = axes[1].imshow(mat2, cmap = 'inferno', origin ='lower')

axes[0].set_xlabel('x position')
axes[1].set_xlabel('x position')
axes[1].set_ylabel('y position')
axes[0].set_ylabel('y position')
axes[1].axes.get_yaxis().set_visible(False)

fig.subplots_adjust(wspace = 0.03)

axes[0].set_title('Numerical solution')
axes[1].set_title('Analytic solution')

ax = fig.add_axes([0.125, 0.2, 0.78, 0.025])
fig.text(0.49,0.15,'Potential V', fontweight = 'bold')
plt.colorbar(im1, cax = ax, orientation = 'horizontal')

plt.setp(axes, xticks=[0, 50, 100, 150, 200], xticklabels=[0, 5, 10, 15, 20], yticks=[0, 20, 40, 60, 80], yticklabels=[0, 2, 4, 6, 8])


fig, axes = plt.subplots(2,2)
mat1 = np.genfromtxt("n1.txt")
mat2 = np.genfromtxt("n2.txt")
mat3 = np.genfromtxt("n3.txt")
mat4 = np.genfromtxt("n4.txt")

im1 = axes[0][0].imshow(mat1, cmap = 'inferno', origin ='lower')
im2 = axes[0][1].imshow(mat2, cmap = 'inferno', origin ='lower')
im3 = axes[1][0].imshow(mat3, cmap = 'inferno', origin ='lower')
im4 = axes[1][1].imshow(mat4, cmap = 'inferno', origin ='lower')

axes[0][0].set_ylabel('y position')
axes[1][0].set_ylabel('y position')
axes[1][0].set_xlabel('x position')
axes[1][1].set_xlabel('x position')

axes[0][1].axes.get_yaxis().set_visible(False)
axes[0][1].axes.get_xaxis().set_visible(False)
axes[0][0].axes.get_xaxis().set_visible(False)
axes[1][1].axes.get_yaxis().set_visible(False)

fig.subplots_adjust(wspace = 0.03)

axes[0][0].set_title('k = 0')
axes[0][1].set_title('k = 300')
axes[1][0].set_title('k = 600')
axes[1][1].set_title('k = 1100')

plt.setp(axes, xticks=[0, 50, 100, 150], xticklabels=[0, 5, 10, 15], yticks=[0, 20, 40, 60, 80], yticklabels=[0, 2, 4, 6, 8])
"""

fig, axes = plt.subplots(2,2)
mat1 = np.genfromtxt("01.txt")
mat2 = np.genfromtxt("001.txt")
mat3 = np.genfromtxt("0001.txt")
mat4 = np.genfromtxt("00001.txt")


im1 = axes[0][0].imshow(mat1, cmap = 'inferno', origin ='lower')
im2 = axes[0][1].imshow(mat2, cmap = 'inferno', origin ='lower')
im3 = axes[1][0].imshow(mat3, cmap = 'inferno', origin ='lower')
im4 = axes[1][1].imshow(mat4, cmap = 'inferno', origin ='lower')

axes[0][0].set_ylabel('y position')
axes[1][0].set_ylabel('y position')
axes[1][0].set_xlabel('x position')
axes[1][1].set_xlabel('x position')

axes[0][1].axes.get_yaxis().set_visible(False)
axes[0][1].axes.get_xaxis().set_visible(False)
axes[0][0].axes.get_xaxis().set_visible(False)
axes[1][1].axes.get_yaxis().set_visible(False)

fig.subplots_adjust(wspace = 0.03)

axes[0][0].set_title('accuracy = 0.1')
axes[0][1].set_title('accuracy = 0.01')
axes[1][0].set_title('accuracy = 0.001')
axes[1][1].set_title('accuracy = 0.00001')

plt.setp(axes, xticks=[0, 50, 100, 150], xticklabels=[0, 5, 10, 15], yticks=[0, 20, 40, 60, 80], yticklabels=[0, 2, 4, 6, 8])


plt.show()