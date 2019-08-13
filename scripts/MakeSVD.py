#!/usr/bin/python3
import sys
import numpy as np
import numpy.random as rnd
import numpy.linalg as la


def cPrintVector(lab,v,fmt):
    n = v.shape[0]
    sys.stdout.write( 'real8_t %s[%d] = { ' % (lab,n,) )
    sys.stdout.write( fmt % (v[0],) )
    for i in range(1,n):
        sys.stdout.write( ', ' )
        sys.stdout.write( fmt % (v[i],) )
    sys.stdout.write( ' };\n\n' )
        

def cPrintMatrix(lab,A,fmt):
    m = A.shape[0]
    n = A.shape[1]
    sys.stdout.write( 'real8_t %s[%d][%d] = {\n' % (lab,m,n,) )

    sys.stdout.write( '    { ' )
    sys.stdout.write( fmt % (A[0,0],) )
    for j in range(1,n):
        sys.stdout.write( ', ' )
        sys.stdout.write( fmt % (A[0,j],) )
    sys.stdout.write( ' },\n' )

    for i in range(1,m):
        sys.stdout.write( '    { ' )
        sys.stdout.write( fmt % (A[i,0],) )
        for j in range(1,n):
            sys.stdout.write( ', ' )
            sys.stdout.write( fmt % (A[i,j],) )
        if ( i==m-1):
            sys.stdout.write( ' }\n    };\n\n' )
        else:
            sys.stdout.write( ' },\n' )

def small(std):
    return std*np.floor(rnd.normal()*10000)/10000

def mktab(m,n,s):
    tab = np.zeros((m,n))
    for i in range(m):
        for j in range(n):
            tab[i,j] = small(s)
            
    return np.matrix(tab)

def Stack(m,n,s):
    tab = np.zeros((m,n))
    for i in range(n):
        tab[i,i] = s[i]
    return np.matrix(tab)
    

NS = 27
NV = 4

a = mktab(NS,NV,1.0)

#print(a)

U, s, V = la.svd(a, full_matrices=True)
S = Stack(NS,NV,s)

#print(U)
#print(S)
#print(V)

b = np.dot( U, np.dot( S, V ) )

c = a - b

cPrintMatrix( 'adat', a,   '%7.4f' )
cPrintVector( 'sdat', s,   '%23.16e' )
cPrintMatrix( 'vdat', V, '%23.16e' )
cPrintMatrix( 'vdat_t', V.T, '%23.16e' )
