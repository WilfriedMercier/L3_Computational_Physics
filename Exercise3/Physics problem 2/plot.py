import matplotlib.pyplot as plt
import numpy as np

fig, axes = plt.subplots(2,2) #plotting figure and subplots (grid of 2x2)

name = 'no_dev.txt'
name2 = 'dev.txt'
name3 = 'no_dev_gauss.txt'
name4 = 'dev_gauss.txt'

data = np.genfromtxt(name) #generating data from files
data2 = np.genfromtxt(name2)
data3 = np.genfromtxt(name3)
data4 = np.genfromtxt(name4)

axes[0][0].hist(data, 100) #plotting the four histograms for exercise3
axes[0][1].hist(data2, 100)
axes[1][0].hist(data3, 100)
axes[1][1].hist(data4, 100)

axes[0][0].set_title('No signal without Gaussian smearing') #set the titles for each subplot
axes[0][1].set_title('Signal with 95% confidence without Gaussian smearing')
axes[1][0].set_title('No signal with Gaussian smearing')
axes[1][1].set_title('Signal with 95% confidence and Gaussian smearing')

axes[0][0].set_xlabel('Number of events', weight='bold')#set the x and y axis labels for each subplot
axes[0][1].set_xlabel('Number of events', weight='bold')
axes[1][0].set_xlabel('Number of events', weight='bold')
axes[1][1].set_xlabel('Number of events', weight='bold')
axes[0][0].set_ylabel('Distribution for 50000 throws', weight='bold')
axes[0][1].set_ylabel('Distribution for 50000 throws', weight='bold')
axes[1][0].set_ylabel('Distribution for 50000 throws', weight='bold')
axes[1][1].set_ylabel('Distribution for 50000 throws', weight='bold')

fig.subplots_adjust(hspace = 0.3) #change the space between subplots
fig.subplots_adjust(wspace = 0.1)
axes[0][1].yaxis.set_label_position("right") #change the position of the ticks and labels of the right plots
axes[1][1].yaxis.set_label_position("right")
axes[0][1].yaxis.tick_right()
axes[1][1].yaxis.tick_right()

plt.show()