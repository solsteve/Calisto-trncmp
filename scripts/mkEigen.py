#!/usr/bin/python3

import numpy        as np
import numpy.random as rnd
import numpy.linalg as la

def Small():
    return int(rnd.normal() * 100)/100

def Basic(n):
    return np.matrix([[Small() for i in range(n)] for j in range(n)])

def test(m):
    n = m.shape[0]
    D = la.det(m)
    T = np.trace(m)
    (eval, evec) = la.eig(m)
    tt=np.sum(eval).real  
    dd=np.prod(eval).real
    mse=(D-dd)*(D-dd) + (T-tt)*(T-tt)
    print(D,dd)
    print(T,tt)
    print(mse)
    for i in range(n):
        sig = eval[i]
        vec = evec[:,i]
        q1 = np.dot( m, vec )
        q2 = sig * vec
        q3 = q1 - q2
        mse = np.dot( q3.T, q3.conj() )
        print(mse.sum().real)


a = Basic(7)
b = Basic(7)
c = np.dot( a, b )
s = np.dot( a, a.T )

test(c)

test(s)
