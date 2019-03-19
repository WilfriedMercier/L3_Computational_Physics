import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from Science import scientific_res
from scipy.stats import chisquare


def sin(x,A): #fit for the sin function
    return A*np.sin(x)

"""
                                                        First plot of the four histograms for both methods
"""

"""
name1 = 'data\sin_1_50.txt' #algebrical inversion (the number means the numebr of generated random numbers)
name2 = 'data\sin_1_100.txt'
name3 = 'data\sin_1_5000.txt'
name4 = 'data\sin_1_100000.txt'
"""
name1 = 'data\sin_2_50.txt' #rejection technique (the number means the numebr of generated random numbers)
name2 = 'data\sin_2_100.txt'
name3 = 'data\sin_2_5000.txt'
name4 = 'data\sin_2_100000.txt'

data1 = np.genfromtxt(name1) #generate data for the four histograms
data2 = np.genfromtxt(name2)
data3 = np.genfromtxt(name3)
data4 = np.genfromtxt(name4)

fig, axes = plt.subplots(2,2) #grid of 2x2

n1, bins1, patches1 = axes[0][0].hist(data1, 5) #plot the four histogram
n2, bins2, patches2 = axes[0][1].hist(data2, 10)
n3, bins3, patches3 = axes[1][0].hist(data3, 100)
n4, bins4, patches4 = axes[1][1].hist(data4, 100)

axes[0][0].set_xlabel("Angle x (radians)", weight='bold') #set x and y labels of each subplot
axes[0][0].set_ylabel("Distribution of random numbers", weight='bold')
axes[0][0].set_title(r'$\rm N_{total} = 50$') #set title of each subplot

axes[0][1].set_xlabel("Angle x (radians)", weight='bold')
axes[0][1].set_ylabel("Distribution of random numbers", weight='bold')
axes[0][1].set_title(r'$\rm N_{total} = 100$')

axes[1][0].set_xlabel("Angle x (radians)", weight='bold')
axes[1][0].set_ylabel("Distribution of random numbers", weight='bold')
axes[1][0].set_title(r'$\rm N_{total} = 5000$')

axes[1][1].set_xlabel("Angle x (radians)", weight='bold')
axes[1][1].set_ylabel("Distribution of random numbers", weight='bold')
axes[1][1].set_title(r'$\rm N_{total} = 100000$')

fig.subplots_adjust(wspace = 0.2)
fig.subplots_adjust(hspace = 0.3)

plt.show()


"""
                                Second plot of the change in p-value for the two methods as the number of random number generated increases
"""

"""
figure = plt.figure()

p = [] #p value for algebrical inversion
sigma = [] #deviation
pp = [] #p-value for rejection method
ssigma = [] #deviation

for i in range(9): #100,1000,5000,10000,20000,50000,100000,35000,80000 (i=0 -> N=100, i=1 -> N=1000, i=2 -> N=5000 and so on with N the nmber of generated numbers)
    name = 'data/s_1_' + str(i) + '.txt' #inversion method
    name2 = 'data/s_2_' + str(i) + '.txt' #rejection method

    if (i==0): #k number of bins for the histograms
        k=10
    if (i==1):
        k=50
    else:
        k=100

    data0 = np.genfromtxt(name, usecols=0) #get the data for inversion (more than one in order to compute a mean and deviation)
    data1 = np.genfromtxt(name, usecols=1) 
    data2 = np.genfromtxt(name, usecols=2) 
    data3 = np.genfromtxt(name, usecols=3)  
    data4 = np.genfromtxt(name, usecols=4)

    da0 = np.genfromtxt(name2, usecols=0) #the same for rejetion technique
    da1 = np.genfromtxt(name2, usecols=1)
    da2 = np.genfromtxt(name2, usecols=2)
    da3 = np.genfromtxt(name2, usecols=3)

    n0, bins0, patches0 = plt.hist(data0, k)  # plot histogram (generate the data of the histograms)
    n1, bins1, patches1 = plt.hist(data1, k)
    n2, bins2, patches2 = plt.hist(data2, k)
    n3, bins3, patches3 = plt.hist(data3, k)
    n4, bins4, patches4 = plt.hist(data4, k)
    
    nn0, binns0, pat0 = plt.hist(da0, k)
    nn1, binns1, pat1 = plt.hist(da1, k)
    nn2, binns2, pat2 = plt.hist(da2, k)
    nn3, binns3, pat3 = plt.hist(da3, k)

    param0, cov0 = curve_fit(sin, bins0[:-1], n0) #fit a sine curve
    coef0, err0 = scientific_res(cov0, param0) #get the result in scientific notation
    c0, p0 = chisquare(n0, sin(bins0[:-1], coef0[0])) #perform a chi square test (c = chi, p = p-value)
    
    param1, cov1 = curve_fit(sin, bins1[:-1], n1) #repeat for each data for each method
    coef1, err1 = scientific_res(cov1, param1)
    c1, p1 = chisquare(n1, sin(bins1[:-1], coef1[0]))
    
    param2, cov2 = curve_fit(sin, bins2[:-1], n2)
    coef2, err2 = scientific_res(cov2, param2)
    c2, p2 = chisquare(n2, sin(bins2[:-1], coef2[0]))
    
    param3, cov3 = curve_fit(sin, bins3[:-1], n3)
    coef3, err3 = scientific_res(cov3, param3)
    c3, p3 = chisquare(n3, sin(bins3[:-1], coef3[0]))
    
    param4, cov4 = curve_fit(sin, bins4[:-1], n4)
    coef4, err4 = scientific_res(cov4, param4)
    c4, p4 = chisquare(n4, sin(bins4[:-1], coef4[0]))

    par0, co0 = curve_fit(sin, binns0[:-1], nn0)
    cof0, er0 = scientific_res(co0, par0)
    cc0, pp0 = chisquare(nn0, sin(binns0[:-1], cof0[0]))

    par1, co1 = curve_fit(sin, binns1[:-1], nn1)
    cof1, er1 = scientific_res(co1, par1)
    cc1, pp1 = chisquare(nn1, sin(binns1[:-1], cof1[0]))

    par2, co2 = curve_fit(sin, binns2[:-1], nn2)
    cof2, er2 = scientific_res(co2, par2)
    cc2, pp2 = chisquare(nn2, sin(binns2[:-1], cof2[0]))

    par3, co3 = curve_fit(sin, binns3[:-1], nn3)
    cof3, er3 = scientific_res(co3, par3)
    cc3, pp3 = chisquare(nn3, sin(binns3[:-1], cof3[0]))
    
    p.append((p0 + p1 + p2 + p3 + p4)/5) #compute the mean and add it to the p-value array
    sigma.append(np.std([p0,p1,p2,p3,p4])) #compute the deviation and add it to the p-value array

    pp.append((pp0 + pp1 + pp2 + pp3)/4) #the same for rejection technique
    ssigma.append(np.std([pp0,pp1,pp2,pp3]))

#this is repeated for all the files sin_1_i.txt and sin_2_i.txt with i the variable in the for loop above

plt.clf() #clear the plot (i.e. do not plot the histograms)
plt.errorbar([100,1000,5000,10000,20000,50000,100000,35000,80000], p, yerr=sigma, linestyle='none', marker='s', label='Algebrical inversion') #plot the mean with the deviation as error
plt.errorbar([100,1000,5000,10000,20000,50000,100000,35000,80000], pp, yerr=ssigma, linestyle='none', marker='^', label='Rejection method')

plt.axis([-1000,110000, -0.1,1.1])
plt.xlabel("Number of generated random numbers", weight='bold')
plt.ylabel("P-value", weight='bold')

plt.legend()

plt.show()
"""