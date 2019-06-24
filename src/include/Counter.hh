// ====================================================================== BEGIN FILE =====
// **                                   C O U N T E R                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2011-2019, Stephen W. Soliday                                      **
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
