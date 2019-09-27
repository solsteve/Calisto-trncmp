// ====================================================================== BEGIN FILE =====
// **                          F U Z Z Y : : P A R T I T I O N                          **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2014-2019, Stephen W. Soliday                                      **
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
/** @brief  Fuzzy Partition.
 *  @file   fuzzy/Partition.hh
 *  @author Stephen W. Soliday
 *  @date   2014-Jun-27 Original C++ release.
 *  @date   2018-Aug-09 Ported to Java.
 *  @date   2019-Sep-13 CMake refactorization.
 *
 * Provides the interface for a fuzzy partition.  R -> R^n
 *
 *   NEG    SN  ZERO  SP    POS
 *  ____                    ____ 1
 *      \   /\   /\   /\   /
 *       \ /  \ /  \ /  \ /
 *        X    X    X    X          This partition contains 5 fuzzy functions
 *       / \  / \  / \  / \         1 LeftTrapezoid 3 Triangle, and 1 RightTrapezoid
 *  ____/   \/   \/   \/   \____
 *  ============================ 0
 *
 */
// =======================================================================================


#ifndef __HH_FUZZY_PARTITION_TRNCMP
#define __HH_FUZZY_PARTITION_TRNCMP


#include <fuzzy/Set.hh>
#include <TLogger.hh>


namespace fuzzy {


// =======================================================================================
class Partition {
  // -------------------------------------------------------------------------------------
 protected:
  TLOGGER_HEADER( logger );

  Partition& operator=(const fuzzy::Partition&);

  Set**   fset;
  int32_t num_set;
  real8_t min_ctr;
  real8_t max_ctr;

  
  void destroy ( void );
  bool resize  ( const int32_t n );

  
 public:
  Partition  ( void );
  Partition  ( const int32_t n ); 
  Partition  ( const int32_t n, const real8_t  left, const real8_t right ); 
  Partition  ( const int32_t n, real8_t* ctrs );
  Partition  ( const Partition& psrc );

  ~Partition ( void );

  Set&        get           ( const int32_t i );

  int32_t     nIn           ( void ) const; ///< Number of inputs
  int32_t     nOut          ( void ) const; ///< Number of outputs
  int32_t     size          ( void ) const; ///< Storage size (load/store elements)
  real8_t*    create_buffer ( void );
  real8_t     getCenter     ( const int32_t idx ) const;

  // ----- configuration ----------------------------------

  void        balance   ( void );

  void        set       ( const int32_t n ); 
  void        set       ( const int32_t n, const real8_t minc, const real8_t maxc ); 
  void        set       ( const int32_t n, real8_t* ctrs );

  void        set       ( real8_t* ctrs );
  void        set       ( const real8_t minc, const real8_t maxc );

  void        copy      ( const Partition& psrc );
  Partition*  clone     ( void );


  // ----- execution --------------------------------------

  void        mu        ( real8_t* degree, const real8_t x );
  real8_t     area      ( real8_t* degree );
  real8_t     coa       ( real8_t* degree );

  // ----- storage and transfer ---------------------------

  real8_t*    load      ( real8_t* src );
  real8_t*    store     ( real8_t* dst );
  
  bool        write     ( std::ofstream& ofs, std::string fmt = "%23.16e" );
  bool        read      ( std::ifstream& ifs );

}; // end class Partition


}; // end namespace fuzzy


#endif 


// =======================================================================================
// **                          F U Z Z Y : : P A R T I T I O N                          **
// ======================================================================== END FILE =====
