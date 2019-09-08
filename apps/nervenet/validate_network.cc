// ====================================================================== BEGIN FILE =====
// **                          V A L I D A T E _ N E T W O R K                          **
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
/** @brief Validate Network.
 *  @file   validate_network.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-07
 *
 *  This application validates a trained network.
 */
// =======================================================================================


#include <AppOptions.hh>


// =======================================================================================
int process( ConfigDB::Section* cfg ) {
  // -------------------------------------------------------------------------------------
  std::string filename = cfg->get("netcfg");

  std::cout << "Writing new network configuration to [" << filename << "]\n";
  
  return 0;
}

// =======================================================================================
/** @brief Entry point.
 *  @return 0 on success non-zero on failure
 */
// ---------------------------------------------------------------------------------------
int main( int argc, char *argv[], char **env ) {
  // -------------------------------------------------------------------------------------
  
  // ----- set the command line options -----------------------------------------------------
  AppOptions::cli_map_s CLI[] = {
    { "net", "NNS", "netcfg",  true,  0, "network config file" },
    { 0, 0, 0, false, 0, 0 } 
  };
  
  AppOptions::init( CLI );
  AppOptions::setCommandLine( argc, argv, env );
  
  AppOptions::setTitleLine( "Validate Network" );
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
    std::cerr << "Validate Network FAILED\n\n";
    rv = 1;
  }

  return rv;
}


// =======================================================================================
// **                          V A L I D A T E _ N E T W O R K                          **
// ======================================================================== END FILE =====
