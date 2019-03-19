__author__ = 'Wilfried'

from numpy import sqrt

"""Personnal scientific module"""

def scientific_res(comatrice, parametres, *numeros):
    """
    code allowing to return the result of a fit with the right amount of decimals in the result and
    in the uncertainty

    Syntax :

    resultat_scientifique(cov1, params1, 0, 2)

    to have the parameters 0 and 2 with a scientific precision
    with cov1 the covariance matrix and params1 the matrix containing the parameters"""
    res = []
    err =  []
    if not numeros :
        for i in range(len(parametres)):
            count = 0
            err.append(sqrt(comatrice[i][i]))
            while err[i]<1:
                err[i] *= 10
                count += 1
            err[i] = round(float(err[i]),0)/(10**count)
            res.append(round(parametres[i],count))
    else :
        for i in range(len(numeros)):
            count = 0
            err.append(sqrt(comatrice[numeros[i]][numeros[i]]))
            while err[i]<=1:
                err[i] *= 10
                count += 1
            err[i] = round(float(err[i]),0)/(10**count)
            res.append(round(parametres[numeros[i]],count))
    return res, err