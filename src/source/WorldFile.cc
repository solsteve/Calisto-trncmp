// ====================================================================== BEGIN FILE =====
// **                                 W O R L D F I L E                                 **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2013-2019, Stephen W. Soliday                                      **
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
/** @brief  ESRI World File
 *  @file   WorldFile.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-15.
 *
 *  Provides the interface for a class to maintain coordinate trainsforms.
 */
// =======================================================================================


#include <WorldFile.hh>

// =======================================================================================
WorldFile::WorldFile( void ) : data() {
  // -------------------------------------------------------------------------------------
  this->destroy();
}

  
// =======================================================================================
WorldFile::WorldFile( std::string fspc ) : data() {
  // -------------------------------------------------------------------------------------
  this->read( fspc );
}

  
  
// =======================================================================================
void WorldFile::destroy( void ) {
  // -------------------------------------------------------------------------------------
  this->A( 1.0 );
  this->B( 0.0 );
  this->C( 0.0 );
  this->D( 0.0 );
  this->E(-1.0 );
  this->F( 0.0 );
}

  
// =======================================================================================
WorldFile::~WorldFile ( void ) {
  // -------------------------------------------------------------------------------------
  this->destroy();
}
  

// =======================================================================================
int WorldFile::read( std::string fspc ) {
  // -------------------------------------------------------------------------------------
  std::ifstream inf( fspc );
  
  for ( int r=0; r<3; r++ ) {
    for ( int c=0; c<2; c++ ) {
      inf >> data[r][c];
    }
  }
  inf.close();

  return 0;
}
  
  
// =======================================================================================
int WorldFile::write( std::string fspc ) {
  // -------------------------------------------------------------------------------------
  std::ofstream outf( fspc );
  
  for ( int r=0; r<3; r++ ) {
    for ( int c=0; c<2; c++ ) {
      outf << c_fmt( "%.3f", data[r][c] ) << std::endl;
    }
  }

  outf.close();

  return 0;
}


// =======================================================================================
void WorldFile::fromGDAL( real8_t g[6] ) {
  // -------------------------------------------------------------------------------------
  this->C( g[0] );
  this->A( g[1] );
  this->D( g[2] );
  this->F( g[3] );
  this->B( g[4] );
  this->E( g[5] );
}


// =======================================================================================
// **                                 W O R L D F I L E                                 **
// ======================================================================== END FILE =====
