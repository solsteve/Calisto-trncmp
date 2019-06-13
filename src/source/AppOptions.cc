// ====================================================================== BEGIN FILE =====
// **                                A P P O P T I O N S                                **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2013, 2019, Stephen W. Soliday                                     **
// **                            stephen.soliday@trncmp.org                             **
// **                            http://research.trncmp.org                             **
// **                                                                                   **
// **  -------------------------------------------------------------------------------  **
// **                                                                                   **
// **  This file, and associated source code, is not free software; you may not         **
// **  redistribute it and/or modify it. This library is currently in an on going       **
// **  development phase by its author and has, as yet, not been publicly distributed.  **
// **  Development of this library has been at the sole cost in both time and funding   **
// **  by its author. Until such a public release is made the author retains ALL RIGHTS **
// **  to this software. It is expected that if and when this library is deemed         **
// **  releasable it will be released under the GNU Public license for non-commercial   **
// **  use or with a restricted rights for government use. At that time each source     **
// **  file will contain either/both the standard GPL statement/disclaimer, and/or the  **
// **  DFARS Restricted Rights Legend.                                                  **
// **                                                                                   **
// **  This library exists at the present time WITHOUT ANY WARRANTY; without even the   **
// **  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.         **
// **  As you are not supposed to be in possession of this file if you use it,          **
// **  you use this code AT YOUR OWN RISK.                                              **
// **                                                                                   **
// ----- Modification History ------------------------------------------------------------
//
/** @brief  Application Options.
 *  @file   AppOptions.cc
 *  @author Stephen W. Soliday
 *  @date   2013-06-30  Original release.
 *  @date   2019-Jun-11 CMake refactorization.
 *
 *  Provides the methods for creating a ConfigDB from a combination of default values
 *  configuration file and command line options.
 *  Precedence is:   CommandLine <-- ConfigFile <-- DefaultValues
 */
// =======================================================================================


#include <AppOptions.hh>
#include <TLogger.hh>
#include <StringTool.hh>
#include <FileTool.hh>
#include <string.h>
#include <time.h>

#define EMPTY_MAP     static_cast<cli_map_s*>(0)
#define EMPTY_MAP_PTR static_cast<cli_map_s**>(0)

char**                       AppOptions::NO_ENV            = static_cast<char**>(0);
const char*                  AppOptions::FILENAME          = static_cast<const char*>(0);
const char*                  AppOptions::NO_CFG_ON_CMDLINE = static_cast<const char*>(0);
const char*                  AppOptions::NO_CFG_IN_ENV     = static_cast<const char*>(0);
AppOptions::usage_function_t AppOptions::DEFAULT_USAGE     = static_cast<AppOptions::usage_function_t>(0);

AppOptions::classInstance*   AppOptions::instance = static_cast<AppOptions::classInstance*>(0);

static TLogger* logger = TLogger::getInstance();

// =======================================================================================
/** @brief Constructor
 */
// ---------------------------------------------------------------------------------------
AppOptions::classInstance::classInstance( void )
  : config_base("config"),
    config_path("/etc:~:."),
    env_secname("ENV"),
    opt_secname("CLI"),
    env_keyname(""),
    opt_keyname(""),
    help_keyname(""),
    check_for_help( false ),
    progName("Application"),
    title_line("Application * ver 1.0 * 20xx"),
    argc(0), argv(0), env(0),
    map(0), map_count(0), file_count(0),
    user_supplied(0), config(0) {
  // -------------------------------------------------------------------------------------

  time_t tt = time((time_t*)0);
  struct tm* st = gmtime(&tt);

  char buffer[64];
  sprintf( buffer, "Application * ver 1.0 * %4d", st->tm_year + 1900 );
  title_line = buffer;  
}




// =======================================================================================
/** @brief Destructor
 */
// ---------------------------------------------------------------------------------------
AppOptions::classInstance::~classInstance( void ) {
  // -------------------------------------------------------------------------------------
  if ( (ConfigDB*)0 != config ) { delete config; }

  for ( size_t i=0; i<map_count; i++ ) {
    map[i] = EMPTY_MAP;
  }

  if ( EMPTY_MAP_PTR != map ) { delete map; }
}


// =======================================================================================
/** @brief Resize Map.
 *  @param[in] new_map pointer to a new map.
 *  @param[in] n       number of items in the map.
 */
// ---------------------------------------------------------------------------------------
void AppOptions::classInstance::resize_map( cli_map_s* new_map, size_t n ) {
  // -------------------------------------------------------------------------------------
  cli_map_s** old_map = map;
  map = new cli_map_s*[ map_count + n ];

  for ( size_t i=0; i<map_count; i++ ) {
    map[i]     = old_map[i]; 
    old_map[i] = EMPTY_MAP;
  }

  if ( EMPTY_MAP_PTR != old_map ) { delete old_map; }

  for ( size_t i=0; i<n; i++ ) {
    map[map_count + i] = &(new_map[i]); 
  }

  map_count += n;
}


// =======================================================================================
/** @brief Display Map.
 */
// ---------------------------------------------------------------------------------------
void AppOptions::classInstance::display_map( void ) {
  // -------------------------------------------------------------------------------------
  if ( (cli_map_s**)0 == map ) {
    logger->info("Map was null");
  }

  for ( size_t i=0; i<map_count; i++ ) {
    std::cerr << map[ i ]->opt << " "
	      << map[ i ]->sec << " "
	      << map[ i ]->key << " "
	      << map[ i ]->req << " "
	      << map[ i ]->dec << std::endl;
  }
}


// =======================================================================================
/** @brief End of Data
 */
// ---------------------------------------------------------------------------------------
bool AppOptions::EOD( cli_map_s* cmap ) {
  // -------------------------------------------------------------------------------------
  if ( (char*)0 == cmap->opt ) {
    if ( (char*)0 == cmap->sec ) {
      if ( (char*)0 == cmap->key ) {
	if ( false    == cmap->req ) {
	  if ( (char*)0 == cmap->def ) {
	    if ( (char*)0 == cmap->dec ) {
	      return true;
	    }
	  }
	}
      }
    }
  }
  return false;
}


// =======================================================================================
/** @brief get Instance
 *  @return pointer to the singleton instance of the AppOptions class.
 */
// ---------------------------------------------------------------------------------------
AppOptions::classInstance* AppOptions::getInstance( void ) {
  // -------------------------------------------------------------------------------------
  if ( ( AppOptions::classInstance*)0 == AppOptions::instance ) {
    AppOptions::instance = new AppOptions::classInstance();
  }
  return AppOptions::instance;
}








// =======================================================================================
// ---------------------------------------------------------------------------------------
void AppOptions::init( cli_map_s* cmap, usage_function_t uf ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();
  I->user_supplied = uf;
  addOptions( cmap );
}


// =======================================================================================
/** @brief Free Allocation.
 */
// ---------------------------------------------------------------------------------------
void AppOptions::free( void ) {
  // -------------------------------------------------------------------------------------
  if (( AppOptions::classInstance*)0 == AppOptions::instance) { delete AppOptions::instance; };
  AppOptions::instance = ( AppOptions::classInstance*)0;
}


// =======================================================================================
/** @brief Title Line.
 *  @param[in] line title line
 *
 *  Set the title line displayed when the application runs.
 */
// ---------------------------------------------------------------------------------------
void AppOptions::setTitleLine( std::string line ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();
  I->title_line = line;
}


// =======================================================================================
/** @brief 
 *  @param[in] 
 *
 *  
 */
// ---------------------------------------------------------------------------------------
void AppOptions::setConfigBase( std::string base ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();
  I->config_base = base;
}


// =======================================================================================
/** @brief 
 *  @param[in] 
 *
 *  
 */
// ---------------------------------------------------------------------------------------
void AppOptions::setConfigPath( std::string path ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();
  I->config_path = path;
}

// =======================================================================================
/** @brief 
 *  @param[in] 
 *
 *  
 */
// ---------------------------------------------------------------------------------------
void AppOptions::setEnvSectionName( std::string sec_name ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();
  I->env_secname = sec_name;
}

// =======================================================================================
/** @brief 
 *  @param[in] 
 *
 *  
 */
// ---------------------------------------------------------------------------------------
void AppOptions::setOptSectionName( std::string sec_name ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();
  I->opt_secname = sec_name;
}

// =======================================================================================
/** @brief 
 *  @param[in] 
 *
 *  
 */
// ---------------------------------------------------------------------------------------
void AppOptions::setEnvConfigFilename( std::string env_name ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();
  I->env_keyname = env_name;
}

// =======================================================================================
/** @brief 
 *  @param[in] 
 *
 *  
 */
// ---------------------------------------------------------------------------------------
void AppOptions::setOptConfigFilename( std::string opt_name ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();
  I->opt_keyname = opt_name;
}

// =======================================================================================
/** @brief 
 *  @param[in] 
 *
 *  
 */
// ---------------------------------------------------------------------------------------
void AppOptions::setHelp( std::string help_name ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();
  I->help_keyname = help_name;
  I->check_for_help = true;
}
  static void setHelp              ( std::string help_name );

// =======================================================================================
/** @brief 
 *  @param[in] 
 *
 *  
 */
// ---------------------------------------------------------------------------------------
void AppOptions::setCommandLine( int argc, char** argv, char **env ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();
  I->argc = argc;
  I->argv = argv;
  I->env  = env;
  I->progName = argv[0];
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void AppOptions::addOptions( cli_map_s* cmap ) {
  // -------------------------------------------------------------------------------------
    AppOptions::classInstance* I = AppOptions::getInstance();

    size_t idx = 0;
    
    while ( (const char*)0 != cmap[idx].sec ) {
      char fn[8];
      if ( AppOptions::FILENAME == cmap[idx].opt ) {
	sprintf( fn, "file%lu", I->file_count );
	cmap[idx].opt = clone( fn );
	I->file_count += 1;
      }
      idx += 1;
    }
 
    I->resize_map( cmap, idx );
}


// =======================================================================================
/** @brief 
 *
 *  
 */
// ---------------------------------------------------------------------------------------
void AppOptions::usage( void ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();
  if ( AppOptions::DEFAULT_USAGE == I->user_supplied ) {
    AppOptions::auto_usage( I->progName, I->map, I->map_count );
  } else {
    (*(I->user_supplied))( (char*)(I->progName.c_str()) );
  }
}

// =======================================================================================
/** @brief 
 *  @param[in] pn program name
 *
 *  
 */
// ---------------------------------------------------------------------------------------
void AppOptions::usage( char* pn ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();
  if ( AppOptions::DEFAULT_USAGE == I->user_supplied ) {
    AppOptions::auto_usage( pn, I->map, I->map_count );
  } else {
    (*(I->user_supplied))( pn );
  }
}

// =======================================================================================
/** @brief 
 *  @param[in] program name
 *  @param[in] nuf user supplied usage function
 *
 *  
 */
// ---------------------------------------------------------------------------------------
void AppOptions::usage( char* pn, usage_function_t nuf ) {
  // -------------------------------------------------------------------------------------
  (*nuf)( pn );
}


// ==========================================================================================
/** @brief Auto generated usage statement.
 *  <p>
 *  Auto generate a usage/help screen. An important data structure for this call is
 *  command_line_map: each entry has 5 fields (char*, char*, char*, bool, char* )
 *  { option, section, key, required, default, description }, the last entry must have 0's
 *  { 0, 0, 0, false, 0, 0 }
 *  option      - key from the command line. AppOptions::FILENAME indicates that a string
 *                instead of a key=value pair is used, these replace file0, file1,...fileN
 *  section     - the section where the option will be stored.
 *  key         - the key in the section that this option will be stored.
 *  required    - this value is required on either the command line or the config file.
 *  default     - default value ((char*)0 indicates that no default value is used.
 *  description - description to be printed in the usage screen.
 *  <p>
 *
 *  @param pname Name of the executable (from argv[0] )
 *  @param cmap command line processing map (see above)
 */
// ------------------------------------------------------------------------------------------
void AppOptions::auto_usage( std::string pname, AppOptions::cli_map_s** cmap, size_t n_maps ) {
  // ----------------------------------------------------------------------------------------
AppOptions::classInstance* I = AppOptions::getInstance();
 
 std::cerr << std::endl << I->title_line << std::endl;
  
  if ( (AppOptions::cli_map_s**)0 == cmap ) {
    logger->warn("To use AppOptions::auto_usage a valid cli_map_s must be supplied");
  } else {
    if ( (AppOptions::cli_map_s*)0 == cmap[0] ) {
      logger->warn("To use AppOptions::auto_usage a valid cli_map_s must be supplied");
    } else {

      size_t n_file   = 0;

      for ( size_t i=0; i<n_maps; i++ ) {
	if ( 0 == strncmp(  "file", cmap[ i ]->opt, 4 ) ) { n_file += 1; }
      }

      size_t n_opts = n_maps - n_file;

      std::cerr << std::endl << "  USAGE: " << pname;
      if ( 0 < n_opts ) { std::cerr << " options"; }
      if ( 0 < n_file ) { std::cerr << " files"; }
      std::cerr << std::endl;

      bool req_items = false;

      // ----- display options -----------------------------------------------------------
      if ( 0 < n_opts ) {
	std::cerr << std::endl << "    options" << std::endl;
	  for (size_t i=0; i<n_maps; i++) {
	    if ( 0 != strncmp( "file", cmap[ i ]->opt, 4 ) ) {
	      std::cerr << "      " << cmap[ i ]->opt;
	      if ( cmap[ i ]->req ) {
		req_items = true;
		std::cerr << "\t*- ";
	      } else {
		std::cerr << "\t - ";
	      }
	      std::cerr << cmap[ i ]->dec << std::endl;
	    }
	  }
	}
      
      // ----- display files -------------------------------------------------------------
      if ( 0 < n_file ) {
	size_t fc = 0;
	std::cerr << std::endl << "    files" << std::endl;
	  for (size_t i=0; i<n_maps; i++) {
	    if ( 0 == strncmp(  "file", cmap[ i ]->opt, 4 ) ) {
	      std::cerr << "      file" << fc;
	      fc += 1;
	      if ( cmap[ i ]->req ) {
		std::cerr << "\t*- ";
		req_items = true;
	      } else {
		std::cerr << "\t - ";
	      }
	      std::cerr << cmap[ i ]->dec << std::endl;
	    }
	  }
	}

      // ----- display foot note ---------------------------------------------------------

      if ( req_items ) {

	int gram = 0;
	std::string line;

	if ( 0 < n_opts ) { gram +=  1; }
	if ( 1 < n_opts ) { gram +=  1; }
	if ( 0 < n_file ) { gram += 10; }
	if ( 1 < n_file ) { gram += 10; }

	if (  1 == gram ) { line = "this option is";          }
	if (  2 == gram ) { line = "these options are";       }
	if ( 10 == gram ) { line = "this file is";            }
	if ( 11 == gram ) { line = "these option/file are";   }
	if ( 12 == gram ) { line = "these options/file are";  }
	if ( 20 == gram ) { line = "these files are";         }
	if ( 21 == gram ) { line = "these option/files are";  }
	if ( 22 == gram ) { line = "these options/files are"; }

        std::cerr << "\n  *- " << line << " required.\n";
      }
      
      // ---------------------------------------------------------------------------------
      
      std::cerr << std::endl;
    }
  }
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
int AppOptions::parseCommandLine( ConfigDB* cfg, int argc, char** argv, std::string secname ) {
  // -------------------------------------------------------------------------------------
  ConfigDB::Entry ent;
  int  fileCounter = 0;
  cfg->set( secname, "progname", argv[0] );
  int ierr = 0;
  for (int i=1; i<argc; i++) {
    int rv = ent.fromString( argv[i], false );
    switch(rv) {
      case 0:  { // ----- KV Pair --------------------------------------------------------
        cfg->set( secname, ent.getKey(), ent.getValue() );
      } break;
      case 2:  { // ----- filename -------------------------------------------------------
        char file_key[32];
        snprintf( file_key, 32, "file%d", fileCounter );
        cfg->set( secname, file_key, argv[i] );
        fileCounter += 1;        
      } break;
      case 4:  { // ----- option missing value -------------------------------------------
        logger->warn( "option [%s] contains no value", argv[i] );
        ierr = rv;
      } break;
      default: { // ----- error ----------------------------------------------------------
        ierr = rv;
      } break;
    }
  }
  
  return ierr;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
int AppOptions::parseEnvironment( ConfigDB* cfg, char** env, std::string envname ) {
  // -------------------------------------------------------------------------------------
  ConfigDB::Entry ent;
  size_t idx = 0;
  int ierr = 0;
  while ( env[idx] ) {
    int rv = ent.fromString( env[idx], false );
    switch(rv) {
      case 0: { // ----- env variable is a KV Pair ---------------------------------------
        cfg->set( envname, ent.getKey(), ent.getValue() );
      } break;
      case 4: { // ----- env variable is "present == true" flag --------------------------
        cfg->set( envname, ent.getKey(), "true" );
      } break;
      default: { // ----- error ----------------------------------------------------------
        ierr = rv;
      } break;
    }    
    idx++;
  }
  return ierr;
}








// =======================================================================================
/** @brief Set ConfigDB
 *  @param[in] db source ConfigDB
 *  @return pointer to the underlying ConfigDB
 *
 *  If no ConfigDB exists create one. Merge the source ConfigDB int this one.
 */
// ---------------------------------------------------------------------------------------
ConfigDB* AppOptions::setConfigDB( ConfigDB* db ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();

  if ( (ConfigDB*)0 == I->config ) {
    I->config = new ConfigDB();
  }
  
  I->config->merge( db );
  
  return I->config;
}

// =======================================================================================
/**
 *  @return pointer to the populated configuration file.
 *
 *  A ConfigDB is constructed by reading data in successive layers each layer over
 *  writing the previous.
 *
 *  For the following example:
 *      cfg=test.ini is on the command line.
 *      MY_CONFIG=~/common.ini as an environment variable key-pair
 *      cfg_base = "example.cfg"
 *      cfg_path = "/usr/share/trncmp:/etc:~/lib:~:."
 *
 *  empty ConfigDB                 <-- performed first
 *  default_map
 *  /usr/share/trncmp/example.cfg
 *  /etc/example.cfg
 *  ~/lib/example.cfg
 *  ~/lib/example.cfg
 *  ./example.cfg
 *  ~/common.ini
 *  ./test.ini
 *  command_line_overrides         <-- last performed
 */
// ---------------------------------------------------------------------------------------
ConfigDB* AppOptions::getConfigDB( void ) {
  // -------------------------------------------------------------------------------------
  AppOptions::classInstance* I = AppOptions::getInstance();

  // -------------------------------------------------------------------------------------
  // Check for help request
  // -------------------------------------------------------------------------------------

  if ( I->check_for_help ) {
    if ( (char**)0 != I->argv ) {
      for ( int i=0; i<I->argc; i++ ) {
	if ( 0 == I->help_keyname.compare( I->argv[i] ) ) {
	  AppOptions::usage( I->argv[0] );
	  return (ConfigDB*)0;
	}
      }
    }
  }

  // -------------------------------------------------------------------------------------
  // allocate a new config DB if necessary
  // -------------------------------------------------------------------------------------

  if ( (ConfigDB*)0 == I->config ) {
    I->config = new ConfigDB();
  }

  // -------------------------------------------------------------------------------------
  // add defaults from the user if available
  // -------------------------------------------------------------------------------------

  for ( size_t idx=0; idx<I->map_count; idx++ ) {
    if ( (const char*)0 != I->map[idx]->def ) {
      I->config->set( I->map[idx]->sec, I->map[idx]->key, I->map[idx]->def );
    }
  }

  // -------------------------------------------------------------------------------------
  // parse the command line for options and environment variables
  // -------------------------------------------------------------------------------------

  ConfigDB::Section* csec = (ConfigDB::Section*)0;
  ConfigDB::Section* esec = (ConfigDB::Section*)0;

  if ( (char**)0 != I->env ) {
    AppOptions::parseEnvironment( I->config, I->env, I->env_secname );
    if ( I->config->hasSection( I->env_secname ) ) {
      esec = I->config->get( I->env_secname );
    } else {
      logger->error( LOCATION, "failed to read environment section: %s", I->env_secname.c_str() );
      delete I->config;
      return (ConfigDB*)0;
    }
  }

  if ( (char**)0 != I->argv ) {
    AppOptions::parseCommandLine( I->config, I->argc, I->argv, I->opt_secname );
    if ( I->config->hasSection( I->opt_secname ) ) {
      csec = I->config->get( I->opt_secname );
    } else {
      logger->error( LOCATION, "failed to read command line section: %s", I->opt_secname.c_str() );
      delete I->config;
      return (ConfigDB*)0;
    }
  }

  // -------------------------------------------------------------------------------------
  // first try to guess where config files are
  // -------------------------------------------------------------------------------------

  if ( 0 < I->config_base.size() ) {
    const char* prefix[] = { "", "." };
    size_t      prefix_n = 2;

    const char* suffix[] = { "", ".ini", ".cfg", ".config" };
    size_t      suffix_n = 4;

    StringTool::Splitter SP( I->config_path, ':' );

    size_t n = SP.size();

    for (size_t i=0; i<n; i++) {
      for ( size_t j=0; j<prefix_n; j++ ) {
	for ( size_t k=0; k<suffix_n; k++ ) {
	  std::string test = SP[i] + "/" + prefix[j] + I->config_base + suffix[k];
	  //std::cout << "Try [" << test << "]";
	  if ( true == FileTool::fileExists( test ) ) {
	    //std::cout << " (found)";
	    I->config->readINI( test );
	  }
	  //std::cout << std::endl;
	}
      }
    }
  }
  
  // -------------------------------------------------------------------------------------
  // check to see if there is an environment variable for the config filename
  // -------------------------------------------------------------------------------------

  if ( AppOptions::NO_ENV != I->env ) {
    if ( 0 < I->env_keyname.length() ) {
      if ( I->config->hasSection( I->env_secname ) ) {
	esec = I->config->get( I->env_secname );
	if ( esec->hasKey( I->env_keyname ) ) {
	  std::string cfgfn = esec->get( I->env_keyname );
	  logger->debug( "Reading config from ENV: %s", cfgfn.c_str() );
	  I->config->readINI( cfgfn );
	}
      }
    }
  }

  // -------------------------------------------------------------------------------------
  // next check to see if there is a command line option for the config filename
  // -------------------------------------------------------------------------------------

  if ( 0 < I->opt_keyname.length() ) {
    if ( csec->hasKey(I->opt_keyname) ) {
      std::string cfgfn = csec->get( I->opt_keyname );
      logger->debug( "Reading config from CMDLIN: %s", cfgfn.c_str() );
      I->config->readINI( cfgfn );
    }
  }

  // -------------------------------------------------------------------------------------
  // use command line options to override keypairs in the config database
  // -------------------------------------------------------------------------------------

  for ( size_t idx=0; idx<I->map_count; idx++ ) {
    const char* cli_opt = I->map[ idx ]->opt;
    if ( csec->hasKey( cli_opt ) ) {
      std::string cli_var = csec->get( cli_opt );
      I->config->set( I->map[idx]->sec, I->map[idx]->key, cli_var );
    }
  }

  // -------------------------------------------------------------------------------------
  // finally validate the contents of the config database
  // -------------------------------------------------------------------------------------

  int missing_opt = 0;
  for ( size_t idx=0; idx<I->map_count; idx++ ) {
    try {
      if ( I->map[ idx ]->req ) {
	ConfigDB::Section* sec = I->config->get( I->map[ idx ]->sec );
	if ( ! sec->hasKey( I->map[ idx ]->key ) ) {
	  std::cerr << std::endl << "You either need [" << I->map[ idx ]->opt
		    << "] on the command line, or ["
		    << I->map[ idx ]->sec << "." << I->map[ idx ]->key
		    << "] in the configuration file" << std::endl;
	  missing_opt += 1;
	}
      }
    } catch ( ConfigDB::NoSuchSection e ) {
      missing_opt += 1;
    }
  }



  if ( 0 < missing_opt ) {
    logger->error( "missing options from the command line." );
    AppOptions::usage();
    delete I->config;
    I->config = (ConfigDB*)0;
  }

  return I->config;
}


// =======================================================================================
// **                                A P P O P T I O N S                                **
// ======================================================================== END FILE =====
