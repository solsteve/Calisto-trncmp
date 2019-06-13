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
 *  @file   AppOptions.hh
 *  @author Stephen W. Soliday
 *  @date   2013-06-30  Original release.
 *  @date   2019-Jun-11 CMake refactorization.
 *
 *  Provides the interface for creating a ConfigDB from a combination of default values
 *  configuration file and command line options.
 *  Precedence is:   CommandLine <-- ConfigFile <-- DefaultValues
 */
// =======================================================================================

#ifndef __APPOPTIONS_TRNCMP_HH
#define __APPOPTIONS_TRNCMP_HH

#include <ConfigDB.hh>


// =======================================================================================
/** @brief Application Options.
 *  @note this is a Singlton class.
 */
// ---------------------------------------------------------------------------------------
class AppOptions {
  // -------------------------------------------------------------------------------------
 public:
  
  // =====================================================================================
  typedef struct {                                                // AppOptions::cli_map_s
    // -------------------------------------------------------------------------------------
    const char* opt;   //< command line option that overrides a config file entry
    const char* sec;   //< section to be overridden in ConfigDB
    const char* key;   //< key     to be overridden in ConfigDB
    bool        req;   //< boolean flag, this option is required
    const char* def;   //< default value
    const char* dec;   //< description for the auto generated usage statement
  } cli_map_s;
  
  typedef void (*usage_function_t)( char* pn );



  
 protected:

  // =====================================================================================
  class classInstance {                                       // AppOptions::classInstance
    // -----------------------------------------------------------------------------------
   protected:
    EMPTY_PROTOTYPE( classInstance );

   public:
    std::string config_base;     //< configuration file base for searching
    std::string config_path;     //< configuration file path for searching

    std::string env_secname;     //< section name for environment variables
    std::string opt_secname;     //< section name for command line options

    std::string env_keyname;     //< keyname for override config file found in ENV
    std::string opt_keyname;     //< keyname for override config file found on CommandLine
    std::string help_keyname;    //< keyname for asking for help on CommandLine
    bool        check_for_help;
    std::string progName;        //< name of the application

    std::string title_line;      //< constructed by default

    int         argc;               //< shallow copy of command line pointers
    char**      argv;
    char**      env;

    cli_map_s**      map;        //< array of command line option descriptions
    size_t           map_count;  //< number of current maps
    size_t           file_count; //< number of option less file names
    usage_function_t user_supplied;

    ConfigDB* config;            //< parsed configuration DB

    classInstance( void );
    ~classInstance( void );
 
    void resize_map( cli_map_s* cmap, size_t n );
    
    void display_map( void );

  }; // end class AppOptions::classInstance




  static bool EOD( cli_map_s* cmap );

  static classInstance* instance;

  static classInstance* getInstance( void );

  AppOptions  ( void ) {};
  ~AppOptions ( void ) {};

  // ----- static functions and data structures ------------------------------------------

 public:

  static void init                 ( cli_map_s* cmap, usage_function_t uf = (usage_function_t)0 );
  static void free                 ( void );

  static void setTitleLine         ( std::string line );
  static void setConfigBase        ( std::string base );
  static void setConfigPath        ( std::string path );
  static void setEnvSectionName    ( std::string sec_name );
  static void setOptSectionName    ( std::string sec_name );
  static void setEnvConfigFilename ( std::string env_name );
  static void setOptConfigFilename ( std::string opt_name );
  static void setHelp              ( std::string help_name );
  static void setCommandLine       ( int argc, char** argv, char** env = (char**)0 );
  static void addOptions           ( cli_map_s* cmap );

  static void usage( void );
  static void usage( char* pn );
  static void usage( char* pn, usage_function_t nuf );

  static void auto_usage( std::string pname, AppOptions::cli_map_s** cmap, size_t n_user );

  static int  parseCommandLine ( ConfigDB* cfg, int argc, char** argv, std::string secname );
  static int  parseEnvironment ( ConfigDB* cfg,           char** env,  std::string secname );

  static void display_map( void ) { AppOptions::getInstance()->display_map(); };
 
  static ConfigDB* setConfigDB  ( ConfigDB* db );
  static ConfigDB* getConfigDB  ( void );

  static char**           NO_ENV;
  static const char*      FILENAME;
  static const char*      NO_DEFCFG;
  static const char*      NO_CFG_ON_CMDLINE;
  static const char*      NO_CFG_IN_ENV;
  static usage_function_t DEFAULT_USAGE;
}; // end class AppOptions























#endif


// =======================================================================================
// **                                A P P O P T I O N S                                **
// ======================================================================== END FILE =====
