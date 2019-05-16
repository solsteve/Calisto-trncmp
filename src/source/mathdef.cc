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
 *  @file   mathdef.cc
 *  @author Stephen W. Soliday
 *  @date   1991-01-12  Original release.
 *  @date   2009-02-01  Major revision.
 *  @date   2019-Apr-11 CMake refactorization.
 *
 *  Provides basic constants and math utilities.
 */
// =======================================================================================


#include <trncmp.hh>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


// ========================================================================== [0, m) =====t
/** @brief Floating Point Modula.
 *  @param[in] v value in the range (-Inf, +Inf).
 *  @param[in] m modulus in the range (0, +Inf).
 *  @return positive modulus in the range [0, m).
 *
 *  Returns a Positive Modulus for v in m.
 * <pre>
 *     -8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7
 *      0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3
 * </pre>
 */
// ---------------------------------------------------------------------------------------
real8_t PFmod( const real8_t v, const real8_t m ) {
  // -------------------------------------------------------------------------------------
  if ( v < -m )       { return m - fmod( -v, m ); }
  if ( v < 0.0 )      { return v + m; }
  if ( v <  m )       { return v; }
  if ( v <  D_TWO*m ) { return v - m; }
  return fmod( v, m );
}


// ========================================================================== [0, m) =====t
/** @brief Floating Point Modula.
 *  @param[in] v value in the range (-Inf, +Inf).
 *  @param[in] m modulus in the range (0, +Inf).
 *  @return positive modulus in the range [0, m).
 *
 *  Returns a Positive Modulus for v in m.
 * <pre>
 *     -8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7
 *      0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3
 * </pre>
 */
// ---------------------------------------------------------------------------------------
real4_t PFmod( const real4_t v, const real4_t m ) {
  // -------------------------------------------------------------------------------------
  if ( v < -m )       { return m - fmodf( -v, m ); }
  if ( v < 0.0 )      { return v + m; }
  if ( v <  m )       { return v; }
  if ( v <  F_TWO*m ) { return v - m; }
  return fmodf( v, m );
}


// =======================================================================================t
/** @brief Linear.
 *  @param[out] slope slope.
 *  @param[out] inter y intercept.
 *  @param[in]  x1    first  x coordinate.
 *  @param[in]  y1    first  y coordinate.
 *  @param[in]  x2    second x coordinate.
 *  @param[in]  y2    second y coordinate.
 *  @return true if singular.
 *
 *  Find the slope and intercept for the linear y = m x + b.
 */
// ---------------------------------------------------------------------------------------
bool linear( real8_t* slope, real8_t* inter,
             const real8_t x1, const real8_t y1,
             const real8_t x2, const real8_t y2 ) {
  // -------------------------------------------------------------------------------------
  real8_t d = x2-x1;
  if ( isZero(d) ) {
    *slope = MAX_POS_DOUBLE;
    *inter = D_ZERO;
    return true;
  }
  *slope = ( y2 - y1 ) / d;
  *inter = ( x2*y1 - x1*y2 ) / d;
  return false;
}


// =======================================================================================t
/** @brief Linear.
 *  @param[out] slope slope.
 *  @param[out] inter y intercept.
 *  @param[in]  x1    first  x coordinate.
 *  @param[in]  y1    first  y coordinate.
 *  @param[in]  x2    second x coordinate.
 *  @param[in]  y2    second y coordinate.
 *  @return true if singular.
 *
 *  Find the slope and intercept for the linear y = m x + b.
 */
// ---------------------------------------------------------------------------------------
bool linear( real4_t* slope, real4_t* inter,
             const real4_t x1, const real4_t y1,
             const real4_t x2, const real4_t y2 ) {
  // -------------------------------------------------------------------------------------
  real4_t d = x2-x1;
  if ( isZero(d) ) {
    *slope = MAX_POS_FLOAT;
    *inter = F_ZERO;
    return true;
  }
  *slope = ( y2 - y1 ) / d;
  *inter = ( x2*y1 - x1*y2 ) / d;
  return false;
}


// =======================================================================================t
/** @brief Linear.
 *  @param[out] slope slope.
 *  @param[out] inter y intercept.
 *  @param[in]  x     pointer to array of x coordinates.
 *  @param[in]  y     pointer to array of y coordinates.
 *  @param[in]  n     number of coordinates.
 *  @return true if singular.
 *
 *  Solve least squares for slope and intercept.
 */
// ---------------------------------------------------------------------------------------
bool linear( real8_t* slope, real8_t* inter,
             real8_t* x, real8_t* y, const size_t n ) {
  // -------------------------------------------------------------------------------------
  
  real8_t X  = x[0];
  real8_t Y  = y[0];
  real8_t X2 = x[0]*x[0];
  real8_t XY = x[0]*y[0];
  real8_t N  = (real8_t) n;

  for ( size_t i=1; i<n; i++ ) {
    X  += x[i];
    Y  += y[i];
    X2 += x[i]*x[i];
    XY += x[i]*y[i];
  }

  real8_t det = N*X2 - X*X;

  if ( isZero(det) ) {
    *slope = MAX_POS_DOUBLE;
    *inter = D_ZERO;
    return true;
  }

  *slope = (N*XY - X*Y)  / det;
  *inter = (X2*Y - X*XY) / det;
  
  return false;
}


// =======================================================================================t
/** @brief Linear.
 *  @param[out] slope slope.
 *  @param[out] inter y intercept.
 *  @param[in]  x     pointer to array of x coordinates.
 *  @param[in]  y     pointer to array of y coordinates.
 *  @param[in]  n     number of coordinates.
 *  @return true if singular.
 *
 *  Solve least squares for slope and intercept.
 */
// ---------------------------------------------------------------------------------------
bool linear( real4_t* slope, real4_t* inter,
             real4_t* x, real4_t* y, const size_t n ) {
  // -------------------------------------------------------------------------------------
  
  real4_t X  = x[0];
  real4_t Y  = y[0];
  real4_t X2 = x[0]*x[0];
  real4_t XY = x[0]*y[0];
  real4_t N  = (real4_t) n;

  for ( size_t i=1; i<n; i++ ) {
    X  += x[i];
    Y  += y[i];
    X2 += x[i]*x[i];
    XY += x[i]*y[i];
  }

  real4_t det = N*X2 - X*X;
  if ( isZero(det) ) {
    *slope = MAX_POS_FLOAT;
    *inter = F_ZERO;
    return true;
  }

  *slope = (N*XY - X*Y)  / det;
  *inter = (X2*Y - X*XY) / det;

  return false;
}


// =======================================================================================
/** @brief Random Source.
 *  @param[in] buffer pointer to the destination of the seed matter.
 *  @param[in] n      number of bytes.
 *
 *  Interface with /dev/urandom
 *  WARNING this is not suitable for large sequences. Use it to seed a PRNG
 */
// ---------------------------------------------------------------------------------------
void urandom( void* buffer, size_t n ) {
  // -------------------------------------------------------------------------------------
  int fd   = open("/dev/urandom", O_RDONLY);

  size_t    i = n;
  u_int8_t* p = static_cast<u_int8_t*>(buffer);

  while (0 < i) {
    size_t r = read(fd, static_cast<void*>(p), i);
    p = (p+r);
    i =  i-r;
  }

  close(fd);
}


// =======================================================================================t
/** @brief Arctangent.
 *  @param[in] y numerator of slope term.
 *  @param[in] x denomenator of slope term.
 *  @return a four quadrant arctangent in the range [0,2Pi).
 *
 *  Four quadrant arctangent [0,2Pi).
 */
// ---------------------------------------------------------------------------------------
real8_t ArcTan( const real8_t y, const real8_t x ) {
  // -------------------------------------------------------------------------------------
  if (x>D_ZERO) {
    if (y>D_ZERO) { return         atan(y/x); }  // y>0, x>0
    if (y<D_ZERO) { return D_2PI + atan(y/x); }  // y<0, x>0
    return                 D_ZERO; }             // y=0, x>0
  if (x<D_ZERO) {
    if (y>D_ZERO) { return D_PI  + atan(y/x); }  // y>0, x<0
    if (y<D_ZERO) { return D_PI  + atan(y/x); }  // y<0, x<0
    return                 D_PI; }               // y=0, x<0

  if (y>D_ZERO)   { return D_PI_2;  }            // y>0, x=0
  if (y<D_ZERO)   { return D_3PI_2; }            // y<0, x=0
  return                   D_ZERO;               // y=0, x=0
}


// =======================================================================================t
/** @brief Arctangent.
 *  @param[in] y numerator of slope term.
 *  @param[in] x denomenator of slope term.
 *  @return a four quadrant arctangent in the range [0,2Pi).
 *
 *  Four quadrant arctangent [0,2Pi).
 */
// ---------------------------------------------------------------------------------------
real4_t ArcTan( const real4_t y, const real4_t x ) {
  // -------------------------------------------------------------------------------------
  if (x>F_ZERO) {
    if (y>F_ZERO) { return         atanf(y/x); }  // y>0, x>0
    if (y<F_ZERO) { return F_2PI + atanf(y/x); }  // y<0, x>0
    return                 F_ZERO; }              // y=0, x>0
  if (x<F_ZERO) {
    if (y>F_ZERO) { return F_PI  + atanf(y/x); }  // y>0, x<0
    if (y<F_ZERO) { return F_PI  + atanf(y/x); }  // y<0, x<0
    return                 F_PI; }                // y=0, x<0

  if (y>F_ZERO)   { return F_PI_2;  }             // y>0, x=0
  if (y<F_ZERO)   { return F_3PI_2; }             // y<0, x=0
  return                   F_ZERO;                // y=0, x=0
}


// =======================================================================================t
/** @brief Arctangent.
 *  @param[in] y numerator of slope term.
 *  @param[in] x denomenator of slope term.
 *  @return a four quadrant arctangent in the range (-Pi,Pi].
 *
 *  Four quadrant arctangent (-Pi,Pi].
 */
// ---------------------------------------------------------------------------------------
real8_t ArcTanPM( const real8_t y, const real8_t x ) {
  // -------------------------------------------------------------------------------------
  if (x>D_ZERO) {
    if (y>D_ZERO) { return  atan(y/x); }        // x>0, y>0
    if (y<D_ZERO) { return  atan(y/x); }        // x>0, y<0
    return                  D_ZERO; }           // x>0, y=0
  if (x<D_ZERO) {
    if (y>D_ZERO) { return  D_PI + atan(y/x); } // x<0, y>0
    if (y<D_ZERO) { return  atan(y/x) - D_PI; } // x<0, y<0
    return                  D_PI; }             // x<0, y=0
   
  if (y>D_ZERO) {   return  D_PI_2; }           // x=0, y>0
  if (y<D_ZERO) {   return -D_PI_2; }           // x=0, y<0
  
  return                    D_ZERO;             // x=0, y=0
}


// =======================================================================================t
/** @brief Arctangent.
 *  @param[in] y numerator of slope term.
 *  @param[in] x denomenator of slope term.
 *  @return a four quadrant arctangent in the range (-Pi,Pi].
 *
 *  Four quadrant arctangent (-Pi,Pi].
 */
// ---------------------------------------------------------------------------------------
real4_t ArcTanPM( const real4_t y, const real4_t x ) {
  // -------------------------------------------------------------------------------------
  if (x>F_ZERO) {
    if (y>F_ZERO) { return  atan(y/x); }        // x>0, y>0
    if (y<F_ZERO) { return  atan(y/x); }        // x>0, y<0
    return                  F_ZERO; }           // x>0, y=0
  if (x<F_ZERO) {
    if (y>F_ZERO) { return  F_PI + atan(y/x); } // x<0, y>0
    if (y<F_ZERO) { return  atan(y/x) - F_PI; } // x<0, y<0
    return                  F_PI; }             // x<0, y=0
   
  if (y>F_ZERO) {   return  F_PI_2; }           // x=0, y>0
  if (y<F_ZERO) {   return -F_PI_2; }           // x=0, y<0
  
  return                    F_ZERO;             // x=0, y=0
}


// =======================================================================================t
/** @brief Angle between two vectors.
 *  @param[in] Ax x component of vector A.
 *  @param[in] Ay y component of vector A.
 *  @param[in] Bx x component of vector B.
 *  @param[in] By y component of vector B.
 *  @return radians in the range -Pi to Pi from +x towards +y axis.
 * 
 *  Angle in radians from vector A to vector B.
 */
// ---------------------------------------------------------------------------------------
real8_t Angle( const real8_t Ax, const real8_t Ay,
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


// =======================================================================================t
/** @brief Angle between two vectors.
 *  @param[in] Ax x component of vector A.
 *  @param[in] Ay y component of vector A.
 *  @param[in] Bx x component of vector B.
 *  @param[in] By y component of vector B.
 *  @return radians in the range -Pi to Pi from +x towards +y axis.
 * 
 *  Angle in radians from vector A to vector B.
 */
// ---------------------------------------------------------------------------------------
real4_t Angle( const real4_t Ax, const real4_t Ay,
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


// =======================================================================================t
/** @brief Parametric.
 *  @param[in] p vector for result.
 *  @param[in] a vector for zero point.
 *  @param[in] b vector for one  point.
 *  @param[in] n number of dimensions.
 *  @param[in] t parametric (0 <= t <=1 ).
 *
 *  Linear parametric between two multi-dimensional points.
 */
// ---------------------------------------------------------------------------------------
void parametric( real8_t* p, real8_t* a, real8_t* b, size_t n, real8_t t ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=0; i<n; i++) {
    p[i] = (a[i] + ((b[i]-a[i])*t));
  }
}


// =======================================================================================t
/** @brief Parametric.
 *  @param[in] p vector for result.
 *  @param[in] a vector for zero point.
 *  @param[in] b vector for one  point.
 *  @param[in] n number of dimensions.
 *  @param[in] t parametric (0 <= t <=1 ).
 *
 *  Linear parametric between two multi-dimensional points.
 */
// ---------------------------------------------------------------------------------------
void parametric( real4_t* p, real4_t* a, real4_t* b, size_t n, real4_t t ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=0; i<n; i++) {
    p[i] = (a[i] + ((b[i]-a[i])*t));
  }
}


// =======================================================================================
/** @brief Hexadecimal to decimal.
 *  @param[in] v single hexadecimal digit.
 *  @return value of digit.
 *
 *  Convert a single hexadecimal digit in ASCII into its decimal integer value.
 */
// ---------------------------------------------------------------------------------------
int hex2dec( const char v ) {
  // -------------------------------------------------------------------------------------
  int rv = 0;
  switch( v ) {
    case '1':           rv =  1; break;
    case '2':           rv =  2; break;
    case '3':           rv =  3; break;
    case '4':           rv =  4; break;
    case '5':           rv =  5; break;
    case '6':           rv =  6; break;
    case '7':           rv =  7; break;
    case '8':           rv =  8; break;
    case '9':           rv =  9; break;
    case 'a': case 'A': rv = 10; break;
    case 'b': case 'B': rv = 11; break;
    case 'c': case 'C': rv = 12; break;
    case 'd': case 'D': rv = 13; break;
    case 'e': case 'E': rv = 14; break;
    case 'f': case 'F': rv = 15; break;
    default: break;
  }
  return rv;
}


// =======================================================================================
/** @brief Hexadecimal to binary.
 *  @param[out] bin array of bytes.
 *  @param[in]  hex array of hexadecimal digits.
 *  @param[in]  nh  number of hexadecimal digits.
 *  @return number of bytes produced.
 *
 *  Convert a string of hexadecimal digits into binary bytes.
 */
// ---------------------------------------------------------------------------------------
size_t hex2bin( u_int8_t* bin, const char* hex, size_t nh ) {
  // -------------------------------------------------------------------------------------
  size_t    s = 0;
  size_t    d = 0;

  if ( 1 == (nh%2) ) {
    bin[d] = (u_int8_t) hex2dec( hex[s] );
    d=1;
    s=1;
  }

  while ( s<nh ) {
    int A = 16 * hex2dec( hex[s] ); s++;
    int B =      hex2dec( hex[s] ); s++;
    bin[d] = (u_int8_t)(A + B);
    d++;
  }

  return d;
}


// =======================================================================================t
/** @brief GCD.
 *  @param cu first number.
 *  @param cv second number.
 *  @return the greatest common divisor.
 *
 *  Compute the greatest common divisor using Iterative Euclid algorithm.
 */
// ---------------------------------------------------------------------------------------
int32_t gcd( const int32_t cu, const int32_t cv ) {
  // -------------------------------------------------------------------------------------
  int32_t t;
  int32_t u = cu;
  int32_t v = cv;
  while (v) {
    t = u; 
    u = v; 
    v = t % v;
  }
  return (u < 0L) ? (-u) : (u); /* abs(u) */
}


// =======================================================================================t
/** @brief GCD.
 *  @param cu first number.
 *  @param cv second number.
 *  @return the greatest common divisor.
 *
 *  Compute the greatest common divisor using Iterative Euclid algorithm.
 */
// ---------------------------------------------------------------------------------------
int64_t gcd( const int64_t cu, const int64_t cv ) {
  // -------------------------------------------------------------------------------------
  int64_t t;
  int64_t u = cu;
  int64_t v = cv;
  while (v) {
    t = u; 
    u = v; 
    v = t % v;
  }
  return (u < 0LL) ? (-u) : (u); /* abs(u) */
}


// =======================================================================================
// **                                   M A T H D E F                                   **
// ======================================================================== END FILE =====
