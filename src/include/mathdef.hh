// ====================================================================== BEGIN FILE =====
// **                                   M A T H D E F                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 1991, 09, 19  Stephen W. Soliday                                   **
// **                              stephen.soliday@trncmp.org                           **
// **                              http://research.trncmp.org                           **
// **                                                                                   **
// **  -------------------------------------------------------------------------------  **
// **                                                                                   **
// **  This file, and associated source code, is not free software; you may not         **
// **  redistribute it and/or modify it. This library is currently in an on going       **
// **  development phase by its author and has, as yet, not been publicly distributed.  **
// **  Development of this library has been at the sole cost in both time and funding   **
// **  by its author. Until such a public release is made the author retains ALL RIGHTS **
// **  to this software. It is expected that if and when this library is deemed         **
// **  releasable it will be released under the GNU Public license for non-commercial   **
// **  use or with a restricted rights for government use. At that time each source     **
// **  file will contain either/both the standard GPL statement/disclaimer, and/or the  **
// **  DFARS Restricted Rights Legend.                                                  **
// **                                                                                   **
// **  This library exists at the present time WITHOUT ANY WARRANTY; without even the   **
// **  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.         **
// **  As you are not supposed to be in possession of this file if you use it,          **
// **  you use this code AT YOUR OWN RISK.                                              **
// **                                                                                   **
// ----- Modification History ------------------------------------------------------------
//
/** @brief  Extended math functions
 *  @file   mathdef.hh
 *  @author Stephen W. Soliday
 *  @date   1991-01-12  Original release.
 *  @date   2009-02-01  Major revision.
 *  @date   2019-Apr-11 CMake refactorization.
 *
 *  Provides basic constants and math utilities.
 */
// =======================================================================================

#ifndef __HH_MATHDEF_TRNCMP
#define __HH_MATHDEF_TRNCMP

#include <limits>
#include <math.h>

// ===== MACROS ==========================================================================

#  define  D_ZERO      ( (real8_t) 0.0e+0 )                            /**<  0          */
#  define  D_HALF      ( (real8_t) 5.0e-1 )                            /**<  1/2        */
#  define  D_ONE       ( (real8_t) 1.0e+0 )                            /**<  1          */
#  define  D_TWO       ( (real8_t) 2.0e+0 )                            /**<  2          */
#  define  D_THREE     ( (real8_t) 3.0e+0 )                            /**<  3          */
#  define  D_FOUR      ( (real8_t) 4.0e+0 )                            /**<  4          */
#  define  D_FIVE      ( (real8_t) 5.0e+0 )                            /**<  5          */
#  define  D_SIX       ( (real8_t) 6.0e+0 )                            /**<  6          */
#  define  D_SEVEN     ( (real8_t) 7.0e+0 )                            /**<  7          */
#  define  D_EIGHT     ( (real8_t) 8.0e+0 )                            /**<  8          */
#  define  D_NINE      ( (real8_t) 9.0e+0 )                            /**<  9          */
#  define  D_TEN       ( (real8_t) 1.0e+1 )                            /**< 10          */
#  define  D_E         ( (real8_t) exp(D_ONE) )                        /**<  E (Napier) */
#  define  D_PI        ( (real8_t) acos(-D_ONE) )                      /**<  Pi         */

#  define  D_LD_2      ( (real8_t) log(D_TWO) )                        /**< Log_e(2)    */
#  define  D_LD_10     ( (real8_t) log(D_TEN) )                        /**< Log_e(10)   */
#  define  D_LD_PI     ( (real8_t) log(D_PI) )                         /**< Log_e(Pi)   */

#  define  D_LOG_2     ( (real8_t) log10(D_TWO) )                      /**< Log_10(2)   */
#  define  D_LOG_E     ( (real8_t) log10(D_E) )                        /**< Log_10(E)   */
#  define  D_LOG_PI    ( (real8_t) log10(D_PI) )                       /**< Log_10(Pi)  */

#  define  D_L2_10     ( (real8_t) log(D_TEN)/D_LD_2 )                 /**< Log_2(10)   */
#  define  D_L2_E      ( (real8_t) log(D_E)/D_LD_2 )                   /**< Log_2(E)    */
#  define  D_L2_PI     ( (real8_t) log(D_PI)/D_LD_2 )                  /**< Log_2(Pi)   */

#  define  D_LPI_2     ( (real8_t) log(D_TWO)/D_LD_PI )                /**< Log_pi(2)   */
#  define  D_LPI_10    ( (real8_t) log(D_TEN)/D_LD_PI )                /**< Log_pi(10)  */
#  define  D_LPI_E     ( (real8_t) log(D_E)/D_LD_PI )                  /**< Log_pi(E)   */

#  define  D_2PI       ( (real8_t) D_TWO*D_PI )                        /**< 2*Pi        */
#  define  D_3PI       ( (real8_t) D_THREE*D_PI )                      /**< 3*Pi        */
#  define  D_4PI       ( (real8_t) D_FOUR*D_PI )                       /**< 4*Pi        */
#  define  D_PI_2      ( (real8_t) acos(D_ZERO) )                      /**< Pi/2        */
#  define  D_PI_4      ( (real8_t) D_HALF*D_PI_2 )                     /**< Pi/4        */
#  define  D_3PI_2     ( (real8_t) D_THREE*D_PI_2 )                    /**< 3*Pi/2      */
#  define  D_3PI_4     ( (real8_t) D_THREE*D_PI_4 )                    /**< 3*Pi/4      */
#  define  D_5PI_4     ( (real8_t) D_FIVE*D_PI_4 )                     /**< 5*Pi/4      */
#  define  D_7PI_4     ( (real8_t) D_SEVEN*D_PI_4 )                    /**< 7*Pi/4      */

#  define  D_PI2       ( (real8_t) D_PI*D_PI )                         /**< Pi**2       */
#  define  D_1_PI      ( (real8_t) D_ONE/D_PI )                        /**< 1/Pi        */
#  define  D_2_PI      ( (real8_t) D_TWO/D_PI )                        /**< 2/Pi        */

#  define  D_SQRTPI    ( (real8_t) sqrt(D_PI) )                        /**< sqrt(Pi)    */
#  define  D_SQRT2PI   ( (real8_t) sqrt(D_2PI) )                       /**< sqrt(2Pi)   */
#  define  D_1_SQRTPI  ( (real8_t) D_ONE/D_SQRTPI )                    /**< 1/sqrt(Pi)  */
#  define  D_1_SQRT2PI ( (real8_t) D_ONE/D_SQRT2PI )                   /**< 1/sqrt(2Pi) */
#  define  D_2_SQRTPI  ( (real8_t) D_TWO/D_SQRTPI )                    /**< 2/sqrt(Pi)  */

#  define  D_SQRT_PI_2 ( (real8_t) sqrt(D_PI/D_TWO) )                  /**< sqrt(Pi/2)  */
#  define  D_SQRT_PI_4 ( (real8_t) sqrt(D_PI)/D_TWO )                  /**< sqrt(Pi)/2  */

#  define  D_SQRTE     ( (real8_t) exp(D_HALF) )                       /**< sqrt(E)     */
#  define  D_1_SQRTE   ( (real8_t) D_ONE/D_SQRTE )                     /**< 1/sqrt(E)   */

#  define  D_SQRT2     ( (real8_t) sqrt(D_TWO) )                       /**< sqrt(2)     */
#  define  D_1_SQRT2   ( (real8_t) D_ONE/D_SQRT2 )                     /**< 1/sqrt(2)   */
#  define  D_2_SQRT2   ( (real8_t) D_TWO/D_SQRT2 )                     /**< 2/sqrt(2)   */

#  define  D_SQRT3     ( (real8_t) sqrt(D_THREE) )                     /**< sqrt(3)     */
#  define  D_1_SQRT3   ( (real8_t) D_ONE/D_SQRT3 )                     /**< 1/sqrt(3)   */
#  define  D_2_SQRT3   ( (real8_t) D_TWO/D_SQRT3 )                     /**< 2/sqrt(3)   */

#  define  D_180_PI    ( (real8_t) 1.8e2/D_PI )                        /**< 180/Pi      */
#  define  D_PI_180    ( (real8_t) D_PI/1.8e2 )                        /**< Pi/180      */

#  define  D_EULER     ( (real8_t) 5.7721566490153286554942724e-01 )   /**< Euler       */

// ---------------------------------------------------------------------------------------

#  define  F_ZERO      ( (real4_t)  0.0F )                             /**<  0          */
#  define  F_HALF      ( (real4_t)  0.5F )                             /**<  1/2        */
#  define  F_ONE       ( (real4_t)  1.0F )                             /**<  1          */
#  define  F_TWO       ( (real4_t)  2.0F )                             /**<  2          */
#  define  F_THREE     ( (real4_t)  3.0F )                             /**<  3          */
#  define  F_FOUR      ( (real4_t)  4.0F )                             /**<  4          */
#  define  F_FIVE      ( (real4_t)  5.0F )                             /**<  5          */
#  define  F_SIX       ( (real4_t)  6.0F )                             /**<  6          */
#  define  F_SEVEN     ( (real4_t)  7.0F )                             /**<  7          */
#  define  F_EIGHT     ( (real4_t)  8.0F )                             /**<  8          */
#  define  F_NINE      ( (real4_t)  9.0F )                             /**<  9          */
#  define  F_TEN       ( (real4_t) 10.0F )                             /**< 10          */
#  define  F_E         ( (real4_t) expf(F_ONE) )                       /**<  E (Napier) */
#  define  F_PI        ( (real4_t) acosf(-F_ONE) )                     /**<  Pi         */

#  define  F_LF_2      ( (real4_t) logf(F_TWO) )                       /**< Log_e(2)    */
#  define  F_LF_10     ( (real4_t) logf(F_TEN) )                       /**< Log_e(10)   */
#  define  F_LF_PI     ( (real4_t) logf(F_PI) )                        /**< Log_e(Pi)   */

#  define  F_LOG_2     ( (real4_t) log10f(F_TWO) )                     /**< Log_10(2)   */
#  define  F_LOG_E     ( (real4_t) log10f(F_E) )                       /**< Log_10(E)   */
#  define  F_LOG_PI    ( (real4_t) log10f(F_PI) )                      /**< Log_10(Pi)  */

#  define  F_L2_10     ( (real4_t) logf(F_TEN)/F_LF_2 )                /**< Log_2(10)   */
#  define  F_L2_E      ( (real4_t) logf(F_E)/F_LF_2 )                  /**< Log_2(E)    */
#  define  F_L2_PI     ( (real4_t) logf(F_PI)/F_LF_2 )                 /**< Log_2(Pi)   */

#  define  F_LPI_2     ( (real4_t) logf(F_TWO)/F_LF_PI )               /**< Log_pi(2)   */
#  define  F_LPI_10    ( (real4_t) logf(F_TEN)/F_LF_PI )               /**< Log_pi(10)  */
#  define  F_LPI_E     ( (real4_t) logf(F_E)/F_LF_PI )                 /**< Log_pi(E)   */

#  define  F_2PI       ( (real4_t) F_TWO*F_PI )                        /**< 2*Pi        */
#  define  F_3PI       ( (real4_t) F_THREE*F_PI )                      /**< 3*Pi        */
#  define  F_4PI       ( (real4_t) F_FOUR*F_PI )                       /**< 4*Pi        */
#  define  F_PI_2      ( (real4_t) acosf(F_ZERO) )                     /**< Pi/2        */
#  define  F_PI_4      ( (real4_t) F_HALF*F_PI_2 )                     /**< Pi/4        */
#  define  F_3PI_2     ( (real4_t) F_THREE*F_PI_2 )                    /**< 3*Pi/2      */
#  define  F_3PI_4     ( (real4_t) F_THREE*F_PI_4 )                    /**< 3*Pi/4      */
#  define  F_5PI_4     ( (real4_t) F_FIVE*F_PI_4 )                     /**< 5*Pi/4      */
#  define  F_7PI_4     ( (real4_t) F_SEVEN*F_PI_4 )                    /**< 7*Pi/4      */

#  define  F_PI2       ( (real4_t) F_PI*F_PI )                         /**< Pi**2       */
#  define  F_1_PI      ( (real4_t) F_ONE/F_PI )                        /**< 1/Pi        */
#  define  F_2_PI      ( (real4_t) F_TWO/F_PI )                        /**< 2/Pi        */

#  define  F_SQRTPI    ( (real4_t) sqrtf(F_PI) )                       /**< sqrt(Pi)    */
#  define  F_SQRT2PI   ( (real4_t) sqrtf(F_2PI) )                      /**< sqrt(2Pi)   */
#  define  F_1_SQRTPI  ( (real4_t) F_ONE/F_SQRTPI )                    /**< 1/sqrt(Pi)  */
#  define  F_1_SQRT2PI ( (real4_t) F_ONE/F_SQRT2PI )                   /**< 1/sqrt(2Pi) */
#  define  F_2_SQRTPI  ( (real4_t) F_TWO/F_SQRTPI )                    /**< 2/sqrt(Pi)  */

#  define  F_SQRT_PI_2 ( (real4_t) sqrtf(F_PI/F_TWO) )                 /**< sqrt(Pi/2)  */
#  define  F_SQRT_PI_4 ( (real4_t) sqrtf(F_PI)/F_TWO )                 /**< sqrt(Pi)/2  */

#  define  F_SQRTE     ( (real4_t) expf(F_HALF) )                      /**< sqrt(E)     */
#  define  F_1_SQRTE   ( (real4_t) F_ONE/F_SQRTE )                     /**< 1/sqrt(E)   */

#  define  F_SQRT2     ( (real4_t) sqrtf(F_TWO) )                      /**< sqrt(2)     */
#  define  F_1_SQRT2   ( (real4_t) F_ONE/F_SQRT2 )                     /**< 1/sqrt(2)   */
#  define  F_2_SQRT2   ( (real4_t) F_TWO/F_SQRT2 )                     /**< 2/sqrt(2)   */

#  define  F_SQRT3     ( (real4_t) sqrtf(F_THREE) )                    /**< sqrt(3)     */
#  define  F_1_SQRT3   ( (real4_t) F_ONE/F_SQRT3 )                     /**< 1/sqrt(3)   */
#  define  F_2_SQRT3   ( (real4_t) F_TWO/F_SQRT3 )                     /**< 2/sqrt(3)   */

#  define  F_180_PI    ( (real4_t) 1.8e2/F_PI )                        /**< 180/Pi      */
#  define  F_PI_180    ( (real4_t) F_PI/180.0f )                       /**< Pi/180      */

#  define  F_EULER     ( (real4_t) 0.5772156649015328f )               /**< Euler       */

// ---------------------------------------------------------------------------------------

#  ifdef __DBL_MAX__
#     define MAX_POS_DOUBLE  ((real8_t)   __DBL_MAX__  )
#     define MAX_NEG_DOUBLE  ((real8_t) -(__DBL_MAX__) )
#  else
#     define MAX_POS_DOUBLE  ((real8_t)  1.79769313486231e+308L )
#     define MAX_NEG_DOUBLE  ((real8_t) -1.79769313486231e+308L )
#  endif

#  ifdef __FLT_MAX__
#     define MAX_POS_FLOAT  ((real4_t)   __FLT_MAX__  )
#     define MAX_NEG_FLOAT  ((real4_t) -(__FLT_MAX__) )
#  else
#     define MAX_POS_FLOAT  ((real4_t)  3.4028234663e+38F )
#     define MAX_NEG_FLOAT  ((real4_t) -3.4028234663e+38F )
#  endif

#  ifdef __DBL_MIN__
#     define MIN_POS_DOUBLE  ((real8_t)   __DBL_MIN__  )
#     define MIN_NEG_DOUBLE  ((real8_t) -(__DBL_MIN__) )
#  else
#     define MIN_POS_DOUBLE  ((real8_t)  2.2250738585072e-308L )
#     define MIN_NEG_DOUBLE  ((real8_t) -2.2250738585072e-308L )
#  endif

#  ifdef __FLT_MIN__
#     define MIN_POS_FLOAT  ((real8_t)   __DBL_MIN__  )
#     define MIN_NEG_FLOAT  ((real8_t) -(__DBL_MIN__) )
#  else
#     define MIN_POS_FLOAT  ((real8_t)  1.17549435082e-38F )
#     define MIN_NEG_FLOAT  ((real8_t) -1.17549435082e-38F )
#  endif

#  ifdef __DBL_EPSILON__
#     define D_EPSILON  ((real8_t)   __DBL_EPSILON__ )
#  else
#     define D_EPSILON  ((real8_t)   2.2204460492503e-16L )
#  endif

#  ifdef __FLT_EPSILON__
#     define F_EPSILON  ((real8_t)   __FLT_EPSILON__ )
#  else
#     define F_EPSILON  ((real8_t)   1.1920928955078125-7F )
#  endif

// =======================================================================================

real8_t ArcTan            ( const real8_t y, const real8_t x );
real8_t ArcTanPM          ( const real8_t y, const real8_t x );
real8_t RadCorrect        ( const real8_t r );
real8_t RadCorrectPM      ( const real8_t r );
real8_t centerOfMass      ( const real8_t* M,   const real8_t* X,   const size_t n );
real8_t centerOfMassRad   ( const real8_t* mag, const real8_t* rad, const size_t n );
real8_t centerOfMassRadPM ( const real8_t* mag, const real8_t* rad, const size_t n );
real8_t normalize         (       real8_t* vec,                     const size_t n );
real8_t SumSquareDiff     ( const real8_t* A,   const size_t n );
real8_t SumSquareDiff     ( const real8_t* A,   const real8_t* B,   const size_t n );
int32_t SumSquareDiff     ( const int32_t* A,   const int32_t* B,   const size_t n );
real8_t EuclideanDistance ( const real8_t* A,   const real8_t* B,   const size_t n );
real8_t MeanSquareError   ( const real8_t* A,   const real8_t* B,   const size_t n );

bool    linear            ( real8_t& slope, real8_t& inter,
                            const real8_t x1, const real8_t y1,
                            const real8_t x2, const real8_t y2 );

bool    linear            ( real4_t& slope, real4_t& inter,
                            const real4_t x1, const real4_t y1,
                            const real4_t x2, const real4_t y2 );


bool    linear            ( real8_t& slope, real8_t& inter,
                            real8_t* x, real8_t* y, const size_t n );

bool    linear            ( real4_t& slope, real4_t& inter,
                            real4_t* x, real4_t* y, const size_t n );

void    urandom           ( void* buffer, size_t n );

// =======================================================================================
/** @brief Are two values equal.
 *  @param a first number.
 *  @param b second number.
 *  @param tol tollerance
 *  @return true or false.
 *
 *  Determine if two numbers are within tollerance equal to each other.
 */
// ---------------------------------------------------------------------------------------
template< class T >
    inline bool areEqual( T a, T b, T tol ) {
// -------------------------------------------------------------------------------------
  T d = a-b;
  if (d >  tol) { return false; }
  if (d < -tol) { return false; }
  return true;
}

// =======================================================================================
/** @brief Are two values equal.
 *  @param a first number.
 *  @param b second number.
 *  @return true or false.
 *
 *  Determine if two numbers are equal to each other.
 */
// ---------------------------------------------------------------------------------------
template< class T >
inline bool areEqual( T a, T b ) {
  // -------------------------------------------------------------------------------------
  if (a > b) { return false; }
  if (a < b) { return false; }
  return true;
}

// =======================================================================================
/** @brief Are two values not equal.
 *  @param a first number.
 *  @param b second number.
 *  @param tol tollerance
 *  @return true or false.
 *
 *  Determine if two numbers are not within tollerance equal to each other.
 */
// ---------------------------------------------------------------------------------------
template< class T >
inline bool notEqual( T a, T b, T tol ) {
  // -------------------------------------------------------------------------------------
  T d = a-b;
  if (d >  tol) { return true; }
  if (d < -tol) { return true; }
  return false;
}

// =======================================================================================
/** @brief Are two values not equal.
 *  @param a first number.
 *  @param b second number.
 *  @return true or false.
 *
 *  Determine if two numbers are not equal to each other.
 */
// ---------------------------------------------------------------------------------------
template< class T >
inline bool notEqual( T a, T b ) {
  // -------------------------------------------------------------------------------------
  if (a > b) { return true; }
  if (a < b) { return true; }
  return false;
}

// =======================================================================================
/** @brief is zero.
 *  @param x test value
 *  @param eta small value
 *
 *  Is the test value within eta of zero
 */
// ---------------------------------------------------------------------------------------
template <class T>
inline bool isZero( T x, T eta ) {
  // -------------------------------------------------------------------------------------
  if (x >  eta) { return false; }
  if (x < -eta) { return false; }
  return true;
}

// =======================================================================================
/** @brief is zero.
 *  @param x test value
 *
 *  Is the test value zero
 */
// ---------------------------------------------------------------------------------------
template <class T>
inline bool isZero( T x ) {
  // -------------------------------------------------------------------------------------
  if (x > (T)0) { return false; }
  if (x < (T)0) { return false; }
  return true;
}

// =======================================================================================
/** @brief is not zero.
 *  @param x test value
 *  @param eta small value
 *
 *  Is the test value not within eta of zero
 */
// ---------------------------------------------------------------------------------------
template <class T>
inline bool isNotZero( T x, T eta ) {
  // -------------------------------------------------------------------------------------
  if (x >  eta) { return true; }
  if (x < -eta) { return true; }
  return false;
}

// =======================================================================================
/** @brief is not zero.
 *  @param x test value
 *
 *  Is the test value not zero
 */
// ---------------------------------------------------------------------------------------
template <class T>
inline bool isNotZero( T x ) {
  // -------------------------------------------------------------------------------------
  if (x > (T)0) { return true; }
  if (x < (T)0) { return true; }
  return false;
}

// =======================================================================================
/** @brief Root.
 *  @param b base
 *  @param r root
 *  @return b^e
 *
 *  Find the (r)th root of (b)
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Root( real8_t b, real8_t r ) {
  // -------------------------------------------------------------------------------------
  return exp(log(b)/r);
}

// =======================================================================================
/** @brief Root.
 *  @param b base
 *  @param r root
 *  @return b^e
 *
 *  Find the (r)th root of (b)
 */
// ---------------------------------------------------------------------------------------
inline  real4_t Root( real4_t b, real4_t r ) {
  // -------------------------------------------------------------------------------------
  return expf(logf(b)/r);
}

// =======================================================================================
/** @brief Power.
 *  @param b base.
 *  @param e exponent.
 *  @return b^e.
 *
 *  Raise (b) to the power of (e).
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Power(const real8_t b, const real8_t e ) {
  // -------------------------------------------------------------------------------------
  return exp(log(b)*e);
}

// =======================================================================================
/** @brief Power.
 *  @param b base.
 *  @param e exponent.
 *  @return b^e.
 *
 *  Raise (b) to the power of (e).
 */
// ---------------------------------------------------------------------------------------
inline  real4_t Power(const real4_t b, const real4_t e ) {
  // -------------------------------------------------------------------------------------
  return expf(logf(b)*e);
}

// =======================================================================================
/** @brief Convert degrees.
 *  @param d degrees.
 *  @return radians.
 *
 *  Convert decimal degrees into radians.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t DEG2RAD(const real8_t d ) {
  // -------------------------------------------------------------------------------------
  return d*D_PI_180;
}

// =======================================================================================
/** @brief Convert degrees.
 *  @param d degrees.
 *  @return radians.
 *
 *  Convert decimal degrees into radians.
 */
// ---------------------------------------------------------------------------------------
inline  real4_t DEG2RAD(const real4_t d ) {
  // -------------------------------------------------------------------------------------
  return d*F_PI_180;
}

// =======================================================================================
/** @brief Convert radians.
 *  @param r radians.
 *  @return degrees.
 *
 *  Convert radians into decimal degrees.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t RAD2DEG( const real8_t r ) {
  // -------------------------------------------------------------------------------------
  return r*D_180_PI;
}

// =======================================================================================
/** @brief Convert radians.
 *  @param r radians.
 *  @return degrees.
 *
 *  Convert radians into decimal degrees.
 */
// ---------------------------------------------------------------------------------------
inline  real4_t RAD2DEG( const real4_t r ) {
  // -------------------------------------------------------------------------------------
  return r*F_180_PI;
}

// =======================================================================================
/** @brief Degree Based SINE.
 *  @param a degrees.
 *  @return sine.
 *
 *  Return sine of angle.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t sin_deg(const real8_t a) {
  // -------------------------------------------------------------------------------------
  return sin(DEG2RAD((real8_t)a));
}

// =======================================================================================
/** @brief Degree Based SINE.
 *  @param a degrees.
 *  @return sine.
 *
 *  Return sine of angle.
 */
// ---------------------------------------------------------------------------------------
inline  real4_t sin_deg(const real4_t a) {
  // -------------------------------------------------------------------------------------
  return sinf(DEG2RAD(a));
}

// =======================================================================================
/** @brief Degree Based COSINE.
 *  @param a degrees.
 *  @return cosine.
 *
 *  Return cosine of angle.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t cos_deg(const real8_t a) {
  // -------------------------------------------------------------------------------------
  return cos(DEG2RAD(a));
}

// =======================================================================================
/** @brief Degree Based COSINE.
 *  @param a degrees.
 *  @return cosine.
 *
 *  Return cosine of angle.
 */
// ---------------------------------------------------------------------------------------
inline  real4_t cos_deg(const real4_t a) {
  // -------------------------------------------------------------------------------------
  return cosf(DEG2RAD(a));
}

// =======================================================================================
/** @brief Degree Based TANGENT.
 *  @param a degrees.
 *  @return tangent.
 *
 *  Return tangent of angle.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t tan_deg( const real8_t a ) {
  // -------------------------------------------------------------------------------------
  return tan(DEG2RAD(a));
}

// =======================================================================================
/** @brief Degree Based TANGENT.
 *  @param a degrees.
 *  @return tangent.
 *
 *  Return tangent of angle.
 */
// ---------------------------------------------------------------------------------------
inline  real4_t tan_deg( const real4_t a ) {
  // -------------------------------------------------------------------------------------
  return tanf(DEG2RAD(a));
}

// =======================================================================================
/** @brief Degree SINCOS.
 *  @param x angle in degrees.
 *  @param s pointer to return a sine.
 *  @param c pointer to return a cosine.
 */
// ---------------------------------------------------------------------------------------
inline void sincos_deg( real8_t x, real8_t *s, real8_t *c ) {
  // -------------------------------------------------------------------------------------
  real8_t r = DEG2RAD(x);
  sincos( r, s, c );
}

// =======================================================================================
/** @brief Degree SINCOS.
 *  @param x angle in degrees.
 *  @param s pointer to return a sine.
 *  @param c pointer to return a cosine.
 */
// ---------------------------------------------------------------------------------------
inline void sincos_deg( real4_t x, real4_t *s, real4_t *c ) {
  // -------------------------------------------------------------------------------------
  real4_t r = DEG2RAD(x);
  sincosf( r, s, c );
}

// =======================================================================================
/** @brief Degree acos.
 *  @param x ratio.
 *  @return arc cosine in degrees.
 */
// ---------------------------------------------------------------------------------------
inline real8_t acos_deg( real8_t x ) {
  // -------------------------------------------------------------------------------------
  return RAD2DEG( acos( x ) );
}

// =======================================================================================
/** @brief Degree acos.
 *  @param x ratio.
 *  @return arc cosine in degrees.
 */
// ---------------------------------------------------------------------------------------
inline real4_t acos_deg( real4_t x ) {
  // -------------------------------------------------------------------------------------
  return RAD2DEG( acosf( x ) );
}

// =======================================================================================
/** @brief Degree asin.
 *  @param x ratio.
 *  @return arc sine in degrees.
 */
// ---------------------------------------------------------------------------------------
inline real8_t asin_deg( real8_t x ) {
  // -------------------------------------------------------------------------------------
  return RAD2DEG( asin( x ) );
}

// =======================================================================================
/** @brief Degree asin.
 *  @param x ratio.
 *  @return arc sine in degrees.
 */
// ---------------------------------------------------------------------------------------
inline real4_t asin_deg( real4_t x ) {
  // -------------------------------------------------------------------------------------
  return RAD2DEG( asinf( x ) );
}

// ========================================================================== [0, m) =====
/** @brief Floating Point Modula.
 *  @param v value in the range (-Inf, +Inf).
 *  @param m modulus in the range (0, +Inf).
 *  @return positive modulus in the range [0, m).
 *
 *  Returns a Positive Modulus for v in m.
 * <pre>
 *     -8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7
 *      0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3
 * </pre>
 */
// ---------------------------------------------------------------------------------------
inline  real8_t PFmod( real8_t v, const real8_t m ) {
  // -------------------------------------------------------------------------------------
  real8_t im;
   
  im = fmod( v, m );

  if (im < D_ZERO) { return m + im; }

  return im;
}


// ========================================================================== [0, m) =====
/** @brief Floating Point Modula.
 *  @param v value in the range (-Inf, +Inf).
 *  @param m modulus in the range (0, +Inf).
 *  @return positive modulus in the range [0, m).
 *
 *  Returns a Positive Modulus for v in m.
 * <pre>
 *     -8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7
 *      0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3
 * </pre>
 */
// ---------------------------------------------------------------------------------------
inline  real4_t PFmod( real4_t v, const real4_t m ) {
  // -------------------------------------------------------------------------------------
  real4_t im;
   
  im = fmodf( v, m );

  if (im < D_ZERO) { return m + im; }

  return im;
}


// ======================================================================== [0, 360) =====
/** @brief Floating Point Modula.
 *  @param  r      radian in the range (-Inf, +Inf).
 *  @return  radian in the range [0, +360).
 *
 *  Use Modulus to correct degree ranges in the positve range [0, 360).
 */
// ---------------------------------------------------------------------------------------
inline  real8_t DegreeCorrect( real8_t r ) {
  // -------------------------------------------------------------------------------------
  if (r < -360.0)  { return PFmod(r, 360.0); }
  if (r <  D_ZERO) { return r + 360.0; }
  if (r <  360.0)  { return r; }
  if (r <  720.0)  { return r - 360.0; }

  return fmod(r,360.0);
}

// ======================================================================== [0, 360) =====
/** @brief Floating Point Modula.
 *  @param  r      radian in the range (-Inf, +Inf).
 *  @return  radian in the range [0, +360).
 *
 *  Use Modulus to correct degree ranges in the positve range [0, 360).
 */
// ---------------------------------------------------------------------------------------
inline  real4_t DegreeCorrect( real4_t r ) {
  // -------------------------------------------------------------------------------------
  if (r < -360.0f)  { return PFmod(r, 360.0f); }
  if (r <  0.0f)    { return r + 360.0f; }
  if (r <  360.0f)  { return r; }
  if (r <  720.0f)  { return r - 360.0f; }

  return fmod(r,360.0f);
}

// =======================================================================================
/** @brief Angular Difference A-B.
 *  @param a first angle A.
 *  @param b second angle B.
 *  @return angular difference.
 *
 *  Difference between two angles is expressed as a NO-REFLEX angle in the range or (-90,+90]
 * <pre>
 *   -20 = AngleDiff( 350,  10 );
 *    20 = AngleDiff(  10, 350 );
 *</pre>
 */
// ---------------------------------------------------------------------------------------
inline  real8_t AngleDiff( real8_t a, real8_t b ) {
  // -------------------------------------------------------------------------------------
  real8_t dif = a - b;
  if (dif >  180.0) { return dif - 360.0; }
  if (dif < -180.0) { return dif + 360.0; }
  return dif;
}

// =======================================================================================
/** @brief Angular Difference A-B.
 *  @param a first angle A.
 *  @param b second angle B.
 *  @return angular difference.
 *
 *  Difference between two angles is expressed as a NO-REFLEX angle in the range or (-90,+90]
 * <pre>
 *   -20 = AngleDiff( 350,  10 );
 *    20 = AngleDiff(  10, 350 );
 *</pre>
 */
// ---------------------------------------------------------------------------------------
inline  real4_t AngleDiff( real4_t a, real4_t b ) {
  // -------------------------------------------------------------------------------------
  real4_t dif = a - b;
  if (dif >  180.0f) { return dif - 360.0f; }
  if (dif < -180.0f) { return dif + 360.0f; }
  return dif;
}

// =======================================================================================
/** @brief Radian Difference A-B
 *  Difference between two angles is expressed as a NO-REFLEX angle in the range or (-Pi,+Pi]
 * <pre>
 *   -1.283185 = RadianDiff( 6,  1 );
 *    1.283185 = RadianDiff( 1,  6 );
 *</pre>
 *
 *  @param a first radian A.
 *  @param b second radian B.
 *  @return radian difference.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t RadianDiff( real8_t a, real8_t b ) {
  // -------------------------------------------------------------------------------------
  real8_t dif = a - b;
  if (dif >  D_PI) { return dif - D_2PI; }
  if (dif < -D_PI) { return dif + D_2PI; }
  return dif;
}

// =======================================================================================
/** @brief Radian Difference A-B
 *  @param a first radian A.
 *  @param b second radian B.
 *  @return radian difference.
 *  Difference between two angles is expressed as a NO-REFLEX angle in the range or (-Pi,+Pi]
 *
 * <pre>
 *   -1.283185 = RadianDiff( 6,  1 );
 *    1.283185 = RadianDiff( 1,  6 );
 *</pre>
 */
// ---------------------------------------------------------------------------------------
inline  real4_t RadianDiff( real4_t a, real4_t b ) {
  // -------------------------------------------------------------------------------------
  real4_t dif = a - b;
  if (dif >  F_PI) { return dif - F_2PI; }
  if (dif < -F_PI) { return dif + F_2PI; }
  return dif;
}

// =======================================================================================
/** @brief Parametric.
 *  @param a zero point.
 *  @param b one  point.
 *  @param t parametric (0 <= t <=1 ).
 *  @return a * (1-t) + b * t.
 *
 *  Linear parametric between two points.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t parametric( const real8_t a, const real8_t b, const real8_t t) {
  // -------------------------------------------------------------------------------------
  return (a + ((b-a)*t));
}

// =======================================================================================
/** @brief Parametric.
 *  @param a zero point.
 *  @param b one  point.
 *  @param t parametric (0 <= t <=1 ).
 *  @return a * (1-t) + b * t.
 *
 *  Linear parametric between two points.
 */
// ---------------------------------------------------------------------------------------
inline  real4_t parametric( const real4_t a, const real4_t b, const real4_t t) {
  // -------------------------------------------------------------------------------------
  return (a + ((b-a)*t));
}

// =======================================================================================
/** @brief Parametric.
 *  @param p vector for result.
 *  @param a vector for zero point.
 *  @param b vector for one  point.
 *  @param n number of dimensions.
 *  @param t parametric (0 <= t <=1 ).
 *
 *  Linear parametric between two multi-dimensional points.
 */
// ---------------------------------------------------------------------------------------
inline  void parametric( real8_t* p, real8_t* a, real8_t* b, size_t n, real8_t t ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=0; i<n; i++) {
    p[i] = (a[i] + ((b[i]-a[i])*t));
  }
}

// =======================================================================================
/** @brief Parametric.
 *  @param p vector for result.
 *  @param a vector for zero point.
 *  @param b vector for one  point.
 *  @param n number of dimensions.
 *  @param t parametric (0 <= t <=1 ).
 *
 *  Linear parametric between two multi-dimensional points.
 */
// ---------------------------------------------------------------------------------------
inline  void parametric( real4_t* p, real4_t* a, real4_t* b, size_t n, real4_t t ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=0; i<n; i++) {
    p[i] = (a[i] + ((b[i]-a[i])*t));
  }
}

// =======================================================================================
/** @brief Magnitude of a vector |a|.
 *  @param Ax x component of vector A.
 *  @param Ay y component of vector A.
 *  @return magnitude of vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Mag( const real8_t Ax, const real8_t Ay ) {
  // -------------------------------------------------------------------------------------
  return sqrt((Ax*Ax) + (Ay*Ay));
}

// =======================================================================================
/** @brief Magnitude of a vector |a|.
 *  @param Ax x component of vector A.
 *  @param Ay y component of vector A.
 *  @return magnitude of vector.
 */
// ---------------------------------------------------------------------------------------
inline  real4_t Mag( const real4_t Ax, const real4_t Ay ) {
  // -------------------------------------------------------------------------------------
  return sqrtf((Ax*Ax) + (Ay*Ay));
}

// =======================================================================================
/** @brief Magnitude of a vector |a|.
 *  @param Ax x component of vector A.
 *  @param Ay y component of vector A.
 *  @param Az z component of vector A.
 *  @return magnitude of vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Mag( const real8_t Ax, const real8_t Ay, const real8_t Az ) {
  // -------------------------------------------------------------------------------------
  return sqrt((Ax*Ax) + (Ay*Ay) + (Az*Az));
}

// =======================================================================================
/** @brief Magnitude of a vector |a|.
 *  @param Ax x component of vector A.
 *  @param Ay y component of vector A.
 *  @param Az z component of vector A.
 *  @return magnitude of vector.
 */
// ---------------------------------------------------------------------------------------
inline  real4_t Mag( const real4_t Ax, const real4_t Ay, const real4_t Az ) {
  // -------------------------------------------------------------------------------------
  return sqrtf((Ax*Ax) + (Ay*Ay) + (Az*Az));
}

// =======================================================================================
/** @brief Magnitude of a vector |ab|.
 *  @param Ax x coordinate of endpoint A.
 *  @param Ay y coordinate of endpoint A.
 *  @param Bx x coordinate of endpoint B.
 *  @param By y coordinate of endpoint B.
 *  @return magnitude of vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Mag( const real8_t Ax, const real8_t Ay,
                     const real8_t Bx, const real8_t By ) {
  // -------------------------------------------------------------------------------------
  return Mag((Bx-Ax), (By-Ay));
}

// =======================================================================================
/** @brief Magnitude of a vector |ab|.
 *  @param Ax x coordinate of endpoint A.
 *  @param Ay y coordinate of endpoint A.
 *  @param Bx x coordinate of endpoint B.
 *  @param By y coordinate of endpoint B.
 *  @return magnitude of vector.
 */
// ---------------------------------------------------------------------------------------
inline  real4_t Mag( const real4_t Ax, const real4_t Ay,
                     const real4_t Bx, const real4_t By ) {
  // -------------------------------------------------------------------------------------
  return Mag((Bx-Ax), (By-Ay));
}

// =======================================================================================
/** @brief Dot Product of two vectors.
 *  @param Ax x component of vector A.
 *  @param Ay y component of vector A.
 *  @param Bx x component of vector B.
 *  @param By y component of vector B.
 *  @return the inner product of the 2D vectors A and B.
 */
// --------------------------------------------------------------------------------------
inline  real8_t Dot( const real8_t Ax, const real8_t Ay,
                     const real8_t Bx, const real8_t By ) {
  // ------------------------------------------------------------------------------------
  return (Ax*Bx) + (Ay*By);
}

// =======================================================================================
/** @brief Dot Product of two vectors.
 *  @param Ax x component of vector A.
 *  @param Ay y component of vector A.
 *  @param Bx x component of vector B.
 *  @param By y component of vector B.
 *  @return the inner product of the 2D vectors A and B.
 */
// --------------------------------------------------------------------------------------
inline  real4_t Dot( const real4_t Ax, const real4_t Ay,
                     const real4_t Bx, const real4_t By ) {
  // ------------------------------------------------------------------------------------
  return (Ax*Bx) + (Ay*By);
}

// =======================================================================================
/** @brief Dot Product of two vectors.
 *  @param Ax x component of vector A.
 *  @param Ay y component of vector A.
 *  @param Az z component of vector A.
 *  @param Bx x component of vector B.
 *  @param By y component of vector B.
 *  @param Bz z component of vector B.
 *  @return the inner product of the 3D vectors A and B.
 */
// --------------------------------------------------------------------------------------
inline  real8_t Dot( const real8_t Ax, const real8_t Ay, const real8_t Az,
                     const real8_t Bx, const real8_t By, const real8_t Bz ) {
  // ------------------------------------------------------------------------------------
  return (Ax*Bx) + (Ay*By) + (Az*Bz);
}

// =======================================================================================
/** @brief Dot Product of two vectors.
 *  @param Ax x component of vector A.
 *  @param Ay y component of vector A.
 *  @param Az z component of vector A.
 *  @param Bx x component of vector B.
 *  @param By y component of vector B.
 *  @param Bz z component of vector B.
 *  @return the inner product of the 3D vectors A and B.
 */
// --------------------------------------------------------------------------------------
inline  real4_t Dot( const real4_t Ax, const real4_t Ay, const real4_t Az,
                     const real4_t Bx, const real4_t By, const real4_t Bz ) {
  // ------------------------------------------------------------------------------------
  return (Ax*Bx) + (Ay*By) + (Az*Bz);
}

// =======================================================================================
/** @brief Cross Product of two vectors.
 *  @param Ax x coordinate of point A.
 *  @param Ay y coordinate of point A.
 *  @param Bx x coordinate of point B.
 *  @param By y coordinate of point B.
 *  @return magnitude and sign
 *
 * Resulting value is perpendicular the the plane formed by the two angles.
 * In this case +/- Z, the angles being in the X-Y plane.
 */
// --------------------------------------------------------------------------------------
inline  real8_t Cross( const real8_t Ax, const real8_t Ay,
                       const real8_t Bx, const real8_t By ) {
  // ------------------------------------------------------------------------------------
  return Ax*By - Ay*Bx;
}

// =======================================================================================
/** @brief Cross Product of two vectors.
 *  @param Ax x coordinate of point A.
 *  @param Ay y coordinate of point A.
 *  @param Bx x coordinate of point B.
 *  @param By y coordinate of point B.
 *  @return magnitude and sign
 *
 * Resulting value is perpendicular the the plane formed by the two angles.
 * In this case +/- Z, the angles being in the X-Y plane.
 */
// --------------------------------------------------------------------------------------
inline  real4_t Cross( const real4_t Ax, const real4_t Ay,
                       const real4_t Bx, const real4_t By ) {
  // ------------------------------------------------------------------------------------
  return Ax*By - Ay*Bx;
}

// =======================================================================================
/** @brief Cross Product of two vectors.
 *  @param Cx x coordinate of point C.
 *  @param Cy y coordinate of point C.
 *  @param Cz z coordinate of point C.
 *  @param Ax x coordinate of point A.
 *  @param Ay y coordinate of point A.
 *  @param Az z coordinate of point A.
 *  @param Bx x coordinate of point B.
 *  @param By y coordinate of point B.
 *  @param Bz y coordinate of point B.
 *
 */
// --------------------------------------------------------------------------------------
inline  void Cross( real8_t *Cx,  real8_t *Cy,  real8_t *Cz, 
                    const real8_t Ax, const real8_t Ay, const real8_t Az,
                    const real8_t Bx, const real8_t By, const real8_t Bz ) {
  // ------------------------------------------------------------------------------------
  *Cx = Ay*Bz - Az*By;
  *Cy = Az*Bx - Ax*Bz;
  *Cz = Ax*By - Ay*Bx;
}

// =======================================================================================
/** @brief Cross Product of two vectors.
 *  @param Cx x coordinate of point C.
 *  @param Cy y coordinate of point C.
 *  @param Cz z coordinate of point C.
 *  @param Ax x coordinate of point A.
 *  @param Ay y coordinate of point A.
 *  @param Az z coordinate of point A.
 *  @param Bx x coordinate of point B.
 *  @param By y coordinate of point B.
 *  @param Bz y coordinate of point B.
 *
 */
// --------------------------------------------------------------------------------------
inline  void Cross( real4_t *Cx,  real4_t *Cy,  real4_t *Cz, 
                    const real4_t Ax, const real4_t Ay, const real4_t Az,
                    const real4_t Bx, const real4_t By, const real4_t Bz ) {
  // ------------------------------------------------------------------------------------
  *Cx = Ay*Bz - Az*By;
  *Cy = Az*Bx - Ax*Bz;
  *Cz = Ax*By - Ay*Bx;
}

// =======================================================================================
/** @brief Angle between two vectors.
 *  @param Ax x component of vector A.
 *  @param Ay y component of vector A.
 *  @param Bx x component of vector B.
 *  @param By y component of vector B.
 *  @return radians in the range -Pi to Pi from +x towards +y axis.
 * 
 *  Angle in radians from vector A to vector B.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Angle( const real8_t Ax, const real8_t Ay,
                       const real8_t Bx, const real8_t By ) {
  // -------------------------------------------------------------------------------------

  real8_t AdotB    = Ax*Bx + Ay*By;
  real8_t magAmagB = sqrt( (Ax*Ax + Ay*Ay)*(Bx*Bx + By*By) );
  real8_t ang      = acos(AdotB/magAmagB);
  real8_t AcrossB  = Ax*By - Ay*Bx;
  
  if (AcrossB < 0.0) {
    return -ang;
  }

  return ang;
}

// =======================================================================================
/** @brief Angle between two vectors.
 *  @param Ax x component of vector A.
 *  @param Ay y component of vector A.
 *  @param Bx x component of vector B.
 *  @param By y component of vector B.
 *  @return radians in the range -Pi to Pi from +x towards +y axis.
 * 
 *  Angle in radians from vector A to vector B.
 */
// ---------------------------------------------------------------------------------------
inline  real4_t Angle( const real4_t Ax, const real4_t Ay,
                       const real4_t Bx, const real4_t By ) {
  // -------------------------------------------------------------------------------------

  real4_t AdotB    = Ax*Bx + Ay*By;
  real4_t magAmagB = sqrtf( (Ax*Ax + Ay*Ay)*(Bx*Bx + By*By) );
  real4_t ang      = acosf(AdotB/magAmagB);
  real4_t AcrossB  = Ax*By - Ay*Bx;
  
  if (AcrossB < 0.0f) {
    return -ang;
  }

  return ang;
}

// =======================================================================================
/** @brief Angle between two vectors.
 *  @param Ax x component of vector A.
 *  @param Ay y component of vector A.
 *  @param Az z component of vector A.
 *  @param Bx x component of vector B.
 *  @param By y component of vector B.
 *  @param Bz z component of vector B.
 *  @return radians in the range 0 to Pi.
 * 
 *  Angle in radians from vector A to vector B.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Angle( const real8_t Ax, const real8_t Ay, const real8_t Az,
                       const real8_t Bx, const real8_t By, const real8_t Bz ) {
  // -------------------------------------------------------------------------------------
  real8_t AdotB    = Ax*Bx + Ay*By + Az*Bz;
  real8_t magAmagB = sqrt( (Ax*Ax + Ay*Ay + Az*Az)*(Bx*Bx + By*By + Bz*Bz) );

  return acos(AdotB/magAmagB);
}

// =======================================================================================
/** @brief Angle between two vectors.
 *  @param Ax x component of vector A.
 *  @param Ay y component of vector A.
 *  @param Az z component of vector A.
 *  @param Bx x component of vector B.
 *  @param By y component of vector B.
 *  @param Bz z component of vector B.
 *  @return radians in the range 0 to Pi.
 * 
 *  Angle in radians from vector A to vector B.
 */
// ---------------------------------------------------------------------------------------
inline  real4_t Angle( const real4_t Ax, const real4_t Ay, const real4_t Az,
                       const real4_t Bx, const real4_t By, const real4_t Bz ) {
  // -------------------------------------------------------------------------------------
  real4_t AdotB    = Ax*Bx + Ay*By + Az*Bz;
  real4_t magAmagB = sqrtf( (Ax*Ax + Ay*Ay + Az*Az)*(Bx*Bx + By*By + Bz*Bz) );

  return acosf(AdotB/magAmagB);
}

// =======================================================================================
/** @brief Clamp.
 *  @param X value to clamp.
 *  @param tol effective zero.
 *
 *  Determine if a floating point number is within some tolerance of zero. The defualt
 *  being 10**-10.
 */
// ---------------------------------------------------------------------------------------
inline real8_t clamp( real8_t X, real8_t tol = 1.0e-10 ) {
  // -------------------------------------------------------------------------------------
  if (X >  tol) { return X; }
  if (X < -tol) { return X; }
  return D_ZERO;
}

// =======================================================================================
/** @brief Clamp.
 *  @param X value to clamp.
 *  @param tol effective zero.
 *
 *  Determine if a floating point number is within some tolerance of zero. The defualt
 *  being 10**-10.
 */
// ---------------------------------------------------------------------------------------
inline real4_t clamp( real4_t X, real4_t tol = 1.0e-10f ) {
  // -------------------------------------------------------------------------------------
  if (X >  tol) { return X; }
  if (X < -tol) { return X; }
  return F_ZERO;
}

// =======================================================================================
/** @brief Power 2.
 *  @param X value.
 *  @return value**2.
 *
 *  Raise value to the 2nd power.
 */
// ---------------------------------------------------------------------------------------
template <class T>
inline T pow_2( T X ) {
  // -------------------------------------------------------------------------------------1-
  return X*X;
}

// =======================================================================================
/** @brief Power 3.
 *  @param X value.
 *  @return value**3.
 *
 *  Raise value to the 3rd power.
 */
// -------------------------------------------------------------------------------------2-
template <class T>
inline T pow_3( T X ) {
  // ---------------------------------------------------------------------------------------
  return X*X*X;
}

// =======================================================================================
/** @brief Power 4.
 *  @param X value.
 *  @return value**4.
 *
 *  Raise value to the 4th power.
 */
// -------------------------------------------------------------------------------------2-
template <class T>
inline T pow_4( T X ) {
  // ---------------------------------------------------------------------------------------
  T a = X*X;
  return a*a;
}

// =======================================================================================
/** @brief Power 5.
 *  @param X value.
 *  @return value**5.
 *
 *  Raise value to the 5th power.
 */
// -------------------------------------------------------------------------------------3-
template <class T>
inline T pow_5( T X ) {
  // ---------------------------------------------------------------------------------------
  T a = X*X;
  
  return a*a*X ;
}

// =======================================================================================
/** @brief Power 6.
 *  @param X value.
 *  @return value**6.
 *
 *  Raise value to the 6th power.
 */
// -------------------------------------------------------------------------------------3-
template <class T>
inline T pow_6( T X ) {
  // ---------------------------------------------------------------------------------------
  T b = X*X*X;
  return b*b;
}

// =======================================================================================
/** @brief Power 7.
 *  @param X value.
 *  @return value**7.
 *
 *  Raise value to the 7th power.
 */
// -------------------------------------------------------------------------------------4-
template <class T>
inline T pow_7( T X ) {
  // ---------------------------------------------------------------------------------------
  T b = X*X*X;
  return b*b*X;
}

// =======================================================================================
/** @brief Power 8.
 *  @param X value.
 *  @return value**8.
 *
 *  Raise value to the 8th power.
 */
// -------------------------------------------------------------------------------------3-
template <class T>
inline T pow_8( T X ) {
  // ---------------------------------------------------------------------------------------
  T a = X*X;
  T b = a*a;
  return b*b;
}

// =======================================================================================
/** @brief Power 9.
 *  @param X value.
 *  @return value**9.
 *
 *  Raise value to the 9th power.
 */
// -------------------------------------------------------------------------------------4-
template <class T>
inline T pow_9( T X ) {
  // ---------------------------------------------------------------------------------------
  T a = X*X;
  T b = a*a;
  return b*b*X;
}

// =======================================================================================
/** @brief Linear.
 *  @param[in] slope slope.
 *  @param[in] inter y intercept.
 *  @param[in] x     independent variable.
 *  @return dependent variable.
 *
 *  y = m x + b.
 */
// ---------------------------------------------------------------------------------------
template <class T>
inline T linear( const T slope, const T inter, const T x ) {
  // -------------------------------------------------------------------------------------
  return slope*x + inter;
}

inline real8_t sumsq( real8_t* a, real8_t* b, size_t n ) { return SumSquareDiff(a,b,n); };
inline real8_t sumsq( real8_t* a, size_t n )             { return SumSquareDiff(a,n);   };


#endif

// =======================================================================================
// **                                   M A T H D E F                                   **
// ======================================================================== END FILE =====
