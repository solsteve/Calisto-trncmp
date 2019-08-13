#!/usr/bin/python3
import sys
import numpy as np
import numpy.random as rnd
import numpy.linalg as la

def ROT1(A): # roll
    C = np.cos( np.pi * A / 180.0 )
    S = np.sin( np.pi * A / 180.0 )
    return np.matrix( [
        [1.0, 0.0, 0.0],
        [0.0,  C,  -S ],
        [0.0,  S,   C ] ] )

def ROT2(A): # pitch
    C = np.cos( np.pi * A / 180.0 )
    S = np.sin( np.pi * A / 180.0 )
    return np.matrix( [
        [ C,  0.0,  S],
        [0.0, 1.0, 0.0],
        [-S,  0.0,  C] ] )

def ROT3(A): # yaw
    C = np.cos( np.pi * A / 180.0 )
    S = np.sin( np.pi * A / 180.0 )
    return np.matrix( [
        [1.0, 0.0, 0.0],
        [0.0, 1.0, 0.0],
        [0.0, 0.0, 1.0] ] )

rnd.seed()

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

def smallX(std):
    return std*np.floor(rnd.normal()*10000)/10000

def small(std):
    return std*rnd.normal()

def Stack(m,n,s):
    tab = np.zeros((m,n))
    for i in range(n):
        tab[i,i] = s[i]
    return np.matrix(tab)
    
N_SAMP = 40

MU_X = 10.0
MU_Y =  5.0
MU_Z =  2.0

SIGMA_X = 9.0
SIGMA_Y = 4.0
SIGMA_Z = 1.0

ROLL  = 10.0
PITCH = 30.0
YAW   = 45.0

sfmt = '%10.6f'

rot = np.dot( ROT3(YAW), np.dot( ROT2(PITCH), ROT1(ROLL) ) )

data = np.matrix(np.zeros((N_SAMP,3)))
P    = np.matrix(np.zeros((3,1)))

nmv = np.sqrt( N_SAMP - 1.0 )

for i in range(N_SAMP):
    P[0,0] = small( SIGMA_X )
    P[1,0] = small( SIGMA_Y )
    P[2,0] = small( SIGMA_Z )

    X = np.dot(rot,P)

    data[i,0] = X[0]
    data[i,1] = X[1]
    data[i,2] = X[2]

Y = data / nmv

CV1 = np.cov( data, rowvar=False, ddof=1 )

CV2 = np.dot( data.T, data ) / ( N_SAMP - 1.0 )

CV3 = np.dot( Y.T, Y )

#cPrintMatrix( 'cov1', CV1, sfmt )
#cPrintMatrix( 'cov2', CV2, sfmt )
cPrintMatrix( 'cov3', CV3, sfmt )



m1 = data.mean(axis=0).reshape((3,1))
U1, s1, V1 = la.svd( data, full_matrices=True )

m2 = data.mean(axis=0).reshape((3,1))
U2, s2, V2 = la.svd( Y, full_matrices=True )

sfmt = '%10.6f'

#cPrintVector( 'mu1',   m1, sfmt )
#cPrintVector( 'sdat1', s1, sfmt )
#cPrintMatrix( 'vdat1', V1, sfmt )

cPrintVector( 'mu2',   m2, sfmt )
cPrintVector( 'sdat2', s2, sfmt )
cPrintMatrix( 'vdat2', V2, sfmt )

w1, v1 = la.eig(CV1)
w2, v2 = la.eig(CV2)
w3, v3 = la.eig(CV3)

#cPrintVector( 'eval1', w1, sfmt )
#cPrintMatrix( 'evec1', v1, sfmt )

#cPrintVector( 'eval2', w2, sfmt )
#cPrintMatrix( 'evec2', v2, sfmt )

cPrintVector( 'eval3', np.sqrt(w3), sfmt )
cPrintMatrix( 'evec3', v3.T, sfmt )
