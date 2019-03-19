import matplotlib.pyplot as plt
import numpy as np

figure, ax = plt.subplots(2,2) #figure and subplots (2x2 grid)

name = '2D.txt'
name2 = '2D_corrected.txt'

k = 5 #m
binx = 20*k #10 cm resolution in x
biny = 20*k/3 #30 cm resolution in y

data0 = np.genfromtxt(name,usecols=0) #generate data from two files (x and y coordinates of gamma rays)
data1 = np.genfromtxt(name,usecols=1)
data_2_0 = np.genfromtxt(name2,usecols=0) #corrected (gaussian term) data
data_2_1 = np.genfromtxt(name2,usecols=1)

dat0 =[] #empty arrays to redefine the grid of points (since most of the important values are close to the center)
dat1 = []
dat_2_0 =[]
dat_2_1 = []

for i in range(np.size(data0)):
    if (abs(data0[i]) < k and abs(data1[i]) < k): #if we are close enough from the center fill the arrays
        dat0.append(data0[i])
        dat1.append(data1[i])

for i in range(np.size(data_2_0)): #the same as before
    if (abs(data_2_0[i]) < k and abs(data_2_1[i]) < k):
        dat_2_0.append(data_2_0[i])
        dat_2_1.append(data_2_1[i])

c,x,y = np.histogram2d(dat0,dat1,binx) #make 2D histograms with the redefined arrays
c1,x1,y1 = np.histogram2d(dat_2_0,dat_2_1,binx)
c2,x2,y2 = np.histogram2d(dat_2_0,dat_2_1,binx)
c3,x3,y3 = np.histogram2d(dat_2_0,dat_2_1,binx) #c2 and c3 are similar because we will add/substract a Poisson noise

a,b = np.shape(c2) #get the shape of histogram c2

for i in range(a):
    for j in range(b): #create two new arrays with an added and substracted Poisson noise
        c2[i][j] -= np.sqrt(c2[i][j])
        c3[i][j] += np.sqrt(c3[i][j])


im = ax[0][0].imshow(c.T, cmap='hot', origin='lower') #plot the histograms
im1 = ax[0][1].imshow(c1.T, cmap='hot', origin='lower')
im2 = ax[1][0].imshow(c2.T, cmap='hot', origin='lower')
im3 = ax[1][1].imshow(c3.T, cmap='hot', origin='lower')

ax[0][0].set_title("Uncorrected distribution") #set titles
ax[0][1].set_title("Corrected distribution")
ax[1][0].set_title("Corrected distribution with Poisson noise (lower bound)")
ax[1][1].set_title("Corrected distribution with Poisson noise (upper bound)")

plt.setp(ax, xticks = [0,20,40,60,80], xticklabels = [-5,-3,-1,1,3], yticks = [0,20,40,60,80], yticklabels = [-5,-3,-1,1,3])
#reset the axes ticks labels as we are technically plotting an image and not directly a histogram (it starts at (0,0))

figure.subplots_adjust(wspace = 0)#adjust space between subplots

figure.colorbar(im, ax=ax[0][0])#plot the colorbars of each histogram
figure.colorbar(im1, ax=ax[0][1])
figure.colorbar(im2, ax=ax[1][0])
figure.colorbar(im3, ax=ax[1][1])

plt.show()