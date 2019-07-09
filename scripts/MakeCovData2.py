#!/usr/bin/python3

import numpy as np
import numpy.random as rnd

def ROT(A):
    C = np.cos( np.pi * A / 180.0 )
    S = np.sin( np.pi * A / 180.0 )
    return np.matrix( [
        [C,  -S ],
        [S,   C ] ] )

rnd.seed()

N_SAMP = 40

MU_X = 10.0
MU_Y =  5.0

SIGMA_X = 7.0
SIGMA_Y = 3.0

ANGLE = 10.0

rot = ROT( ANGLE )

data = np.matrix(np.zeros((N_SAMP,2)))
P    = np.matrix(np.zeros((2,1)))

for i in range(N_SAMP):
    P[0,0] = MU_X + SIGMA_X*rnd.normal()
    P[1,0] = MU_Y + SIGMA_Y*rnd.normal()

    X = np.dot(rot,P)

    data[i,:] = X.T

C = np.cov(data.T)

print( '\nreal8_t cov[2][2] = {' )
print( '   { %23.16e, %23.16e },' % ( C[0,0], C[0,1] ) )
print( '   { %23.16e, %23.16e }'  % ( C[1,0], C[1,1] ) )
print( '};\n' )

n = np.shape(data)[0]

print( '\nreal8_t data[][2] = {' )
for i in range(n):
    if ( i == n-1 ):
        print( '   { %23.16e, %23.16e }'  % ( data[i,0], data[i,1] ) )
    else:
        print( '   { %23.16e, %23.16e },' % ( data[i,0], data[i,1] ) )
        
print( '};\n' )
   
