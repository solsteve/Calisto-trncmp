// ====================================================================== BEGIN FILE =====
// **                          R E A D _ P O I N T _ C L O U D                          **
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
/** @brief Read PointNet point cloud data
 *  @file   read_point_cloud.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Oct-21
 *
 *  This is a stub for conversion.
 */
// =======================================================================================


#include <point_cloud.hh>

// =======================================================================================
/** @brief Entry point.
 *  @return 0 on success non-zero on failure
 *
 *  Main entry point for the conversion stub.
 */
// ---------------------------------------------------------------------------------------
int main( void ) {
  // -------------------------------------------------------------------------------------
  PointCloud cloud( "/data/ARA/PointNet/PointCloud-ForumOfficeComplex.bin" );
  char    buffer[128];

  std::ofstream outf( "/tmp/utm-fast.csv" );

  std::cout << "Reading " << cloud.N() << " records.\n";
  outf << cloud.N() << std::endl;

  for ( int32_t i=0; i<cloud.N(); i++ ) {
    sprintf( buffer, "%10.3f %11.3f %7.3f %3d %3d %3d",
             cloud.point(i).x,
             cloud.point(i).y,
             cloud.point(i).z,
             cloud.point(i).r,
             cloud.point(i).g,
             cloud.point(i).b );
    outf << buffer << std::endl;
  }
  
  outf.close();

  return 0;
}


// =======================================================================================
/** @brief Entry point.
 *  @return 0 on success non-zero on failure
 *
 *  Main entry point for the conversion stub.
 */
// ---------------------------------------------------------------------------------------
int TEST04( void ) {
  // -------------------------------------------------------------------------------------

  std::ifstream  inf( "/data/ARA/PointNet/PointCloud-ForumOfficeComplex.bin", std::ios::out | std::ios::binary );

  std::ofstream outf( "/tmp/utm-slow.csv" );

  int32_t nrec;
  real8_t xutm, yutm, elev;
  int16_t red, green, blue;
  char    buffer[128];

  inf.read( (char*)(&nrec), 4 );

  outf << nrec << std::endl;

  for ( int32_t i=0; i<nrec; i++ ) {
    inf.read( (char*)(&xutm),  8 );
    inf.read( (char*)(&yutm),  8 );
    inf.read( (char*)(&elev),  8 );
    inf.read( (char*)(&red),   2 );
    inf.read( (char*)(&green), 2 );
    inf.read( (char*)(&blue),  2 );


    sprintf( buffer, "%10.3f %11.3f %7.3f %3d %3d %3d", xutm, yutm, elev, red, green, blue );
    outf << buffer << std::endl;
  }

  inf.close();
  outf.close();
  
  return 0;
}


// =======================================================================================
// **                                      M A I N                                      **
// ======================================================================== END FILE =====
