// ====================================================================== BEGIN FILE =====
// **                               P O I N T _ C L O U D                               **
// =======================================================================================
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
/** @brief  Open3D Point Cloud data (output from PointNet)
 *  @file   point_cloud.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Oct-22
 *
 *  
 */
// =======================================================================================


#include <point_cloud.hh>
#include <Dice.hh>

#define INIT_VAR1(a) x(0.0e0), y(0.0e0), z(0.0e0), r(a), g(a), b(a)
#define INIT_VAR2(a) num_points(a), points(0)

TLOGGER_REFERENCE( PointCloud, logger );


// =======================================================================================
PointCloud::Point::Point( void ) : INIT_VAR1(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
PointCloud::Point::~Point( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}


// =======================================================================================
void PointCloud::Point::destroy( void ) {
  // -------------------------------------------------------------------------------------
  x = 0.0e0;
  y = 0.0e0;
  z = 0.0e0;
  r = 0;
  g = 0;
  b = 0;
}


// =======================================================================================
void PointCloud::destroy( void ) {
  // -------------------------------------------------------------------------------------
  delete[] points;
  points     = static_cast<PointCloud::Point*>(0);
  num_points = 0;
}


// =======================================================================================
PointCloud::~PointCloud( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}


// =======================================================================================
PointCloud::PointCloud( std::string fspc ) : INIT_VAR2(0) {
  // -------------------------------------------------------------------------------------

  std::ifstream inf( fspc, std::ios::out | std::ios::binary );

  int32_t nrec;
  real8_t xutm, yutm, elev;
  int16_t red, green, blue;

  inf.read( (char*)(&nrec), 4 );

  num_points = nrec;
  points     = new PointCloud::Point[ nrec ];

  std::cout << "Reading " << nrec << " records.\n";

  for ( int32_t i=0; i<nrec; i++ ) {
    inf.read( (char*)(&xutm),  8 );
    inf.read( (char*)(&yutm),  8 );
    inf.read( (char*)(&elev),  8 );
    inf.read( (char*)(&red),   2 );
    inf.read( (char*)(&green), 2 );
    inf.read( (char*)(&blue),  2 );

    points[i].x = xutm;
    points[i].y = yutm;
    points[i].z = elev;
    points[i].r = red;
    points[i].g = green;
    points[i].b = blue;
  }

  inf.close();
}


// =======================================================================================
PointCloud::PointCloud( std::string fspc, real8_t ratio ) : INIT_VAR2(0) {
  // -------------------------------------------------------------------------------------
  Dice* dd = Dice::getInstance();

  std::ifstream inf( fspc, std::ios::out | std::ios::binary );

  int32_t max_count, count;
  real8_t xutm, yutm, elev;
  int16_t red, green, blue;

  inf.read( (char*)(&max_count), 4 );

  int32_t desired_count = (int32_t) floor( 0.5 + ratio * (real8_t)max_count );

  points = new PointCloud::Point[ desired_count ];

  std::cout << "Reading      " << max_count << " records.\n";
  std::cout << "   Selecting " << desired_count << " sub set.\n";

  int32_t index = 0;
  for ( int32_t i=0; i<max_count; i++ ) {
    inf.read( (char*)(&xutm),  8 );
    inf.read( (char*)(&yutm),  8 );
    inf.read( (char*)(&elev),  8 );
    inf.read( (char*)(&red),   2 );
    inf.read( (char*)(&green), 2 );
    inf.read( (char*)(&blue),  2 );

    if ( dd->boolean( ratio ) ) {
      points[index].x = xutm;
      points[index].y = yutm;
      points[index].z = elev;
      points[index].r = red;
      points[index].g = green;
      points[index].b = blue;
      index += 1;
    }

    if ( index >= desired_count ) { break; }
  }

  inf.close();

  num_points = index;
  std::cout << "   Created   " << num_points << " records.\n";  
}


// =======================================================================================
// **                               P O I N T _ C L O U D                               **
// ======================================================================== END FILE =====
