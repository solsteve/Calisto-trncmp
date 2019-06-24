// ====================================================================== BEGIN FILE =====
// **                                                                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 1989-2019, Stephen W. Soliday                                      **
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
/** @brief 
 *  @file   .cc
 *  @author Stephen W. Soliday
 *  @date   2019-May-16
 *
 *  
 */
// =======================================================================================

#ifndef __STATE_HH
#define __STATE_HH

#include <cstdlib>
#include <cstdio>
#include <ostream>
#include <Counter.hh>

// =======================================================================================
class State {
  // -------------------------------------------------------------------------------------
 public:

  static const size_t EMPTY;
  static const size_t PO;
  static const size_t PX;

  static const size_t INPLAY;
  static const size_t WIN;
  static const size_t DRAW;

  static char   marker   ( const size_t p );
  static size_t check    ( State& S );
  static size_t index    ( size_t x[] );
  static size_t maxIndex ( void );
  static size_t toggle   ( size_t p );


  bool   valid;    ///< valid representation
  size_t id;       ///< id number
  size_t board[9]; ///< board in row order
  size_t next[9];  ///< next address in row order no one points to zero so that is unconnected
  size_t result;   ///< INPLAY, WIN, DRAW
  size_t current;  ///< The next player to move from this state, or the winner.
  size_t winner;   ///< The next player to move from this state, or the winner.

  size_t uid;

  State( void );
  ~State ( void );

  void   clear   ( void );
  void   display ( std::ostream& os );
  bool   compare ( size_t t[] );

  void   load  ( Counter& C );
  void   load  ( size_t src[] );
  void   store ( size_t dst[] );

  void   write ( std::ofstream& fp );
  void   read  ( std::ifstream& fp );
};



#endif

// =======================================================================================
// **                                                                                   **
// ======================================================================== END FILE =====
