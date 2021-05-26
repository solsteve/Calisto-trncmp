// ====================================================================== BEGIN FILE =====
// **                                P C 2 H O R I Z O N                                **
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
/** @brief  Point Cloud to Horizon (isBuilding flags)
 *  @file   PC2Horizon.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Oct-22
 */
// =======================================================================================


#include <AppOptions.hh>
#include <point_cloud.hh>
#include <gkb_horiz.hh>
#include <StringTool.hh>
#include <StopWatch.hh>
#include <omp.h>


// =======================================================================================
class Labels {
  // -------------------------------------------------------------------------------------
 protected:
  size_t   num;
  int16_t* r;
  int16_t* g;
  int16_t* b;
  int16_t* cls;

 public:
  Labels( std::string fspc );
  ~Labels( void );

  int16_t find( int16_t tr, int16_t tg, int16_t tb );
};

// =======================================================================================
class WedgeParts {
  // -------------------------------------------------------------------------------------
 public:
  real8_t A1;
  real8_t A2;
  real8_t S1;
  real8_t C1;
  real8_t S2;
  real8_t C2;
  
  WedgeParts( void ) : A1(0.0), A2(0.0), S1(0.0), C1(0.0), S2(0.0), C2(0.0) {};
  ~WedgeParts( void ) {};
  void set( real8_t ctr, real8_t wdt );
};

// =======================================================================================
void WedgeParts::set( real8_t ctr, real8_t wdt ){
  // -------------------------------------------------------------------------------------
  real8_t hw = 5.0e-1 * wdt;
  A1 = ctr - hw;
  A2 = ctr + hw;
  S1 = sin( A1 );
  C1 = cos( A1 );
  S2 = sin( A2 );
  C2 = cos( A2 );
}


// =======================================================================================
Labels::Labels( std::string fspc ) : num(0), r(0), g(0), b(0), cls(0) {
  // -------------------------------------------------------------------------------------
  std::ifstream fp( fspc );

  fp >> num;

  r   = new int16_t[num];
  g   = new int16_t[num];
  b   = new int16_t[num];
  cls = new int16_t[num];

  for ( size_t i=0; i<num; i++ ) {
    fp >> r[i];
    fp >> g[i];
    fp >> b[i];
    fp >> cls[i];
  }

  fp.close();
}

// =======================================================================================
Labels::~Labels( void ) {
  // -------------------------------------------------------------------------------------
  delete r;
  delete g;
  delete b;
  delete cls;
  num = 0;
}

// =======================================================================================
int16_t Labels::find( int16_t tr, int16_t tg, int16_t tb ) {
  // -------------------------------------------------------------------------------------
  for ( size_t i=0; i<num; i++ ) {
    if ( tr == r[i] ) {
      if ( tg == g[i] ) {
        if ( tb == b[i] ) {
          return cls[i];
        }
      }
    }
  }
  return -1;
}


// =======================================================================================
size_t isInWedge( real8_t     dst_elv[2],
                  bool*       used,
                  PointCloud* cloud,
                  real8_t     grid_x, real8_t grid_y, real8_t grid_z,
                  real8_t     S1,     real8_t C1,
                  real8_t     S2,     real8_t C2,
                  real8_t     min_range ) {
  // -------------------------------------------------------------------------------------

  size_t num_points = cloud->N();

  dst_elv[0] = -D_ONE;
  dst_elv[1] = -D_ONE;
  real8_t mr2 = min_range * min_range;

  size_t  mx_index = num_points;
  real8_t mx_angle = D_ZERO;
  
  for ( size_t j=0; j<num_points; j++ ) {
    if ( ! used[j] ) {
      real8_t dx = cloud->point(j).x - grid_x;
      real8_t dy = cloud->point(j).y - grid_y;

      real8_t cross_1 = (dy * C1) - (dx * S1);
      real8_t cross_2 = (dx * S2) - (dy * C2);
                                     
      bool inWedge = true;
      if ( cross_1 < D_ZERO ) { inWedge = false; }
      if ( cross_2 < D_ZERO ) { inWedge = false; }

      if ( inWedge ) {
        used[j] = true;
        real8_t dz = cloud->point(j).z - grid_z;
        real8_t r2 = (dx*dx) + (dy*dy);
        if ( r2 > mr2 ) {
          real8_t angle = dx*dx / r2;
          if ( angle > mx_angle ) {
            mx_angle = angle;
            mx_index = j;
            dst_elv[0] = r2;
            dst_elv[1] = dz;
          }
        }
      }
    }
  }

  if ( dst_elv[0] > D_ZERO ) { dst_elv[0] = sqrt( dst_elv[0] ); }

  return mx_index;
}

  

// =======================================================================================
size_t* buildAltitudeTable( GKBH& gkb, PointCloud& cloud ) {
  // -------------------------------------------------------------------------------------
  std::cout << "buildAltitudeTable * Slow Reference Version\n";
  StopWatch SW;
  
  size_t num_grid   = gkb.NG();
  size_t num_points = cloud.N();

  size_t* table = new size_t[ num_grid ];
  
  SW.reset();
  // -------------------------------------------------------------------------------------

  for ( size_t i=0; i<num_grid; i++ ) {
    GKBH::Point* point = gkb.point(i);
    real8_t grid_x = point->xutm;
    real8_t grid_y = point->yutm;
    real8_t grid_z = point->alt;

    real8_t dx = cloud.point(0).x - grid_x;
    real8_t dy = cloud.point(0).y - grid_y;
    real8_t dz = cloud.point(0).z - grid_z;
    real8_t d2 = (dx*dx) + (dy*dy) + (dz*dz);
    
    size_t  min_index = 0;
    real8_t min_dist2 = d2;
    for ( size_t j=1; j<num_points; j++ ) {
      dx = cloud.point(j).x - grid_x;
      dy = cloud.point(j).y - grid_y;
      dz = cloud.point(j).z - grid_z;
      d2 = (dx*dx) + (dy*dy) + (dz*dz);
      if ( d2 < min_dist2 ) {
        min_dist2 = d2;
        min_index = j;
      }
    }
    table[i] = min_index;
  }
    
  // -------------------------------------------------------------------------------------
  real8_t elapsed_time = SW.check();
  std::cout << "    " << elapsed_time << " seconds\n";
  return table;
}


// =======================================================================================
void ComputeWedges( size_t gp_index, GKBH& gkb, PointCloud& cloud,
                    size_t* reg_index, int16_t* isBuilding,
                    WedgeParts* wedge, size_t num_wedge ) {
  // -------------------------------------------------------------------------------------
  size_t       num_points = cloud.N();
  GKBH::Point* point      = gkb.point( gp_index );
  real8_t      grid_x     = point->xutm;
  real8_t      grid_y     = point->yutm;
  real8_t      grid_z     = cloud.point(reg_index[ gp_index ]).z;

  bool* used = new bool[ num_points ];
  for ( size_t k=0; k<num_points; k++ ) {
    used[k] = false;
  }
    
  for ( size_t j=0; j<num_wedge; j++ ) {

    real8_t dst_elv[2];
    
    size_t horizon = isInWedge( dst_elv, used, &cloud,
                                grid_x, grid_y, grid_z,
                                wedge[j].S1, wedge[j].C1, wedge[j].S2, wedge[j].C2,
                                1.0 );

    point->wedge(j).distance  = dst_elv[0];
    point->wedge(j).elevation = dst_elv[1];
    point->wedge(j).flag      = isBuilding[ horizon ];   
  }

  delete used;
}



// =======================================================================================
int process( ConfigDB::Section* cfg ) {
  // -------------------------------------------------------------------------------------
  std::string gFilename = cfg->get( "gkb" );
  std::string pFilename = cfg->get( "pcloud" );
  std::string oFilename = cfg->get( "output" );
  std::string lFilename = cfg->get( "label" );
  real8_t     ratio     = StringTool::asReal8( cfg->get( "ratio" ) ) / 100.0;

  PointCloud cloud( pFilename, ratio );
  std::cout << "Point Cloud file = " << pFilename << std::endl;

  GKBH       gkb( gFilename );
  std::cout << "GKB file         = " << gFilename << std::endl;

  std::cout << "Output file      = " << oFilename << std::endl;

  Labels     labels( lFilename );
  std::cout << "Label file       = " << lFilename << std::endl;

  size_t  num_wedge = gkb.NW();
  real8_t da = D_2PI / static_cast<real8_t>(num_wedge);

  WedgeParts wedge[ num_wedge ];

  real8_t angle = D_ZERO;
  for ( size_t i=0; i<num_wedge; i++ ) {
    real8_t rad = D_PI_2 - angle;
    if ( rad < D_ZERO ) rad = D_2PI + rad;
    wedge[i].set( rad, da );    
    angle += da;
  }
  
  // -------------------------------------------------------------------------------------

  size_t* reg_index = buildAltitudeTable( gkb, cloud );
  
  // -------------------------------------------------------------------------------------

  size_t num_grid   = gkb.NG();
  size_t num_points = cloud.N();

  int16_t* isBuilding = new int16_t[ num_points ];
  
  for ( size_t i=0; i<num_points; i++ ) {
    isBuilding[i] = labels.find( cloud.point(i).r,
                                 cloud.point(i).g,
                                 cloud.point(i).b );
  }
  
  size_t gp;
  // ====================================
#pragma omp parallel for private(gp) shared(gkb, cloud, reg_index, isBuilding, wedge, num_wedge)
  for ( gp=0; gp<num_grid; gp++ ) {
    ComputeWedges( gp, gkb, cloud, reg_index, isBuilding, wedge, num_wedge );
  }
  // ====================================

  delete isBuilding;

  gkb.write( oFilename );
  
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
    { "gkb",   "APP", "gkb",    true,   0,    "input GKB wedge   file name" },
    { "pc",    "APP", "pcloud", true,   0,    "input point cloud file name" },
    { "lab",   "APP", "label",  true,   0,    "input label file" },
    { "of",    "APP", "output", true,   0,    "output GKB file" },
    { "ratio", "APP", "ratio",  false, "100.0", "percent of point cloud points to use" },
    { 0, 0, 0, false, 0, 0 } 
  };
  
  AppOptions::init( CLI );
  AppOptions::setCommandLine( argc, argv, env );
  
  AppOptions::setTitleLine( "PointNet to Horizon" );
  AppOptions::setConfigBase( "ctest" );
  AppOptions::setConfigPath( "~:.." );
  AppOptions::setEnvSectionName("NewEnv");
  AppOptions::setOptSectionName( "NewOpts" );
  AppOptions::setEnvConfigFilename( "ECFG" );
  AppOptions::setOptConfigFilename( "cfg" );
  AppOptions::setHelp( "help" );

  AppOptions::setExampleLine( "pc=/data/ARA/PointNet/PointCloud-ForumOfficeComplex.bin gkb=/data/ARA/PointNet/ForumComplex-GKB.bin lab=/data/ARA/PointNet/labels-groundtruth.txt of=test.out" );

  AppOptions::addUsageText( "Build a GKB file from PointNet data" );
  AppOptions::addUsageText( "ratio: randomly sub samples point cloud data" );
  AppOptions::addUsageText( "  by default(100) all points are compared" );
  AppOptions::addUsageText( "  ratio=10 only 1 in 10 (random) cloud points will be compared" );
  AppOptions::addUsageText( "  each wedge for each GKB grid point randomly selects a" );
  AppOptions::addUsageText( "  different subsample." );

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
// **                              C T E S T _ A P P O P T                              **
// ======================================================================== END FILE =====
