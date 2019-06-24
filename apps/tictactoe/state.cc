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

#include <state.hh>

const size_t State::EMPTY  = 0;
const size_t State::PO     = 1;
const size_t State::PX     = 2;

const size_t State::INPLAY = 0;
const size_t State::WIN    = 1;
const size_t State::DRAW   = 2;


// =======================================================================================
void State::clear( void ) {
  // -------------------------------------------------------------------------------------
  valid = false;
  id    = 0;
  uid   = 0;
  
  for ( size_t i=0; i<9; i++ ) {
    board[i] = 0;
    next[i]  = 0;
  }
  
  result  = INPLAY;
  current = EMPTY;
  winner  = EMPTY;
}


// =======================================================================================
State::State( void ) : valid(false), id(0), result(0), current(0), winner(0), uid(0)  {
  // -------------------------------------------------------------------------------------
  clear();
}


// =======================================================================================
State::~State( void ) {
  // -------------------------------------------------------------------------------------
  clear();
}


// =======================================================================================
void State::display( std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  const char *RES[] = { "inplay", "win", "draw" };
  
  os << " "   << State::marker( board[0] )
     << " | " << State::marker( board[1] )
     << " | " << State::marker( board[2] )

     << "\n---+---+---\n"

     << " "   << State::marker( board[3] )
     << " | " << State::marker( board[4] )
     << " | " << State::marker( board[5] )

     << "     " << id

     << "\tplay: " << State::marker( current )
     << " [" << RES[result] << "]: " << State::marker( winner )

     << "\n---+---+---\n"

     << " "   << State::marker( board[6] )
     << " | " << State::marker( board[7] )
     << " | " << State::marker( board[8] )

     << "\n\n";
}


// =======================================================================================
void State::load( Counter& C ) {
  // -------------------------------------------------------------------------------------
  C.store( board );
}


// =======================================================================================
void State::load( size_t src[] ) {
  // -------------------------------------------------------------------------------------
  for ( size_t i=0; i<9; i++ ) {
    board[i] = src[i];
  }
}


// =======================================================================================
void State::store( size_t dst[] ) {
  // -------------------------------------------------------------------------------------
  for ( size_t i=0; i<9; i++ ) {
    dst[i] = board[i];
  }
}


// =======================================================================================
char State::marker( const size_t p ) {
  // -------------------------------------------------------------------------------------
  char mark = '-';
  if ( State::EMPTY == p ) { mark = '.'; }
  if ( State::PO    == p ) { mark = 'o'; }
  if ( State::PX    == p ) { mark = 'x'; }

  return mark;
}


// =======================================================================================
size_t State::check( State& S ) {
  // -------------------------------------------------------------------------------------
  if ( (PO==S.board[0]) && (PO==S.board[1]) && (PO==S.board[2]) ) { return PO; }
  if ( (PO==S.board[3]) && (PO==S.board[4]) && (PO==S.board[5]) ) { return PO; }
  if ( (PO==S.board[6]) && (PO==S.board[7]) && (PO==S.board[8]) ) { return PO; }
  if ( (PO==S.board[0]) && (PO==S.board[3]) && (PO==S.board[6]) ) { return PO; }
  if ( (PO==S.board[1]) && (PO==S.board[4]) && (PO==S.board[7]) ) { return PO; }
  if ( (PO==S.board[2]) && (PO==S.board[5]) && (PO==S.board[8]) ) { return PO; }
  if ( (PO==S.board[0]) && (PO==S.board[4]) && (PO==S.board[8]) ) { return PO; }
  if ( (PO==S.board[2]) && (PO==S.board[4]) && (PO==S.board[6]) ) { return PO; }

  if ( (PX==S.board[0]) && (PX==S.board[1]) && (PX==S.board[2]) ) { return PX; }
  if ( (PX==S.board[3]) && (PX==S.board[4]) && (PX==S.board[5]) ) { return PX; }
  if ( (PX==S.board[6]) && (PX==S.board[7]) && (PX==S.board[8]) ) { return PX; }
  if ( (PX==S.board[0]) && (PX==S.board[3]) && (PX==S.board[6]) ) { return PX; }
  if ( (PX==S.board[1]) && (PX==S.board[4]) && (PX==S.board[7]) ) { return PX; }
  if ( (PX==S.board[2]) && (PX==S.board[5]) && (PX==S.board[8]) ) { return PX; }
  if ( (PX==S.board[0]) && (PX==S.board[4]) && (PX==S.board[8]) ) { return PX; }
  if ( (PX==S.board[2]) && (PX==S.board[4]) && (PX==S.board[6]) ) { return PX; }

  return EMPTY;
}


// =======================================================================================
bool State::compare( size_t t[] ) {
  // -------------------------------------------------------------------------------------
  for ( size_t i=0; i<9; i++ ) {
    if ( t[i] != board[i] ) {
      return false;
    }
  }
  return true;
}  


// =======================================================================================
size_t State::index( size_t x[] ) {
  // -------------------------------------------------------------------------------------
  size_t S = 0;
  size_t M = 1;
  for ( size_t i=0; i<9; i++ ) {
    S += (M*x[i]);
    M *= 3;
  }
  return S;  
}

// =======================================================================================
size_t State::maxIndex( void ) {
  // -------------------------------------------------------------------------------------
  size_t M = 1;
  for ( size_t i=0; i<9; i++ ) {
    M *= 3;
  }
  return M-1;  
}


// =======================================================================================
size_t State::toggle( size_t p ) {
  // -------------------------------------------------------------------------------------
  return ( (PO == p) ? (PX) : (PO));  
}


// =======================================================================================
void   State::write( std::ofstream& fp ) {
  // -------------------------------------------------------------------------------------
  fp << c_fmt( "%6lu", uid );
  fp << c_fmt( "%4lu", id );
  fp << c_fmt( " %lu", result );
  fp << c_fmt( " %lu", current );

  for ( size_t j=0; j<9; j++ ) {
    fp << c_fmt( " %lu", board[j] );
  }

  for ( size_t j=0; j<9; j++ ) {
    fp << c_fmt( " %4lu", next[j] );
  }

  fp << "\n";
}


// =======================================================================================
void   State::read( std::ifstream& fp ) {
  // -------------------------------------------------------------------------------------
  fp >> uid >> id >> result >> current;
  
  for ( size_t j=0; j<9; j++ ) {
    fp >> board[j];
  }
  
  for ( size_t j=0; j<9; j++ ) {
    fp >> next[j];
  }
}


// =======================================================================================
// **                                                                                   **
// ======================================================================== END FILE =====
