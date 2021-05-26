// ====================================================================== BEGIN FILE =====
// **                                  R E A D _ G K B                                  **
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
/** @brief Read Binary GKB data
 *  @file   read_gkb.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Oct-21
 *
 *  This is a stub for conversion.
 */
// =======================================================================================


#include <gkb_horiz.hh>


// =======================================================================================
/** @brief Entry point.
 *  @return 0 on success non-zero on failure
 *
 *  Main entry point for the conversion stub.
 */
// ---------------------------------------------------------------------------------------
int main( void ) {
  // -------------------------------------------------------------------------------------
  char buffer[128];

  GKBH* gkb = new GKBH( "/data/ARA/PointNet/ForumComplex-GKB.bin" );

  std::cout << "Number of grids:  " << gkb->NG() << std::endl;
  std::cout << "Number of Wedges: " << gkb->NW() << std::endl;

  std::ofstream outf( "/tmp/test_gkb_struct.dat" );

  outf << gkb->NG() << " " << gkb->NW() << std::endl;

  for ( size_t i=0; i<gkb->NG(); i++ ) {
    GKBH::Point* pnt = gkb->point(i);

    sprintf( buffer, "%d %10.3f %11.3f", pnt->zone, pnt->xutm, pnt->yutm );
    outf << buffer << std::endl;

    for ( size_t j=0; j<gkb->NW(); j++ ) {
      sprintf( buffer, "%6.2f %11.3f %11.3f %d",
               pnt->wedge(j).angle,
               pnt->wedge(j).distance,
               pnt->wedge(j).elevation,
               pnt->wedge(j).flag );
      outf << buffer << std::endl;
    }
  }

  outf.close();

  std::cout << "Write /tmp/test.gkb\n";
  gkb->write( "/tmp/test.gkb" );
  std::cout << "Done\n";

  delete gkb;
}


// =======================================================================================
/** @brief Entry point.
 *  @return 0 on success non-zero on failure
 *
 *  Main entry point for the conversion stub.
 */
// ---------------------------------------------------------------------------------------
int TEST03( void ) {
  // -------------------------------------------------------------------------------------

  std::ifstream  inf( "/data/ARA/PointNet/ForumComplex-GKB.bin", std::ios::in | std::ios::binary );

  std::ofstream outf( "/tmp/test_gkb_cpp.dat" );

  int32_t ng, na;
  real8_t xutm, yutm, angle, distance, elevation;
  int16_t zone, flag;
  char    buffer[128];

  inf.read( (char*)(&ng), 4 );
  inf.read( (char*)(&na), 4 );

  std::cout << "Reading " << ng << " grids. " << na << " wedges each\n";

  outf << ng << " " << na << std::endl;

  for ( int32_t i=0; i<ng; i++ ) {

    inf.read( (char*)(&zone), 2 );
    inf.read( (char*)(&xutm), 8 );
    inf.read( (char*)(&yutm), 8 );

    sprintf( buffer, "%d %10.3f %11.3f", zone, xutm, yutm );
    outf << buffer << std::endl;

    for ( int32_t j=0; j<na; j++ ) {

      inf.read( (char*)(&angle),     8);
      inf.read( (char*)(&distance),  8);
      inf.read( (char*)(&elevation), 8);
      inf.read( (char*)(&flag),      2);

      sprintf( buffer, "%6.2f %11.3f %11.3f %d", angle, distance, elevation, flag );
      outf << buffer << std::endl;
    }
  }

  inf.close();
  outf.close();
  
  return 0;
}


// =======================================================================================
// **                                  R E A D _ G K B                                  **
// ======================================================================== END FILE =====
