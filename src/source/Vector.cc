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
 */
// =======================================================================================


#include <Vector.hh>
#include <stdexcept>      // std::length_error


const int32_t Vector::static_one = 1;


// =======================================================================================
/** @brief Attach external buffer.
 *  @param[in] buffer pointer to a data source.
 *  @param[in] n      number of elements to use.
 *
 *  Make this Vector a view of another source. The buffer is attached to this Vector as
 *  its data buffer. The number of elements n becomes the dimension of this Vector.
 *
 *  @note it is the programers responsibility to clean this buffer up. A common mistake
 *        is to attack a local array to a Vector with a greater scope. When the local
 *        array goes out of scope the effect on using the Vector elsewhere becomes
 *        undefined.
 */
// ---------------------------------------------------------------------------------------
void Vector::attach( real8_t* buffer, int32_t n ) {
  // -------------------------------------------------------------------------------------
  destroy();
  x   = buffer;
  ne  = n;
  nx  = n;
  own = false;
}

// =======================================================================================
/** @brief Resize.
 *  @param[in] n      desired number of elements.
 *  @param[in] source optional source buffer.
 *
 *  Resize this Vector, if the current allocation will not suport the desired
 *  number of elements. Optionally supply an external buffer.
 *  @note if this Vector does not own its data it may only be resized with another
 *        source buffer.
 */
// ---------------------------------------------------------------------------------------
void Vector::resize( const int32_t n, real8_t* source ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<real8_t*>(0) == source ) {
    if ( n > nx ) {
      if ( own ) {
        destroy();
        x   = new real8_t[n];
        own = true;
        nx  = n;
      } else {
        throw std::invalid_argument( "Vector::resize - Vector does not own its buffer" );
      }
    }
    ne = n;
  } else {
    attach( source, n );
  }
}


// =======================================================================================
/** @brief Destroy.
 *
 *  Deallocate space for Vector.
 */
// ---------------------------------------------------------------------------------------
void Vector::destroy ( void ) {
  // -------------------------------------------------------------------------------------
  if ( own ) {
    if ( static_cast<real8_t*>(0) != x ) {
      delete[] x;
    }
  }
  x   = static_cast<real8_t*>(0);
  ne  = 0;
  nx  = 0;
  own = true;
}
















// =======================================================================================
/** @brief Set.
 *  @param[in] v value to set. (default: 0)
 *
 *  Set every element of this Vector to v.
 */
// ---------------------------------------------------------------------------------------
void Vector::set( const real8_t v ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<ne; i++ ) {
    at(i) = v;
  }
}


// =======================================================================================
/** @brief Equals.
 *  @param[in] that reference to a Vector for comparison.
 *  @param[in] eps  tolerance.
 *  @return true if every coresponding element of this Vector and that are less
 *          than eps difference. (default: system epsilon)
 *
 *  Perform an element by element comparison bewteen the Vectors this and that.
 *  If the absoulte value of the difference between any pair of elements is greater than
 *  eps return a false.
 */
// ---------------------------------------------------------------------------------------
bool Vector::equals( const Vector& that, const real8_t eps ) const {
  // -------------------------------------------------------------------------------------
  if ( this->size() != that.size() ) {return false;}
  for ( int32_t i=0; i<ne; i++ ) {
    const real8_t dif = get(i) - that.get(i);
    if ( dif < -eps ) {return false;}
    if ( dif >  eps ) {return false;}
  }
  return true;
}








// =======================================================================================
/** @brief Load.
 *  @param[in] src pointer to a source data buffer.
 *  @param[in] ins source increment value. (default: 1)
 *  @return pointer to the next availble position in the src data buffer.
 *
 *  Copy the contents of the suorce buffer into this Vector.
 */
// ---------------------------------------------------------------------------------------
real8_t* Vector::load( real8_t* src, const int32_t ins ) {
  // -------------------------------------------------------------------------------------
  if ( ne > 6 ) {
    dcopy_(&ne, src, &ins, x, &static_one );
  } else {
    if ( 1 == ins ) {
      for ( int32_t i=0; i<ne; i++ ) {
	at(i) = *(src+i);
      }
    } else {
      for ( int32_t i=0, j=0; i<ne; i++ ) {
	at(i) = *(src+j);
	j += ins;
      }      
    }
  }
  return (src+ne*ins);
}


// =======================================================================================
/** @brief Store.
 *  @param[out] dst pointer to a destination data buffer.
 *  @param[in]  ins destination increment value. (default: 1)
 *  @return pointer to the next availble position in the dst data buffer.
 *
 *  Store the elements of this Vector into a destiantion buffer.
 */
// ---------------------------------------------------------------------------------------
real8_t* Vector::store( real8_t* dst, const int32_t ins ) {
  // -------------------------------------------------------------------------------------
  dcopy_(&ne, x, &static_one, dst, &ins );
  return (dst+ne*ins);
}


// =======================================================================================
/** @brief To String.
 *  @param[in] V    reference to a Vector.
 *  @param[in] sfmt edit descriptor.   (default:  %g)
 *  @param[in] sdel element separator. (default: ',')
 *  @return string representing the Vector.
 *
 *  Format a string that represents the Vector. The format sfmt is identical to the 
 *  edit descriptors used by printf.
 */
// ---------------------------------------------------------------------------------------
std::string toString( Vector& V, std::string sfmt, std::string sdel ) {
  // -------------------------------------------------------------------------------------
  std::string df  = sdel + sfmt;
  const char* fmt = sfmt.c_str();
  const char* del = df.c_str();

  char buffer[64];
  snprintf( buffer, 64, fmt, V.get(0) );
  std::string tstr = buffer;

  int32_t i, n = size(V);
  for ( i=1; i<n; i++ ) {
    snprintf( buffer, 64, del, V.get(i) );
    tstr.append( buffer );
  }

  return tstr;
}


// =======================================================================================
/** @brief To String.
 *  @param[in] lp   left prefix.
 *  @param[in] V    reference to a Vector.
 *  @param[in] rp   right postfix.
 *  @param[in] sfmt edit descriptor.   (default:  %g)
 *  @param[in] sdel element separator. (default: ',')
 *  @return string representing the Vector.
 *
 *  Format a string that represents the Vector. The format sfmt is identical to the 
 *  edit descriptors used by printf. Surround the Vector with lp and rp.
 */
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
  for ( int32_t i=0; i<ne; i++ ) {
    at(i) += s;
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
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) += v.get(i);
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) = s + v.get(i);
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) = v.get(i) + s;
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
    this->resize( a.ne );
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) = a.get(i) + b.get(i);
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
  for ( int32_t i=0; i<ne; i++ ) {
    at(i) -= s;
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
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) -= v.get(i);
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) = s - v.get(i);
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) = v.get(i) - s;
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
    this->resize( a.ne );
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) = a.get(i) - b.get(i);
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
  for ( int32_t i=0; i<ne; i++ ) {
    at(i) *= s;
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
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) *= v.get(i);
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) = s * v.get(i);
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) = v.get(i) * s;
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
    this->resize( a.ne );
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) = a.get(i) * b.get(i);
    }
  } else {
    throw  std::length_error( "two vectors are not equal in size" );
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
  for ( int32_t i=0; i<ne; i++ ) {
    at(i) /= s;
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
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) /= v.get(i);
    }
  } else {
    throw  std::length_error( "two vectors are not equal in size" );
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
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) = s / v.get(i);
    }
  } else {
    throw  std::length_error( "two vectors are not equal in size" );
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
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) = v.get(i) / s;
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
    this->resize( a.ne );
    for ( int32_t i=0; i<ne; i++ ) {
      at(i) = a.get(i) / b.get(i);
    }
  } else {
    throw  std::length_error( "two vectors are not equal in size" );
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
    for ( int32_t i=0; i<ne; i++ ) {
      sum += ( get(i) * v.get(i) );
    }
  } else {
    throw  std::length_error( "two vectors are not equal in size" );
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
  for ( int32_t i=0; i<ne; i++ ) {
    sum += Abs( get(i) );
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
  for ( int32_t i=0; i<ne; i++ ) {
    const real8_t t = get(i);
    sum += (t*t);
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
  for ( int32_t i=0; i<ne; i++ ) {
    sum += get(i);
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
    for ( int32_t i=0; i<ne; i++ ) {
      const real8_t d = get(i) - v.get(i);
      sum += (d*d);
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
    for ( int32_t i=0; i<ne; i++ ) {
      sum += Abs( get(i) - v.get(i) );
    }
  } else {
    throw std::length_error( "two vectors are not equal in size" );
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
