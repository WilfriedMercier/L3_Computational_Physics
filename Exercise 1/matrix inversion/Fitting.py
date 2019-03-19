__author__ = 'Wilfried'
from numpy import exp

"""Module containing the most common fits"""

def linear(t,a):
    """linear fit with a as slope"""
    return a*t

def affine(t,a,C):
    """affine fit with a as slope and C as the intercept"""
    return a*t+C

def exp_grow_asymptote(t,A,C,tau):
    """exponential fit of a growing transitory regime
    A is the weight, C is the asymptotic value and tau the characteristic time
    For t=0 the value is A+C
    For t=infinte the value is C"""
    return A*exp(-t/tau)+C

def exp_reduc_asymptote(t,A,C,tau):
    """"exponential fit of a reducing transitory regime
    A is the weight, C is the intercept and tau the characteristic time
    For t=0 the value is C
    Fot t=infinite the value is A+C"""
    return A*(1-exp(-t/tau))+C