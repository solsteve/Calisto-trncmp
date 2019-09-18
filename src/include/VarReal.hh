// ====================================================================== BEGIN FILE =====
// **                                   V A R R E A L                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2015-2019, Stephen W. Soliday                                      **
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
//
/** @brief  Variable row length array.
 *  @file   VarReal.hh
 *  @author Stephen W. Soliday
 *  @date   2015-Feb-09 Original release.
 *  @date   2019-Sep-01 CMake refactorization.
 *
 *  Provides the interface for a templated 2-D array with variable row length.
 */
// =======================================================================================


#ifndef __HH_VARREAL_TRNCMP
#define __HH_VARREAL_TRNCMP

#include <trncmp.hh>

// =======================================================================================
class VarReal {
  // -------------------------------------------------------------------------------------
 protected:
  int32_t   n_buf;
  int32_t   n_row;
  int32_t*  n_col;
  real8_t*  data;
  real8_t** rowptr;

  EMPTY_PROTOTYPE( VarReal );

  void destroy ( void );
  void resize  ( const int32_t nr, const int32_t* nc );
  
 public:
  VarReal  ( void );
  VarReal  ( const int32_t nr, const int32_t* nc );
  VarReal  ( const int32_t nr, const int32_t* nc, real8_t* src );
  ~VarReal ( void );

  int32_t  size  ( void ) const;
  int32_t  nRow  ( void ) const;
  int32_t  nCol  ( const int32_t c ) const;

  real8_t  get        ( const int32_t r, const int32_t c ) const;
  void     set        ( const int32_t r, const int32_t c, const real8_t val );
  
  real8_t& operator() ( const int32_t r, const int32_t c );
  real8_t* operator() ( const int32_t r );

  real8_t* load  ( real8_t* src );
  real8_t* store ( real8_t* dst );

}; // end class VarReal


#endif

// =======================================================================================
// **                                   V A R R E A L                                   **
// ======================================================================== END FILE =====
