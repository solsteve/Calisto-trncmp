// ====================================================================== BEGIN FILE =====
// **                           E X E C U T E _ N E T W O R K                           **
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
/** @brief Execute Network.
 *  @file   execute_network.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-07
 *
 *  This application uses a trained network to label data.
 */
// =======================================================================================


#include <AppOptions.hh>
#include <TLogger.hh>
#include <Exemplar.hh>
#include <nns/BPNN.hh>
#include <StopWatch.hh>

TLOGGER_INSTANCE(logger);

// =======================================================================================
int process( ConfigDB::Section* cfg ) {
  // -------------------------------------------------------------------------------------
  StopWatch SW;

  std::string netcfg  = cfg->get("netcfg");
  std::string infile  = cfg->get("infile");
  std::string outfile = cfg->get("outfile");

  std::string ifmt = cfg->get("ifmt");
  std::string ofmt = (cfg->hasKey("ofmt")) ? (cfg->get("ofmt")) : (ifmt);

  
  Exemplar input( infile );

  nns::BPNN net( netcfg );

  const int32_t n_input  = net.nInput();
  const int32_t n_output = net.nOutput();

  const int32_t n_sample = input.nSample();

  if ( n_input != input.nInput() ) {
    logger->error( "Network and input data not compatable: net(in)=%d data(in)=%d",
                   n_input, input.nInput() );
    return 1;
  }

  Exemplar output( n_sample, n_input, n_output );

  std::cout << "BPNN configuration from [" << netcfg << "]\n";
  std::cout << "Reading from [" << infile << "]\n";
  
  SW.reset();
  for ( int32_t i=0; i<n_sample; i++ ) {
    real8_t* in_inp  = input.getIn(i);
    real8_t* out_inp = output.getIn(i);
    real8_t* out_out = output.getOut(i);
    copy( out_inp, in_inp, n_input );
    net.execute( in_inp, out_out );
  }
  real8_t elapsed = SW.check();

  std::cerr << "Elapsed training: " << elapsed << " seconds\n";

  std::cout << "Writting to  [" << outfile << "]\n";
  std::cout << "Using: " << ifmt << " and " << ofmt << " as formats\n";
  output.setInputFormat( ifmt );
  output.setOutputFormat( ofmt );
  output.write( outfile );
  
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
    { "net",  "NNS", "netcfg",  true,  0, "network config file" },
    { "if",   "NNS", "infile",  true,  0, "input file (if labels exist they are ignored)" },
    { "of",   "NNS", "outfile", true,  0, "output file (input and output written as a pair)" },
    { "fmt",  "NNS", "ifmt",    true,  "%23.16e", "label file input  format (default: %23.16e)" },
    { "ofmt", "NNS", "ofmt",    false, 0,         "label file output format (default: same as fmt)" },
    { 0, 0, 0, false, 0, 0 } 
  };
  
  AppOptions::init( CLI );
  AppOptions::setCommandLine( argc, argv, env );
  
  AppOptions::setTitleLine( "Execute Network" );
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
    std::cerr << "Execute Network FAILED\n\n";
    rv = 1;
  }

  return rv;
}


// =======================================================================================
// **                           E X E C U T E _ N E T W O R K                           **
// ======================================================================== END FILE =====
