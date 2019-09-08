// ====================================================================== BEGIN FILE =====
// **                             T R A I N _ N E T W O R K                             **
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
/** @brief Train Network.
 *  @file   train_network.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-07
 *
 *  This application trains a network created with make_network.
 */
// =======================================================================================


#include <AppOptions.hh>
#include <BPNN.hh>
#include <Exemplar.hh>
#include <StringTool.hh>
#include <StopWatch.hh>


// =======================================================================================
  void train_net( BPNN* net, Exemplar* train, Exemplar* test,
                  int32_t epochs, int32_t report, int32_t batch, real8_t eta ) {
  // -------------------------------------------------------------------------------------
    StopWatch SW;

    SW.reset();
    {







    }
    real8_t elapsed = SW.check();

    std::cerr << "Elapsed training: " << elapsed << " seconds\n";
}

// =======================================================================================
int process( ConfigDB::Section* cfg ) {
  // -------------------------------------------------------------------------------------
  std::string oldnet    = cfg->get("oldcfg");
  std::string newnet    = cfg->get("oldcfg");
  
  Exemplar* train = new Exemplar( cfg->get("train") );
  Exemplar* test  = static_cast<Exemplar*>(0);
  if ( cfg->hasKey( "test" ) ) {
    test = new Exemplar( cfg->get("test") );
  }

  int32_t n_train = train->nSample();
  int32_t n_test  = (static_cast<Exemplar*>(0)==test) ? (0) : (test->nSample());

  int32_t epochs = StringTool::asInt32( cfg->get( "epochs" ) );
  real8_t eta    = StringTool::asReal8( cfg->get( "eta" ) );
  real8_t bp     = StringTool::asReal8( cfg->get( "batch" ) );
  int32_t report = StringTool::asInt32( cfg->get( "report" ) );
  if ( bp > 1.0 ) { bp /= 100.0; }
  int32_t batch  = (int32_t) floor( 0.5 + bp * (real8_t)n_train );

  BPNN* net = new BPNN( oldnet );

  train_net( net, train, test, epochs, report, batch, eta );
  
  net->write( newnet );

  delete net;
  if (static_cast<Exemplar*>(0) != test) { delete test; }
  delete train;
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
    { "old", "NNS", "oldcfg",  true,   0,     "old network config file" },
    { "new", "NNS", "newcfg",  true,   0,     "new network config file" },
    { "trn", "NNS", "train",   true,   0,     "training exemplars" },
    { "tst", "NNS", "test",    false,  0,     "testing exemplars" },
    { "epc", "NNS", "epochs",  true,  "1000", "number of epochs" },
    { "bat", "NNS", "batch",   true,  "10",   "batch size (percent of training data)" },
    { "rpt", "NNS", "report",  true,  "100",  "number of epochs between reports" },
    { "eta", "NNS", "eta",     true,  "0.09", "training coefficient" },
    { 0, 0, 0, false, 0, 0 } 
  };
  
  AppOptions::init( CLI );
  AppOptions::setCommandLine( argc, argv, env );
  
  AppOptions::setTitleLine( "Train Network" );
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
    std::cerr << "Train Network FAILED\n\n";
    rv = 1;
  }

  return rv;
}


// =======================================================================================
// **                             T R A I N _ N E T W O R K                             **
// ======================================================================== END FILE =====
