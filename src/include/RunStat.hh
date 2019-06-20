// ====================================================================== BEGIN FILE =====
// **                                   R U N S T A T                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2015, 2019, Stephen W. Soliday                                     **
// **                            stephen.soliday@trncmp.org                             **
// **                            http://research.trncmp.org                             **
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
/** @brief  Running Statistics.
 *  @file   RunStat.hh
 *  @author Stephen W. Soliday
 *  @date   2015-01-26  Original release.
 *  @date   2019-Jun-14 CMake refactorization.
 *
 *  Provides the interface for a running statistics.
 */
// =======================================================================================


#ifndef __RUNSTAT_TRNCMP_HH
#define __RUNSTAT_TRNCMP_HH

#include <trncmp.hh>


// =======================================================================================
class RunStat {
  // -------------------------------------------------------------------------------------
 protected:
  std::string name;
  real8_t     min_val;
  real8_t     max_val;
  real8_t     mean_val;
  real8_t     mean_val_sq;
  bool        is_first;
  size_t      num_samp;
  size_t      min_idx;
  size_t      max_idx;

 public:

  RunStat  ( std::string nm );
  ~RunStat ( void );
  
  size_t  count  ( void );
  real8_t minv   ( void );
  real8_t maxv   ( void );
  real8_t mean   ( void );
  real8_t var    ( void );
  real8_t stdev  ( void );
  size_t  mini   ( void );
  size_t  maxi   ( void );

  void    reset  ( void );

  void    report ( std::ostream& os = std::cout );

  // =====================================================================================
  /** @brief Update.
   *  @param[in] v sample value.
   */
  // -------------------------------------------------------------------------------------
  template<class T>
  void update( T v ) {
    // -----------------------------------------------------------------------------------
    real8_t x = (real8_t) v;
    if ( is_first ) {
      min_val     = x;
      max_val     = x;
      mean_val    = x;
      mean_val_sq = x*x;
      is_first    = false;
      num_samp       = 1;
      min_idx     = 0;
      max_idx     = 0;
    } else {
      if ( x < min_val ) { min_val = x; min_idx = num_samp; }
      if ( x > max_val ) { max_val = x; max_idx = num_samp; }

      real8_t t  = (real8_t)num_samp * mean_val;
      real8_t t2 = (real8_t)num_samp * mean_val_sq;
      num_samp++;
      mean_val    = (x   + t )/(real8_t)num_samp;
      mean_val_sq = (x*x + t2)/(real8_t)num_samp;      
    }

  };

  // =====================================================================================
  /** @brief Batch Update.
   *  @param[in] a pointer to an array of sample values.
   *  @param[in] n number of ellements in the sample array.
   */
  // -------------------------------------------------------------------------------------
  template<class T>
  void batch( T* a, size_t n ) {
    // -----------------------------------------------------------------------------------
    for ( size_t i=0; i<n; i++ ) {
      update( a[i] );
    }
  };

}; // end class RunStat


// =======================================================================================
/** @brief Minimum.
 *  @return minimum sampled value.
 */
// ---------------------------------------------------------------------------------------
inline  size_t RunStat::count( void ) {
  // -------------------------------------------------------------------------------------
  return num_samp;
}


// =======================================================================================
/** @brief Minimum.
 *  @return minimum sampled value.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t RunStat::minv( void ) {
  // -------------------------------------------------------------------------------------
  return min_val;
}


// =======================================================================================
/** @brief maximum.
 *  @return maximum sampled value.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t RunStat::maxv( void ) {
  // -------------------------------------------------------------------------------------
  return max_val;
}


// =======================================================================================
/** @brief Mean.
 *  @return mean of the sampled values.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t RunStat::mean( void ) {
  // -------------------------------------------------------------------------------------
  return mean_val;
}


// =======================================================================================
/** @brief Standard Deviation.
 *  @return mean of the standard deviation of the sampled values.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t RunStat::stdev( void ) {
  // -------------------------------------------------------------------------------------
  return sqrt( var() );
}


// =======================================================================================
/** @brief Minimum.
 *  @return index of the minimum sampled value.
 */
// ---------------------------------------------------------------------------------------
inline  size_t RunStat::mini( void ) {
  // -------------------------------------------------------------------------------------
  return min_idx;
}


// =======================================================================================
/** @brief Maximum.
 *  @return index of the maximum sampled value.
 */
// ---------------------------------------------------------------------------------------
inline  size_t RunStat::maxi( void ) {
  // -------------------------------------------------------------------------------------
  return max_idx;
}


#endif


// =======================================================================================
// **                                   R U N S T A T                                   **
// ======================================================================== END FILE =====
