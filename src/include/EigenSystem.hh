// ====================================================================== BEGIN FILE =====
// **                             E I G E N S Y S T E M                                 **
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
/** @brief  Eigen System.
 *  @file   EigenSystem.hh
 *  @author Stephen W. Soliday
 *  @date 2019-Jul-08
 *
 *  Provides the interface for computing general and symetric eigen systems.
 */
// =======================================================================================

#ifndef __HH_EIGENSYSTEM_TRNCMP
#define __HH_EIGENSYSTEM_TRNCMP

#include <array_print.hh>
#include <TLogger.hh>

// =======================================================================================
// ---------------------------------------------------------------------------------------
class EigenSystem {
  // -------------------------------------------------------------------------------------

protected:
  TLOGGER_HEADER( logger );
  EMPTY_PROTOTYPE( EigenSystem );

  bool     is_sym;  ///< Flag true is input matrix is symetric.

  int32_t  N;       ///< The order of the matrix A.
  real8_t* A ;      ///< N-by-N input matrix
  int32_t  LDA;     ///< The leading dimension	of the array A.
  real8_t* WR;      ///< Array to receive the real eigen values.
  real8_t* WI;      ///< Array to receive the imaginary eigen values.
  real8_t* VL;      ///< UNUSED.
  int32_t  LDVL;    ///< UNUSED.
  real8_t* VR;      ///< The right eigenvectors
  int32_t  LDVR;    ///< The leading dimension	of the array VR.
  real8_t* WORK;    ///< Workspace
  int32_t  LWORK;   ///< The dimension	of the array WORK.
  int32_t  INFO;    ///< Return status form LAPACK driver routine.  

  real8_t**  vec_real;  ///< Real eigenvectors
  real8_t**  vec_imag;  ///< Imaginary eigenvectors
  
  EigenSystem( int32_t n, bool sym );

public:
  ~EigenSystem( void );

  static EigenSystem* general        ( real8_t **data, size_t n );
  static EigenSystem* general        ( real8_t  *data, size_t n );

  static EigenSystem* symetric       ( real8_t **data, size_t n );
  static EigenSystem* symetric       ( real8_t  *data, size_t n );

  static EigenSystem* upper_triangle ( real8_t  *data, size_t n );
  static EigenSystem* lower_triangle ( real8_t  *data, size_t n );

  size_t       size           ( void );

  void         set            ( real8_t **data );
  void         set            ( real8_t  *data );
  void         setUpper       ( real8_t  *data ); 
  void         setLower       ( real8_t  *data ); 

  void         compute        ( void );

  real8_t      eval           ( const size_t i );
  real8_t      ieval          ( const size_t i );
  real8_t*     evec           ( const size_t i );
  real8_t      evec           ( const size_t i, const size_t j );
  real8_t*     ievec          ( const size_t i );
  real8_t      ievec          ( const size_t i, const size_t j );

  void display( std::ostream& os, std::string fmt );
};


// =======================================================================================
/** @brief Size.
 *  @return order of the input matrix.
 */
// ---------------------------------------------------------------------------------------
inline  size_t EigenSystem::size( void ) {
  // -------------------------------------------------------------------------------------
  return (size_t)N;
}


// =======================================================================================
/** @brief Real eigen value.
 *  @param[in] i index.
 *  @return the real part of the ith eigen value.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t EigenSystem::eval( const size_t i ) {
  // -------------------------------------------------------------------------------------
  return WR[i];
}


// =======================================================================================
/** @brief Imaginary eigen value.
 *  @param[in] i index.
 *  @return the imaginary part of the ith eigen value.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t EigenSystem::ieval( const size_t i ) {
  // -------------------------------------------------------------------------------------
  return WI[i];
}


// =======================================================================================
/** @brief Eigen vector.
 *  @param[in] i index.
 *  @return pointer to the ith right eigen vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t* EigenSystem::evec( const size_t i ) {
  // -------------------------------------------------------------------------------------
  return (VR+(LDVR*i));
}


// =======================================================================================
/** @brief Eigen vector.
 *  @param[in] i index.
 *  @param[in] j element.
 *  @return the jth element of the ith right eigen vector.
 *
 */
// ---------------------------------------------------------------------------------------
inline  real8_t  EigenSystem::evec( const size_t i, const size_t j ) {
  // -------------------------------------------------------------------------------------
  return VR[LDVR*i + j];
}


#endif


// =======================================================================================
// **                             E I G E N S Y S T E M                                 **
// ======================================================================== END FILE =====
