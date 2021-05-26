// ====================================================================== BEGIN FILE =====
// **                                 G K B _ H O R I Z                                 **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2020, Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
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
/** @brief GKB Horizon Data
 *  @file   gkb_horiz.hh
 *  @author Stephen W. Soliday
 *  @date   2020-Oct-21
 *
 *  
 */
// =======================================================================================

#include <gkb_horiz.hh>


TLOGGER_REFERENCE( GKBH, logger );

#define INIT_VAR1(a) angle(a), width(a), distance(a), elevation(a)
#define INIT_VAR2(a) n_wedges(a), wedges(a), zone(a), xutm(a), yutm(a), alt(a), lon(a), lat(a)
#define INIT_VAR3(a) n_grid_points(a), n_grid_wedges(a), grid_points(a)

// =======================================================================================
// ---------------------------------------------------------------------------------------
GKBH::Wedge::Wedge( void ) : INIT_VAR1(0) {
  // -------------------------------------------------------------------------------------
}

  
// =======================================================================================
// ---------------------------------------------------------------------------------------
GKBH::Wedge::~Wedge( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}

  
// =======================================================================================
// ---------------------------------------------------------------------------------------
void GKBH::Wedge::destroy( void ) {
  // -------------------------------------------------------------------------------------
  angle     = 0.0;
  width     = 0.0;
  distance  = 0.0;
  elevation = 0.0;    
}

  
// =======================================================================================
// ---------------------------------------------------------------------------------------
GKBH::Point::Point( size_t nw, std::ifstream& inf, bool ASCII ) : INIT_VAR2(0) {
  // -------------------------------------------------------------------------------------
  if ( ASCII ) {
    readASCII( nw, inf );
  } else {
    read( nw, inf );
  }   
}

  
// =======================================================================================
// ---------------------------------------------------------------------------------------
void GKBH::Point::read( size_t nw, std::ifstream& inf ) {
  // -------------------------------------------------------------------------------------
  real8_t x, y, z, angle, distance, elevation, ln, lt;
  int16_t zn, flag;

  n_wedges = nw;
  wedges   = new GKBH::Wedge[ nw ];

  inf.read( (char*)(&zn), 2 );
  inf.read( (char*)(&x),  8 );
  inf.read( (char*)(&y),  8 );
  inf.read( (char*)(&z),  8 );
  inf.read( (char*)(&ln), 8 );
  inf.read( (char*)(&lt), 8 );

  zone = zn;
  xutm = x;
  yutm = y;
  alt  = z;
  lon  = ln;
  lat  = lt;

  for ( int32_t j=0; j<nw; j++ ) {
    inf.read( (char*)(&angle),     8);
    inf.read( (char*)(&distance),  8);
    inf.read( (char*)(&elevation), 8);
    inf.read( (char*)(&flag),      2);

    wedges[j].angle     = angle;
    wedges[j].distance  = distance;
    wedges[j].elevation = elevation;
    wedges[j].flag      = flag;
  }
}

  
// =======================================================================================
// ---------------------------------------------------------------------------------------
void GKBH::Point::readASCII( size_t nw, std::ifstream& inf ) {
  // -------------------------------------------------------------------------------------
  real8_t x, y, z, lt, ln, angle, distance, elevation;
  int16_t zn, flag;

  n_wedges = nw;
  wedges   = new GKBH::Wedge[ nw ];

  inf >> zn >> x >> y >> z >> lt >> ln;

  zone = zn;
  xutm = x;
  yutm = y;
  alt  = z;
  lon  = ln;
  lat  = lt;

  for ( int32_t j=0; j<nw; j++ ) {
    inf >> angle >> distance >> elevation >> flag;

    wedges[j].angle     = angle;
    wedges[j].distance  = distance;
    wedges[j].elevation = elevation;
    wedges[j].flag      = flag;
  }
}

  
// =======================================================================================
// ---------------------------------------------------------------------------------------
void GKBH::Point::write( std::ofstream& outf ) {
  // -------------------------------------------------------------------------------------
  int16_t zn = zone;
  real8_t x  = xutm;
  real8_t y  = yutm;
  real8_t z  = alt;
  real8_t ln = lon;
  real8_t lt = lat;

  outf.write( (char*)(&zn), 2 );
  outf.write( (char*)(&x),  8 );
  outf.write( (char*)(&y),  8 );
  outf.write( (char*)(&z),  8 );
  outf.write( (char*)(&ln), 8 );
  outf.write( (char*)(&lt), 8 );
    
  for ( int32_t j=0; j<n_wedges; j++ ) {
    real8_t angle     = wedges[j].angle;
    real8_t distance  = wedges[j].distance;
    real8_t elevation = wedges[j].elevation;
    int16_t flag      = wedges[j].flag;

    outf.write( (char*)(&angle),     8);
    outf.write( (char*)(&distance),  8);
    outf.write( (char*)(&elevation), 8);
    outf.write( (char*)(&flag),      2);
  }
}

  
// =======================================================================================
// ---------------------------------------------------------------------------------------
void GKBH::Point::writeASCII( std::ofstream& outf ) {
  // -------------------------------------------------------------------------------------
  char buffer[128];

  sprintf( buffer, "%d %.3f %.3f %.3f %.6f %.6f\n", zone, xutm, yutm, alt, lat, lon );
  outf << buffer;

  for ( int32_t j=0; j<n_wedges; j++ ) {

    sprintf( buffer, "%.4f %.3f %.3f %d\n", 
             wedges[j].angle,
             wedges[j].distance,
             wedges[j].elevation,
             wedges[j].flag );

             outf << buffer;
  }
}

  
// =======================================================================================
// ---------------------------------------------------------------------------------------
GKBH::Point::~Point( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}

  
// =======================================================================================
// ---------------------------------------------------------------------------------------
void GKBH::Point::destroy( void ) {
  // -------------------------------------------------------------------------------------
  delete[] wedges;
  wedges   = static_cast<Wedge*>(0);
  n_wedges = 0;
}

  
// =======================================================================================
// ---------------------------------------------------------------------------------------
GKBH::GKBH( std::string fspc, bool ASCII ) : INIT_VAR3(0) {
  // -------------------------------------------------------------------------------------
  if ( ASCII ) {
    readASCII( fspc );
  } else {
   read( fspc );
  } 
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void GKBH::read( std::string fspc ) {
  // -------------------------------------------------------------------------------------
  std::ifstream  inf( fspc, std::ios::in | std::ios::binary );

  int32_t ng, na;

  inf.read( (char*)(&ng), 4 );
  inf.read( (char*)(&na), 4 );

  n_grid_points = ng;
  n_grid_wedges = na;

  grid_points = new GKBH::Point*[n_grid_points];

  for ( int32_t i=0; i<ng; i++ ) {
    grid_points[i] = new GKBH::Point( na, inf );
  }

  inf.close();
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void GKBH::readASCII( std::string fspc ) {
  // -------------------------------------------------------------------------------------
  std::ifstream inf( fspc );

  int32_t ng, na;

  inf >> ng >> na;

  n_grid_points = ng;
  n_grid_wedges = na;

  grid_points = new GKBH::Point*[n_grid_points];

  for ( int32_t i=0; i<ng; i++ ) {
    grid_points[i] = new GKBH::Point( na, inf, true );
  }

  inf.close();
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void GKBH::write( std::string fspc ) {
  // -------------------------------------------------------------------------------------
  int32_t ng = static_cast<int32_t>( n_grid_points );
  int32_t na = static_cast<int32_t>( n_grid_wedges );

  std::ofstream  outf( fspc, std::ios::out | std::ios::binary );  

  if ( outf ) {
    outf.write( (char*)(&ng), 4 );
    outf.write( (char*)(&na), 4 );
    
    for ( int32_t i=0; i<ng; i++ ) {
      grid_points[i]->write( outf );
    }
    
    outf.close();
  } else {
    std::cout << "Failed to open " << fspc << " for writing\n";
  }
}

  
// =======================================================================================
// ---------------------------------------------------------------------------------------
void GKBH::writeASCII( std::string fspc ) {
  // -------------------------------------------------------------------------------------
  char buffer[64];
  int32_t ng = static_cast<int32_t>( n_grid_points );
  int32_t na = static_cast<int32_t>( n_grid_wedges );

  std::ofstream  outf( fspc );  

  if ( outf ) {
    sprintf( buffer, "%d %d\n", ng, na );
    outf << buffer;
    
    for ( int32_t i=0; i<ng; i++ ) {
      grid_points[i]->writeASCII( outf );
    }
    
    outf.close();
  } else {
    std::cout << "Failed to open " << fspc << " for writing\n";
  }
}

  
// =======================================================================================
// ---------------------------------------------------------------------------------------
GKBH::~GKBH( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void GKBH::destroy( void ) {
  // -------------------------------------------------------------------------------------
  for ( size_t i=0; i<n_grid_points; i++ ) {
    if ( static_cast<GKBH::Point*>(0) != grid_points[i] ) {
      delete grid_points[i];
    }
    grid_points[i] = static_cast<GKBH::Point*>(0);
  }
  delete grid_points;
  grid_points   = static_cast<GKBH::Point**>(0);
  n_grid_points = 0;
  n_grid_wedges = 0;
}


// =======================================================================================
// **                                 G K B _ H O R I Z                                 **
// ======================================================================== END FILE =====
