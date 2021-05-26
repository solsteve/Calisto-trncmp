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

  GKBH* gkb= static_cast<GKBH*>(0);

  int test1 = 0;
  int test2 = 0;

  if ( cfg->hasKey( "ibin" ) ) { test1 += 1; }
  if ( cfg->hasKey( "iasc" ) ) { test1 += 2; }
  if ( cfg->hasKey( "obin" ) ) { test2 += 1; }
  if ( cfg->hasKey( "oasc" ) ) { test2 += 2; }

  // -------------------------------------------------------------------------------------
  
  switch(test1) {
    case 0:
      std::cerr << "You must use either ibin= or iasc=" << std::endl;
      return 1;
      break;
    case 1:
      gkb = new GKBH( cfg->get( "ibin" ) );
      break;
    case 2:
      gkb = new GKBH( cfg->get( "iasc" ), true );
      break;
    case 3:
      std::cerr << "You must not use ibin= and iasc= together" << std::endl;
      return 2;
      break;
  }
  
  // -------------------------------------------------------------------------------------

  switch(test2) {
    case 0:
      std::cerr << "You must use either obin= or oasc=" << std::endl;
      return 3;
      break;
    case 1:
      gkb->write( cfg->get( "obin" ) );
      break;
    case 2:
      gkb->writeASCII( cfg->get( "oasc" ) );
      break;
    case 3:
      std::cerr << "You must not use obin= and oasc= together" << std::endl;
      return 4;
      break;
  }
  
  // -------------------------------------------------------------------------------------

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

  // ----- set the command line options -----------------------------------------------------
  AppOptions::cli_map_s CLI[] = {
    { "ibin", "APP", "ibin", false, 0, "input  binary GKB" },
    { "iasc", "APP", "iasc", false, 0, "input  ASCII  GKB" },
    { "obin", "APP", "obin", false, 0, "output binary GKB" },
    { "oasc", "APP", "oasc", false, 0, "output ASCII  GKB" },
    { 0, 0, 0, false, 0, 0 } 
  };
  
  AppOptions::init( CLI );
  AppOptions::setCommandLine( argc, argv, env );
  
  AppOptions::setTitleLine( "Copy GKB" );
  AppOptions::setConfigBase( "ctest" );
  AppOptions::setConfigPath( "~:.." );
  AppOptions::setEnvSectionName("NewEnv");
  AppOptions::setOptSectionName( "NewOpts" );
  AppOptions::setEnvConfigFilename( "ECFG" );
  AppOptions::setOptConfigFilename( "cfg" );
  AppOptions::setHelp( "help" );

  AppOptions::setExampleLine( "ibin=test.bin oasc=test.txt" );

  AppOptions::addUsageText( "Copy/convert GKB files" );

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
