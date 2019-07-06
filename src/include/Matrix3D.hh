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
 public:
  real8_t  a00, a01, a02;   ///< First  row
  real8_t  a10, a11, a12;   ///< Second row
  real8_t  a20, a21, a22;   ///< Third  row

  constexpr Matrix3D ( void );
  constexpr Matrix3D ( const real8_t q[3][3] );
  constexpr Matrix3D ( const real8_t* q );
  constexpr Matrix3D ( const real8_t q00, const real8_t q01, const real8_t q02,
                       const real8_t q10, const real8_t q11, const real8_t q12,
                       const real8_t q20, const real8_t q21, const real8_t q22 );
  
  Matrix3D  ( const real8_t* q, matrix3d_format_e order );
  Matrix3D  ( const Matrix3D& m );
  Matrix3D  ( const Matrix3D* m );

  ~Matrix3D ( void );

  Matrix3D&       operator=  ( const Matrix3D& ) = default;

  void            set        ( const real8_t s = D_ZERO );
  void            copy       ( const Matrix3D& that );
  void            copy       ( const Matrix3D* that );

  void            fromArray  ( const real8_t A[3][3] );
  void            toArray    ( real8_t A[3][3] );

  real8_t*        load       ( const real8_t* src, matrix3d_format_e order = ROW_MAJOR );
  real8_t*        store      ( const real8_t* dst, matrix3d_format_e order = ROW_MAJOR );

  static Matrix3D Zero       ( void );
  static Matrix3D Ident      ( void );

  const Matrix3D  T          ( void );

  real8_t         det        ( void ) const;
  const Matrix3D  inverse    ( void );
  
  real8_t&        at         ( const size_t r, const size_t c );
  real8_t&        operator() ( const size_t r, const size_t c );

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


std::string    toString  ( Matrix3D& M,
                           std::string sfmt = DEFAULT_PRINT_FORMAT,
                           std::string cdel = DEFAULT_PRINT_COL_DELIM,
                           std::string rdel = DEFAULT_PRINT_ROW_DELIM );
  
std::string    toString  ( Matrix3D* M,
                           std::string sfmt = DEFAULT_PRINT_FORMAT,
                           std::string cdel = DEFAULT_PRINT_COL_DELIM,
                           std::string rdel = DEFAULT_PRINT_ROW_DELIM );

#endif


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Matrix3D::Matrix3D( void )
:   a00(D_ZERO), a01(D_ZERO), a02(D_ZERO),
    a10(D_ZERO), a11(D_ZERO), a12(D_ZERO),
    a20(D_ZERO), a21(D_ZERO), a22(D_ZERO) {
  // -------------------------------------------------------------------------------------
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
inline  constexpr Matrix3D::Matrix3D( const real8_t q00, const real8_t q01, const real8_t q02,
                                      const real8_t q10, const real8_t q11, const real8_t q12,
                                      const real8_t q20, const real8_t q21, const real8_t q22 )
:   a00(q00), a01(q01), a02(q02),
    a10(q10), a11(q11), a12(q12),
    a20(q20), a21(q21), a22(q22) {
  // -------------------------------------------------------------------------------------
}

    
// =======================================================================================
/** @brief Constructor.
 *  @param q three by three static array.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Matrix3D::Matrix3D( const real8_t q[3][3] )
:   a00(q[0][0]), a01(q[0][1]), a02(q[0][2]),
    a10(q[1][0]), a11(q[1][1]), a12(q[1][2]),
    a20(q[2][0]), a21(q[2][1]), a22(q[2][2]) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] q     pointer to array containing data.
 *  @param[in] order enum for format of data.
 *
 *  order: ROW_MAJOR, COLUMN_MAJOR, UPPER_TRIANGLE, LOWER_TRIANGLE
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Matrix3D::Matrix3D( const real8_t* q )
:   a00(q[0]), a01(q[1]), a02(q[2]),
    a10(q[3]), a11(q[4]), a12(q[5]),
    a20(q[6]), a21(q[7]), a22(q[8]) {
  // -------------------------------------------------------------------------------------
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
  return Matrix3D( this->a00, this->a10, this->a20,
                   this->a01, this->a11, this->a21,
                   this->a02, this->a12, this->a22 );
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
  this->a00 += s;  this->a01 += s;  this->a02 += s;
  this->a10 += s;  this->a11 += s;  this->a12 += s;
  this->a20 += s;  this->a21 += s;  this->a22 += s;
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
  this->a00 -= s;  this->a01 -= s;  this->a02 -= s;
  this->a10 -= s;  this->a11 -= s;  this->a12 -= s;
  this->a20 -= s;  this->a21 -= s;  this->a22 -= s;
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
  this->a00 *= s;  this->a01 *= s;  this->a02 *= s;
  this->a10 *= s;  this->a11 *= s;  this->a12 *= s;
  this->a20 *= s;  this->a21 *= s;  this->a22 *= s;
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
  this->a00 /= s;  this->a01 /= s;  this->a02 /= s;
  this->a10 /= s;  this->a11 /= s;  this->a12 /= s;
  this->a20 /= s;  this->a21 /= s;  this->a22 /= s;
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
  this->a00 += that.a00;  this->a01 += that.a01;  this->a02 += that.a02;
  this->a10 += that.a10;  this->a11 += that.a11;  this->a12 += that.a12;
  this->a20 += that.a20;  this->a21 += that.a21;  this->a22 += that.a22;
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
  this->a00 -= that.a00;  this->a01 -= that.a01;  this->a02 -= that.a02;
  this->a10 -= that.a10;  this->a11 -= that.a11;  this->a12 -= that.a12;
  this->a20 -= that.a20;  this->a21 -= that.a21;  this->a22 -= that.a22;
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
  this->a00 *= that.a00;  this->a01 *= that.a01;  this->a02 *= that.a02;
  this->a10 *= that.a10;  this->a11 *= that.a11;  this->a12 *= that.a12;
  this->a20 *= that.a20;  this->a21 *= that.a21;  this->a22 *= that.a22;
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
  this->a00 /= that.a00;  this->a01 /= that.a01;  this->a02 /= that.a02;
  this->a10 /= that.a10;  this->a11 /= that.a11;  this->a12 /= that.a12;
  this->a20 /= that.a20;  this->a21 /= that.a21;  this->a22 /= that.a22;
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
      ( this->a00 * ((this->a11 * this->a22) - (this->a21 * this->a12)) ) +
      ( this->a10 * ((this->a21 * this->a02) - (this->a01 * this->a22)) ) +
      ( this->a20 * ((this->a01 * this->a12) - (this->a11 * this->a02)) );
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
  return Matrix3D( s+m.a00, s+m.a01, s+m.a02,
                   s+m.a10, s+m.a11, s+m.a12,
                   s+m.a20, s+m.a21, s+m.a22 );
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
  return Matrix3D( s-m.a00, s-m.a01, s-m.a02,
                   s-m.a10, s-m.a11, s-m.a12,
                   s-m.a20, s-m.a21, s-m.a22 );
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
  return Matrix3D( s*m.a00, s*m.a01, s*m.a02,
                   s*m.a10, s*m.a11, s*m.a12,
                   s*m.a20, s*m.a21, s*m.a22 );
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
  return Matrix3D( s/m.a00, s/m.a01, s/m.a02,
                   s/m.a10, s/m.a11, s/m.a12,
                   s/m.a20, s/m.a21, s/m.a22 );
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
  return Matrix3D( m.a00+s, m.a01+s, m.a02+s,
                   m.a10+s, m.a11+s, m.a12+s,
                   m.a20+s, m.a21+s, m.a22+s );
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
  return Matrix3D( m.a00-s, m.a01-s, m.a02-s,
                   m.a10-s, m.a11-s, m.a12-s,
                   m.a20-s, m.a21-s, m.a22-s );
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
  return Matrix3D( m.a00*s, m.a01*s, m.a02*s,
                   m.a10*s, m.a11*s, m.a12*s,
                   m.a20*s, m.a21*s, m.a22*s );
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
  return Matrix3D( m.a00/s, m.a01/s, m.a02/s,
                   m.a10/s, m.a11/s, m.a12/s,
                   m.a20/s, m.a21/s, m.a22/s );
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
  return Matrix3D( A.a00+B.a00, A.a01+B.a01, A.a02+B.a02,
                   A.a10+B.a10, A.a11+B.a11, A.a12+B.a12,
                   A.a20+B.a20, A.a21+B.a21, A.a22+B.a22 );
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
  return Matrix3D( A.a00-B.a00, A.a01-B.a01, A.a02-B.a02,
                   A.a10-B.a10, A.a11-B.a11, A.a12-B.a12,
                   A.a20-B.a20, A.a21-B.a21, A.a22-B.a22 );
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
  return Matrix3D( A.a00*B.a00, A.a01*B.a01, A.a02*B.a02,
                   A.a10*B.a10, A.a11*B.a11, A.a12*B.a12,
                   A.a20*B.a20, A.a21*B.a21, A.a22*B.a22 );
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
  return Matrix3D( A.a00/B.a00, A.a01/B.a01, A.a02/B.a02,
                   A.a10/B.a10, A.a11/B.a11, A.a12/B.a12,
                   A.a20/B.a20, A.a21/B.a21, A.a22/B.a22 );
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


// =======================================================================================
// **                                  M A T R I X 3 D                                  **
// ======================================================================== END FILE =====
