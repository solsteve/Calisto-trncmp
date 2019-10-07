// ====================================================================== BEGIN FILE =====
// **                              E V O : : T O O L K I T                              **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 1995-2019, Stephen W. Soliday                                      **
// **                           stephen.soliday@trncmp.org                              **
// **                           http://research.trncmp.org                              **
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
/** @brief ToolKit.
 *  @file   evo/ToolKit.hh
 *  @author Stephen W. Soliday
 *  @date   2014-Jun-27 Original C++ release
 *  @date   2019-Sep-27 CMake refactorization.
 *
 *  Provides an interface for basic operators.
 */
// =======================================================================================

#ifndef __HH_EVO_TOOLKIT_TRNCMP
#define __HH_EVO_TOOLKIT_TRNCMP


#include <Dice.hh>


namespace evo {


// =======================================================================================
class ToolKit {
  // -------------------------------------------------------------------------------------
 protected:
  Dice* dd;

  ToolKit  ( Dice* d );

  static ToolKit* theInstance;

  EMPTY_PROTOTYPE( ToolKit );

 public:
  ~ToolKit ( void );

  static ToolKit* getInstance ( void );
  static ToolKit* getInstance ( Dice* d );
  static void     delInstance ( void );

  static real8_t  parametric  ( const real8_t a, const real8_t b, const real8_t t );
  static int32_t  parametric  ( const int32_t a, const int32_t b, const real8_t t );

  static real8_t  parametric  ( const real8_t a, const real8_t b, const real8_t t,
                   const real8_t min_value, const real8_t max_value );
  static int32_t  parametric  ( const int32_t a, const int32_t b, const real8_t t,
                   const int32_t min_value, const int32_t max_value );

  void randomize ( real8_t* a, int32_t n, const real8_t min_val, const real8_t max_val );
  void randomize ( int32_t* a, int32_t n, const int32_t min_val, const int32_t max_val );
  void randomize ( int32_t* a, int32_t n );

  void bracket   ( real8_t* a, int32_t n,
                   const real8_t min_val, const real8_t max_val,
                   real8_t* src = static_cast<real8_t*>(0) );

  void bracket   ( int32_t* a, int32_t n,
                   const int32_t min_val, const int32_t max_val,
                   int32_t* src = static_cast<int32_t*>(0) );

  void noise     ( real8_t* a, int32_t n, const real8_t sigma,
                   const real8_t min_val, const real8_t max_val,
                   real8_t* src = static_cast<real8_t*>(0) );
  
  void noise     ( int32_t* a, int32_t n, const real8_t sigma,
                   const int32_t min_val, const int32_t max_val,
                   int32_t* src = static_cast<int32_t*>(0) );
  
  void permute   ( int32_t* a, int32_t n, const real8_t sigma,
                   int32_t* src = static_cast<int32_t*>(0) );

  void crossover ( real8_t* c1, real8_t* c2, real8_t* p1, real8_t* p2,
                   const int32_t n, const real8_t t,
                   const real8_t min_val, const real8_t max_val );
  
  void crossover ( int32_t* c1, int32_t* c2, int32_t* p1, int32_t* p2,
                   const int32_t n, const real8_t t,
                   const int32_t min_val, const int32_t max_val );
  
  void mutate    ( real8_t* c, const int32_t n,
                   const real8_t sigma, const real8_t perc,
                   const real8_t min_val, const real8_t max_val,
                   real8_t* p = static_cast<real8_t*>(0) );

  void mutate    ( int32_t* c, const int32_t n,
                   const real8_t sigma, const real8_t perc,
                   const int32_t min_val, const int32_t max_val,
                   int32_t* p= static_cast<int32_t*>(0) );

}; // end class ToolKit

// =======================================================================================
/** @brief Parametric.
 *  @param[in] A zero point.
 *  @param[in] B one  point.
 *  @param[in] t parametric ( 0 <= t <=1 ).
 *  @return a * ( 1-t ) + b * t.
 *
 *  Linear parametric between two points.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t ToolKit::parametric( const real8_t A, const real8_t B, const real8_t t ) {
  // -------------------------------------------------------------------------------------
  return A + ( t * ( B - A ) );
}


// =======================================================================================
/** @brief Parametric.
 *  @param[in] sA zero point.
 *  @param[in] sB one  point.
 *  @param[in] t  parametric ( 0 <= t <=1 ).
 *  @return a * ( 1-t ) + b * t.
 *
 *  Linear parametric between two points.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t ToolKit::parametric( const int32_t a, const int32_t b, const real8_t t ) {
  // -------------------------------------------------------------------------------------
  return (int32_t) floor( t * ( real8_t )( b - a ) + D_HALF ) + a;
}


// =======================================================================================
/** @brief Parametric.
 *  @param[in] A   zero point.
 *  @param[in] B   one  point.
 *  @param[in] t   parametric ( 0 <= t <=1 ).
 *  @param[in] min_value minimum value.
 *  @param[in] max_value maximum value.
 *  @return a * ( 1-t ) + b * t.
 *
 *  Linear parametric between two points.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t ToolKit::parametric( const real8_t A, const real8_t B, const real8_t t,
                   const real8_t min_value, const real8_t max_value ) {
  // -------------------------------------------------------------------------------------
  real8_t x = A + ( t * ( B - A ) );
  return (( min_value > x) ? (min_value) :((max_value < x) ? (max_value) :(x)));
}


// =======================================================================================
/** @brief Parametric.
 *  @param[in] sA  zero point.
 *  @param[in] sB  one  point.
 *  @param[in] t   parametric ( 0 <= t <=1 ).
 *  @param[in] min_value minimum value.
 *  @param[in] max_value maximum value.
 *  @return a * ( 1-t ) + b * t.
 *
 *  Linear parametric between two points.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t ToolKit::parametric( const int32_t a, const int32_t b, const real8_t t,
                   const int32_t min_value, const int32_t max_value ) {
  // -------------------------------------------------------------------------------------
  int32_t x = (int32_t) floor( t * ( real8_t )( b - a ) + D_HALF ) + a;
  return (( min_value > x) ? (min_value) :((max_value < x) ? (max_value) :(x)));
}


}; // end namespace evo


#endif


// =======================================================================================
// **                              E V O : : T O O L K I T                              **
// =========================================================================== END FILE ==
