// ====================================================================== BEGIN FILE =====
// **                                      D I C E                                      **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 1990-2019, Stephen W. Soliday                                      **
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
/** @brief  Dice.
 *  @file   Dice.hh
 *  @author Stephen W. Soliday
 *  @date 1990-02-17 Original release.
 *  @date 2009-02-07 Major revision.
 *  @date 2016-10-11 Major revision.
 *  @date 2019-Jun-14 CMake refactorization.
 *
 *  Provides the interface for various random distributions.
 */
// =======================================================================================


#ifndef __HH_DICE_TRNCMP
#define __HH_DICE_TRNCMP


#include <Entropy.hh>
#include <TLogger.hh>


// =======================================================================================
// ---------------------------------------------------------------------------------------
class Dice {
  // -------------------------------------------------------------------------------------
private:
  EMPTY_PROTOTYPE( Dice );
  TLOGGER_HEADER( logger );
  
  static Dice* theInstance;  //< static singleton instance.
  Entropy*     ent_engine;   //< pointer to an entropy source.

  // -------------------------------------------------------------------------------------
protected:
  bool              have_spare;      //< state flag for Box-Muller.
  real8_t           rand1, rand2;     //< state variables for Box-Muller.

  Dice  ( void );                                        //< seed with /dev/urandom.
  Dice  ( std::string fspc );                            //< seed with binary file.
  Dice  ( void* sm, size_t n );                          //< seed with array.

  Dice  ( Entropy* eng );                                //< seed with /dev/urandom.
  Dice  ( Entropy* eng, std::string fspc );              //< seed with binary file.
  Dice  ( Entropy* eng, void* sm, size_t n );            //< seed with array.

  // -------------------------------------------------------------------------------------
public:

  ~Dice ( void );
  
  // ----- global instance ---(preferred)-------------------------------------------------
  
  static Dice* getInstance ( void );                              //< seed with /dev/urandom.
  static Dice* getInstance ( std::string fspc );                  //< seed with binary file.
  static Dice* getInstance ( void* sm, size_t n );                //< seed with array.

  static Dice* getInstance ( Entropy* eng );                      //< seed with /dev/urandom.
  static Dice* getInstance ( Entropy* eng, std::string fspc );    //< seed with binary file.
  static Dice* getInstance ( Entropy* eng, void* sm, size_t n );  //< seed with array.

  static void  delInstance ( void );

  // ----- apply seed to running instance ------------------------------------------------

  void      seed_set    ( void );                          //< seed with /dev/urandom.
  void      seed_set    ( std::string fspc );              //< seed with binary file.
  void      seed_set    ( void* src, size_t n );           //< seed with array.

  size_t    seed_size   ( void ) { return ent_engine->seed_size(); }

  // ----- core random functions ---------------------------------------------------------

  bool      boolean   ( real8_t thres = D_HALF );
  real8_t   uniform   ( void );
  real8_t   normal    ( void );
  size_t    index     ( size_t maxValue );
}; // end class Dice


#endif


// =======================================================================================
// **                                      D I C E                                      **
// ======================================================================== END FILE =====
