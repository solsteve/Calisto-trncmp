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
 *  @file   Vector.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-12
 *
 *  Provides the interface for a BLAS and LAPACK Compatable Vector.
 *
 *  \verbatim
 *  Given:
 *     ne   = 5
 *     incx = 3
 *     xn   = 13    =   1 + (ne-1)*incx = 1 + (5-1)*3
 *
 *  The following Vector {0,1,2,3,4} would be stored in memory as:
 *     0|.|.|1|.|.|2|.|.|3|.|.|4
 *  \endverbatim
 */
// =======================================================================================

#ifndef __HH_VECTOR_TRNCMP
#define __HH_VECTOR_TRNCMP


#include <blas_interface.hh>
#include <array_print.hh>


// =======================================================================================
class Vector {
  // -------------------------------------------------------------------------------------
 protected:
  real8_t * x;     ///< pointer to vectors data vector.
  int32_t   xn;    ///< allocated buffer length.
  int32_t   ne;    ///< number of elements.
  int32_t   incx;  ///< internal memory increment.

  void destroy ( void );
  void resize  ( const int32_t n, const int32_t inc );
  
public:
  Vector  ( void );
  Vector  ( const int32_t n,                    const bool init=false );
  Vector  ( const int32_t n, const int32_t inc, const bool init=false );
  
  Vector  ( const int32_t n,                    real8_t* a, const int32_t ins=1 );
  Vector  ( const int32_t n, const int32_t inc, real8_t* a, const int32_t ins=1 );
  
  Vector  ( const Vector& src );

  ~Vector ( void );

  void     set        ( const real8_t v=D_ZERO );
  bool     equals     ( const Vector& V, const real8_t eps = D_EPSILON );
  void     copy       ( const Vector& src );

  real8_t* load       ( real8_t* src, const int32_t ins=1 );
  real8_t* store      ( real8_t* dst, const int32_t ins=1 );

  real8_t& at         ( const int32_t i );
  real8_t& operator() ( const int32_t i );
  Vector&  operator=  ( const Vector& src );

  int32_t  size       ( void );
  void     swap       ( Vector& that );

  void     add        ( const real8_t s );
  void     add        ( const Vector& v );
  void     add        ( const real8_t s, const Vector& v );
  void     add        ( const Vector& v, const real8_t s );
  void     add        ( const Vector& a, const Vector& b );

  void     sub        ( const real8_t s );
  void     sub        ( const Vector& v );
  void     sub        ( const real8_t s, const Vector& v );
  void     sub        ( const Vector& v, const real8_t s );
  void     sub        ( const Vector& a, const Vector& b );

  void     mul        ( const real8_t s );
  void     mul        ( const Vector& v );
  void     mul        ( const real8_t s, const Vector& v );
  void     mul        ( const Vector& v, const real8_t s );
  void     mul        ( const Vector& a, const Vector& b );

  void     div        ( const real8_t s );
  void     div        ( const Vector& v );
  void     div        ( const real8_t s, const Vector& v );
  void     div        ( const Vector& v, const real8_t s );
  void     div        ( const Vector& a, const Vector& b );

  real8_t  dot        ( const Vector& v );

  real8_t  norm1      ( void )            const;
  real8_t  norm       ( void )            const;
  real8_t  normsq     ( void )            const;

  real8_t  sum        ( void )            const;
  real8_t  sumsq      ( void )            const;
  real8_t  sumsq      ( const Vector& v ) const;

  real8_t  dist1      ( const Vector& v ) const;
  real8_t  dist       ( const Vector& v ) const;
  real8_t  distsq     ( const Vector& v ) const;

  void     normalize  ( void );
  void     normalize  ( const Vector& v );

  // ----- BLAS inteface methods ---------------------------------------------------------

  /** @brief Data Buffer. @return pointer to data buffer. */
  const real8_t* X    ( void ) { return x; }
  
  /** @brief Number of Elements. @return pointer to number of elements. */
  const int32_t* N    ( void ) { return &ne; }

  /** @brief Increment. @return pointer to the increment. */
  const int32_t* INCX ( void ) { return &incx; }
  
}; // end class Vector


int32_t size( const Vector& V );

std::string toString( Vector& V,
		      std::string sfmt = DEFAULT_PRINT_FORMAT,
		      std::string sdel = DEFAULT_PRINT_DELIM );

std::string toString( std::string lp, Vector& V, std::string rp,
		      std::string sfmt = DEFAULT_PRINT_FORMAT,
		      std::string sdel = DEFAULT_PRINT_DELIM );


// ----- BLAS Level One Interface --------------------------------------------------------

/*
  AXPY
  DOT
  NRM2
  SUM
  AMAX
*/

#define INIT_VEC(a) x(a), xn(a), ne(a), incx(a)


// =======================================================================================
/** @brief Copy.
 *  @param[in] M reference to a source Matrix.
 *
 *  Copy all of the elements of the source M. Resize if necessary this Matrix.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector::copy( const Vector& src ) {
  // -------------------------------------------------------------------------------------
  if ( ne != src.ne ) { resize( src.ne, 1 ); }
  dcopy_(&(src.ne), src.x, &(src.incx), x, &incx );
}


// =======================================================================================
/** @brief Access.
 *  @param[in] idx index.
 *  @return reference to the element at (idx).
 *
 *  Access the element at (idx).
 */
// ---------------------------------------------------------------------------------------
inline  real8_t& Vector::at( const int32_t idx ) {
  // -------------------------------------------------------------------------------------
  return *(x+(idx*incx));
}


// =======================================================================================
/** @brief Access.
 *  @param[in] idx index.
 *  @return reference to the element at (idx).
 *
 *  Access the element at (idx).
 */
// ---------------------------------------------------------------------------------------
inline  real8_t& Vector::operator()( const int32_t idx ) {
  // -------------------------------------------------------------------------------------
  return *(x+(idx*incx));
}


// =======================================================================================
/** @brief Assignment.
 *  @param[in] rhs reference to a source Vector.
 *  @return reference to this Vector.
 *
 *  Copy all of the elements of the source src. Resize if necessary this Vector.
 */
// ---------------------------------------------------------------------------------------
inline  Vector&  Vector::operator=  ( const Vector& src ) {
  // -------------------------------------------------------------------------------------
  this->copy( src );
  return *this;
}


// =======================================================================================
/** @brief Size.
 *  @return number of elements.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t Vector::size( void ) {
  // -------------------------------------------------------------------------------------
  return ne;
}


// =======================================================================================
/** @brief Swap.
 *  @param[in] that reference to another Vector.
 *
 *  Swap all elemnts of this with the corresponding elements of that.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector::swap( Vector& that ) {
  // -------------------------------------------------------------------------------------
  int32_t n = Min( this->ne, that.ne );
  dswap_( &n, this->x, &(this->incx), that.x, &(that.incx) );
}


// =======================================================================================
/** @brief Constructor.
 *
 *  Construct an empty Vector of zero length.
 */
// ---------------------------------------------------------------------------------------
inline  Vector::Vector( void ) : INIT_VEC(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] n    number of elements in this Vector.
 *  @param[in] init if true pre initialize the vector with zeros.
 *
 *  Construct a Vector of n length. Optionally initialize the elements.
 */
// ---------------------------------------------------------------------------------------
inline  Vector::Vector( const int32_t n, const bool init ) : INIT_VEC(0) {
  // -------------------------------------------------------------------------------------
  resize(n,1);
  if ( init ) {
    set(D_ZERO);
  }
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] n  number of elements in this Vector.
 *  @param[in] it if true pre initialize the vector with zeros.
 *
 *  Construct a Vector of n length. Optionally initialize the elements.
 */
// ---------------------------------------------------------------------------------------
inline  Vector::Vector( const int32_t n, const int32_t inc, const bool init ) : INIT_VEC(0) {
  // -------------------------------------------------------------------------------------
  resize(n,inc);
  if ( init ) {
    set(D_ZERO);
  }
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  Vector::Vector( const int32_t n,
			real8_t* a, const int32_t ins ) : INIT_VEC(0) {
  // -------------------------------------------------------------------------------------
  resize(n,1);
  load(a,ins);
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  Vector::Vector( const int32_t n, const int32_t inc,
			real8_t* a, const int32_t ins ) : INIT_VEC(0) {
  // -------------------------------------------------------------------------------------
  resize(n,inc);
  load(a,ins);
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  Vector::Vector( const Vector& src ) : INIT_VEC(0) {
  // -------------------------------------------------------------------------------------
  copy(src);
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  Vector::~Vector( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}



// =======================================================================================
/** @brief Norm.
 *  @return L2 norm for the vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t  Vector::norm( void ) const {
  // -------------------------------------------------------------------------------------
  return sqrt(this->normsq());
}


// =======================================================================================
/** @brief Sum Squared.
 *  @return square of the Euclidean norm for the vector.
 *  @note this is an alias for  Vector::normsq
 */
// ---------------------------------------------------------------------------------------
inline real8_t Vector::sumsq( void ) const {
  // -------------------------------------------------------------------------------------
  return normsq();
}


// =======================================================================================
/** @brief Distance.
 *  @param[in] v reference to another Vector.
 *  @return Euclidian distance.
 */
// ---------------------------------------------------------------------------------------
inline real8_t Vector::dist( const Vector& v ) const {
  // -------------------------------------------------------------------------------------
  return sqrt(sumsq( v ));
}


// =======================================================================================
/** @brief Distance.
 *  @return square of the Euclidian distance.
 *  @note this is an alias for  Vector::sumsq
 */
// ---------------------------------------------------------------------------------------
inline real8_t Vector::distsq( const Vector& v ) const {
  // -------------------------------------------------------------------------------------
  return sumsq( v );
}
















// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  int32_t size( Vector& V ) {
  // -------------------------------------------------------------------------------------
  return V.size();
}


#endif


// =======================================================================================
// **                                    V E C T O R                                    **
// ======================================================================== END FILE =====
