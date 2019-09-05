#!/usr/bin/python3

import numpy as np
import numpy.random as rnd
import numpy.linalg as la

rnd.seed()

#/ =======================================================================================
def small():
    #/ -----------------------------------------------------------------------------------
    x = 20.0*rnd.uniform() - 10.0
    return float( '%.2f' % (x,) )

#/ =======================================================================================
def table( nr, nc ):
    #/ -----------------------------------------------------------------------------------
    a = [[small() for i in range(nc)] for j in range(nr)]
    return np.matrix(a)

#/ =======================================================================================
def CForm( lab, a, fmt ):
    #/ -----------------------------------------------------------------------------------
    buffer = 'real8_t %s[] = {' % (lab,)
    prefix = len(buffer)*' '
    nr = a.shape[0]
    nc = a.shape[1]
    for r in range(nr):
        if (r > 0):
            buffer = '%s%s' % (buffer,prefix,)
        for c in range(nc):
            if (0 == c):
                ss = fmt % (a[r,c],)
                buffer = '%s %s' % (buffer, ss,)
            else:
                ss = fmt % (a[r,c],)
                buffer = '%s, %s' % (buffer, ss,)
        if ( r == (nr-1) ):
            buffer = '%s };\n' % (buffer,)
        else:
            buffer = '%s,\n' % (buffer,)
    return buffer

#/ =======================================================================================
#/ =======================================================================================
nr = 5
nk = 11
nc = 7

print("""
// =======================================================================================
TEST(test_matrix_dgemm, norm_norm ) {
  // -------------------------------------------------------------------------------------
""" )
adat = table(nr,nk)
bdat = table(nk,nc)
cdat = np.dot( adat, bdat )
print('  ',CForm('adat',  adat,  '%5.2f'))
print('  ',CForm('bdat',  bdat,  '%5.2f'))
print('  ',CForm('cdat',  cdat,  '%9.4f'))

print("""
  Matrix A = Matrix::row_major(%d,%d,adat);
  Matrix B = Matrix::row_major(%d,%d,bdat);
  Matrix C = Matrix::row_major(%d,%d,cdat);
  Matrix T;
  T.dot(A,B);
  real8_t s = T.sumsq( C );
  EXPECT_NEAR( 0.0, s, 1.0e-25 );
}


""" % ( nr, nk, nk, nc, nr, nc ) )

print("""
// =======================================================================================
TEST(test_matrix_dgemm, norm_trans ) {
  // -------------------------------------------------------------------------------------
""" )
adat = table(nr,nk)
bdat = table(nc,nk)
cdat = np.dot( adat, bdat.T )
print('  ',CForm('adat',  adat,  '%5.2f'))
print('  ',CForm('bdat',  bdat,  '%5.2f'))
print('  ',CForm('cdat',  cdat,  '%9.4f'))

print("""
  Matrix A = Matrix::row_major(%d,%d,adat);
  Matrix B = Matrix::row_major(%d,%d,bdat);
  Matrix C = Matrix::row_major(%d,%d,cdat);
  Matrix T;
  T.dot(A,false,B,true);
  real8_t s = T.sumsq( C );
  EXPECT_NEAR( 0.0, s, 1.0e-26 );

}


""" % ( nr, nk, nc, nk, nr, nc ) )


print("""
// =======================================================================================
TEST(test_matrix_dgemm, trans_norm ) {
  // -------------------------------------------------------------------------------------
""" )
adat = table(nk,nr)
bdat = table(nk,nc)
cdat = np.dot( adat.T, bdat )
print('  ',CForm('adat',  adat,  '%5.2f'))
print('  ',CForm('bdat',  bdat,  '%5.2f'))
print('  ',CForm('cdat',  cdat,  '%9.4f'))

print("""
  Matrix A = Matrix::row_major(%d,%d,adat);
  Matrix B = Matrix::row_major(%d,%d,bdat);
  Matrix C = Matrix::row_major(%d,%d,cdat);
  Matrix T;
  T.dot(A,true,B,false);
  real8_t s = T.sumsq( C );
  EXPECT_NEAR( 0.0, s, 1.0e-26 );
}


""" % ( nk, nr, nk, nc, nr, nc ) )

print("""
// =======================================================================================
TEST(test_matrix_dgemm, trans_trans ) {
  // -------------------------------------------------------------------------------------
""" )
adat = table(nk,nr)
bdat = table(nc,nk)
cdat = np.dot( adat.T, bdat.T )
print('  ',CForm('adat',  adat,  '%5.2f'))
print('  ',CForm('bdat',  bdat,  '%5.2f'))
print('  ',CForm('cdat',  cdat,  '%9.4f'))

print("""
  Matrix A = Matrix::row_major(%d,%d,adat);
  Matrix B = Matrix::row_major(%d,%d,bdat);
  Matrix C = Matrix::row_major(%d,%d,cdat);
  Matrix T;
  T.dot(A,true,B,true);
  real8_t s = T.sumsq( C );
  EXPECT_NEAR( 0.0, s, 1.0e-26 );
}


""" % ( nk, nr, nc, nk, nr, nc ) )

