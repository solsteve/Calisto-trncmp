// ====================================================================== BEGIN FILE =====
// **                                    L I N A L G                                    **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019, Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
// **                                                                                   **
// **  -------------------------------------------------------------------------------  **
// **                                                                                   **
// **  Callisto is free software: you can redistribute it and/or modify it under the    **
// **  terms of the GNU General Public License as published by the Free Software        **
// **  Foundation, either version 3 of the License, or (at your option)                 **
// **  any later version.                                                               **
// **                                                                                   **
// **  Callisto is distributed in the hope that it will be useful, but WITHOUT          **
// **  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS    **
// **  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.   **
// **                                                                                   **
// **  You should have received a copy of the GNU General Public License along with     **
// **  Callisto. If not, see <https://www.gnu.org/licenses/>.                           **
// **                                                                                   **
// ----- Modification History ------------------------------------------------------------
//
/** @brief  Linear algebra functions.
 *  @file   LinAlg.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-23
 *
 *  Provides the mathods for linear algebra functions.
 */
// =======================================================================================

#include <LinAlg.hh>

TLOGGER_INSTANCE( logger );

// =======================================================================================
/** @brief Get Row.
 *  @param[out] v    reference to the destination Vector.
 *  @param[in]  M    reference to the source      Matrix.
 *  @param[in]  ridx row index.
 *
 *  Extract row ridx from the Matrix M and store it in the Vector v.
 */
// ---------------------------------------------------------------------------------------
void getRow( Vector& v, Matrix& M, int32_t ridx ) {
  // -------------------------------------------------------------------------------------
  int32_t nr = M.size(0);
  int32_t nc = M.size(1);
  int32_t r  = ridx % nr;
  v.resize(nc);
  for ( int32_t c=0; c<nc; c++ ) {
    v(c) = M(r,c);
  }
}


// =======================================================================================
/** @brief Set Row.
 *  @param[in,out] M    reference to the Matrix.
 *  @param[in]     v    reference to the source Vector.
 *  @param[in]     ridx row index.
 *
 *  Set the ridx row of Matrix M with the elements from Vector v.
 */
// ---------------------------------------------------------------------------------------
void setRow( Matrix& M, Vector& v, int32_t ridx ) {
  // -------------------------------------------------------------------------------------
  int32_t nr = M.size(0);
  int32_t nc = Min( M.size(1), v.size() );
  int32_t r  = ridx % nr;
  for ( int32_t c=0; c<nc; c++ ) {
    M(r,c) = v(c);
  }
}


// =======================================================================================
/** @brief Get Column.
 *  @param[out] v    reference to the destination Vector.
 *  @param[in]  M    reference to the source      Matrix.
 *  @param[in]  cidx column index.
 *
 *  Extract column cidx from the Matrix M and store it in the Vector v.
 */
// ---------------------------------------------------------------------------------------
void getCol( Vector& v, Matrix& M, int32_t cidx ) {
  // -------------------------------------------------------------------------------------
  int32_t nr = M.size(0);
  int32_t nc = M.size(1);
  int32_t c  = cidx % nc;
  v.resize(nr);
  for ( int32_t r=0; r<nr; r++ ) {
    v(r) = M(r,c);
  }
}


// =======================================================================================
/** @brief Set Column.
 *  @param[in,out] M    reference to the Matrix.
 *  @param[in]     v    reference to the source Vector.
 *  @param[in]     cidx column index.
 *
 *  Set the cidx column of Matrix M with the elements from Vector v.
 */
// ---------------------------------------------------------------------------------------
void setCol( Matrix& M, Vector& v, int32_t cidx ) {
  // -------------------------------------------------------------------------------------
  int32_t nr = Min( M.size(0), v.size() );
  int32_t nc = M.size(1);
  int32_t c  = cidx % nc;
  for ( int32_t r=0; r<nr; r++ ) {
    M(r,c) = v(r);
  }
}


// =======================================================================================
/** @brief Get Diagonal.
 *  @param[out] v reference to the destination Vector.
 *  @param[in]  M reference to the source      Matrix.
 *
 *  Extract the diagonal from the Matrix M and store it in the Vector v.
 */
// ---------------------------------------------------------------------------------------
void getDiag( Vector& v, Matrix& M ) {
  // -------------------------------------------------------------------------------------
  int32_t n = Min( M.size(0), M.size(1) );
  v.resize(n);
  for ( int32_t i=0; i<n; i++ ) {
    v(i) = M(i,i);
  }
}


// =======================================================================================
/** @brief Set Diagonal.
 *  @param[in,out] M reference to the Matrix.
 *  @param[in]  
 *
 *  Set the diagonal of Matrix M with the elements from Vector v.
 */
// ---------------------------------------------------------------------------------------
void setDiag( Matrix& M, Vector& v ) {
  // -------------------------------------------------------------------------------------
  int32_t n = Min( M.size(0), Min( M.size(1), v.size() ) );
  for ( int32_t i=0; i<n; i++ ) {
    M(i,i) = v(i);
  }
}


// =======================================================================================
/** @brief Vector-matrix Multiply.
 *  @param[out] a reference to the destination Vector.
 *  @param[in]  v reference to the left  hand side Vector.
 *  @param[in]  M reference to the right hand side Matrix.
 *
 *  Perform a Vector dot Matrix operation.  <a| = <v|M
 */
// ---------------------------------------------------------------------------------------
void dot( Vector& a, Vector& v, Matrix& M ) {
  // -------------------------------------------------------------------------------------
  int32_t n  = v.size();
  int32_t nr = M.size(0);
  int32_t nc = M.size(1);
  if ( n == nr ) {
    a.resize(nc);
    for ( int32_t c=0; c<nc; c++ ) {
      real8_t sum = D_ZERO;
      for ( int32_t i=0; i<nr; i++ ) {
        sum += (v(i) * M(i,c));
      }
      a(c) = sum;
    }
  } else {
    logger->error( "dot: v(1,%d) does not match M(%d,%d)", n, nr, nc );
  }
}


// =======================================================================================
/** @brief Vector-matrix Multiply.
 *  @param[out] a reference to the destination Vector.
 *  @param[in]  M reference to the left hand side Matrix.
 *  @param[in]  v reference to the right hand side Vector.
 *
 *  Perform a Matrix dot Vector operation.  |a> = M|v>
 */
// ---------------------------------------------------------------------------------------
void dot( Vector& a, Matrix& M, Vector& v ) {
  // -------------------------------------------------------------------------------------
  int32_t nr = M.size(0);
  int32_t nc = M.size(1);
  int32_t n  = v.size();
  if ( n == nc ) {
    a.resize(nr);
    for ( int32_t r=0; r<nr; r++ ) {
      real8_t sum = D_ZERO;
      for ( int32_t i=0; i<nc; i++ ) {
        sum += (M(r,i) * v(i));
      }
      a(r) = sum;
    }
  } else {
    logger->error( "dot: M(%d,%d) does not match v(%d,1)", nr, nc, n );
  }
}


// =======================================================================================
/** @brief Vector-matrix Multiply.
 *  @param[out] a reference to the destination Vector.
 *  @param[in]  v reference to the left  hand side Vector.
 *  @param[in]  M reference to the right hand side Matrix.
 *  @param[in]  b reference to the additive Vector.
 *
 *  Perform a Vector dot Matrix plus Vector operation.  <a| = <v|M + <b|
 */
// ---------------------------------------------------------------------------------------
void dotAdd( Vector& a, Vector& v, Matrix& M, Vector& b ) {
  // -------------------------------------------------------------------------------------
  int32_t n  = v.size();
  int32_t nr = M.size(0);
  int32_t nc = M.size(1);
  int32_t k  = b.size();
  if ( n == nr ) {
    if ( nc == k ) {
      a.resize(nc);
      for ( int32_t c=0; c<nc; c++ ) {
        real8_t sum = b(c);
        for ( int32_t i=0; i<nr; i++ ) {
          sum += (v(i) * M(i,c));
        }
        a(c) = sum;
      }
    } else {
      logger->error( "dot: b(1,%d) does not match expected (1,%d)", k, nc );
    }
  } else {
    logger->error( "dot: v(1,%d) does not match M(%d,%d)", n, nr, nc );
  }
}


// =======================================================================================
/** @brief Vector-matrix Multiply.
 *  @param[out] a reference to the destination Vector.
 *  @param[in]  M reference to the left  hand side Matrix.
 *  @param[in]  v reference to the right hand side Vector.
 *  @param[in]  b reference to the additive Vector.
 *
 *  Perform a Matrix dot Vector plus Vector operation.  |a> = M|v> + |b>
 */
// ---------------------------------------------------------------------------------------
void dotAdd( Vector& a, Matrix& M, Vector& v, Vector& b ) {
  // -------------------------------------------------------------------------------------
  int32_t nr = M.size(0);
  int32_t nc = M.size(1);
  int32_t n  = v.size();
  int32_t k  = b.size();
  if ( n == nc ) {
    if ( nr == k ) {
      a.resize(nr);
      for ( int32_t r=0; r<nr; r++ ) {
        real8_t sum = b(r);
        for ( int32_t i=0; i<nc; i++ ) {
          sum += (M(r,i) * v(i));
        }
        a(r) = sum;
      }
    } else {
      logger->error( "dot: b(%d,1) does not match expected (%d,1)", k, nr );
    }
  } else {
    logger->error( "dot: M(%d,%d) does not match v(%d,1)", nr, nc, n );
  }
}


// =======================================================================================
/** @brief Outer Product.
 *  @param[out] a reference to the destination Matrix.
 *  @param[in]  col reference to the left  side column vector.
 *  @param[in]  row reference to the right side row vector.
 *
 *  Perform outer product VVector multiplication.  M = |col><row|
 */
// ---------------------------------------------------------------------------------------
void outer( Matrix& M, Vector& col, Vector& row ) {
  // -------------------------------------------------------------------------------------
  int32_t nr = col.size();
  int32_t nc = row.size();
  M.resize(nr,nc);
  for ( int32_t c=0; c<nc; c++ ) {
    for ( int32_t r=0; r<nr; r++ ) {
      M(r,c) = col(r) * row(c);
    }
  }
}


// =======================================================================================
/** @brief Vector-matrix Multiply.
 *  @param[in] a referemnce to the left and right-transpose Vector.
 *  @param[in] M reference to the Matrix operator.
 *  @return scalar.
 *
 *  Perform a Vector dot Matrix dot Vector operation.  s = <a|M|a>
 */
// ---------------------------------------------------------------------------------------
real8_t vMv( Vector& a, Matrix& M ) {
  // -------------------------------------------------------------------------------------
  real8_t scale = D_ZERO;

  int32_t nr = M.size(0);
  int32_t nc = M.size(1);
  int32_t n  = a.size();
  
  if ( nr == nc ) {
    if ( n == nr ) {

      
      for ( int32_t i=0; i<n; i++ ) {
	real8_t sum = D_ZERO;
	for ( int32_t j=0; j<n; j++ ) {
	  sum += ( a(j) * M(j,i) );
	}
	scale += (sum * a(i));
      }

      
    } else {
      logger->error( "vMv(a,M): vector length does not match: Matrix a(1,%d) * M(%d,%d) * a(%d,1)",
		     n, nr, nc, n);
    }
  } else {
    logger->error( "vMv(a,M): Matrix is not square: a(1,%d) * M(%d,%d) * a(%d,1)",
		   n, nr, nc, n );
  }
  
  return scale;
}


// =======================================================================================
/** @brief Vector-matrix Multiply.
 *  @param[in] row reference to the left side column vector.
 *  @param[in] M   reference to the Matrix operator.
 *  @param[in] col reference to the right side row vector.
 *  @return scalar.
 *
 *  Perform a Vector dot Matrix dot Vector operation.  s = <row|M|col>
 */
// ---------------------------------------------------------------------------------------
real8_t vMv( Vector& row, Matrix& M,  Vector& col ) {
  // -------------------------------------------------------------------------------------
  real8_t scale = D_ZERO;

  int32_t nr = M.size(0);
  int32_t nc = M.size(1);
  int32_t n  = row.size();
  int32_t c  = col.size();
  if ( nr == nc ) {
    if (n == c) {
      if ( n == nr ) {
	for ( int32_t i=0; i<n; i++ ) {
	  real8_t sum = D_ZERO;
	  for ( int32_t j=0; j<n; j++ ) {
	    sum += ( row(j)*M(j,i) );
	  }
	  scale += col(i)*sum;
	}
      } else {
	logger->error( "vMv(r,M,c): vector length does not match: "
		       "Matrix row(1,%d) * M(%d,%d) * col(%d,1)",
		       n, nr, nc, c);
      }
    } else {
      logger->error( "vMv(r,M,c): vectors notsame length: "
		     "row(1,%d) * M(%d,%d) * col(%d,1)",
		     n, nr, nc, c );
    }
  } else {
    logger->error( "vMv(r,M,c): Matrix is not square: "
		   "row(1,%d) * M(%d,%d) * col(%d,1)",
		   n, nr, nc, c );
  }
  
  return scale;
}


// =======================================================================================
/** @brief Vector-matrix Multiply.
 *  @param[in] a  referemnce to the left and right-transpose sample Vector.
 *  @param[in] mu referemnce to the left and right-transpose mean   Vector.
 *  @param[in] S reference to the Matrix operator.
 *  @return scalar.
 *
 *  Perform a Vector dot Matrix dot Vector operation.  s = <a-mu|S|a-mu>
 *  @note is a is a sample Vector and mu is a Vector representing the mean of the
 *        samples, and S is the inverse of the covariance of the samples then the
 *        scalar returned is the square of the Mahalanobis distance. 
 */
// ---------------------------------------------------------------------------------------
real8_t vMv( Vector& a, Vector& mu, Matrix& S ) {
  // -------------------------------------------------------------------------------------
  real8_t scale = D_ZERO;

  int32_t nr = S.size(0);
  int32_t nc = S.size(1);
  int32_t n  = a.size();
  int32_t m  = mu.size();
  
  if ( nr == nc ) {
    if ( n == nr ) {
      if ( n == m ) {

      
	for ( int32_t i=0; i<n; i++ ) {
	  real8_t sum = D_ZERO;
	  for ( int32_t j=0; j<n; j++ ) {
	    sum += ( (a(j) - mu(j)) * S(j,i) );
	  }
	  scale += ( sum * (a(i) - mu(i)) );
	}

      
      } else {
	logger->error( "vSv(a,mu,S): vector lengths does not match: "
		       "Matrix a(1,%d) && mu(1,%d)",
		       n, m);
      }
    } else {
      logger->error( "vSv(a,mu,S): vector length does not match: "
		     "Matrix a(1,%d) * S(%d,%d) * a(%d,1)",
		     n, nr, nc, n);
    }
  } else {
    logger->error( "vSv(a,mu,S): Matrix is not square: a(1,%d) * S(%d,%d) * a(%d,1)",
		   n, nr, nc, n );
  }
  
  return scale;
}



// =======================================================================================
/** @brief Covariance.
 *  @param[out] cov reference to the covariance Matrix.
 *  @param[in]  tab reference to the Table containng the data.
 *  @param[in]  mu  reference to a Vector containing the column means from the table.
 */
// ---------------------------------------------------------------------------------------
void covariance( Matrix& cov, const Table& tab, const Vector& mu ) {
  // -------------------------------------------------------------------------------------
  int32_t ns   = tab.size(0);
  int32_t nv   = tab.size(1);
  real8_t fnm1 = static_cast<real8_t>(ns - 1);

  cov.resize(nv);

  for ( int32_t i=0; i<nv; i++ ) {
    real8_t iMean = mu.get(i);
    for ( int32_t j=i; j<nv; j++ ) {
      real8_t jMean = mu.get(j);
      real8_t c_sum = D_ZERO;
      for ( int32_t k=0; k<ns; k++ ) {
        real8_t x = tab.get(k,i) - iMean;
        real8_t y = tab.get(k,j) - jMean;
        c_sum += ( x * y );
      }
      c_sum /= fnm1;
      cov(i,j) = c_sum;
      cov(j,i) = c_sum;
    }
  }

}


// =======================================================================================
/** @brief Covariance.
 *  @param[out] cov reference to the covariance Matrix.
 *  @param[in]  tab reference to the Table containng the data.
 *  @param[in]  mu  pointer to an array containing the column means from the table.
 */
// ---------------------------------------------------------------------------------------
void covariance( Matrix& cov, const Table& tab, real8_t* mu ) {
  // -------------------------------------------------------------------------------------
  Vector temp( size(tab,1), mu );
  covariance( cov, tab, temp );
}


// =======================================================================================
/** @brief Covariance.
 *  @param[out] cov reference to the covariance Matrix.
 *  @param[in]  tab reference to the Table containng the data.
 */
// ---------------------------------------------------------------------------------------
void covariance( Matrix& cov, const Table& tab ) {
  // -------------------------------------------------------------------------------------
  real8_t temp[size(tab,1)];
  tab.mean( temp, size(tab,1), 0 );
  covariance( cov, tab, temp );
}


// =======================================================================================
/** @brief Correlation.
 *  @param[out] cor reference to the correlation Matrix.
 *  @param[in]  cov reference to the covariance Matrix.
 */
// ---------------------------------------------------------------------------------------
void correlate( Matrix& cor, const Matrix& cov ) {
  // -------------------------------------------------------------------------------------
  const int32_t n = Min( size( cov, 0 ), size( cov, 1 ) );
  cor.resize( n, n );
  for ( int32_t j=0; j<n; j++ ) {
    const real8_t jvar = cov.get(j,j);
    for ( int32_t i=0; i<n; i++ ) {
      if ( i==j ) {
	cor(i,i) = D_ONE;
      } else {
	real8_t w = cov.get(i,j) / ( cov.get(i,i) * jvar );
	cor(i,j) = w;
	cor(j,i) = w;
      }
    }
  }
}


// =======================================================================================
// **                                    L I N A L G                                    **
// ======================================================================== END FILE =====
