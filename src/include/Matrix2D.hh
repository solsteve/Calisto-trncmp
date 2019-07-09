// ====================================================================== BEGIN FILE =====
// **                                  M A T R I X 2 D                                  **
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
 *  @file   Matrix2D.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-06
 *
 *  Provides the interface for a three by three element matrix.
 */
// =======================================================================================

#ifndef __HH_MATRIX2D_TRNCMP
#define __HH_MATRIX2D_TRNCMP


#include <array_print.hh>

typedef enum { ROW_MAJOR, COLUMN_MAJOR, UPPER_TRIANGLE, LOWER_TRIANGLE } matrix2d_format_e;


// =======================================================================================
class Matrix2D {
  // -------------------------------------------------------------------------------------
 public:
  real8_t  a00, a01;   ///< First  row
  real8_t  a10, a11;   ///< Second row

  constexpr Matrix2D ( void );
  constexpr Matrix2D ( const real8_t q[2][2] );
  constexpr Matrix2D ( const real8_t* q );
  constexpr Matrix2D ( const real8_t q00, const real8_t q01,
                       const real8_t q10, const real8_t q11 );
  
  Matrix2D  ( const real8_t* q, matrix2d_format_e order );
  Matrix2D  ( const Matrix2D& m );
  Matrix2D  ( const Matrix2D* m );

  ~Matrix2D ( void );

  Matrix2D&       operator=   ( const Matrix2D& ) = default;

  void            set         ( const real8_t s = D_ZERO );
  void            copy        ( const Matrix2D& that );
  void            copy        ( const Matrix2D* that );

  void            fromArray   ( const real8_t A[2][2] );
  void            toArray     ( real8_t A[2][2] );

  real8_t*        load        ( const real8_t* src, matrix2d_format_e order = ROW_MAJOR );
  real8_t*        store       ( const real8_t* dst, matrix2d_format_e order = ROW_MAJOR );

  static Matrix2D Zero        ( void );
  static Matrix2D Ident       ( void );

  const Matrix2D  T           ( void );

  real8_t         det         ( void ) const;
  const Matrix2D  inverse     ( void );
  
  real8_t&        at          ( const size_t r, const size_t c );
  real8_t&        operator()  ( const size_t r, const size_t c );

  void            swap        ( Matrix2D& M );
  void            swap_row    ( void );
  void            swap_col    ( void );

  void            getRow      ( real8_t r[2], size_t i );
  void            getColumn   ( real8_t c[2], size_t i );
  void            getDiagonal ( real8_t d[2] );

  void            setRow      ( const real8_t r[2], size_t i );
  void            setColumn   ( const real8_t c[2], size_t i );
  void            setDiagonal ( const real8_t d[2] );

  // ----- inplace element operations -------------------------------------

  Matrix2D& operator=  ( const real8_t s );
  Matrix2D& operator+= ( const real8_t s );
  Matrix2D& operator-= ( const real8_t s );
  Matrix2D& operator*= ( const real8_t s );
  Matrix2D& operator/= ( const real8_t s );
  
  Matrix2D& operator+= ( const Matrix2D& v );
  Matrix2D& operator-= ( const Matrix2D& v );
  Matrix2D& operator*= ( const Matrix2D& v );
  Matrix2D& operator/= ( const Matrix2D& v );
};

const Matrix2D operator+ ( const real8_t&  s, const Matrix2D& v );
const Matrix2D operator+ ( const Matrix2D& v, const real8_t&  s );
const Matrix2D operator+ ( const Matrix2D& A, const Matrix2D& B );

const Matrix2D operator- ( const real8_t&  s, const Matrix2D& v );
const Matrix2D operator- ( const Matrix2D& v, const real8_t&  s );
const Matrix2D operator- ( const Matrix2D& A, const Matrix2D& B );

const Matrix2D operator* ( const real8_t&  s, const Matrix2D& v );
const Matrix2D operator* ( const Matrix2D& v, const real8_t&  s );
const Matrix2D operator* ( const Matrix2D& A, const Matrix2D& B );

const Matrix2D operator/ ( const real8_t&  s, const Matrix2D& v );
const Matrix2D operator/ ( const Matrix2D& v, const real8_t&  s );
const Matrix2D operator/ ( const Matrix2D& A, const Matrix2D& B );

const Matrix2D dot       ( const Matrix2D& A, const Matrix2D& B );
const Matrix2D dot       ( const Matrix2D* A, const Matrix2D* B );

real8_t        sum       ( const Matrix2D& M );
real8_t        sumsq     ( const Matrix2D& M );
real8_t        sumsq     ( const Matrix2D& A, const Matrix2D& B );

std::string    toString  ( Matrix2D& M,
                           std::string sfmt = DEFAULT_PRINT_FORMAT,
                           std::string cdel = DEFAULT_PRINT_COL_DELIM,
                           std::string rdel = DEFAULT_PRINT_ROW_DELIM );
  
std::string    toString  ( Matrix2D* M,
                           std::string sfmt = DEFAULT_PRINT_FORMAT,
                           std::string cdel = DEFAULT_PRINT_COL_DELIM,
                           std::string rdel = DEFAULT_PRINT_ROW_DELIM );

#endif


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Matrix2D::Matrix2D( void )
:   a00(D_ZERO), a01(D_ZERO),
    a10(D_ZERO), a11(D_ZERO) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param q00 element at index (0,0)
 *  @param q01 element at index (0,1)
 *  @param q10 element at index (1,0)
 *  @param q11 element at index (1,1)
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Matrix2D::Matrix2D( const real8_t q00, const real8_t q01,
                                      const real8_t q10, const real8_t q11 )
:   a00(q00), a01(q01),
    a10(q10), a11(q11) {
  // -------------------------------------------------------------------------------------
}

    
// =======================================================================================
/** @brief Constructor.
 *  @param q three by three static array.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Matrix2D::Matrix2D( const real8_t q[2][2] )
:   a00(q[0][0]), a01(q[0][1]),
    a10(q[1][0]), a11(q[1][1]) {
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
inline  constexpr Matrix2D::Matrix2D( const real8_t* q )
:   a00(q[0]), a01(q[1]),
    a10(q[2]), a11(q[3]) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Zero.
 *  @return Zero Matrix.
 */
// ---------------------------------------------------------------------------------------
inline Matrix2D Matrix2D::Zero( void ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( D_ZERO, D_ZERO,
                   D_ZERO, D_ZERO );
}


// =======================================================================================
/** @brief Identity.
 *  @return Identity Matrix.
 */
// ---------------------------------------------------------------------------------------
inline Matrix2D Matrix2D::Ident( void ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( D_ONE,  D_ZERO,
                   D_ZERO, D_ONE );
}


// =======================================================================================
/** @brief Transpose.
 *  @return Transpose of this Matrix2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D Matrix2D::T( void ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( this->a00, this->a10,
                   this->a01, this->a11 );
}


// =======================================================================================
/** @brief toString.
 *  @param[in] v    pointer to a matrix.
 *  @param[in] sfmt edit descriptor.
 *  @param[in] cdel column delimiter.
 *  @param[in] rdel row delimiter.
 *  @return string representation of the matrix.
 *
 *  Format a Matrix2D for printing and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
inline  std::string toString( Matrix2D* M, std::string sfmt,
                              std::string cdel, std::string rdel ) {
  // -------------------------------------------------------------------------------------
  return toString( *M, sfmt, cdel, rdel );
}


// =======================================================================================
/** @brief Inplace scalar addition.
 *  @param[in] s scalar value.
 *  @return reference to this Matrix2D.
 *
 *  Add the scalar to all the elements of this Matrix2D.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix2D& Matrix2D::operator+= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->a00 += s;  this->a01 += s;
  this->a10 += s;  this->a11 += s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar subtraction.
 *  @param[in] s scalar value.
 *  @return reference to this Matrix2D.
 *
 *  Subtract the scalar from all elements of this Matrix2D.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix2D& Matrix2D::operator-= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->a00 -= s;  this->a01 -= s;
  this->a10 -= s;  this->a11 -= s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar multiplication.
 *  @param[in] s scalar value.
 *  @return reference to this Matrix2D.
 *
 *  Multiply all elements of this Matrix2D by the scalar.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix2D& Matrix2D::operator*= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->a00 *= s;  this->a01 *= s;
  this->a10 *= s;  this->a11 *= s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar division.
 *  @param[in] s scalar value.
 *  @return reference to this Matrix2D.
 *
 *  Divide all elements of this Matrix2D by the scalar.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix2D& Matrix2D::operator/= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->a00 /= s;  this->a01 /= s;
  this->a10 /= s;  this->a11 /= s;
  return *this;
}







// =======================================================================================
/** @brief Inplace matrix addition.
 *  @param[in] that reference to a Matrix2D.
 *  @return reference to this Matrix2D.
 *
 *  Element wise addition.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix2D& Matrix2D::operator+= ( const Matrix2D& that ) {
  // -------------------------------------------------------------------------------------
  this->a00 += that.a00;  this->a01 += that.a01;
  this->a10 += that.a10;  this->a11 += that.a11;
  return *this;
}


// =======================================================================================
/** @brief Inplace matrix subtraction.
 *  @param[in] that reference to a Matrix2D.
 *  @return reference to this Matrix2D.
 *
 *  Element wise subtraction.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix2D& Matrix2D::operator-= ( const Matrix2D& that ) {
  // -------------------------------------------------------------------------------------
  this->a00 -= that.a00;  this->a01 -= that.a01;
  this->a10 -= that.a10;  this->a11 -= that.a11;
  return *this;
}


// =======================================================================================
/** @brief Inplace matrix multiplication.
 *  @param[in] that reference to a Matrix2D.
 *  @return reference to this Matrix2D.
 *
 *  Element wise multiplication.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix2D& Matrix2D::operator*= ( const Matrix2D& that ) {
  // -------------------------------------------------------------------------------------
  this->a00 *= that.a00;  this->a01 *= that.a01;
  this->a10 *= that.a10;  this->a11 *= that.a11;
  return *this;
}


// =======================================================================================
/** @brief Inplace matrix division.
 *  @param[in] that reference to a Matrix2D.
 *  @return reference to this Matrix2D.
 *
 *  Element wise division.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix2D& Matrix2D::operator/= ( const Matrix2D& that ) {
  // -------------------------------------------------------------------------------------
  this->a00 /= that.a00;  this->a01 /= that.a01;
  this->a10 /= that.a10;  this->a11 /= that.a11;
  return *this;
}



// =======================================================================================
/** @brief Determinant.
 *  @return determinant of this matrix.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Matrix2D::det( void ) const {
  // -------------------------------------------------------------------------------------
  return (a00 * a11) - (a01 * a10);
}


// =======================================================================================
/** @brief Swap.
 *  @param[inout] that reference to a matrix.
 *
 *  Swap the contents of this with that.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix2D::swap( Matrix2D& that ) {
  // -------------------------------------------------------------------------------------
  ::swap( this->a00, that.a00 );
  ::swap( this->a01, that.a01 );
  ::swap( this->a10, that.a10 );
  ::swap( this->a11, that.a11 );
}


// =======================================================================================
/** @brief Swap Rows.
 *
 *  Swap the contents of two rows with each other.
 */ 
// ---------------------------------------------------------------------------------------
inline  void Matrix2D::swap_row( void ) {
  // -------------------------------------------------------------------------------------
  ::swap( a00, a10 );
      ::swap( a01, a11 );
}


// =======================================================================================
/** @brief Swap Columns.
 *
 *  Swap the contents of two colums with each other.
 */ 
// ---------------------------------------------------------------------------------------
inline  void Matrix2D::swap_col( void ) {
  // -------------------------------------------------------------------------------------
      ::swap( a00, a01 );
      ::swap( a10, a11 );
}


// =======================================================================================
/** @brief Get Row.
 *  @param[out] r reference to a two element array.
 *  @param[in]  i index.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix2D::getRow( real8_t r[2], size_t i ) {
  // -------------------------------------------------------------------------------------
  switch(i%2) {
    case 0:
      r[0] = this->a00;
      r[1] = this->a01;
      break;
    
    case 1:
      r[0] = this->a10;
      r[1] = this->a11;
      break;
    
    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}


// =======================================================================================
/** @brief Get Column.
 *  @param[out] c reference to a two element array.
 *  @param[in]  i index.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix2D::getColumn( real8_t c[2], size_t i ) {
  // -------------------------------------------------------------------------------------
  switch(i%2) {
    case 0:
      c[0] = this->a00;
      c[1] = this->a10;
      break;
    
    case 1:
      c[0] = this->a01;
      c[1] = this->a11;
      break;
    
    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}


// =======================================================================================
/** @brief Get Diagonal.
 *  @param[out] d reference to a two element array.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix2D::getDiagonal( real8_t d[2] ) {
  // -------------------------------------------------------------------------------------
  d[0] = this->a00;
  d[1] = this->a11;
}


// =======================================================================================
/** @brief Set Row.
 *  @param[in] r reference to a two element array.
 *  @param[in] i index.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix2D::setRow( const real8_t r[2], size_t i ) {
  // -------------------------------------------------------------------------------------
  switch(i%2) {
    case 0:
      this->a00 = r[0];
      this->a01 = r[1];
      break;
      
    case 1:
      this->a10 = r[0];
      this->a11 = r[1];
      break;
      
    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}


// =======================================================================================
/** @brief Set Column.
 *  @param[in] c reference to a two element array.
 *  @param[in] i index.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix2D::setColumn( const real8_t c[2], size_t i ) {
  // -------------------------------------------------------------------------------------
  switch(i%3) {
    case 0:
      this->a00 = c[0];
      this->a10 = c[1];
      break;
      
    case 1:
      this->a01 = c[0];
      this->a11 = c[1];
      break;
      
    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}


// =======================================================================================
/** @brief Set Diagonal.
 *  @param[in] d reference to a two element array.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix2D::setDiagonal( const real8_t d[2] ) {
  // -------------------------------------------------------------------------------------
  this->a00 = d[0];
  this->a11 = d[1];
}












// =======================================================================================
/** @brief Addition.
 *  @param s scalar value.
 *  @param m reference Matrix2D.
 *  @return new matrix.
 *
 *  Add a scalar value to each element of a Matrix2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D operator+( const real8_t& s, const Matrix2D& m ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( s+m.a00, s+m.a01,
                   s+m.a10, s+m.a11 );
}

// =======================================================================================
/** @brief Subtraction.
 *  @param s scalar value.
 *  @param m reference Matrix2D.
 *  @return new matrix.
 *
 *  Subtract each element of a Matrix2D from the same scalar value.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D operator-( const real8_t& s, const Matrix2D& m ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( s-m.a00, s-m.a01,
                   s-m.a10, s-m.a11 );
}

// =======================================================================================
/** @brief Multiplication.
 *  @param s scalar value.
 *  @param m reference Matrix2D.
 *  @return new matrix.
 *
 *  Multiply each element of a Matrix2D with the same scalar value.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D operator*( const real8_t& s, const Matrix2D& m ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( s*m.a00, s*m.a01,
                   s*m.a10, s*m.a11 );
}

// =======================================================================================
/** @brief Division.
 *  @param s scalar value.
 *  @param m reference Matrix2D.
 *  @return new matrix.
 *
 *  Divide the same scalar value by each element of a Matrix2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D operator/( const real8_t& s, const Matrix2D& m ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( s/m.a00, s/m.a01,
                   s/m.a10, s/m.a11 );
}


// =======================================================================================
/** @brief Addition.
 *  @param m reference Matrix2D.
 *  @param s scalar value.
 *  @return new matrix.
 *
 *  Add a scalar value to each element of a Matrix2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D operator+( const Matrix2D& m, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( m.a00+s, m.a01+s,
                   m.a10+s, m.a11+s );
}


// =======================================================================================
/** @brief Subtraction.
 *  @param m reference Matrix2D.
 *  @param s scalar value.
 *  @return new matrix.
 *
 *  Subtract the same scalar value from each element of a Matrix2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D operator-( const Matrix2D& m, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( m.a00-s, m.a01-s,
                   m.a10-s, m.a11-s );
}


// =======================================================================================
/** @brief Multiplication.
 *  @param m reference Matrix2D.
 *  @param s scalar value.
 *  @return new matrix.
 *
 *  Multiply the same scalar value with each element of a Matrix2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D operator*( const Matrix2D& m, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( m.a00*s, m.a01*s,
                   m.a10*s, m.a11*s );
}


// =======================================================================================
/** @brief Division.
 *  @param m reference Matrix2D.
 *  @param s scalar value.
 *  @return new matrix.
 *
 *  Divide the same scalar value by each element of a Matrix2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D operator/( const Matrix2D& m, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( m.a00/s, m.a01/s,
                   m.a10/s, m.a11/s );
}




// =======================================================================================
/** @brief Addition.
 *  @param A reference Matrix2D.
 *  @param B reference Matrix2D.
 *  @return new matrix.
 *
 *  Add two Matrices in element wise addition.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D operator+( const Matrix2D& A, const Matrix2D& B ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( A.a00+B.a00, A.a01+B.a01,
                   A.a10+B.a10, A.a11+B.a11 );
}


// =======================================================================================
/** @brief Subtraction.
 *  @param A reference Matrix2D.
 *  @param B reference Matrix2D.
 *  @return new matrix.
 *
 *  Subtract two Matrices in element wise subtraction.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D operator-( const Matrix2D& A, const Matrix2D& B ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( A.a00-B.a00, A.a01-B.a01,
                   A.a10-B.a10, A.a11-B.a11 );
}


// =======================================================================================
/** @brief Multiplication.
 *  @param A reference Matrix2D.
 *  @param B reference Matrix2D.
 *  @return new matrix.
 *
 *  Multiply two Matrices in element wise multiplication.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D operator*( const Matrix2D& A, const Matrix2D& B ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( A.a00*B.a00, A.a01*B.a01,
                   A.a10*B.a10, A.a11*B.a11 );
}


// =======================================================================================
/** @brief Division.
 *  @param A reference Matrix2D.
 *  @param B reference Matrix2D.
 *  @return new matrix.
 *
 *  Divide two Matrices in element wise division.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D operator/( const Matrix2D& A, const Matrix2D& B ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( A.a00/B.a00, A.a01/B.a01,
                   A.a10/B.a10, A.a11/B.a11 );
}


// =======================================================================================
/** @brief Dot Product.
 *  @param[in] A pointer to the first  Matrix2D.
 *  @param[in] B pointer to the second Matrix2D.
 *  @return dot product of two matrices.
 *
 *  Dot product of a Matrix2D onto a Matrix2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D dot( const Matrix2D* A, const Matrix2D* B ) {
  // -------------------------------------------------------------------------------------
  return dot( *A, *B );
}


// =======================================================================================
// **                                  M A T R I X 2 D                                  **
// ======================================================================== END FILE =====
