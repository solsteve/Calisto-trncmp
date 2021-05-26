// ====================================================================== BEGIN FILE =====
// **                                A P P O P T I O N S                                **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2013-2019, Stephen W. Soliday                                      **
// **                           stephen.soliday@trncmp.org                              **
// **                           http://research.trncmp.org                              **
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

#ifndef __HH_APPOPTIONS_TRNCMP
#define __HH_APPOPTIONS_TRNCMP

#include <ConfigDB.hh>


// =======================================================================================
/** @brief Application Options.
 *  @note this is a Singlton class.
 */
// ---------------------------------------------------------------------------------------
class AppOptions {
  // -------------------------------------------------------------------------------------
 public:

  static size_t MAX_USAGE_TEXT;
  
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
    std::string  config_base;     //< configuration file base for searching
    std::string  config_path;     //< configuration file path for searching

    std::string  env_secname;     //< section name for environment variables
    std::string  opt_secname;     //< section name for command line options

    std::string  env_keyname;     //< keyname for override config file found in ENV
    std::string  opt_keyname;     //< keyname for override config file found on CommandLine
    std::string  help_keyname;    //< keyname for asking for help on CommandLine
    bool         check_for_help;
    std::string  progName;        //< name of the application

    std::string  title_line;      //< constructed by default
    std::string  example_line;    //< example usage
    bool         display_example;
    std::string* usage_lines;
    size_t       usage_line_index;
    
    int              argc;       //< shallow copy of command line pointers
    char**           argv;
    char**           env;

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

  static void setConfigBase        ( std::string base );
  static void setConfigPath        ( std::string path );
  static void setHelp              ( std::string help_name );
  static void setTitleLine         ( std::string line );

  static void setExampleLine       ( std::string line );
  static void addUsageText         ( std::string line );    // **** ADD FUNCTION



  
  static void setEnvSectionName    ( std::string sec_name );
  static void setOptSectionName    ( std::string sec_name );
  static void setEnvConfigFilename ( std::string env_name );
  static void setOptConfigFilename ( std::string opt_name );
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
  static char**           NO_ARGV;
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
