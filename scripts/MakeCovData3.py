#!/usr/bin/python3

import numpy as np
import numpy.random as rnd

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

N_SAMP = 40

MU_X = 10.0
MU_Y =  5.0
MU_Z =  2.0

SIGMA_X = 7.0
SIGMA_Y = 3.0
SIGMA_Z = 1.0

ROLL  = 10.0
PITCH = 30.0
YAW   = 45.0

rot = np.dot( ROT3(YAW), np.dot( ROT2(PITCH), ROT1(ROLL) ) )

data = np.matrix(np.zeros((N_SAMP,3)))
P    = np.matrix(np.zeros((3,1)))

for i in range(N_SAMP):
    P[0,0] = SIGMA_X*rnd.normal()
    P[1,0] = SIGMA_Y*rnd.normal()
    P[2,0] = SIGMA_Z*rnd.normal()

    X = np.dot(rot,P)

    data[i,0] = X[0]
    data[i,1] = X[1]
    data[i,2] = X[2]

C1 = np.cov(data.T)

for i in range(N_SAMP):
    data[i,0] += MU_X
    data[i,1] += MU_Y
    data[i,2] += MU_Z

C2 = np.cov(data.T)

print( '\nreal8_t cov[3][3] = {' )
print( '   { %23.16e, %23.16e, %23.16e },' % ( C1[0,0], C1[0,1], C1[0,2] ) )
print( '   { %23.16e, %23.16e, %23.16e },' % ( C1[1,0], C1[1,1], C1[1,2] ) )
print( '   { %23.16e, %23.16e, %23.16e }'  % ( C1[2,0], C1[2,1], C1[2,2] ) )
print( '};\n' )

print( '\nreal8_t cov[3][3] = {' )
print( '   { %23.16e, %23.16e, %23.16e },' % ( C2[0,0], C2[0,1], C2[0,2] ) )
print( '   { %23.16e, %23.16e, %23.16e },' % ( C2[1,0], C2[1,1], C2[1,2] ) )
print( '   { %23.16e, %23.16e, %23.16e }'  % ( C2[2,0], C2[2,1], C2[2,2] ) )
print( '};\n' )

n = np.shape(data)[0]

print( '\nreal8_t data[][3] = {' )
for i in range(n):
    if ( i == n-1 ):
        print( '   { %23.16e, %23.16e, %23.16e }'  % ( data[i,0], data[i,1], data[i,2] ) )
    else:
        print( '   { %23.16e, %23.16e, %23.16e },' % ( data[i,0], data[i,1], data[i,2] ) )
        
print( '};\n' )
   
