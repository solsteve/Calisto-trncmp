// ====================================================================== BEGIN FILE =====
// **                                      D I C E                                      **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 1990, 2009,16,19, Stephen W. Soliday                               **
// **                                  stephen.soliday@trncmp.org                       **
// **                                  http://research.trncmp.org                       **
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


#ifndef __DICE_TRNCMP_HH
#define __DICE_TRNCMP_HH


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

  bool      seed_set    ( void );                          //< seed with /dev/urandom.
  bool      seed_set    ( std::string fspc );              //< seed with binary file.
  bool      seed_set    ( void* src, size_t n );           //< seed with array.

  size_t    seed_size   ( void ) { return ent_engine->seedSize(); }

  // ----- core random functions ---------------------------------------------------------

  bool      boolean   ( real8_t thres = N_HALF );
  real8_t   uniform   ( void );
  real8_t   gaussian  ( void );
  size_t    index     ( size_t maxValue );
}; // end class Dice

#endif

// =======================================================================================
// **                                      D I C E                                      **
// ======================================================================== END FILE =====
