// ====================================================================== BEGIN FILE =====
// **                                C O M P A R E G K B                                **
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
/** @brief  Compare GKB files
 *  @file   CompareGKB.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Nov-03
 */
// =======================================================================================


#include <AppOptions.hh>
#include <gkb_horiz.hh>

TLOGGER_INSTANCE( logger );


// =======================================================================================
void confuse( std::ostream& os, size_t TP, size_t TN, size_t FP, size_t FN ) {
  // -------------------------------------------------------------------------------------

    os << "TP " << TP << std::endl;
    os << "TN " << TN << std::endl;
    os << "FP " << FP << std::endl;
    os << "FN " << FN << std::endl;

    real8_t acc = ((real8_t)(TP+TN)) / ((real8_t)(TP+TN+FP+FN));

    os << "Acc = " << acc << std::endl;
}


// =======================================================================================
int process( ConfigDB::Section* cfg ) {
  // -------------------------------------------------------------------------------------
  std::string gtFilename = cfg->get( "ground" );
  std::string ptFilename = cfg->get( "point" );
  std::string outFilename = cfg->get( "output" );

  std::cout << "Original GKB file = " << gtFilename << std::endl;
  GKBH* gkb_gk = new GKBH( gtFilename );
  std::cout << "   " << gkb_gk->NG() << " grid points were read\n";

  std::cout << "PointNet GKB file = " << ptFilename << std::endl;
  GKBH* gkb_pn = new GKBH( ptFilename );
  std::cout << "   " << gkb_pn->NG() << " grid points were read\n";

  size_t num_grid  = gkb_gk->NG();
  size_t num_wedge = gkb_gk->NW();

  if ( num_grid != gkb_pn->NG() ) {
    logger->error( "Files are incompatable: grid points %d != %d", num_grid, gkb_pn->NG() );
    return 1;
  }

  if ( num_wedge != gkb_pn->NW() ) {
    logger->error( "Files are incompatable: wedge count %d != %d", num_wedge, gkb_pn->NW() );
    return 2;
  }

  // -------------------------------------------------------------------------------------

  std::ofstream outf( outFilename );

  size_t TP = 0;
  size_t TN = 0;
  size_t FP = 0;
  size_t FN = 0;

  outf << "\"POINT\",\"WEDGE\",\"GT\",\"PN\",\"DIST\",\"ELV\"" << std::endl;
  
  for ( size_t g=0; g< num_grid; g++ ) {
    GKBH::Point* gk_point = gkb_gk->point(g);
    GKBH::Point* pn_point = gkb_pn->point(g);

    real8_t gx1 = gk_point->xutm;
    real8_t gy1 = gk_point->yutm;

    real8_t gx2 = pn_point->xutm;
    real8_t gy2 = pn_point->yutm;

    for ( size_t j=0; j<num_wedge; j++ ) {
      real8_t dd = gk_point->wedge(j).distance  - pn_point->wedge(j).distance;
      real8_t de = gk_point->wedge(j).elevation - pn_point->wedge(j).elevation;
      

      if ( 1 == gk_point->wedge(j).flag ) {
        if ( 1 == pn_point->wedge(j).flag ) {
          TP++;
        }
        if ( 0 == pn_point->wedge(j).flag ) {
          FN++;
        }
      }

      if ( 0 == gk_point->wedge(j).flag ) {
        if ( 1 == pn_point->wedge(j).flag ) {
          FP++;
        }
        if ( 0 == pn_point->wedge(j).flag ) {
          TN++;
        }
      }

      outf << g << "," << j << ", ";
      outf << gk_point->wedge(j).flag << ",";
      outf << pn_point->wedge(j).flag << ", ";
      outf << c_fmt( "%g", dd ) << ",";
      outf << c_fmt( "%g", de ) << "\n";
      
    }
    
  }

  confuse( std::cout, TP, TN, FP, FN );

  outf.close();

  
  // -------------------------------------------------------------------------------------

  delete gkb_gk;
  delete gkb_pn;
  
  return 0;
}

// =======================================================================================
/** @brief Entry point.
 *  @return 0 on success non-zero on failure
 *
 *  Main entry point for the version test.
 */
// ---------------------------------------------------------------------------------------
int main( int argc, char *argv[], char **env ) {
  // -------------------------------------------------------------------------------------
  //       /data/ARA/PointNet/PointCloud-ForumOfficeComplex.bin
  // ----- set the command line options -----------------------------------------------------
  AppOptions::cli_map_s CLI[] = {
    { "gt", "APP", "ground", true, 0, "input ground truth GKB file" },
    { "pt", "APP", "point",  true, 0, "input pointnet horizon file" },
    { "of", "APP", "output", true, 0, "output metrics file" },
    { 0, 0, 0, false, 0, 0 } 
  };
  
  AppOptions::init( CLI );
  AppOptions::setCommandLine( argc, argv, env );
  
  AppOptions::setTitleLine( "Compare Binary GKB" );
  AppOptions::setConfigBase( "ctest" );
  AppOptions::setConfigPath( "~:.." );
  AppOptions::setEnvSectionName("NewEnv");
  AppOptions::setOptSectionName( "NewOpts" );
  AppOptions::setEnvConfigFilename( "ECFG" );
  AppOptions::setOptConfigFilename( "cfg" );
  AppOptions::setHelp( "help" );

  AppOptions::setExampleLine( "gt=/data/ARA/PointNet/ForumComplex-GKB.bin pt=/data/ARA/PointNet/point-horizon.bin" );

  AppOptions::addUsageText( "Calculate metrics comparing GKB to Point Clouds" );

  ConfigDB* cfg = AppOptions::getConfigDB();

  int rv = -1;
  if ( (ConfigDB*)0 != cfg ) {
    rv = process( cfg->get( "APP" ) );
    delete cfg;
  } else {
    std::cerr << "AppOpts Test FAILED\n\n";
  }

  return rv;
}


// =======================================================================================
// **                                C O M P A R E G K B                                **
// ======================================================================== END FILE =====
