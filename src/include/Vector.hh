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
  int32_t   ne;    ///< number of elements.
  int32_t   nx;    ///< max allocation
  bool      own;   ///< does this Vector own its buffer x?

  static const int32_t static_one;
  
  void destroy        ( void );
              
 public:
  Vector              ( void );
  Vector              ( const int32_t n,             const bool init=false );
  Vector              ( const int32_t n, real8_t* a, const int32_t ins=1 );
  
  Vector              ( const Vector& src );

  ~Vector             ( void );

  static Vector view  ( real8_t* buffer, int32_t n );
  void     attach     ( real8_t* buffer, int32_t n );

  void     resize     ( const int32_t n, real8_t* source = static_cast<real8_t*>(0) );

  void     set        ( const real8_t v=D_ZERO );
  bool     equals     ( const Vector& V, const real8_t eps = D_EPSILON ) const;
  void     copy       ( const Vector& src );

  real8_t* load       ( real8_t* src, const int32_t ins=1 );
  real8_t* store      ( real8_t* dst, const int32_t ins=1 );

  void     set        ( const int32_t i, const real8_t val );
  real8_t  get        ( const int32_t i ) const;
  real8_t& at         ( const int32_t i );
  real8_t& operator() ( const int32_t i );
  Vector&  operator=  ( const Vector& src );

  int32_t  size       ( void ) const;
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
  const real8_t* X    ( void ) const { return x; }
  
  /** @brief Number of Elements. @return pointer to number of elements. */
  const int32_t* N    ( void ) const { return &ne; }

  /** @brief Increment. @return pointer to the increment. */
  const int32_t* INCX ( void ) const { return &static_one; }
  
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

#define INIT_VEC(a) x(a), ne(a), nx(a), own(true)


// =======================================================================================
/** @brief Create Vector with an external buffer.
 *  @param[in] buffer pointer to a data source.
 *  @param[in] n      number of elements to use.
 *
 *  Make a Vector as view of another source. The buffer is attached to the new Vector as
 *  its data buffer. The number of elements n becomes the dimension of that Vector.
 *
 *  @note it is the programers responsibility to clean this buffer up.
 */
// ---------------------------------------------------------------------------------------
inline  Vector Vector::view( real8_t* buffer, int32_t n ) {
  // -------------------------------------------------------------------------------------
  Vector temp;
  temp.attach( buffer, n );
  return temp;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] M reference to a source Matrix.
 *
 *  Copy all of the elements of the source M. Resize if necessary this Matrix.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector::copy( const Vector& src ) {
  // -------------------------------------------------------------------------------------
  resize( src.ne );
  for ( int32_t i=0; i<ne; i++ ) {
    at(i) = src.get(i);
  }
  //dcopy_(src.N(), src.X(), src.INCX(), x, &ne );
}


// =======================================================================================
/** @brief Access.
 *  @param[in] idx index.
 *  @param[in] val value.
 *
 *  Access the element at (idx).
 */
// ---------------------------------------------------------------------------------------
inline  void Vector::set( const int32_t idx, const real8_t val ) {
  // -------------------------------------------------------------------------------------
  *(x+idx) = val;
}


// =======================================================================================
/** @brief Access.
 *  @param[in] idx index.
 *  @return reference to the element at (idx).
 *
 *  Access the element at (idx).
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Vector::get( const int32_t idx ) const {
  // -------------------------------------------------------------------------------------
  return *(x+idx);
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
  return *(x+idx);
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
  return *(x+idx);
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
inline  int32_t Vector::size( void ) const {
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
  for ( int32_t i=0; i<n; i++ ) {
    real8_t t = at(i);
    at(i) = that(i);
    that(i) = t;
  }
  //dswap_( &n, this->x, &(static_one), that.X(), that.INCX() );
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
  resize(n);
  if ( init ) {
    set(D_ZERO);
  }
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] n   number of elements in this Vector.
 *  @param[in] a   pointer to source data.
 *  @param[in] ins source increment value. (default: 1)
 *
 *  Construct a Vector with the contents of a.
 */
// ---------------------------------------------------------------------------------------
inline  Vector::Vector( const int32_t n,
			real8_t* a, const int32_t ins ) : INIT_VEC(0) {
  // -------------------------------------------------------------------------------------
  resize(n);
  load(a,ins);
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] src reference to a source Vector.
 *
 *  Copy constructor, instantiates this Vector as a copy of the source.
 */
// ---------------------------------------------------------------------------------------
inline  Vector::Vector( const Vector& src ) : INIT_VEC(0) {
  // -------------------------------------------------------------------------------------
  copy(src);
}


// =======================================================================================
/** @brief Destructor.
 */
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
/** @brief Size.
 *  @return the number of elements in this Vector.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t size( const Vector& V ) {
  // -------------------------------------------------------------------------------------
  return V.size();
}


#endif


// =======================================================================================
// **                                    V E C T O R                                    **
// ======================================================================== END FILE =====
