// ====================================================================== BEGIN FILE =====
// **                            D I S P L A Y C O M P A R E                            **
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
/** @brief  Compare GKB files with PointCloud
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
  std::string pntFilename = cfg->get( "pfile" );
  std::string csvFilename = cfg->get( "cfile" );
  real8_t     pratio      = StringTool::asReal8( cfg->get( "prat" ) ) / 100.0;
  real8_t     gratio      = StringTool::asReal8( cfg->get( "grat" ) ) / 100.0;
  std::string gFlag       = cfg->get( "gdat" );
  std::string pFlag       = cfg->get( "pdat" );

  std::cout << "GKB File = " << gkbFilename << std::endl;
  GKBH  gkb( gkbFilename );
  std::cout << "   " << gkb.NG() << " grid points were read\n";

  std::cout << "Point Cloud File = " << pntFilename << std::endl;
  PointCloud cloud( pntFilename, pratio );
  std::cout << "   " << cloud.N() << " points were read\n";

  size_t num_grid  = gkb.NG();
  size_t num_point = cloud.N();

  // -------------------------------------------------------------------------------------

  FILE* fp = fopen( csvFilename.c_str(),  "w" );
  FILE* gfp = fopen( "/tmp/just-gkb.csv", "w" );
  FILE* pfp = fopen( "/tmp/just-pnt.csv", "w" );
  
  fprintf( fp, "X,Y,Z,LAYER\n" );
  fprintf( gfp, "X,Y,Z,LAYER\n" );
  fprintf( pfp, "X,Y,Z,LAYER\n" );

  size_t gcount = 0;
  for ( size_t i=0; i<num_grid; i++ ) {
    GKBH::Point* point  = gkb.point( i );
    real8_t      grid_x = point->xutm;
    real8_t      grid_y = point->yutm;
    real8_t      grid_z = 0.0;

    if ( dd->boolean( gratio ) ) {
      fprintf( fp, "%.3f,%.3f,%.3f,%s\n",
               grid_x, grid_y, grid_z,
               gFlag.c_str() );
      fprintf( gfp, "%.3f,%.3f,%.3f,%s\n",
               grid_x, grid_y, grid_z,
               gFlag.c_str() );
      gcount += 1;
    }
  }

  size_t pcount = 0;
  for ( size_t j=0; j<num_point; j++ ) {
    real8_t pnt_x = cloud.point(j).x;
    real8_t pnt_y = cloud.point(j).y;
    real8_t pnt_z = 0.0;
    fprintf( fp, "%.3f,%.3f,%.3f,%s\n",
               pnt_x, pnt_y, pnt_z,
               pFlag.c_str() );
    fprintf( pfp, "%.3f,%.3f,%.3f,%s\n",
               pnt_x, pnt_y, pnt_z,
               pFlag.c_str() );
    pcount += 1;
  }

  fclose( fp );
  fclose( gfp );
  fclose( pfp );

  std::cout << csvFilename << " contains\n"
            << gcount << " gkb records and\n"
            << pcount << " point cloud records.\n\n";
 
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
    { "gkb",   "APP", "gfile", true,   0,      "input  GKB   file" },
    { "pnt",   "APP", "pfile", true,   0,      "input  Point file" },
    { "csv",   "APP", "cfile", true,   0,      "output CSV file" },
    
    { "g",     "APP", "gdat",  false, "1",     "flag for GKB points" },
    { "p",     "APP", "pdat",  false, "0",     "flag for Point Cloud points" },
    { "prat",  "APP", "prat", false, "100.0", "percent of point cloud points to use" },
    { "grat",  "APP", "grat", false, "100.0", "percent of GKB points to use" },
    { 0, 0, 0, false, 0, 0 } 
  };
  
  AppOptions::init( CLI );
  AppOptions::setCommandLine( argc, argv, env );
  
  AppOptions::setTitleLine( "Compare GKB to Point Cloud" );
  AppOptions::setConfigBase( "ctest" );
  AppOptions::setConfigPath( "~:.." );
  AppOptions::setEnvSectionName("NewEnv");
  AppOptions::setOptSectionName( "NewOpts" );
  AppOptions::setEnvConfigFilename( "ECFG" );
  AppOptions::setOptConfigFilename( "cfg" );
  AppOptions::setHelp( "help" );

  AppOptions::setExampleLine( "gkb=gkb.bin pnt=pointcloud.bin csv=overlay.csv" );

  AppOptions::addUsageText( "Create an XGobi CSV file" );
  AppOptions::addUsageText( "Display Overlay of GKB grid points and "  );
  AppOptions::addUsageText( "   WorldFile registered PointCloud data."  );

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
