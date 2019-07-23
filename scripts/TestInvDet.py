#!/usr/bin/python3

import numpy as np
import numpy.random as rnd
import numpy.linalg as la

rnd.seed()

def small():
    x = 20.0*rnd.uniform() - 10.0
    return float( '%.2f' % (x,) )

def table( nr, nc ):
    a = [[small() for i in range(nc)] for j in range(nr)]
    return np.matrix(a)

def TEST(nsamp):

    fp = open('invdet.dat','w')

    fp.write('%d\n' % (nsamp,) )
    
    for samp in range(nsamp):
        n = rnd.randint(2,3)
        A = table(n,n)
        B = la.inv(A)
        d = la.det(A)

        fp.write( '%d  %25.18e ' % (n,d,) )

        for r in range(n):
            for c in range(n):
                x = A[r,c]
                fp.write( ' %.4f' % (x,) )

        for r in range(n):
            for c in range(n):
                x = B[r,c]
                fp.write( ' %25.18e' % (x,) )

        fp.write( '\n' )

    fp.close()
    
#/ =======================================================================================

TEST(200)
