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

def CForm( lab, a, fmt ):
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

def TEST( name, op ):
    print("""
  // =======================================================================================
    TEST(test_vector_element, %s) {
    // -------------------------------------------------------------------------------------
    """ % (name,))
    nr = rnd.randint(2,4)
    nc = rnd.randint(3,7)
    A  = table(nr,nc)
    B  = table(nr,nc)
    k  = small()
    C  = op(A,B)
    S0 = op(A,k)
    S1 = op(B,k)
    S2 = op(k,B )
    print('   ',CForm('A',  A,  '%g'))
    print('   ',CForm('B',  B,  '%g'))
    print('   ',CForm('C',  C,  '%19.12e'))
    print('   ',CForm('S0', S0, '%19.12e'))
    print('   ',CForm('S1', S1, '%19.12e'))
    print('   ',CForm('S2', S2, '%19.12e'))
    print("""    {
      Matrix  X = Matrix::row_major(%d,%d,A);
      Matrix  S = Matrix::row_major(%d,%d,S0);
      real8_t s = %g;
      X.%s(s);
      EXPECT_TRUE( X.equals(S, 1.0e-15) );
    }
""" % (nr,nc,nr,nc,k,name,) )

    print("""    {
      Matrix X = Matrix::row_major(%d,%d,A);
      Matrix Y = Matrix::row_major(%d,%d,B);
      Matrix Z = Matrix::row_major(%d,%d,C);
      X.%s(Y);
      EXPECT_TRUE( X.equals(Z, 1.0e-15) );
    }
""" % (nr,nc,nr,nc,nr,nc,name,) )

    print("""    {
      Matrix X = Matrix::row_major(%d,%d,A);
      Matrix Y = Matrix::row_major(%d,%d,B);
      Matrix S = Matrix::row_major(%d,%d,S1);
      real8_t s = %g;
      X.%s(Y,s);
      EXPECT_TRUE( X.equals(S, 1.0e-15) );
    }
""" % (nr,nc,nr,nc,nr,nc,k,name,) )

    print("""    {
      Matrix X = Matrix::row_major(%d,%d,A);
      Matrix Y = Matrix::row_major(%d,%d,B);
      Matrix S = Matrix::row_major(%d,%d,S2);
      real8_t s = %g;
      X.%s(s,Y);
      EXPECT_TRUE( X.equals(S, 1.0e-15) );
    }
""" % (nr,nc,nr,nc,nr,nc,k,name,) )

    print("""    {
      Matrix X = Matrix::row_major(%d,%d,A);
      Matrix Y = Matrix::row_major(%d,%d,B);
      Matrix Z = Matrix::row_major(%d,%d,C);
      Matrix T(2);
      T.%s(X,Y);
      EXPECT_TRUE( T.equals(Z, 1.0e-15) );
    }
""" % (nr,nc,nr,nc,nr,nc,name,) )

    print('}\n\n')

def ADD(x,y): return x + y
def SUB(x,y): return x - y
def MUL(x,y): return np.multiply(x,y)
def DIV(x,y): return np.divide(x,y)


def TEST02():

    # -------------------------------------------------
    nr = rnd.randint(3,5)
    nc = rnd.randint(4,7)
    A  = table(nr,nc)
    s  = A.sum()

    print('   ',CForm('adat',  A,  '%g'))
    print("""
  Matrix  A = Matrix::row_major(%d,%d,adat);
  EXPECT_NEAR( %.2f, A.sum(), 1.0e-18 );
""" % (nr,nc,s) )

    # -------------------------------------------------
    nr = rnd.randint(3,5)
    nc = rnd.randint(4,7)
    A  = table(nr,nc)
    s  = np.multiply(A,A).sum()

    print('   ',CForm('adat',  A,  '%g'))
    print("""
  Matrix  A = Matrix::row_major(%d,%d,adat);
  EXPECT_NEAR( %.4f, A.sumsq(), 1.0e-18 );
""" % (nr,nc,s) )

    # -------------------------------------------------
    nr = rnd.randint(3,5)
    nc = rnd.randint(4,7)
    A  = table(nr,nc)
    B  = table(nr,nc)
    C = A - B
    
    s  = np.multiply(C,C).sum()

    print('   ',CForm('adat',  A,  '%g'))
    print('   ',CForm('bdat',  B,  '%g'))
    print("""
  Matrix  A = Matrix::row_major(%d,%d,adat);
  Matrix  B = Matrix::row_major(%d,%d,bdat);
  EXPECT_NEAR( %.4f, A.sumsq(B), 1.0e-18 );
""" % (nr,nc,nr,nc,s) )

    print( "\n------------------------------------\n\n" )

    m = 4
    n = 6
    k = 5

    A  = table(m,k)
    B  = table(k,n)
    C  = np.dot(A,B)

    print('   ',CForm('adat',  A,  '%.2f'))
    print('   ',CForm('bdat',  B,  '%.2f'))
    print('   ',CForm('cdat',  C,  '%.4f'))
    
    print("""
  Matrix  A = Matrix::row_major(%d,%d,adat);
  Matrix  B = Matrix::row_major(%d,%d,bdat);
  Matrix  C = Matrix::row_major(%d,%d,cdat);
  Matrix  T(2);

  T.dot(A,B);

  EXPECT_TRUE( T.equals(C, 1.0e-15) );

""" % (m,k,k,n,m,n) )


D_N = [ 'D_ZERO', 'D_ONE', 'D_TWO', 'D_THREE', 'D_FOUR', 'D_FIVE', 'D_SIX', 'D_SEVEN', 'D_EIGHT', 'D_NINE' ]

    
def TEST03(n):
    A  = table(n,n)
    B = la.inv(A)
    d = la.det(A)
    print('\n{')
    print('   ',CForm('adat',  A,  '%.2f'))
    print('   ',CForm('bdat',  B,  '%25.18e'))
    print("""
  Matrix  A1 = Matrix::row_major(%d,%d,adat);
  Matrix  A2 = Matrix::row_major(%d,%d,adat);
  Matrix  B  = Matrix::row_major(%d,%d,bdat);
  real8_t d  = %25.18e;
  Matrix C(2);
  Matrix E(2);

  real8_t D = C.inverse(A1);
  EXPECT_TRUE( C.equals(B) );
  EXPECT_NEAR( d, D, 1.0e-9 );
  E.dot( A2, B );
  EXPECT_NEAR( %s, E.sum(), 1.0e-9 );
}

 """ % (n,n,n,n,n,n,d,D_N[n]) )

    
#/ =======================================================================================


#TEST('add',ADD)
#TEST('sub',SUB)
#TEST('mul',MUL)
#TEST('div',DIV)


TEST03(4)
TEST03(5)
TEST03(6)
TEST03(7)
