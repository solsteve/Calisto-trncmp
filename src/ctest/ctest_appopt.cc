// ====================================================================== BEGIN FILE =====
// **                              C T E S T _ A P P O P T                              **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2019, Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
// **                                                                                   **
// **  -------------------------------------------------------------------------------  **
// **                                                                                   **
// **  This program is free software: you can redistribute it and/or modify it under    **
// **  the terms of the GNU General Public License as published by the Free Software    **
// **  Foundation, either version 3 of the License, or (at your option)                 **
// **  any later version.                                                               **
// **                                                                                   **
// **  This program is distributed in the hope that it will be useful, but WITHOUT      **
// **  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS    **
// **  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.   **
// **                                                                                   **
// **  You should have received a copy of the GNU General Public License along with     **
// **  this program. If not, see <http://www.gnu.org/licenses/>.                        **
// **                                                                                   **
// ----- Modification History ------------------------------------------------------------
//
/** @brief Test the Version
 *  @file   ctest_version.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-13
 *
 *  This is a test of AppOptions
 */
// =======================================================================================


#include <AppOptions.hh>


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
    { AppOptions::FILENAME, "APP", "option",  true,  0, "operation: E, D, or G" },
    { "if",                 "APP", "infspc",  true,  0, "input file name" },
    { "of",                 "APP", "outfspc", false, 0, "output file name" },
    { "n",                  "APP", "count",   false, 0, "number of records to process" },
    { 0, 0, 0, false, 0, 0 } 
  };
  
  AppOptions::init( CLI );
  AppOptions::setCommandLine( argc, argv, env );
  
  AppOptions::setTitleLine( "My Big Test" );
  AppOptions::setConfigBase( "ctest" );
  AppOptions::setConfigPath( "~:.." );
  AppOptions::setEnvSectionName("NewEnv");
  AppOptions::setOptSectionName( "NewOpts" );
  AppOptions::setEnvConfigFilename( "ECFG" );
  AppOptions::setOptConfigFilename( "cfg" );
  AppOptions::setHelp( "help" );

  ConfigDB* cfg = AppOptions::getConfigDB();

  if ( (ConfigDB*)0 != cfg ) {
    cfg->writeINI( std::cout );
    delete cfg;
  } else {
    std::cerr << "AppOpts Test FAILED\n\n";
  }

  return 0;
}


// =======================================================================================
// **                              C T E S T _ A P P O P T                              **
// ======================================================================== END FILE =====
