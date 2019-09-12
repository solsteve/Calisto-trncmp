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
#include <Exemplar.hh>
#include <FileTool.hh>
#include <TLogger.hh>
#include <ConfusionMatrix.hh>

TLOGGER_INSTANCE(logger);

// =======================================================================================
int process( ConfigDB::Section* cfg ) {
  // -------------------------------------------------------------------------------------
  std::string true_data_filename = cfg->get( "true" );
  std::string test_data_filename = cfg->get( "test" );

  Exemplar trueData( true_data_filename );
  Exemplar testData( test_data_filename );

  const int32_t n_sample = trueData.nSample();
  const int32_t n_input  = trueData.nInput();
  const int32_t n_output = trueData.nOutput();

  if ( n_sample != testData.nSample() ) {
    logger->error( "Ground-truth and test data files are not compatable: true(samp)=%d test(samp)=%d",
                   n_input, testData.nSample() );
    return 1;
  }

  if ( n_input != testData.nInput() ) {
    logger->error( "Ground-truth and test data files are not compatable: true(in)=%d test(in)=%d",
                   n_input, testData.nInput() );
    return 2;
  }

  if ( n_output != testData.nOutput() ) {
    logger->error( "Ground-truth and test data files are not compatable: true(out)=%d test(out)=%d",
                   n_input, testData.nOutput() );
    return 3;
  }

  // -------------------------------------------------------------------------------------

  std::string report_filename = "/dev/stdout";

  if ( cfg->hasKey( "report" ) ) {
    std::string rname = cfg->get( "report" );
    if ( '1' == rname[0] ) {
      report_filename = "/dev/stdout";
    } else {
      if ( '2' == rname[0] ) {
        report_filename = "/dev/stderr";
      } else {
        report_filename = rname;
      }
    }
  }

  // -------------------------------------------------------------------------------------
  
  ConfusionMatrix CM( n_output );
  
  for ( int32_t i=0; i<n_sample; i++ ) {
    const int32_t r = (int32_t) MaxLoc( trueData.getOut(i), n_output );
    const int32_t c = (int32_t) MaxLoc( testData.getOut(i), n_output );
    CM.add( r, c );
  }

  std::ofstream report = FileTool::openWrite( report_filename );

  CM.display( );

  report.close();

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
    { "tru", "NNS", "true",   true,  0, "path to ground truthed exemplar file" },
    { "tst", "NNS", "test",   true,  0, "path to exemplar file to be tested" },
    { "rpt", "NNS", "report", false, 0, "path to report file 1=stdout, 2=stderr" },
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
