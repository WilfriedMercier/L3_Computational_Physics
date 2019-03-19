# coding: utf8
__author__ = 'Wilfried'
import numpy as np
import matplotlib.pyplot as plt
from scipy.misc import factorial
from Fitting import linear
from Fitting import power_law
from scipy.optimize import curve_fit
from Science import scientific_res

t = np.arange(0,100,1)
t_prime = np.arange(0,1100,10)

fig = plt.figure()
sub1 = plt.subplot(1,2,1)
sub2 = plt.subplot(1,2,2)

name2 = 'time_size_LU.txt'
name1 = 'time_size_SVD.txt'
name3 = 'time_comp_size.txt'

n1 = np.genfromtxt(name1, usecols=0, skip_header=1)
n2 = np.genfromtxt(name2, usecols=0, skip_header=1)
t1 = np.genfromtxt(name1, usecols=1, skip_header=1)
t2 = np.genfromtxt(name2, usecols=1, skip_header=1)

param1, cov1 = curve_fit(power_law, n1, t1)
param2, cov2 = curve_fit(power_law, n2, t2)
coeff1, err1 = scientific_res(cov1, param1)
coeff2, err2 = scientific_res(cov2, param2)

sub2.plot(n1,t1, "^r", label="SVD : k = " + str(coeff1[0]) + r'$\pm$' + str(err1[0]))
sub1.loglog(n1,t1, "^r", label="SVD")
sub2.plot(n2,t2, "sb", label="LU : k = " + str(coeff2[0]) + r'$\pm$' + str(err2[0]))
sub1.loglog(n2,t2, "sb", label="LU")
sub1.loglog(t, (3.287*10**(-3)) * factorial(t), "g", label="inverse")
sub2.plot(t_prime, power_law(t_prime, coeff1[0], coeff1[1]), "r")
sub2.plot(t_prime, power_law(t_prime, coeff2[0], coeff2[1]), "b")

sub1.set_xlabel("n")
sub2.set_xlabel("n")
sub1.set_ylabel("Response time t(ms)")

sub2.axis([20,1100,1,40000])
sub2.yaxis.tick_right()
fig.subplots_adjust(wspace=0.05)

sub1.legend(loc=2)
sub2.legend(loc=2)

plt.show()

