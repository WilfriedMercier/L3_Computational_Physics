import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from Science import scientific_res
from scipy.stats import chisquare

a = 1.6596343*10**(-5)
t = 1000
x = np.arange(0,0.5+0.5/499,0.5/499)

def th(x,l,A,B,E):
    return(E + A*x + B*np.exp(-l*x))
def th2(x,E,A):
    return(E + A*x)

name = 'Temp.txt'
name2 = 'Temp0.txt'
name3 = "Temp0bis.txt"
"""
mat = np.genfromtxt(name)

param, cov = curve_fit(th, x, mat[0])
param1, cov1 = curve_fit(th, x, mat[50])
param2, cov2 = curve_fit(th, x, mat[300])
param3, cov3 = curve_fit(th, x, mat[1000])
#param4, cov4 = curve_fit(th, x, mat[5000])
param5, cov5 = curve_fit(th2, x, mat[9000])

coef, err = scientific_res(cov, param)
coef1, err1 = scientific_res(cov1, param1)
coef2, err2 = scientific_res(cov2, param2)
coef3, err3 = scientific_res(cov3, param3)
#coef4, err4 = scientific_res(cov4, param4)
coef5, err5 = scientific_res(cov5, param5)

c, p = chisquare(mat[0],th(x, coef[0], coef[1], coef[2], coef[3]))
c1, p1 = chisquare(mat[50],th(x, coef1[0], coef1[1], coef1[2], coef1[3]))
c2, p2 = chisquare(mat[300],th(x, coef2[0], coef2[1], coef2[2], coef2[3]))
c3, p3 = chisquare(mat[1000],th(x, coef3[0], coef3[1], coef3[2], coef3[3]))
c4, p4 = chisquare(mat[9000],th2(x, coef5[0], coef5[1]))
c = np.round(c, 2)
c1 = np.round(c1, 2)
c2 = np.round(c2, 2)
c3 = np.round(c3, 2)
c4 = np.round(c4, 2)
p = np.round(p, 2)
p1 = np.round(p1, 2)
p2 = np.round(p2, 2)
p3 = np.round(p3, 2)
p4 = np.round(p4, 2)


plt.plot(x, mat[0], "*", label="t = 0 s")
plt.plot(x, mat[50], "s", label="t = 50 s")
plt.plot(x, mat[300], "^", label="t = 300 s")
plt.plot(x, mat[1000], "+", label="t = 1000 s")
plt.plot(x, mat[5000], "x", label="t = 5000 s")
plt.plot(x, mat[9000], ".", label="t = 9000 s")
plt.plot(x, th(x, coef[0], coef[1], coef[2], coef[3]),"r", label = "fit (t=0) : " + r'$\chi^2 = $' + str(c) + ", p-value = " + str(p))
plt.plot(x, th(x, coef1[0], coef1[1], coef1[2], coef1[3]),"b", label = "fit (t=50) : " + r'$\chi^2 = $' + str(c1) + ", p-value = " + str(p1))
plt.plot(x, th(x, coef2[0], coef2[1], coef2[2], coef2[3]),"y", label = "fit (t=300) : " + r'$\chi^2 = $' + str(c2) + ", p-value = " + str(p2))
plt.plot(x, th(x, coef3[0], coef3[1], coef3[2], coef3[3]),"violet", label = "fit (t=1000) : " + r'$\chi^2 = $' + str(c3) + ", p-value = " + str(p3))
#plt.plot(x, th(x, coef4[0], coef4[1], coef4[2], coef4[3]), label = "fit t =5000")
plt.plot(x, th2(x, coef5[0], coef5[1]), label = "fit (t=9000) : " + r'$\chi^2 = $' + str(c4) + ", p-value = " + str(p4))

plt.ylabel("Temperature (°C)")
plt.xlabel("Position on the poker (m)")

plt.legend()


mat2 = np.genfromtxt(name2)

parm, cova = curve_fit(th, x, mat2[0])
parm1, cova1 = curve_fit(th, x, mat2[50])
parm2, cova2 = curve_fit(th, x, mat2[300])
parm3, cova3 = curve_fit(th, x, mat2[1000])
#parm4, cova4 = curve_fit(th, x, mat2[5000])
parm5, cova5 = curve_fit(th2, x, mat2[9000])

cof, er = scientific_res(cova, parm)
cof1, er1 = scientific_res(cova1, parm1)
cof2, er2 = scientific_res(cova2, parm2)
cof3, er3 = scientific_res(cova3, parm3)
#cof4, er4 = scientific_res(cova4, parm4)
cof5, er5 = scientific_res(cova5, parm5)

cc, pp = chisquare(mat2[0],th(x, cof[0], cof[1], cof[2], cof[3]))
cc1, pp1 = chisquare(mat2[50],th(x, cof1[0], cof1[1], cof1[2], cof1[3]))
cc2, pp2 = chisquare(mat2[300],th(x, cof2[0], cof2[1], cof2[2], cof2[3]))
cc3, pp3 = chisquare(mat2[1000],th(x, cof3[0], cof3[1], cof3[2], cof3[3]))
cc4, pp4 = chisquare(mat2[9000],th2(x, cof5[0], cof5[1]))
cc = np.round(cc, 3)
cc1 = np.round(cc1, 3)
cc2 = np.round(cc2, 3)
cc3 = np.round(cc3, 3)
cc4 = np.round(cc4, 3)
pp = np.round(pp, 3)
pp1 = np.round(pp1, 3)
pp2 = np.round(pp2, 3)
pp3 = np.round(pp3, 3)
pp4 = np.round(pp4, 3)


plt.plot(x, mat2[0], "*", label="t = 0")
plt.plot(x, mat2[50], "s", label="t = 50")
plt.plot(x, mat2[300], "^", label="t = 300")
plt.plot(x, mat2[1000], "+", label="t = 1000")
plt.plot(x, mat2[5000], "x", label="t = 5000")
plt.plot(x, mat2[9000], ".", label="t = 9000")
plt.plot(x, th(x, cof[0], cof[1], cof[2], cof[3]),"r", label = "fit (t=0) : " + r'$\chi^2 = $' + str(cc) + ", p-value = " + str(pp))
plt.plot(x, th(x, cof1[0], cof1[1], cof1[2], cof1[3]),"b", label = "fit (t=50) : " + r'$\chi^2 = $' + str(cc1) + ", p-value = " + str(pp1))
plt.plot(x, th(x, cof2[0], cof2[1], cof2[2], cof2[3]),"y", label = "fit (t=300) : " + r'$\chi^2 = $' + str(cc2) + ", p-value = " + str(pp2))
plt.plot(x, th(x, cof3[0], cof3[1], cof3[2], cof3[3]),"violet", label = "fit (t=1000) : " + r'$\chi^2 = $' + str(cc3) + ", p-value = " + str(pp3))
#plt.plot(x, th(x, cof4[0], cof4[1], cof4[2], cof4[3]), label = "fit t =5000")
plt.plot(x, th2(x, cof5[0], cof5[1]), label = "fit (t=9000) : " + r'$\chi^2 = $' + str(cc4) + ", p-value = " + str(pp4))

plt.ylabel("Temperature (°C)")
plt.xlabel("Position on the poker (m)")

plt.legend()
"""

mat = np.genfromtxt(name3)

plt.plot(x, mat[0], "*", label="t = 0 s")
plt.plot(x, mat[500], "s", label="t = 500 s")
plt.plot(x, mat[2000], ".", label="t = 2000 s")

plt.ylabel("Temperature (°C)")
plt.xlabel("Position on the poker (m)")

plt.legend()

plt.show()