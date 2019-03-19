# coding: utf8
__author__ = 'Wilfried'
import numpy as np
import matplotlib.pyplot as plt
from scipy.misc import factorial
from Fitting import inverse
from scipy.optimize import curve_fit
from Science import scientific_res

fig = plt.figure()
sub1 = plt.subplot(311)
sub2 = plt.subplot(312)
sub3 = plt.subplot(313)

plt.setp(sub1.get_xticklabels(), visible = False)
plt.setp(sub2.get_xticklabels(), visible = False)

fig.subplots_adjust(hspace=0.07)

t = np.arange(-0.1,0,0.0001)
t_prime = np.arange(0,0.1,0.0001)



name2 = 'sol_singular_SVD.txt'
name1 = 'sol_singular_LU.txt'
name3 = 'time_comp_size.txt'

n1 = np.genfromtxt(name1, usecols=0, skip_header=1)
n2 = np.genfromtxt(name2, usecols=0, skip_header=1)
t1 = np.genfromtxt(name1, usecols=1, skip_header=1)
t2 = np.genfromtxt(name2, usecols=1, skip_header=1)

u1 = np.genfromtxt(name1, usecols=2, skip_header=1)
u2 = np.genfromtxt(name2, usecols=2, skip_header=1)

v1 = np.genfromtxt(name1, usecols=3, skip_header=1)
v2 = np.genfromtxt(name2, usecols=3, skip_header=1)


param1, cov1 = curve_fit(inverse, n2, t2)
coeff1, err1 = scientific_res(cov1, param1)

param2, cov2 = curve_fit(inverse, n2, u2)
coeff2, err2 = scientific_res(cov2, param2)

param3, cov3 = curve_fit(inverse, n2, v2)
coeff3, err3 = scientific_res(cov3, param3)

sub1.plot(t, inverse(t, coeff1[0]), "g")
sub1.plot(t_prime, inverse(t_prime, coeff1[0]), "g", label="Fit : " + r'$A/\epsilon$')
sub1.plot(n1,t1, "^r", label="LU")
sub1.plot(n2,t2, "xb", label="SVD")

sub2.plot(t, inverse(t, coeff2[0]), "g")
sub2.plot(t_prime, inverse(t_prime, coeff2[0]), "g", label="Fit : " + r'$A/\epsilon$')
sub2.plot(n1,u1, "^r", label="LU")
sub2.plot(n2,u2, "xb", label="SVD")

sub3.plot(t, inverse(t, coeff3[0]), "g")
sub3.plot(t_prime, inverse(t_prime, coeff3[0]), "g", label="Fit : " + r'$A/\epsilon$')
sub3.plot(n1,v1, "^r", label="LU")
sub3.plot(n2,v2, "xb", label="SVD")


sub3.set_xlabel(r'$\epsilon$')
sub1.set_ylabel(r'$x_0$')
sub2.set_ylabel(r'$x_1$')
sub3.set_ylabel(r'$x_2$')

sub1.axis([-0.05,0.05,-4000,4000])
sub2.axis([-0.05,0.05,-4000,4000])
sub3.axis([-0.05,0.05,-4000,4000])
sub1.legend(loc=2)
plt.show()

