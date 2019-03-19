import numpy as np
import matplotlib.pyplot as plt
"""
ax = [1,2,3]

fig, ax = plt.subplots(1,3)

#name = 'sol_200x20.txt'
name = 'sol.txt'

mat = np.genfromtxt(name)

im1 = ax[0].imshow(mat, cmap = 'inferno', origin ='lower')


x = []
y = []
E_x = []
E_y = []
E = []

for i in range(1,149,2):
    for j in range(1,149,10):
        x.append(j)
        y.append(i)
        E_y.append(-(mat[i+1][j] - mat[i][j])/1)
        E_x.append(-(mat[i][j+1] - mat[i][j])/1)

for i in range(1, 149, 1):
    for j in range(1,149,1):
        E.append(np.sqrt(( (mat[i+1][j] - mat[i][j])/1 )**2 + ( (mat[i][j+1] - mat[i][j])/1)**2))
        #print(E[i*(j-1)])



ax[1].quiver(x,y,E_x,E_y, scale_units='width', scale = 80)
print(np.size(E))
E = np.asarray(E)
E = np.reshape(E, (148, 148))

im2 = ax[2].imshow(E,  cmap = 'hot', origin ='lower')

#ax[0].axis([180,420,0,58])
#ax[2].axis([180,420,0,58])

ax[0].set_xlabel('x position')
ax[1].set_xlabel('x position')
ax[2].set_xlabel('x position')
ax[0].set_ylabel('y position')
ax[1].set_ylabel('y position')
ax[2].set_ylabel('y position')

ax[0].set_title('Electric potential (V)')
ax[1].set_title('Electric field')
ax[2].set_title('Electric field amplitude (V/m)')

ax = fig.add_axes([0.12, 0.15, 0.23, 0.025])
plt.colorbar(im1, cax = ax, orientation = 'horizontal')
ax = fig.add_axes([0.67, 0.15, 0.23, 0.025])
plt.colorbar(im2, cax = ax, orientation = 'horizontal')

im2.set_clim(0,40)

"""
def V(y):
    if (y<=0):
        return -100
    if (y>=20):
        return 100
    else:
        return(-100+10*y)

fig, axes = plt.subplots(1,2)

s = []
E = []
for i in range(-20,40,1):
    for j in range(0,100,1):
        s.append(V(i))
        if (i > 0 and i <20):
            E.append(10)
        else:
            E.append(0)

s = np.asarray(s)
E = np.asarray(E)
s = np.reshape(s, (60, 100))
E = np.reshape(E, (60, 100))

im1 = axes[0].imshow(s, cmap = 'inferno', origin ='lower')
im2 = axes[1].imshow(E, cmap = 'hot', origin ='lower')
im2.set_clim(0,40)

ax = fig.add_axes([0.13, 0.18, 0.35, 0.025])
plt.colorbar(im1, cax = ax, orientation = 'horizontal')
ax = fig.add_axes([0.55, 0.18, 0.35, 0.025])
plt.colorbar(im2, cax = ax, orientation = 'horizontal')

axes[0].set_xlabel('x position')
axes[1].set_xlabel('x position')
axes[0].set_ylabel('y position')
axes[1].set_ylabel('y position')

axes[0].set_title('Electric potential (V)')
axes[1].set_title('Electric field amplitude (V/m)')

plt.show()