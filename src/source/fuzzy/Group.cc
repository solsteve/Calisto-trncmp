// ====================================================================== BEGIN FILE =====
// **                              F U Z Z Y : : G R O U P                              **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2015-2019, Stephen W. Soliday                                      **
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
/** @brief  Fuzzy Group.
 *  @file   fuzzy/Group.cc
 *  @author Stephen W. Soliday
 *
 * Provides the methods for a fuzzy group. A group is a collection of fuzzy Partitions.
 * R^m -> R^(mxSUM(n[i],i=1,n))
 *
 *
 */
// =======================================================================================


#include <fuzzy/Group.hh>


namespace fuzzy {


#define INIT_VAR(_a) num_part(_a), part(_a)


// =======================================================================================
// ---------------------------------------------------------------------------------------
void Group::destroy( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<Partition**>(0) != part ) {
    for ( int32_t i=0; i<num_part; i++ ) {
      if ( static_cast<Partition*>(0) != part[i] ) {
        delete part[i];
      }
      part[i] = static_cast<Partition*>(0);
    }
    delete part;
  }
  part     = static_cast<Partition**>(0);
  num_part = 0;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void Group::resize( const int32_t n ) {
  // -------------------------------------------------------------------------------------
  if ( num_part != n ) {
    destroy();
    num_part = n;
    part     = new Partition*[num_part];
    for ( int32_t i=0; i<num_part; i++ ) {
      part[i] = static_cast<Partition*>(0);
    }
  }
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
Group::Group( void ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
Group::Group( const int32_t np ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  set( np );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
Group::Group( const int32_t np, Partition** psrc ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  set( np, psrc );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
Group::Group( VarReal& V ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  set( V );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
Group::~Group( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
int32_t Group::nIn( void ) const {
  // -------------------------------------------------------------------------------------
  return num_part;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
int32_t Group::nOut( void ) const {
  // -------------------------------------------------------------------------------------
  int32_t sum = 0;
  for ( int32_t i=0; i<num_part; i++ ) {
    sum += part[i]->nOut();
  }
  return sum;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
int32_t Group::size( void ) const {
  // -------------------------------------------------------------------------------------
  int32_t sum = 0;
  for ( int32_t i=0; i<num_part; i++ ) {
    sum += part[i]->size();
  }
  return sum;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t* Group::create_buffer( void ) {
  // -------------------------------------------------------------------------------------
  const int32_t n = size();
  return new real8_t[ n ];
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
Partition& Group::get( const int32_t i ) {
  // -------------------------------------------------------------------------------------
  return *(part[i]);
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void Group::set( const int32_t i, Partition& p ) {
  // -------------------------------------------------------------------------------------
  if ( i < num_part ) {
    if ( 0 > i ) {
      throw( std::invalid_argument( "fuzzy::Group::set - index must be 0 or greater" ) );
    } else {
      if ( static_cast<Partition*>(0) == part[i] ) {
        part[i] = p.clone();
      } else {
        part[i]->copy( p );
      }
    }
  } else {
    throw( std::invalid_argument( "fuzzy::Group::set - index must be less than num_set" ) );
  }
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void Group::set( const int32_t np ) {
  // -------------------------------------------------------------------------------------
  resize( np );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void Group::set( const int32_t np, Partition** psrc ) {
  // -------------------------------------------------------------------------------------
  resize( np );
  for ( int32_t i=0; i<np; i++ ) {
    set( i, *(psrc[i]) );
  }
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void Group::set( VarReal& V ) {
  // -------------------------------------------------------------------------------------
  const int32_t np = V.nRow();
  resize( np );
  for ( int32_t i=0; i<np; i++ ) {
    const int32_t ns = V.nCol(i);
    Partition P( ns, V(i) );
    set( i, P );
  }
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void Group::fuzzify( real8_t* mu, real8_t* x  ) {
  // -------------------------------------------------------------------------------------
    int idx = 0;
    for ( int i=0; i<num_part; i++ ) {
      partitions[i].mu( mu, idx, x[i] );
      idx += partitions[i].size();
    }
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void Group::defuzzify( real8_t* x,  real8_t* mu ) {
  // -------------------------------------------------------------------------------------
    int idx = 0;
    for ( int i=0; i<num_part; i++ ) {
      x[i] = partitions[i].coa( mu, idx );
      idx += partitions[i].size();
    }
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t* Group::load( real8_t* src ) {
  // -------------------------------------------------------------------------------------
  real8_t* ptr = src;
  for ( int32_t i=0; i<num_part; i++ ) {
    ptr = part[i]->load( ptr );
  }
  return ptr;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t* Group::store( real8_t* dst ) {
  // -------------------------------------------------------------------------------------
  real8_t* ptr = dst;
  for ( int32_t i=0; i<num_part; i++ ) {
    ptr = part[i]->store( ptr );
  }
  return ptr;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
bool Group::write( std::ofstream& ofs, std::string fmt ) {
  // -------------------------------------------------------------------------------------
  ofs << num_part << "\n";
  for ( int32_t i=0; i<num_part; i++ ) {
    if ( part[i]->write( ofs, fmt ) ) { return true; }
  }
  return false;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
bool Group::read( std::ifstream& ifs ) {
  // -------------------------------------------------------------------------------------
  int32_t np;
  ifs >> np;
  resize( np );
  for ( int32_t i=0; i<num_part; i++ ) {
    Partition P;
    if ( P.read( ifs) ) { return true; }
    set( i, P );
  }
  return false;
}


}; // end namespace fuzzy


// =======================================================================================
// **                              F U Z Z Y : : G R O U P                              **
// ======================================================================== END FILE =====
