// ====================================================================== BEGIN FILE =====
// **                                  M A T R I X 3 D                                  **
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
/** @brief  Three by three element matrix.
 *  @file   Matrix3D.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-04
 *
 *  Provides the interface for a three by three element matrix.
 */
// =======================================================================================

#ifndef __HH_MATRIX3D_TRNCMP
#define __HH_MATRIX3D_TRNCMP


#include <array_print.hh>

typedef enum { ROW_MAJOR, COLUMN_MAJOR, UPPER_TRIANGLE, LOWER_TRIANGLE } matrix3d_format_e;


// =======================================================================================
class Matrix3D {
  // -------------------------------------------------------------------------------------
 protected:
  void setRowPointer( void );
  real8_t*  m[3];   ///< row pointer

 public:
  real8_t   q[9];   ///< matrix buffer

  Matrix3D  ( void );
  Matrix3D  ( const real8_t  _q[3][3] );
  Matrix3D  ( const real8_t* q );
  Matrix3D  ( const real8_t q00, const real8_t q01, const real8_t q02,
              const real8_t q10, const real8_t q11, const real8_t q12,
              const real8_t q20, const real8_t q21, const real8_t q22 );
  
  Matrix3D  ( const real8_t* _q, matrix3d_format_e order );
  Matrix3D  ( const Matrix3D& _m );
  Matrix3D  ( const Matrix3D* _m );

  ~Matrix3D ( void );

  Matrix3D&       operator=   ( const Matrix3D& ) = default;

  void            set         ( const real8_t s = D_ZERO );
  bool            equals      ( const Matrix3D& that, const real8_t eps = D_EPSILON ) const;
  void            copy        ( const Matrix3D& that );
  void            copy        ( const Matrix3D* that );

  void            fromArray   ( const real8_t A[3][3] );
  void            toArray     (       real8_t A[3][3] );

  real8_t*        load        ( const real8_t* src, matrix3d_format_e order = ROW_MAJOR );
  real8_t*        store       (       real8_t* dst, matrix3d_format_e order = ROW_MAJOR );

  static Matrix3D Zero        ( void );
  static Matrix3D Ident       ( void );

  const Matrix3D  T           ( void );

  real8_t         det         ( void ) const;
  const Matrix3D  inverse     ( void );
  
  real8_t*        at          ( const size_t r );
  real8_t*        operator[]  ( const size_t r );

  void            swap        ( Matrix3D& M );
  void            swap_row    ( size_t ia, size_t ib );
  void            swap_col    ( size_t ia, size_t ib );

  void            getRow      ( real8_t r[3], size_t i );
  void            getColumn   ( real8_t c[3], size_t i );
  void            getDiagonal ( real8_t d[3] );

  void            setRow      ( const real8_t r[3], size_t i );
  void            setColumn   ( const real8_t c[3], size_t i );
  void            setDiagonal ( const real8_t d[3] );


  // ----- inplace element operations -------------------------------------

  Matrix3D& operator=  ( const real8_t s );
  Matrix3D& operator+= ( const real8_t s );
  Matrix3D& operator-= ( const real8_t s );
  Matrix3D& operator*= ( const real8_t s );
  Matrix3D& operator/= ( const real8_t s );
  
  Matrix3D& operator+= ( const Matrix3D& v );
  Matrix3D& operator-= ( const Matrix3D& v );
  Matrix3D& operator*= ( const Matrix3D& v );
  Matrix3D& operator/= ( const Matrix3D& v );
};

const Matrix3D operator+ ( const real8_t&  s, const Matrix3D& v );
const Matrix3D operator+ ( const Matrix3D& v, const real8_t&  s );
const Matrix3D operator+ ( const Matrix3D& A, const Matrix3D& B );

const Matrix3D operator- ( const real8_t&  s, const Matrix3D& v );
const Matrix3D operator- ( const Matrix3D& v, const real8_t&  s );
const Matrix3D operator- ( const Matrix3D& A, const Matrix3D& B );

const Matrix3D operator* ( const real8_t&  s, const Matrix3D& v );
const Matrix3D operator* ( const Matrix3D& v, const real8_t&  s );
const Matrix3D operator* ( const Matrix3D& A, const Matrix3D& B );

const Matrix3D operator/ ( const real8_t&  s, const Matrix3D& v );
const Matrix3D operator/ ( const Matrix3D& v, const real8_t&  s );
const Matrix3D operator/ ( const Matrix3D& A, const Matrix3D& B );

const Matrix3D dot       ( const Matrix3D& A, const Matrix3D& B );
const Matrix3D dot       ( const Matrix3D* A, const Matrix3D* B );

real8_t        sum       ( const Matrix3D& A );
real8_t        sumsq     ( const Matrix3D& A );
real8_t        sumsq     ( const Matrix3D& A, const Matrix3D& B );


std::string    toString  ( Matrix3D& M,
                           std::string sfmt = DEFAULT_PRINT_FORMAT,
                           std::string cdel = DEFAULT_PRINT_COL_DELIM,
                           std::string rdel = DEFAULT_PRINT_ROW_DELIM );
  
std::string    toString  ( Matrix3D* M,
                           std::string sfmt = DEFAULT_PRINT_FORMAT,
                           std::string cdel = DEFAULT_PRINT_COL_DELIM,
                           std::string rdel = DEFAULT_PRINT_ROW_DELIM );

// =======================================================================================
/** @brief Set Row Pointers.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix3D::setRowPointer( void ) {
  // -------------------------------------------------------------------------------------
  m[0] = (q+0);
  m[1] = (q+3);
  m[2] = (q+6);
}

// =======================================================================================
/** @brief Index operator.
 *  @param i index.
 *  @return pointer to the ith row in this matrix.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t* Matrix3D::at( const size_t i ) {
  // -------------------------------------------------------------------------------------
  return m[i];
}


// =======================================================================================
/** @brief Index operator.
 *  @param i index.
 *  @return pointer to the ith row in this matrix.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t* Matrix3D::operator[]( const size_t i ) {
  // -------------------------------------------------------------------------------------
  return m[i];
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix3D::Matrix3D( void ) :
    m{0,0,0},
    q{ D_ZERO, D_ZERO, D_ZERO, 
          D_ZERO, D_ZERO, D_ZERO,
          D_ZERO, D_ZERO, D_ZERO }
{
  // -------------------------------------------------------------------------------------
  setRowPointer();
}


// =======================================================================================
/** @brief Constructor.
 *  @param q00 element at index (0,0)
 *  @param q01 element at index (0,1)
 *  @param q02 element at index (0,2)
 *  @param q10 element at index (1,0)
 *  @param q11 element at index (1,1)
 *  @param q12 element at index (1,2)
 *  @param q20 element at index (2,0)
 *  @param q21 element at index (2,1)
 *  @param q22 element at index (2,2)
 */
// ---------------------------------------------------------------------------------------
inline  Matrix3D::Matrix3D(
    const real8_t q00, const real8_t q01, const real8_t q02,
    const real8_t q10, const real8_t q11, const real8_t q12,
    const real8_t q20, const real8_t q21, const real8_t q22 ) :
    m{0,0,0},
    q{ q00, q01, q02,
          q10, q11, q12,
          q20, q21, q22 }
{
  // -------------------------------------------------------------------------------------
  setRowPointer();
}

    
// =======================================================================================
/** @brief Constructor.
 *  @param q three by three static array.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix3D::Matrix3D( const real8_t _q[3][3] ) :
    m{0,0,0},
    q{ _q[0][0], _q[0][1], _q[0][2],
          _q[1][0], _q[1][1], _q[1][2],
          _q[2][0], _q[2][1], _q[2][2] }
{
  // -------------------------------------------------------------------------------------
  setRowPointer();
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] q     pointer to array containing data.
 *  @param[in] order enum for format of data.
 *
 *  order: ROW_MAJOR, COLUMN_MAJOR, UPPER_TRIANGLE, LOWER_TRIANGLE
 */
// ---------------------------------------------------------------------------------------
inline  Matrix3D::Matrix3D( const real8_t* _q ) :
    m{0,0,0},
    q{ _q[0], _q[1], _q[2],
          _q[3], _q[4], _q[5],
          _q[6], _q[7], _q[8] }
{
  // -------------------------------------------------------------------------------------
  setRowPointer();
}


// =======================================================================================
/** @brief Zero.
 *  @return Zero Matrix.
 */
// ---------------------------------------------------------------------------------------
inline Matrix3D Matrix3D::Zero( void ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( D_ZERO, D_ZERO, D_ZERO,
                   D_ZERO, D_ZERO, D_ZERO,
                   D_ZERO, D_ZERO, D_ZERO );
}


// =======================================================================================
/** @brief Identity.
 *  @return Identity Matrix.
 */
// ---------------------------------------------------------------------------------------
inline Matrix3D Matrix3D::Ident( void ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( D_ONE,  D_ZERO, D_ZERO,
                   D_ZERO, D_ONE,  D_ZERO,
                   D_ZERO, D_ZERO, D_ONE );
}


// =======================================================================================
/** @brief Transpose.
 *  @return Transpose of this Matrix3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D Matrix3D::T( void ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( this->q[0], this->q[3], this->q[6],
                   this->q[1], this->q[4], this->q[7],
                   this->q[2], this->q[5], this->q[8] );
}


// =======================================================================================
/** @brief toString.
 *  @param[in] v    pointer to a matrix.
 *  @param[in] sfmt edit descriptor.
 *  @param[in] cdel column delimiter.
 *  @param[in] rdel row delimiter.
 *  @return string representation of the matrix.
 *
 *  Format a Matrix3D for printing and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
inline  std::string toString( Matrix3D* M, std::string sfmt,
                              std::string cdel, std::string rdel ) {
  // -------------------------------------------------------------------------------------
  return toString( *M, sfmt, cdel, rdel );
}


// =======================================================================================
/** @brief Inplace scalar addition.
 *  @param[in] s scalar value.
 *  @return reference to this Matrix3D.
 *
 *  Add the scalar to all the elements of this Matrix3D.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix3D& Matrix3D::operator+= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->q[0] += s;  this->q[1] += s;  this->q[2] += s;
  this->q[3] += s;  this->q[4] += s;  this->q[5] += s;
  this->q[6] += s;  this->q[7] += s;  this->q[8] += s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar subtraction.
 *  @param[in] s scalar value.
 *  @return reference to this Matrix3D.
 *
 *  Subtract the scalar from all elements of this Matrix3D.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix3D& Matrix3D::operator-= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->q[0] -= s;  this->q[1] -= s;  this->q[2] -= s;
  this->q[3] -= s;  this->q[4] -= s;  this->q[5] -= s;
  this->q[6] -= s;  this->q[7] -= s;  this->q[8] -= s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar multiplication.
 *  @param[in] s scalar value.
 *  @return reference to this Matrix3D.
 *
 *  Multiply all elements of this Matrix3D by the scalar.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix3D& Matrix3D::operator*= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->q[0] *= s;  this->q[1] *= s;  this->q[2] *= s;
  this->q[3] *= s;  this->q[4] *= s;  this->q[5] *= s;
  this->q[6] *= s;  this->q[7] *= s;  this->q[8] *= s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar division.
 *  @param[in] s scalar value.
 *  @return reference to this Matrix3D.
 *
 *  Divide all elements of this Matrix3D by the scalar.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix3D& Matrix3D::operator/= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->q[0] /= s;  this->q[1] /= s;  this->q[2] /= s;
  this->q[3] /= s;  this->q[4] /= s;  this->q[5] /= s;
  this->q[6] /= s;  this->q[7] /= s;  this->q[8] /= s;
  return *this;
}







// =======================================================================================
/** @brief Inplace matrix addition.
 *  @param[in] that reference to a Matrix3D.
 *  @return reference to this Matrix3D.
 *
 *  Element wise addition.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix3D& Matrix3D::operator+= ( const Matrix3D& that ) {
  // -------------------------------------------------------------------------------------
  this->q[0] += that.q[0];  this->q[1] += that.q[1];  this->q[2] += that.q[2];
  this->q[3] += that.q[3];  this->q[4] += that.q[4];  this->q[5] += that.q[5];
  this->q[6] += that.q[6];  this->q[7] += that.q[7];  this->q[8] += that.q[8];
  return *this;
}


// =======================================================================================
/** @brief Inplace matrix subtraction.
 *  @param[in] that reference to a Matrix3D.
 *  @return reference to this Matrix3D.
 *
 *  Element wise subtraction.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix3D& Matrix3D::operator-= ( const Matrix3D& that ) {
  // -------------------------------------------------------------------------------------
  this->q[0] -= that.q[0];  this->q[1] -= that.q[1];  this->q[2] -= that.q[2];
  this->q[3] -= that.q[3];  this->q[4] -= that.q[4];  this->q[5] -= that.q[5];
  this->q[6] -= that.q[6];  this->q[7] -= that.q[7];  this->q[8] -= that.q[8];
  return *this;
}


// =======================================================================================
/** @brief Inplace matrix multiplication.
 *  @param[in] that reference to a Matrix3D.
 *  @return reference to this Matrix3D.
 *
 *  Element wise multiplication.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix3D& Matrix3D::operator*= ( const Matrix3D& that ) {
  // -------------------------------------------------------------------------------------
  this->q[0] *= that.q[0];  this->q[1] *= that.q[1];  this->q[2] *= that.q[2];
  this->q[3] *= that.q[3];  this->q[4] *= that.q[4];  this->q[5] *= that.q[5];
  this->q[6] *= that.q[6];  this->q[7] *= that.q[7];  this->q[8] *= that.q[8];
  return *this;
}


// =======================================================================================
/** @brief Inplace matrix division.
 *  @param[in] that reference to a Matrix3D.
 *  @return reference to this Matrix3D.
 *
 *  Element wise division.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix3D& Matrix3D::operator/= ( const Matrix3D& that ) {
  // -------------------------------------------------------------------------------------
  this->q[0] /= that.q[0];  this->q[1] /= that.q[1];  this->q[2] /= that.q[2];
  this->q[3] /= that.q[3];  this->q[4] /= that.q[4];  this->q[5] /= that.q[5];
  this->q[6] /= that.q[6];  this->q[7] /= that.q[7];  this->q[8] /= that.q[8];
  return *this;
}


// =======================================================================================
/** @brief Determinant.
 *  @return determinant of this matrix.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Matrix3D::det( void ) const {
  // -------------------------------------------------------------------------------------
  return
      ( this->q[0] * ((this->q[4] * this->q[8]) - (this->q[7] * this->q[5])) ) +
      ( this->q[3] * ((this->q[7] * this->q[2]) - (this->q[1] * this->q[8])) ) +
      ( this->q[6] * ((this->q[1] * this->q[5]) - (this->q[4] * this->q[2])) );
}


// =======================================================================================
/** @brief Swap.
 *  @param[inout] that reference to a matrix.
 *
 *  Swap the contents of this with that.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix3D::swap( Matrix3D& that ) {
  // -------------------------------------------------------------------------------------
  std::swap( this->q[0], that.q[0] );
  std::swap( this->q[1], that.q[1] );
  std::swap( this->q[2], that.q[2] );
  std::swap( this->q[3], that.q[3] );
  std::swap( this->q[4], that.q[4] );
  std::swap( this->q[5], that.q[5] );
  std::swap( this->q[6], that.q[6] );
  std::swap( this->q[7], that.q[7] );
  std::swap( this->q[8], that.q[8] );
}


// =======================================================================================
/** @brief Swap Rows.
 *  @param[in] ia first  row.
 *  @param[in] ia second row.
 *
 *  Swap the contents of two rows with each other.
 */ 
// ---------------------------------------------------------------------------------------
inline  void Matrix3D::swap_row( size_t ia, size_t ib ) {
  // -------------------------------------------------------------------------------------
  if ( 0 == ia ) {
    if ( 1 == ib ) {
      std::swap( q[0], q[3] );
      std::swap( q[1], q[4] );
      std::swap( q[2], q[5] );
    }
    if ( 2 == ib ) {
      std::swap( q[0], q[6] );
      std::swap( q[1], q[7] );
      std::swap( q[2], q[8] );
    }
  }

  if ( 1 == ia ) {
    if ( 0 == ib ) {
      std::swap( q[3], q[0] );
      std::swap( q[4], q[1] );
      std::swap( q[5], q[2] );
    }
    if ( 2 == ib ) {
      std::swap( q[3], q[6] );
      std::swap( q[4], q[7] );
      std::swap( q[5], q[8] );
    }
  }

  if ( 2 == ia ) {
    if ( 0 == ib ) {
      std::swap( q[6], q[0] );
      std::swap( q[7], q[1] );
      std::swap( q[8], q[2] );
    }
    if ( 1 == ib ) {
      std::swap( q[6], q[3] );
      std::swap( q[7], q[4] );
      std::swap( q[8], q[5] );
    }
  }

}


// =======================================================================================
/** @brief Swap Columns.
 *  @param[in] ia first  column.
 *  @param[in] ia second column.
 *
 *  Swap the contents of two colums with each other.
 */ 
// ---------------------------------------------------------------------------------------
inline  void Matrix3D::swap_col( size_t ia, size_t ib ) {
  // -------------------------------------------------------------------------------------
  if ( 0 == ia ) {
    if ( 1 == ib ) {
      std::swap( q[0], q[1] );
      std::swap( q[3], q[4] );
      std::swap( q[6], q[7] );
    }
    if ( 2 == ib ) {
      std::swap( q[0], q[2] );
      std::swap( q[3], q[5] );
      std::swap( q[6], q[8] );
    }
  }

  if ( 1 == ia ) {
    if ( 0 == ib ) {
      std::swap( q[1], q[0] );
      std::swap( q[4], q[3] );
      std::swap( q[7], q[6] );
    }
    if ( 2 == ib ) {
      std::swap( q[1], q[2] );
      std::swap( q[4], q[5] );
      std::swap( q[7], q[8] );
    }
  }

  if ( 2 == ia ) {
    if ( 0 == ib ) {
      std::swap( q[2], q[0] );
      std::swap( q[5], q[3] );
      std::swap( q[8], q[6] );
    }
    if ( 1 == ib ) {
      std::swap( q[2], q[1] );
      std::swap( q[5], q[4] );
      std::swap( q[8], q[7] );
    }
  }

}


// =======================================================================================
/** @brief Get Row.
 *  @param[out] r reference to a three element array.
 *  @param[in]  i index.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix3D::getRow( real8_t r[3], size_t i ) {
  // -------------------------------------------------------------------------------------
  switch(i%3) {
    case 0:
      r[0] = this->q[0];
      r[1] = this->q[1];
      r[2] = this->q[2];
      break;
    
    case 1:
      r[0] = this->q[3];
      r[1] = this->q[4];
      r[2] = this->q[5];
      break;
    
    case 2:
      r[0] = this->q[6];
      r[1] = this->q[7];
      r[2] = this->q[8];
      break;

    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}

  
// =======================================================================================
/** @brief Get Column.
 *  @param[out] c reference to a three element array.
 *  @param[in]  i index.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix3D::getColumn( real8_t c[3], size_t i ) {
  // -------------------------------------------------------------------------------------
  switch(i%3) {
    case 0:
      c[0] = this->q[0];
      c[1] = this->q[3];
      c[2] = this->q[6];
      break;
    
    case 1:
      c[0] = this->q[1];
      c[1] = this->q[4];
      c[2] = this->q[7];
      break;
    
    case 2:
      c[0] = this->q[2];
      c[1] = this->q[5];
      c[2] = this->q[8];
      break;

    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}

  
// =======================================================================================
/** @brief Get Diagonal.
 *  @param[out] d reference to a three element array.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix3D::getDiagonal( real8_t d[3] ) {
  // -------------------------------------------------------------------------------------
  d[0] = this->q[0];
  d[1] = this->q[4];
  d[2] = this->q[8];
}

  
// =======================================================================================
/** @brief Set Row.
 *  @param[in] r reference to a three element array.
 *  @param[in] i index.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix3D::setRow( const real8_t r[3], size_t i ) {
  // -------------------------------------------------------------------------------------
  switch(i%3) {
    case 0:
      this->q[0] = r[0];
      this->q[1] = r[1];
      this->q[2] = r[2];
      break;
      
    case 1:
      this->q[3] = r[0];
      this->q[4] = r[1];
      this->q[5] = r[2];
      break;
      
    case 2:
      this->q[6] = r[0];
      this->q[7] = r[1];
      this->q[8] = r[2];
      break;

    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}

  
// =======================================================================================
/** @brief Set Column.
 *  @param[in] c reference to a three element array.
 *  @param[in] i index.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix3D::setColumn( const real8_t c[3], size_t i ) {
  // -------------------------------------------------------------------------------------
  switch(i%3) {
    case 0:
      this->q[0] = c[0];
      this->q[3] = c[1];
      this->q[6] = c[2];
      break;
      
    case 1:
      this->q[1] = c[0];
      this->q[4] = c[1];
      this->q[7] = c[2];
      break;
      
    case 2:
      this->q[2] = c[0];
      this->q[5] = c[1];
      this->q[8] = c[2];
      break;

    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}

  
// =======================================================================================
/** @brief Set Diagonal.
 *  @param[in] d reference to a three element array.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix3D::setDiagonal( const real8_t d[3] ) {
  // -------------------------------------------------------------------------------------
  this->q[0] = d[0];
  this->q[4] = d[1];
  this->q[8] = d[2];
}











// =======================================================================================
/** @brief Addition.
 *  @param s scalar value.
 *  @param m reference Matrix3D.
 *  @return new matrix.
 *
 *  Add a scalar value to each element of a Matrix3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D operator+( const real8_t& s, const Matrix3D& m ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( s+m.q[0], s+m.q[1], s+m.q[2],
                   s+m.q[3], s+m.q[4], s+m.q[5],
                   s+m.q[6], s+m.q[7], s+m.q[8] );
}

// =======================================================================================
/** @brief Subtraction.
 *  @param s scalar value.
 *  @param m reference Matrix3D.
 *  @return new matrix.
 *
 *  Subtract each element of a Matrix3D from the same scalar value.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D operator-( const real8_t& s, const Matrix3D& m ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( s-m.q[0], s-m.q[1], s-m.q[2],
                   s-m.q[3], s-m.q[4], s-m.q[5],
                   s-m.q[6], s-m.q[7], s-m.q[8] );
}

// =======================================================================================
/** @brief Multiplication.
 *  @param s scalar value.
 *  @param m reference Matrix3D.
 *  @return new matrix.
 *
 *  Multiply each element of a Matrix3D with the same scalar value.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D operator*( const real8_t& s, const Matrix3D& m ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( s*m.q[0], s*m.q[1], s*m.q[2],
                   s*m.q[3], s*m.q[4], s*m.q[5],
                   s*m.q[6], s*m.q[7], s*m.q[8] );
}

// =======================================================================================
/** @brief Division.
 *  @param s scalar value.
 *  @param m reference Matrix3D.
 *  @return new matrix.
 *
 *  Divide the same scalar value by each element of a Matrix3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D operator/( const real8_t& s, const Matrix3D& m ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( s/m.q[0], s/m.q[1], s/m.q[2],
                   s/m.q[3], s/m.q[4], s/m.q[5],
                   s/m.q[6], s/m.q[7], s/m.q[8] );
}


// =======================================================================================
/** @brief Addition.
 *  @param m reference Matrix3D.
 *  @param s scalar value.
 *  @return new matrix.
 *
 *  Add a scalar value to each element of a Matrix3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D operator+( const Matrix3D& m, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( m.q[0]+s, m.q[1]+s, m.q[2]+s,
                   m.q[3]+s, m.q[4]+s, m.q[5]+s,
                   m.q[6]+s, m.q[7]+s, m.q[8]+s );
}


// =======================================================================================
/** @brief Subtraction.
 *  @param m reference Matrix3D.
 *  @param s scalar value.
 *  @return new matrix.
 *
 *  Subtract the same scalar value from each element of a Matrix3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D operator-( const Matrix3D& m, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( m.q[0]-s, m.q[1]-s, m.q[2]-s,
                   m.q[3]-s, m.q[4]-s, m.q[5]-s,
                   m.q[6]-s, m.q[7]-s, m.q[8]-s );
}


// =======================================================================================
/** @brief Multiplication.
 *  @param m reference Matrix3D.
 *  @param s scalar value.
 *  @return new matrix.
 *
 *  Multiply the same scalar value with each element of a Matrix3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D operator*( const Matrix3D& m, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( m.q[0]*s, m.q[1]*s, m.q[2]*s,
                   m.q[3]*s, m.q[4]*s, m.q[5]*s,
                   m.q[6]*s, m.q[7]*s, m.q[8]*s );
}


// =======================================================================================
/** @brief Division.
 *  @param m reference Matrix3D.
 *  @param s scalar value.
 *  @return new matrix.
 *
 *  Divide the same scalar value by each element of a Matrix3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D operator/( const Matrix3D& m, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( m.q[0]/s, m.q[1]/s, m.q[2]/s,
                   m.q[3]/s, m.q[4]/s, m.q[5]/s,
                   m.q[6]/s, m.q[7]/s, m.q[8]/s );
}




// =======================================================================================
/** @brief Addition.
 *  @param A reference Matrix3D.
 *  @param B reference Matrix3D.
 *  @return new matrix.
 *
 *  Add two Matrices in element wise addition.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D operator+( const Matrix3D& A, const Matrix3D& B ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( A.q[0]+B.q[0], A.q[1]+B.q[1], A.q[2]+B.q[2],
                   A.q[3]+B.q[3], A.q[4]+B.q[4], A.q[5]+B.q[5],
                   A.q[6]+B.q[6], A.q[7]+B.q[7], A.q[8]+B.q[8] );
}


// =======================================================================================
/** @brief Subtraction.
 *  @param A reference Matrix3D.
 *  @param B reference Matrix3D.
 *  @return new matrix.
 *
 *  Subtract two Matrices in element wise subtraction.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D operator-( const Matrix3D& A, const Matrix3D& B ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( A.q[0]-B.q[0], A.q[1]-B.q[1], A.q[2]-B.q[2],
                   A.q[3]-B.q[3], A.q[4]-B.q[4], A.q[5]-B.q[5],
                   A.q[6]-B.q[6], A.q[7]-B.q[7], A.q[8]-B.q[8] );
}


// =======================================================================================
/** @brief Multiplication.
 *  @param A reference Matrix3D.
 *  @param B reference Matrix3D.
 *  @return new matrix.
 *
 *  Multiply two Matrices in element wise multiplication.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D operator*( const Matrix3D& A, const Matrix3D& B ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( A.q[0]*B.q[0], A.q[1]*B.q[1], A.q[2]*B.q[2],
                   A.q[3]*B.q[3], A.q[4]*B.q[4], A.q[5]*B.q[5],
                   A.q[6]*B.q[6], A.q[7]*B.q[7], A.q[8]*B.q[8] );
}


// =======================================================================================
/** @brief Division.
 *  @param A reference Matrix3D.
 *  @param B reference Matrix3D.
 *  @return new matrix.
 *
 *  Divide two Matrices in element wise division.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D operator/( const Matrix3D& A, const Matrix3D& B ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( A.q[0]/B.q[0], A.q[1]/B.q[1], A.q[2]/B.q[2],
                   A.q[3]/B.q[3], A.q[4]/B.q[4], A.q[5]/B.q[5],
                   A.q[6]/B.q[6], A.q[7]/B.q[7], A.q[8]/B.q[8] );
}


// =======================================================================================
/** @brief Dot Product.
 *  @param[in] A pointer to the first  Matrix3D.
 *  @param[in] B pointer to the second Matrix3D.
 *  @return dot product of two matrices.
 *
 *  Dot product of a Matrix3D onto a Matrix3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D dot( const Matrix3D* A, const Matrix3D* B ) {
  // -------------------------------------------------------------------------------------
  return dot( *A, *B );
}


#endif


// =======================================================================================
// **                                  M A T R I X 3 D                                  **
// ======================================================================== END FILE =====
