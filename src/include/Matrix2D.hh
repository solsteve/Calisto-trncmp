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
 protected:
  void setRowPointer( void );
  real8_t*  m[2];   ///< row pointer

 public:
  real8_t   q[4];   ///< matrix buffer

   Matrix2D ( void );
   Matrix2D ( const real8_t  _q[2][2] );
   Matrix2D ( const real8_t* _q );
   Matrix2D ( const real8_t q00, const real8_t q01,
                       const real8_t q10, const real8_t q11 );
  
  Matrix2D  ( const real8_t* _q, matrix2d_format_e order );
  Matrix2D  ( const Matrix2D& _m );
  Matrix2D  ( const Matrix2D* _m );

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
  
  real8_t*        at          ( const size_t r );
  real8_t*        operator[]  ( const size_t r );

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

// =======================================================================================
/** @brief Set Row Pointers.
 */
// ---------------------------------------------------------------------------------------
inline  void Matrix2D::setRowPointer( void ) {
  // -------------------------------------------------------------------------------------
  m[0] = (q+0);
  m[1] = (q+2);
}


// =======================================================================================
/** @brief Index operator.
 *  @param i index.
 *  @return pointer to the ith row in this matrix.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t* Matrix2D::at( const size_t i ) {
  // -------------------------------------------------------------------------------------
  return m[i];
}


// =======================================================================================
/** @brief Index operator.
 *  @param i index.
 *  @return pointer to the ith row in this matrix.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t* Matrix2D::operator[]( const size_t i ) {
  // -------------------------------------------------------------------------------------
  return m[i];
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix2D::Matrix2D( void ) :
m{0,0},
q{ D_ZERO, D_ZERO,
     D_ZERO, D_ZERO }
{
  // -------------------------------------------------------------------------------------
  setRowPointer();
}


// =======================================================================================
/** @brief Constructor.
 *  @param q00 element at index (0,0)
 *  @param q01 element at index (0,1)
 *  @param q10 element at index (1,0)
 *  @param q11 element at index (1,1)
 */
// ---------------------------------------------------------------------------------------
inline  Matrix2D::Matrix2D( const real8_t q00, const real8_t q01,
                                      const real8_t q10, const real8_t q11 ) :
m{0,0}, q{ q00, q01, q10, q11 }
{
  // -------------------------------------------------------------------------------------
  setRowPointer();
}

    
// =======================================================================================
/** @brief Constructor.
 *  @param q three by three static array.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix2D::Matrix2D( const real8_t _q[2][2] ) :
m{0,0},
   q{ _q[0][0], _q[0][1],
      _q[1][0], _q[1][1] }
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
inline  Matrix2D::Matrix2D( const real8_t* _q ) :
m{0,0},
  q{ _q[0], _q[1],
      _q[2], _q[3] }
{
  // -------------------------------------------------------------------------------------
  setRowPointer();
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
  return Matrix2D( this->q[0], this->q[2],
                   this->q[1], this->q[3] );
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
  this->q[0] += s;  this->q[1] += s;
  this->q[2] += s;  this->q[3] += s;
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
  this->q[0] -= s;  this->q[1] -= s;
  this->q[2] -= s;  this->q[3] -= s;
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
  this->q[0] *= s;  this->q[1] *= s;
  this->q[2] *= s;  this->q[3] *= s;
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
  this->q[0] /= s;  this->q[1] /= s;
  this->q[2] /= s;  this->q[3] /= s;
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
  this->q[0] += that.q[0];  this->q[1] += that.q[1];
  this->q[2] += that.q[2];  this->q[3] += that.q[3];
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
  this->q[0] -= that.q[0];  this->q[1] -= that.q[1];
  this->q[2] -= that.q[2];  this->q[3] -= that.q[3];
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
  this->q[0] *= that.q[0];  this->q[1] *= that.q[1];
  this->q[2] *= that.q[2];  this->q[3] *= that.q[3];
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
  this->q[0] /= that.q[0];  this->q[1] /= that.q[1];
  this->q[2] /= that.q[2];  this->q[3] /= that.q[3];
  return *this;
}



// =======================================================================================
/** @brief Determinant.
 *  @return determinant of this matrix.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Matrix2D::det( void ) const {
  // -------------------------------------------------------------------------------------
  return (q[0] * q[3]) - (q[1] * q[2]);
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
  ::swap( this->q[0], that.q[0] );
  ::swap( this->q[1], that.q[1] );
  ::swap( this->q[2], that.q[2] );
  ::swap( this->q[3], that.q[3] );
}


// =======================================================================================
/** @brief Swap Rows.
 *
 *  Swap the contents of two rows with each other.
 */ 
// ---------------------------------------------------------------------------------------
inline  void Matrix2D::swap_row( void ) {
  // -------------------------------------------------------------------------------------
  ::swap( q[0], q[2] );
      ::swap( q[1], q[3] );
}


// =======================================================================================
/** @brief Swap Columns.
 *
 *  Swap the contents of two colums with each other.
 */ 
// ---------------------------------------------------------------------------------------
inline  void Matrix2D::swap_col( void ) {
  // -------------------------------------------------------------------------------------
      ::swap( q[0], q[1] );
      ::swap( q[2], q[3] );
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
      r[0] = this->q[0];
      r[1] = this->q[1];
      break;
    
    case 1:
      r[0] = this->q[2];
      r[1] = this->q[3];
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
      c[0] = this->q[0];
      c[1] = this->q[2];
      break;
    
    case 1:
      c[0] = this->q[1];
      c[1] = this->q[3];
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
  d[0] = this->q[0];
  d[1] = this->q[3];
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
      this->q[0] = r[0];
      this->q[1] = r[1];
      break;
      
    case 1:
      this->q[2] = r[0];
      this->q[3] = r[1];
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
      this->q[0] = c[0];
      this->q[2] = c[1];
      break;
      
    case 1:
      this->q[1] = c[0];
      this->q[3] = c[1];
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
  this->q[0] = d[0];
  this->q[3] = d[1];
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
  return Matrix2D( s+m.q[0], s+m.q[1],
                   s+m.q[2], s+m.q[3] );
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
  return Matrix2D( s-m.q[0], s-m.q[1],
                   s-m.q[2], s-m.q[3] );
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
  return Matrix2D( s*m.q[0], s*m.q[1],
                   s*m.q[2], s*m.q[3] );
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
  return Matrix2D( s/m.q[0], s/m.q[1],
                   s/m.q[2], s/m.q[3] );
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
  return Matrix2D( m.q[0]+s, m.q[1]+s,
                   m.q[2]+s, m.q[3]+s );
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
  return Matrix2D( m.q[0]-s, m.q[1]-s,
                   m.q[2]-s, m.q[3]-s );
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
  return Matrix2D( m.q[0]*s, m.q[1]*s,
                   m.q[2]*s, m.q[3]*s );
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
  return Matrix2D( m.q[0]/s, m.q[1]/s,
                   m.q[2]/s, m.q[3]/s );
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
  return Matrix2D( A.q[0]+B.q[0], A.q[1]+B.q[1],
                   A.q[2]+B.q[2], A.q[3]+B.q[3] );
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
  return Matrix2D( A.q[0]-B.q[0], A.q[1]-B.q[1],
                   A.q[2]-B.q[2], A.q[3]-B.q[3] );
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
  return Matrix2D( A.q[0]*B.q[0], A.q[1]*B.q[1],
                   A.q[2]*B.q[2], A.q[3]*B.q[3] );
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
  return Matrix2D( A.q[0]/B.q[0], A.q[1]/B.q[1],
                   A.q[2]/B.q[2], A.q[3]/B.q[3] );
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

#endif

// =======================================================================================
// **                                  M A T R I X 2 D                                  **
// ======================================================================== END FILE =====
