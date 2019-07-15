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

  void init    ( const int32_t n, const int32_t inc );
  void destroy ( void );
  
public:
  Vector  ( void );
  Vector  ( real8_t* a, int32_t n );
  Vector  ( const int32_t n, const int32_t inc=1 );
  Vector  ( const Vector& src );
  ~Vector ( void );

  real8_t& operator() ( int32_t i ) { return *(x+(i*incx)); }

  real8_t* load       ( real8_t* src );
  real8_t* store      ( real8_t* dst );

  void     copy       ( const Vector& src );
  Vector&  operator=  ( const Vector& src );

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

  const real8_t* X          ( void )            { return x; }
  const int32_t* INCX       ( void )            { return &incx; }
  const int32_t* N          ( void )            { return &ne; }
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
// ---------------------------------------------------------------------------------------
inline  void Vector::swap( Vector& that ) {
  // -------------------------------------------------------------------------------------
  int32_t n = Min( this->ne, that.ne );
  dswap_( &n, this->x, &(this->incx), that.x, &(that.incx) );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  void Vector::copy( const Vector& src ) {
  // -------------------------------------------------------------------------------------
  if ( ne != src.ne ) { init( src.ne, 1 ); }
  dcopy_(&(src.ne), src.x, &(src.incx), x, &incx );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  Vector::Vector( void ) : INIT_VEC(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  Vector::Vector( real8_t* a, int32_t n ) : INIT_VEC(0) {
// -------------------------------------------------------------------------------------
  init(n,1);
  load(a);
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  Vector::Vector( const int32_t n, const int32_t inc ) : INIT_VEC(0) {
  // -------------------------------------------------------------------------------------
  init(n,inc);
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
// ---------------------------------------------------------------------------------------
inline  Vector&  Vector::operator=  ( const Vector& src ) {
  // -------------------------------------------------------------------------------------
  this->copy( src );
  return *this;
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
  return *(V.N());
}


#endif


// =======================================================================================
// **                                    V E C T O R                                    **
// ======================================================================== END FILE =====
