// ====================================================================== BEGIN FILE =====
// **                                   C O U N T E R                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2011, 2019  Stephen W. Soliday                                     **
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
/** @brief  Counter.
 *  @file   Counter.hh
 *  @author Stephen W. Soliday
 *  @date   2011-Jan-28 Original release.
 *  @date   2019-May-15 CMake refactorization.
 *
 *  Provides the interface for an arbitrary base counter.
 */
// =======================================================================================


#ifndef __HH_COUNTER_TRNCMP
#define __HH_COUNTER_TRNCMP

#include <trncmp.hh>

// =======================================================================================
class Counter {
  // -------------------------------------------------------------------------------------
 protected:
  
  size_t* buffer;
  size_t  counting_base;
  size_t  numberofdigits;

  // -------------------------------------------------------------------------------------
 public:
  
  Counter              ( size_t b, size_t n );
  ~Counter             ( void );

  void     init        ( size_t b, size_t n );
  void     destroy     ( void );

  size_t   value       ( size_t idx );
  size_t   base        ( void );
  size_t   N           ( void );
  size_t   space       ( void );
  size_t   maxValue    ( void );

  void     print       ( std::ostream& outf );
  void     copy        ( Counter* that ); 
  Counter* clone       ( void ); 

  size_t*  load        ( size_t* src );
  size_t*  store       ( size_t* dst );

  void     reset       ( void );
  int      inc         ( size_t d );
  int      inc         ( void );

  size_t   toDecimal   ( void );
  void     fromDecimal ( size_t );

  // -------------------------------------------------------------------------------------
 private:
  Counter(const Counter&);
  Counter& operator=(const Counter&);
};

inline  size_t Counter::value       ( size_t idx ) { return buffer[idx];    };
inline  size_t Counter::base        ( void )       { return counting_base;  };
inline  size_t Counter::N           ( void )       { return numberofdigits; };


#endif 

// =======================================================================================
// **                                   C O U N T E R                                   **
// ======================================================================== END FILE =====
