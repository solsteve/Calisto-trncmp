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

#include <state_table.hh>

// =======================================================================================
// -------------------------------------------------------------------------------------
State* table;
size_t table_size;

// =======================================================================================
StateTable::StateTable( std::string fspc ) : table(0), table_size(0) {
  // -------------------------------------------------------------------------------------
  read( fspc );
}


// =======================================================================================
StateTable::StateTable( size_t n ) : table(0), table_size(0) {
  // -------------------------------------------------------------------------------------
  init( n );
}


// =======================================================================================
StateTable::~StateTable( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}


// =======================================================================================
void StateTable::destroy( void ) {
  // -------------------------------------------------------------------------------------
  if ( 0 < table_size ) {
    delete[] table;
  }
  table_size = 0;
  table = static_cast<State*>(0);
}


// =======================================================================================
void StateTable::init( size_t n ) {
  // -------------------------------------------------------------------------------------
  if ( table_size < n ) {
    destroy();
  }
  table      = new State[ n ];
  table_size = n;
}


// =======================================================================================
void StateTable::write( std::string fspc ) {
  // -------------------------------------------------------------------------------------
    std::ofstream fp( fspc );

    fp << table_size << "\n";

    for ( size_t i=0; i<table_size; i++ ) {
      table[i].write( fp );
    }

  fp.close();
}


// =======================================================================================
void StateTable::read( std::string fspc ) {
  // -------------------------------------------------------------------------------------
    std::ifstream fp( fspc );

    size_t n;
    fp >> n;
    init( n );

    for ( size_t i=0; i<n; i++ ) {
      table[i].read( fp );
    }
  
  fp.close();
}

// =======================================================================================
size_t StateTable::find( size_t t[] ) {
  // -------------------------------------------------------------------------------------
  for ( size_t i=0; i<table_size; i++ ) {
    if ( table[i].compare( t ) ) {
      return i;
    }
  }
  return 0;
}

// =======================================================================================
// **                                                                                   **
// ======================================================================== END FILE =====
