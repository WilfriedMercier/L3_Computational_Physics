# coding: utf8
__author__ = 'Wilfried'
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from Science import scientific_res
from Fitting import linear
from scipy.misc import factorial

n = factorial(np.arange(0,11.2,0.1))

fig = plt.figure()


name1 = 'time_comp_size.txt'

n1 = factorial(np.genfromtxt(name1, usecols=0, skip_header=1))
t1 = np.genfromtxt(name1, usecols=1, skip_header=1)

param, cov = curve_fit(linear, n1, t1)
coeff, err = scientific_res(cov, param)

plt.loglog(n1,t1, "rs", label="Data")
plt.loglog(n, linear(n, coeff), label="Fit : " + r'$t_n = k.n!$' + "\n" + "k = (" + str(coeff[0]) + r'$\pm$' + str(err[0]) + ") s")

plt.xlabel(r'$n!$')
plt.ylabel("Response time (s)")
plt.legend(loc=2)

plt.show()

