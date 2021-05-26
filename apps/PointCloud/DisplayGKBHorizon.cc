// ====================================================================== BEGIN FILE =====
// **                         D I S P L A Y G K B H O R I Z O N                         **
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
#include <point_cloud.hh>
#include <gkb_horiz.hh>
#include <StringTool.hh>
#include <Dice.hh>

TLOGGER_INSTANCE( logger );


// =======================================================================================
int process( ConfigDB::Section* cfg ) {
  // -------------------------------------------------------------------------------------
  Dice* dd = Dice::getInstance();
  dd->seed_set();
  
  std::string gkbFilename = cfg->get( "gfile" );
  std::string hrzFilename = cfg->get( "hfile" );
  std::string gridFilename = cfg->get( "grid" );
  real8_t     ratio       = StringTool::asReal8( cfg->get( "ratio" ) ) / 100.0;
  real8_t     maxelv      = StringTool::asReal8( cfg->get( "maxelv" ) );
  real8_t     minelv      = StringTool::asReal8( cfg->get( "minelv" ) );
  real8_t     mindst      = StringTool::asReal8( cfg->get( "mind" ) );

  std::cout << "GKB File = " << gkbFilename << std::endl;
  GKBH* gkb = new GKBH( gkbFilename );
  std::cout << "   " << gkb->NG() << " grid points were read\n";

  size_t num_grid  = gkb->NG();
  size_t num_wedge = gkb->NW();

  // -------------------------------------------------------------------------------------
  
  real8_t da = D_2PI / static_cast<real8_t>(num_wedge);

  real8_t Cosine[ num_wedge ];
  real8_t Sine[ num_wedge ];

  real8_t angle = D_ZERO;
  for ( size_t i=0; i<num_wedge; i++ ) {
    real8_t rad = D_PI_2 - angle;
    if ( rad < D_ZERO ) rad = D_2PI + rad;
    Cosine[i] = cos( rad );
    Sine[i]   = sin( rad );
    angle += da;
  }
    
  // -------------------------------------------------------------------------------------

  FILE* fp = fopen( hrzFilename.c_str(), "w" );

  fprintf( fp, "\"X\",\"Y\",\"Z\",\"F\"\n" );

  FILE* gfp = fopen( gridFilename.c_str(), "w" );

  fprintf( gfp, "\"X\",\"Y\",\"Z\"\n" );

  size_t count = 0;

  for ( size_t i=0; i<num_grid; i++ ) {
    GKBH::Point* point  = gkb->point( i );
    
    real8_t      grid_x = point->xutm;
    real8_t      grid_y = point->yutm;
    real8_t      grid_z = point->alt;
    
    fprintf( gfp, "%.3f,%.3f,%.3f\n", grid_x, grid_y, grid_z );
    
    if ( grid_z > 0.0 ) {
    if ( grid_z < maxelv ) {
    fprintf( fp, "%.3f,%.3f,%.3f,%d\n", grid_x, grid_y, grid_z, 10 );
    count += 1;

    for ( size_t j=0; j<num_wedge; j++ ) {

      real8_t r = point->wedge( j ).distance;
      real8_t welv = point->wedge( j ).elevation;

      if ( r > mindst ) {
        
        real8_t x = grid_x + r * Cosine[j];
        real8_t y = grid_y + r * Sine[j];
        real8_t z = grid_z + welv;
      
         if ( z > minelv ) {
          if ( z < maxelv ) {

            int16_t flag = point->wedge( j ).flag;

            if ( dd->boolean( ratio ) ) {
              fprintf( fp, "%.3f,%.3f,%.3f,%d\n", x, y, z, flag );
              count += 1;
            }
          }
        }
      }
    }
  }
  }
  }

  fclose( fp );
  fclose( gfp );

  delete gkb;

  std::cout << "   " << count << " cloud points were written to " << hrzFilename << std::endl;
  
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
    { "gkb",   "APP", "gfile",  true,   0,      "input  GKB     file" },
    { "hrz",   "APP", "hfile",  true,   0,      "output horizon file" },
    { "ratio", "APP", "ratio",  false, "100.0", "percent of point cloud points to use" },
    { "maxe",   "APP", "maxelv", false, "300.0", "maximum elevation in meters" },
    { "mine",   "APP", "minelv", false, "0.0",   "minimum elevation in meters" },
    { "mind",  "APP", "mind",   false, "10.0",  "minimum distance  in meters" },
    { "grid",   "APP", "grid",   false, "grid.csv",  "output grid point only csv" },
    { 0, 0, 0, false, 0, 0 } 
  };
  
  AppOptions::init( CLI );
  AppOptions::setCommandLine( argc, argv, env );
  
  AppOptions::setTitleLine( "Display GKB Horizon" );
  AppOptions::setConfigBase( "ctest" );
  AppOptions::setConfigPath( "~:.." );
  AppOptions::setEnvSectionName("NewEnv");
  AppOptions::setOptSectionName( "NewOpts" );
  AppOptions::setEnvConfigFilename( "ECFG" );
  AppOptions::setOptConfigFilename( "cfg" );
  AppOptions::setHelp( "help" );

  AppOptions::setExampleLine( "gkb=../test.out.bin hrz=horizon.csv" );

  AppOptions::addUsageText( "Create an XGobi horizon file" );

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
// **                         D I S P L A Y G K B H O R I Z O N                         **
// ======================================================================== END FILE =====
