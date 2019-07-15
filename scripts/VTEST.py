#!/usr/bin/python3

import numpy as np
import sys

def P( lb, v, fmt ):
    n = v.shape[1]
    sys.stdout.write( 'real8_t %s[] = { ' % (lb,) )
    sys.stdout.write( fmt % (v[0,0],) )
    for i in range(1,n):
        sys.stdout.write( ', ' )
        sys.stdout.write( fmt % (v[0,i],) )
    sys.stdout.write( ' };\n' );

A = np.matrix( [3.1, -4.1, -5.9, 2.6, -5.3,  5.8, 9.7, -9.2] )
B = np.matrix( [2.7,  1.8, -2.8, -1.8, 2.8, -4.5, 9.0,  4.5] )

P( 'adat', A, '%.1f' )
P( 'bdat', B, '%.1f' )

print( '----- add ---------------------------------' )

P( 'test1', A + 1.2, '%.1f' )
P( 'test2', A + B,   '%.1f' )
P( 'test3', 2.1 + B, '%.1f' )
P( 'test4', B + 3.5, '%.1f' )

print( '----- sub ---------------------------------' )

P( 'test1', A - 1.2, '%.1f' )
P( 'test2', A - B,   '%.1f' )
P( 'test3', 2.1 - B, '%.1f' )
P( 'test4', B - 3.5, '%.1f' )

print( '----- mul ---------------------------------' )

P( 'test1', np.multiply(A, 1.2), '%.2f' )
P( 'test2', np.multiply(A,B),   '%.2f' )
P( 'test3', np.multiply(2.1, B), '%.2f' )
P( 'test4', np.multiply(B, 3.5), '%.2f' )

print( '----- div ---------------------------------' )

fmt = '%22.15e'

P( 'test1', A / 1.2, fmt )
P( 'test2', A / B,   fmt )
P( 'test3', 2.1 / B, fmt )
P( 'test4', B / 3.5, fmt )

print( '----- dot ---------------------------------' )

print( np.dot(A,B.T) )

print( '----- norm ---------------------------------' )

n1 = np.sum( np.abs( A ) )
ns = np.sum( np.multiply( A, A ) )
n  = np.sqrt( ns )

print( 'norm1   %f'  % (n1,) )
print( 'norm    %f'   % (n,) )
print( 'normsq  %f' % (ns,) )

print( '----- sum ---------------------------------' )

s   = np.sum( A )
ss  = np.sum( np.multiply( A, A ) )
C   = A - B
ssd = np.sum( np.multiply( C, C ) )

print( 'sum    %f'     % (s,) )
print( 'sumsq  %f'   % (ss,) )
print( 'sumsq  %f'   % (ssd,) )

print( '----- dist ---------------------------------' )

C   = A - B

n1 = np.sum( np.abs( C ) )
ns = np.sum( np.multiply( C, C ) )
n  = np.sqrt( ns )

print( 'dist1   %f'  % (n1,) )
print( 'dist    %f'   % (n,) )
print( 'distsq  %f' % (ns,) )
