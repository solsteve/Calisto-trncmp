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

#ifndef __STATE_TABLE_HH
#define __STATE_TABLE_HH

#include <state.hh>

// =======================================================================================
class StateTable {
  // -------------------------------------------------------------------------------------
 public:

  State* table;
  size_t table_size;

  StateTable  ( std::string fspc );
  StateTable  ( size_t n );
  ~StateTable ( void );

  void   destroy ( void );
  void   init    ( size_t n );

  void   write   ( std::string fspc );
  void   read    ( std::string fspc );
  size_t find    ( size_t t[] );

 private:
  EMPTY_PROTOTYPE( StateTable );
};

#endif

// =======================================================================================
// **                                                                                   **
// ======================================================================== END FILE =====
