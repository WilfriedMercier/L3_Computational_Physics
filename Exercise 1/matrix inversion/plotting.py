# coding: utf8
__author__ = 'Wilfried'
import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()
sub1 = plt.subplot(2,2,1)
sub2 = plt.subplot(2,2,3, sharex=sub1)
sub3 = plt.subplot(2,2,2)
sub4 = plt.subplot(2,2,4, sharex=sub3)

fig.subplots_adjust(hspace=0.07, wspace=0.07)
plt.setp(sub1.get_xticklabels(), visible = False)
plt.setp(sub3.get_xticklabels(), visible = False)

name1 = 'time_comp_pos.txt'
name2 = 'time_comp_neg.txt'

n1 = np.genfromtxt(name1, usecols=0, skip_header=1)
n2 = np.genfromtxt(name2, usecols=0, skip_header=1)
t1 = np.genfromtxt(name1, usecols=1, skip_header=1)
t2 = np.genfromtxt(name2, usecols=1, skip_header=1)

sub1.plot(n1,t1, "^r")
sub2.plot(n2,t2, "^b")
numb1, bin1, patch1 = sub3.hist(t1, 50, facecolor = 'r')
numb2, bin2, patch2 = sub4.hist(t2, 50, facecolor = 'b')

sub1.axis([0,200,0,8])
sub3.set_xlim(0,8)
sub3.yaxis.tick_right()
sub4.yaxis.tick_right()


sub2.set_xlabel("n")
sub4.set_xlabel("Response time t(ms)")
sub1.set_ylabel("Response time t(ms)")
sub2.set_ylabel("Response time t(ms)")
sub3.set_ylabel("Distribution for 200 values")
sub4.set_ylabel("Distribution for 200 values")
sub3.yaxis.set_label_coords(1.1,0.5)
sub4.yaxis.set_label_coords(1.1,0.5)



plt.show()

