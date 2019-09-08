// ====================================================================== BEGIN FILE =====
// **                              M A K E _ N E T W O R K                              **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019, Stephen W. Soliday                                           **
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
/** @brief Make Network.
 *  @file   make_network.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-07
 *
 *  This application is a wizard for building networks.
 */
// =======================================================================================


#include <AppOptions.hh>
#include <StringTool.hh>
#include <string.h>
#include <BPNN.hh>


int32_t Guess( int32_t idx, int32_t mx, int32_t mn, int32_t nl ) {
  const real8_t x  = (real8_t)idx;
  const real8_t y1 = (real8_t)mx;
  const real8_t y2 = (real8_t)mn;
  const real8_t n  = (real8_t)nl;

  const real8_t y = (x*(n*y2 - y1) + y1*(n - D_ONE)) / ((x+D_ONE)*(n-D_ONE));

  return (int32_t)floor( y + 0.5 );
}

// =======================================================================================
class netc {
  // -------------------------------------------------------------------------------------
 public:
  int32_t  nIn;
  int32_t  nOut;
  int32_t  nLayers;
  int32_t* hid;
 protected:
  EMPTY_PROTOTYPE( netc );
  void destroy( void );

 public:
  netc( void ) : nIn(0), nOut(0), nLayers(0), hid(0) {};
  ~netc( void ) { destroy(); };
  void resize( const int32_t ni, const int32_t no, const int32_t nl );
}; // end class netc

// =======================================================================================
void netc::destroy( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<int32_t*>(0) != hid ) { delete[] hid; }
  nIn     = 0;
  nOut    = 0;
  nLayers = 0;
  hid     = static_cast<int32_t*>(0);
}

// =======================================================================================
void netc::resize( const int32_t ni, const int32_t no, const int32_t nl ) {
  // -------------------------------------------------------------------------------------
  if ( nl != nLayers ) {
    destroy();
    nLayers = nl;
    hid = new int32_t[nl];
    for ( int32_t i=0; i<nLayers; i++ ) {
      hid[i] = Guess( i, ni * no, no, nLayers );
    }
    hid[nLayers-1] = no;
  }
  nIn  = ni;
  nOut = no;
}

// =======================================================================================
void firstInput( netc& N ) {
  // -------------------------------------------------------------------------------------
  int32_t ni = StringTool::inputI32( "Number of inputs"  );
  int32_t no = StringTool::inputI32( "Number of outputs" );
  int32_t nl = StringTool::inputI32( "Number of layers"  );

  N.resize( ni, no, nl );

  for ( int32_t i=0; i<N.nLayers-1; i++ ) {
    std::string pr = c_fmt( "Hidden layer %d", i+1 );
    N.hid[i] = StringTool::input( pr, N.hid[i] );
  }
}


// =======================================================================================
void moreInput( netc& N ) {
  // -------------------------------------------------------------------------------------
  int32_t ni = StringTool::input( "Number of inputs",  N.nIn );
  int32_t no = StringTool::input( "Number of outputs", N.nOut );
  int32_t nl = StringTool::input( "Number of layers",  N.nLayers );

  N.resize( ni, no, nl );

  for ( int32_t i=0; i<N.nLayers-1; i++ ) {
    std::string pr = c_fmt( "Hidden layer %d", i+1 );
    N.hid[i] = StringTool::input( pr, N.hid[i] );
  }
}


// =======================================================================================
void display( netc& N, std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  os << "\nCurrent Network Configuration\n"
     <<   "-----------------------------\n\n"
     <<   "  Number of Inputs:  " << N.nIn << "\n";

  for ( int32_t i=0; i<N.nLayers-1; i++ ) {
    os << "  Hidden layer " << (i+1) << ":    " << N.hid[i] << "\n";
  }

  os << "  Number of Outputs: " << N.hid[N.nLayers-1] << "\n\n";
}

// =======================================================================================
int build_network( std::string filename, netc& N ) {
  // -------------------------------------------------------------------------------------
  BPNN net( N.nIn, N.hid, N.nLayers );
  net.randomize();
  net.write( filename );
  return 0;
}


// =======================================================================================
int process( ConfigDB::Section* cfg ) {
  // -------------------------------------------------------------------------------------
  std::string filename = cfg->get("netcfg");

  netc netcfg;
  firstInput( netcfg );
  display( netcfg, std::cerr );

  bool correct = StringTool::YesNo( "Are these values correct" );

  while ( ! correct ) {
    moreInput( netcfg );
    display( netcfg, std::cerr );
    correct = StringTool::YesNo( "Are these values correct" );
  }

  return build_network( filename, netcfg );
}

// =======================================================================================
/** @brief Entry point.
 *  @return 0 on success non-zero on failure
 */
// ---------------------------------------------------------------------------------------
int main( int argc, char *argv[], char **env ) {
  // -------------------------------------------------------------------------------------
  
  // ----- set the command line options --------------------------------------------------
  AppOptions::cli_map_s CLI[] = {
    { "net", "NNS", "netcfg",  true,  0, "network config file" },
    { 0, 0, 0, false, 0, 0 } 
  };
  
  AppOptions::init( CLI );
  AppOptions::setCommandLine( argc, argv, env );
  
  AppOptions::setTitleLine( "Make Network" );
  AppOptions::setConfigBase( "nerve" );
  AppOptions::setConfigPath( "~:.." );
  AppOptions::setEnvSectionName("NewEnv");
  AppOptions::setOptSectionName( "NewOpts" );
  AppOptions::setEnvConfigFilename( "ECFG" );
  AppOptions::setOptConfigFilename( "cfg" );
  AppOptions::setHelp( "help" );

  ConfigDB* cfg = AppOptions::getConfigDB();

  int rv = 0;
  if ( (ConfigDB*)0 != cfg ) {
    rv = process( cfg->get( "NNS" ) );
    delete cfg;
  } else {
    std::cerr << "Make Network FAILED\n\n";
    rv = 1;
  }

  return rv;
}


// =======================================================================================
// **                              M A K E _ N E T W O R K                              **
// ======================================================================== END FILE =====
