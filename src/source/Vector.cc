// ====================================================================== BEGIN FILE =====
// **                                    V E C T O R                                    **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019-, Stephen W. Soliday                                          **
// **                       stephen.soliday@trncmp.org                                  **
// **                       http://research.trncmp.org                                  **
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
/** @brief  BLAS & LAPACK Compatable Vector.
 *  @file   Vector.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-12
 *
 *  Provides the methods for a BLAS and LAPACK Compatable Vector.
 *
 *  Given:
 *     ne   = 5
 *     incx = 3
 *     xn   = 13    =   1 + (ne-1)*incx = 1 + (5-1)*3
 *
 *  The following Vector {0,1,2,3,4} would be stored in memory as:
 *     0|.|.|1|.|.|2|.|.|3|.|.|4
 */
// =======================================================================================


#include <Vector.hh>
#include <stdexcept>      // std::length_error


// =======================================================================================
// ---------------------------------------------------------------------------------------
void Vector::init( const int32_t n, const int32_t inc ) {
  // -------------------------------------------------------------------------------------
  if ( ( n != ne ) || ( inc != incx ) ) {
    destroy();
    ne   = n;
    incx = inc;
    xn   = 1 + ( ne-1 )*incx;
    x    = new real8_t[xn];
  }
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
void Vector::destroy ( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<real8_t*>(0) != x ) {
    delete[] x;
  }
  xn   = 0;
  ne   = 0;
  incx = 0;
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t* Vector::load( real8_t* src ) {
  // -------------------------------------------------------------------------------------
  int32_t one = 1;
  dcopy_(&ne, src, &one, x, &incx );
  return (src+ne);
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t* Vector::store( real8_t* dst ) {
  // -------------------------------------------------------------------------------------
  int32_t one = 1;
  dcopy_(&ne, x, &incx, dst, &one );
  return (dst+ne);
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
std::string toString( Vector& V, std::string sfmt, std::string sdel ) {
  // -------------------------------------------------------------------------------------
  std::string df  = sdel + sfmt;
  const char* fmt = sfmt.c_str();
  const char* del = df.c_str();

  char buffer[64];
  snprintf( buffer, 64, fmt, V(0) );
  std::string tstr = buffer;

  int32_t i, n = size(V);
  for ( i=1; i<n; i++ ) {
    snprintf( buffer, 64, del, V(i) );
    tstr.append( buffer );
  }

  return tstr;
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
std::string toString( std::string lp, Vector& V, std::string rp,
		      std::string sfmt, std::string sdel ) {
  // -------------------------------------------------------------------------------------
  std::string buffer = lp;
  buffer.append( toString( V, sfmt, sdel ) );
  buffer.append( rp );
  return buffer;
}








// =======================================================================================
/** @brief Add.
 *  @param[in] s scalar value.
 *
 *  Add a scalar value to each element of this vector.
 */
// ---------------------------------------------------------------------------------------
void Vector::add( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0, j=0; i<ne; i++ ) {
    *(x+j) += s;
    j += incx;
  } 
}


// =======================================================================================
/** @brief Add.
 *  @param[in] v  another vector.
 *
 *  Add each element of v to each corresponding element of this vector.
 */
// ---------------------------------------------------------------------------------------
void Vector::add( const Vector& v ) {
  // -------------------------------------------------------------------------------------
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      *(x + j) += *(v.x + k);
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}


// =======================================================================================
/** @brief Add.
 *  @param[in] s scalar value.
 *  @param[in] v another vector.
 *
 *  Add a scalar to each element of v and assign to each corresponding
 *  element of this vector.
 */
// ---------------------------------------------------------------------------------------
  void Vector::add( const real8_t s, const Vector& v ) {
  // -------------------------------------------------------------------------------------
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      *(x + j) = s + *(v.x + k);
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}


// =======================================================================================
/** @brief Add.
 *  @param[in] v another vector.
 *  @param[in] s scalar value.
 *
 *  Add a scalar to each element of v and assign to each corresponding
 *  element of this vector.
 */
// ---------------------------------------------------------------------------------------
  void Vector::add( const Vector& v, const real8_t s ) {
  // -------------------------------------------------------------------------------------
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      *(x + j) = *(v.x + k) + s;
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}


// =======================================================================================
/** @brief Add.
 *  @param[in] a left  side vector.
 *  @param[in] b right side vector.
 *
 *  Set this vector to the element wise addition of Vectors a and b.
 */
// ---------------------------------------------------------------------------------------
  void Vector::add( const Vector& a, const Vector& b ) {
  // -------------------------------------------------------------------------------------
  if ( a.ne == b.ne ) {
    if ( this->ne != a.ne ) {
      this->init( a.ne, 1 );
    }
    for ( int32_t i=0, j=0, ka=0, kb=0; i<ne; i++ ) {
      *(this->x + j) = *(a.x + ka) + *(b.x + kb);
      j  += this->incx;
      ka += a.incx;
      kb += b.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}






// =======================================================================================
/** @brief Subtract.
 *  @param[in] s scalar value.
 *
 *  Subtract a scalar value from each element of this vector.
 */
// ---------------------------------------------------------------------------------------
void Vector::sub( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0, j=0; i<ne; i++ ) {
    *(x+j) -= s;
    j += incx;
  } 
}


// =======================================================================================
/** @brief Subtract.
 *  @param[in] v  another vector.
 *
 *  Subtract each element of v from each corresponding element of this vector.
 */
// ---------------------------------------------------------------------------------------
void Vector::sub( const Vector& v ) {
  // -------------------------------------------------------------------------------------
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      *(x + j) -= *(v.x + k);
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}


// =======================================================================================
/** @brief Subtract.
 *  @param[in] s scalar value.
 *  @param[in] v another vector.
 *
 *  Subtract each element of v from a scalar s and assign to each corresponding
 *  element of this vector.
 */
// ---------------------------------------------------------------------------------------
  void Vector::sub( const real8_t s, const Vector& v ) {
  // -------------------------------------------------------------------------------------
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      *(x + j) = s - *(v.x + k);
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}


// =======================================================================================
/** @brief Subtract.
 *  @param[in] v another vector.
 *  @param[in] s scalar value.
 *
 *  Subtract a scalar to each element of v and assign to each corresponding
 *  element of this vector.
 */
// ---------------------------------------------------------------------------------------
  void Vector::sub( const Vector& v, const real8_t s ) {
  // -------------------------------------------------------------------------------------
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      *(x + j) = *(v.x + k) - s;
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}


// =======================================================================================
/** @brief Subtract.
 *  @param[in] a left  side vector.
 *  @param[in] b right side vector.
 *
 *  Set this vector to the element wise subtraction of Vectors a and b.
 */
// ---------------------------------------------------------------------------------------
  void Vector::sub( const Vector& a, const Vector& b ) {
  // -------------------------------------------------------------------------------------
  if ( a.ne == b.ne ) {
    if ( this->ne != a.ne ) {
      this->init( a.ne, 1 );
    }
    for ( int32_t i=0, j=0, ka=0, kb=0; i<ne; i++ ) {
      *(this->x + j) = *(a.x + ka) - *(b.x + kb);
      j  += this->incx;
      ka += a.incx;
      kb += b.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}






// =======================================================================================
/** @brief Multiply.
 *  @param[in] s scalar value.
 *
 *  Multiply a scalar value with each element of this vector.
 */
// ---------------------------------------------------------------------------------------
void Vector::mul( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0, j=0; i<ne; i++ ) {
    *(x+j) *= s;
    j += incx;
  } 
}


// =======================================================================================
/** @brief Multiply.
 *  @param[in] v  another vector.
 *
 *  Multiply each element of v with each corresponding element of this vector.
 */
// ---------------------------------------------------------------------------------------
void Vector::mul( const Vector& v ) {
  // -------------------------------------------------------------------------------------
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      *(x + j) *= *(v.x + k);
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}


// =======================================================================================
/** @brief Multiply.
 *  @param[in] s scalar value.
 *  @param[in] v another vector.
 *
 *  Multiply each element of v with a scalar s and assign to each corresponding
 *  element of this vector.
 */
// ---------------------------------------------------------------------------------------
  void Vector::mul( const real8_t s, const Vector& v ) {
  // -------------------------------------------------------------------------------------
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      *(x + j) = s * *(v.x + k);
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}


// =======================================================================================
/** @brief Multiply.
 *  @param[in] v another vector.
 *  @param[in] s scalar value.
 *
 *  Multiply a scalar with each element of v and assign to each corresponding
 *  element of this vector.
 */
// ---------------------------------------------------------------------------------------
  void Vector::mul( const Vector& v, const real8_t s ) {
  // -------------------------------------------------------------------------------------
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      *(x + j) = *(v.x + k) * s;
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}


// =======================================================================================
/** @brief Multiply.
 *  @param[in] a left  side vector.
 *  @param[in] b right side vector.
 *
 *  Set this vector to the element wise multiplication of Vectors a and b.
 */
// ---------------------------------------------------------------------------------------
  void Vector::mul( const Vector& a, const Vector& b ) {
  // -------------------------------------------------------------------------------------
  if ( a.ne == b.ne ) {
    if ( this->ne != a.ne ) {
      this->init( a.ne, 1 );
    }
    for ( int32_t i=0, j=0, ka=0, kb=0; i<ne; i++ ) {
      *(this->x + j) = *(a.x + ka) * *(b.x + kb);
      j  += this->incx;
      ka += a.incx;
      kb += b.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}






// =======================================================================================
/** @brief Divide.
 *  @param[in] s scalar value.
 *
 *  Divide each element of this vector by a scalar.
 */
// ---------------------------------------------------------------------------------------
void Vector::div( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0, j=0; i<ne; i++ ) {
    *(x+j) /= s;
    j += incx;
  } 
}


// =======================================================================================
/** @brief Divide.
 *  @param[in] v  another vector.
 *
 *  Divide each element of this vector by a coresponding element of v.
 */
// ---------------------------------------------------------------------------------------
void Vector::div( const Vector& v ) {
  // -------------------------------------------------------------------------------------
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      *(x + j) /= *(v.x + k);
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}


// =======================================================================================
/** @brief Divide.
 *  @param[in] s scalar value.
 *  @param[in] v another vector.
 *
 *  Divide a scalar s by each element of v and assign to each corresponding
 *  element of this vector.
 */
// ---------------------------------------------------------------------------------------
  void Vector::div( const real8_t s, const Vector& v ) {
  // -------------------------------------------------------------------------------------
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      *(x + j) = s / *(v.x + k);
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}


// =======================================================================================
/** @brief Divide.
 *  @param[in] v another vector.
 *  @param[in] s scalar value.
 *
 *  Divide each element of v by a scalar and assign to each corresponding
 *  element of this vector.
 */
// ---------------------------------------------------------------------------------------
  void Vector::div( const Vector& v, const real8_t s ) {
  // -------------------------------------------------------------------------------------
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      *(x + j) = *(v.x + k) / s;
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}


// =======================================================================================
/** @brief Divide.
 *  @param[in] a left  side vector.
 *  @param[in] b right side vector.
 *
 *  Set this vector to the element wise division of Vectors a and b.
 */
// ---------------------------------------------------------------------------------------
  void Vector::div( const Vector& a, const Vector& b ) {
  // -------------------------------------------------------------------------------------
  if ( a.ne == b.ne ) {
    if ( this->ne != a.ne ) {
      this->init( a.ne, 1 );
    }
    for ( int32_t i=0, j=0, ka=0, kb=0; i<ne; i++ ) {
      *(this->x + j) = *(a.x + ka) / *(b.x + kb);
      j  += this->incx;
      ka += a.incx;
      kb += b.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
}






// =======================================================================================
/** @brief Dot.
 *  @param[in] v another vector.
 *  @return the dot or inner product.
 *
 *  Compute the inner product of this vecto and v.
 */
// ---------------------------------------------------------------------------------------
real8_t Vector::dot( const Vector& v ) {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      sum += *(x + j) * *(v.x + k);
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
  return sum;
}






// =======================================================================================
/** @brief Norm.
 *  @return L1 norm for the vector.
 */
// ---------------------------------------------------------------------------------------
real8_t Vector::norm1( void ) const {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;
  for ( int32_t i=0, j=0; i<ne; i++ ) {
    sum += Abs( *(x + j) );
    j += incx;
  }
  return sum;
}


// =======================================================================================
/** @brief Norm Squared.
 *  @return square of the Euclidean norm for the vector.
 */
// ---------------------------------------------------------------------------------------
real8_t Vector::normsq( void ) const {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;
  for ( int32_t i=0, j=0; i<ne; i++ ) {
    const real8_t t = *(x + j);
    sum += (t*t);
    j += incx;
  }
  return sum;
}






// =======================================================================================
/** @brief Sum.
 *  @return sum of the elements.
 */
// ---------------------------------------------------------------------------------------
real8_t Vector::sum( void ) const {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;
  for ( int32_t i=0, j=0; i<ne; i++ ) {
    sum += *(x + j);
    j += incx;
  }
  return sum;
}


// =======================================================================================
/** @brief Sum Difference Squared.
 *  @param[in] v reference another Vector.
 *  @return sum of the square differences of the elements.
 */
// ---------------------------------------------------------------------------------------
real8_t Vector::sumsq( const Vector& v ) const {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      const real8_t d = *(x + j) - *(v.x + k);
          sum += (d*d);
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
  return sum;
}


// =======================================================================================
/** @brief Distance.
 *  @param[in] v reference another Vector.
 *  @return L1 distance.
 */
// ---------------------------------------------------------------------------------------
real8_t Vector::dist1( const Vector& v ) const {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;
  if ( ne == v.ne ) {
    for ( int32_t i=0, j=0, k=0; i<ne; i++ ) {
      sum += Abs( *(x + j) - *(v.x + k) );
      j += incx;
      k += v.incx;
    }
  } else {
    throw new std::length_error( "two vectors are not equal in size" );
  }
  return sum;
}


// =======================================================================================
/** @brief Normalize.
 *
 *  Normalize self.
 */
// ---------------------------------------------------------------------------------------
void Vector::normalize( void ) {
  // -------------------------------------------------------------------------------------
  real8_t s = norm();
  if ( isNotZero(s) ) {
    div(s);
  }
}


// =======================================================================================
/** @brief Normalize.
 *  @param[in] v reference to Vector to normalize.
 *
 *  Set this Vector to the normalization of Vector v.
 */
// ---------------------------------------------------------------------------------------
void Vector::normalize( const Vector& v ) {
  // -------------------------------------------------------------------------------------
  real8_t s = v.norm();
  if ( isNotZero(s) ) {
    div(v,s);
  }
}


// =======================================================================================
// **                                    V E C T O R                                    **
// ======================================================================== END FILE =====
