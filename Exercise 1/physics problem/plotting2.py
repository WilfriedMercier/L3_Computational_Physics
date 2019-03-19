# coding: utf8
__author__ = 'Wilfried'
import numpy as np
import matplotlib.pyplot as plt

z = [0]
count = 0

fig, axes = plt.subplots(2,1)
name = 'problem2.txt'

x = np.genfromtxt(name, usecols=0, skip_header=1)
y = np.genfromtxt(name, usecols=1, skip_header=1, max_rows=240)
R1 = np.genfromtxt(name, usecols=2, skip_header=1)
R2 = np.genfromtxt(name, usecols=3, skip_header=1)
R3 = np.genfromtxt(name, usecols=4, skip_header=1)




plt.setp(axes, xticks=[0, 50, 100, 150, 200, 250], xticklabels=[0, 25, 50, 75, 100, 125], yticks=[0, 50, 100, 150, 200], yticklabels=[0, 25, 50, 75, 100])

for i in range(np.size(x)):
    if x[i] != z[count]:
        z.append(x[i])
        count += 1

z = np.asarray(z)

R1 = np.reshape(R1, (np.size(z), np.size(y)))
R2 = np.reshape(R2, (np.size(z), np.size(y)))
R3 = np.reshape(R3, (np.size(z), np.size(y)))

R4 = np.add(R1,R2)
R4 = np.add(R4,R3)

im1 = axes[0].imshow(R4.T, cmap = 'inferno', origin ='lower')
im2 = axes[1].imshow(R4.T, cmap = 'inferno', origin ='lower')

axes[0].axis([0, np.size(z)-1, 0, np.size(y)])
axes[1].axis([0, np.size(z)-1, 0, np.size(y)])

fig.subplots_adjust(hspace = 0.07)
axes[0].axes.get_xaxis().set_visible(False)

axes[1].set_xlabel('x (m)')
axes[0].set_ylabel('y (m)')
axes[1].set_ylabel('y (m)')

ax = fig.add_axes([0.65, 0.517, 0.02, 0.39])
fig.text(0.75,0.7,'Sum of the tensions in the cables (N)', fontweight = 'bold', rotation=90)
plt.colorbar(im1, cax = ax, orientation = 'vertical')

ax2 = fig.add_axes([0.65, 0.1, 0.02, 0.39])
plt.colorbar(im2, cax = ax2, orientation = 'vertical')
im2.set_clim(36000,40000)

plt.show()

