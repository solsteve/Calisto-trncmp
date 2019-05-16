// ====================================================================== BEGIN FILE =====
// **                                  C O N F I G D B                                  **
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
/** @brief  Configuration Database.
 *  @file   ConfigDB.hh
 *  @author Stephen W. Soliday
 *  @date   2013-06-30  Original release.
 *  @date   2019-Apr-28 CMake refactorization.
 *
 *  Provides the methods for a configuration database based on a multi-level
 *  key value pair map.
 */
// =======================================================================================



#include <ConfigDB.hh>
#include <StringTool.hh>
#include <FileTool.hh>

TLOGGER_REFERENCE( ConfigDB, logger );

// =======================================================================================
// ---------------------------------------------------------------------------------------
ConfigDB::Entry::Entry( std::string ln ) : key(), value(), comment() {
  // -------------------------------------------------------------------------------------
  fromString( ln );
}


// =======================================================================================
/** @brief Constructor.
 *  @param k key.
 *  @param v value.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::Entry::Entry( std::string k, std::string v ) : key(k), value(v), comment() {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param k key.
 *  @param v value.
 *  @param c optional comment.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::Entry::Entry( std::string k, std::string v, std::string c )
    : key(k), value(v), comment(c) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::Entry::Entry( void ) : key(), value(), comment() {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
ConfigDB::Entry::~Entry( void ) {
  // -------------------------------------------------------------------------------------
  clear();
}



    
void ConfigDB::Entry::clear( void ) {
  key.erase();
  value.erase();
  comment.erase();
};




//    void        copy       ( Entry* );
//    void        set        ( std::string k, std::string v, std::string c="" );
//    std::string toString   ( void );




// =======================================================================================
// ---------------------------------------------------------------------------------------
int ConfigDB::Entry::fromString( std::string test ) {
  // -------------------------------------------------------------------------------------
  if ( 0 == StringTool::trim( test ).size() ) {
    logger->error( "Line {%s} appears to be empty", test.c_str() );
    return 1;    
  }
  
  size_t sep = test.find_first_of("=:");

  if ( std::string::npos == sep ) {
    logger->error( "Line {%s} is not parsable. It must contain an = or :", test.c_str() );
    return 2;
  }

  key = StringTool::trim( test.substr( 0, sep ) );
  if ( 0 == key.size() ) {
    logger->error( "Line {%s} does not appear to contain a key", test.c_str() );
    return 3;    
  }
  
  std::string rhs = StringTool::trim( test.substr( sep+1 ) );
  if ( 0 == rhs.size() ) {
    logger->error( "Line {%s} does not appear to data after =", test.c_str() );
    return 4;    
  }

  if (( '"' == rhs[0] ) ||
      ( '\'' == rhs[0] )) { // ----- value may be in quotes -------------------------

    value = StringTool::containedBy( rhs, "'\"", "'\"" );
    if ( 0 == value.size() ) {
      logger->error( "Line {%s} quotes contain no value", test.c_str() );
      return 5;    
    }
  } else {
    sep = rhs.find( ';', 0 );
    if (std::string::npos == sep) { // ----- no comments -----------------------------
      value = StringTool::trim( rhs );
    } else { // ----- line has a comment ---------------------------------------------
      value   = StringTool::trim( rhs.substr( 0, sep ));

      if ( 0 == value.size() ) {
        logger->error( "Line {%s} no value", test.c_str() );
        return 6;    
      }
      comment = StringTool::trim( rhs.substr( sep+1 ) );
      if ( 0 == comment.size() ) {
        logger->warn( "Line {%s} comment is empty", test.c_str() );
      }
    }
  }

  return 0;
}














// =======================================================================================
// ---------------------------------------------------------------------------------------
ConfigDB::ConfigDB( void ) : sections(0), file_comments(0) {
  // -------------------------------------------------------------------------------------
}




// =======================================================================================
// ---------------------------------------------------------------------------------------
ConfigDB::ConfigDB( const std::string fspc ) : sections(0), file_comments(0) {
  // -------------------------------------------------------------------------------------
  readINI( fspc, static_cast<int*>(0) );
}












// =======================================================================================
/** @brief Parse INI Line.
 *  @param[in]  ref reference line.
 *  @param[out] return values.
 *  @return line type.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::ini_line_type ConfigDB::ParseLine_INI( std::string& ref, std::string* ret_val ) {
  // -------------------------------------------------------------------------------------
  size_t n,c;
  std::string test = StringTool::trim( ref );

  if ( 0 == test.size() )  { return ConfigDB::INI_BLANK_LINE; }

  // ----- find a line comment -----------------------------------------------------------
  if ( ';' == test[0] ) {
    *ret_val = StringTool::trim( test.substr( 1 ) );
    return ConfigDB::INI_LINE_COMMENT;
  }

  // ----- find a section name -----------------------------------------------------------
  if (( '[' == test[0] ) ||
      ( '{' == test[0] ) ||
      ( '(' == test[0] ) ) {

    *ret_val = StringTool::trim( StringTool::containedBy( test, "[{(", "]})" ) );

    if ( 0 == ret_val[0].size() ) { return ConfigDB::INI_UNKNOWN; }

    if ( "@EOF" == *ret_val ) {
      return ConfigDB::INI_EOF;
    }

    return ConfigDB::INI_SECTION_NAME;
  }

  *ret_val = StringTool::trim( ref );
  return ConfigDB::INI_OTHER_LINE;
}








// =======================================================================================
/** @brief Write INI File.
 *  @param[in] os output stream to write on.
 *  @return code.
 *
 *  Write the configuration onto an output stream.
 */
// ---------------------------------------------------------------------------------------
int ConfigDB::writeINI   ( std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  return 1;
}



// =======================================================================================
/** @brief Read INI File.
 *  @param[in] is input stream to read from.
 *  @return code.
 *
 *  Read the configuration from an input stream.
 */
// ---------------------------------------------------------------------------------------
int ConfigDB::readINI( std::istream& is ) {
  // -------------------------------------------------------------------------------------
  
  return 1;
}



// =======================================================================================
/** @brief Write INI File.
 *  @param[in]  fspc full path to a configuration file.
 *  @param[out] status optional return code.
 *  @return code.
 *
 *  Write the configuration to a file. If status is null error message will be written
 *  to the logger. If status is not null then now message will be written and a return
 *  code will be set. Either way the return code is returned in the normal manner.
 */
// ---------------------------------------------------------------------------------------
int ConfigDB::writeINI( const std::string fspc, int* status ) {
  // -------------------------------------------------------------------------------------
  int istat = 0;
  std::ofstream os = FileTool::openWrite( fspc, &istat );
  if ( 0 == istat ) {
    istat = writeINI( os );
    if ( 0 < istat ) {
      if ( static_cast<int*>(0) == status ) {
        logger->error( LOCATION, "Failed to write %s", fspc.c_str() ); 
      }
    }
    os.close();
  } else {
    if ( static_cast<int*>(0) == status ) {
      logger->error( LOCATION, "Cannot open file %s for writing.", fspc.c_str() ); 
    }
  }

  if ( static_cast<int*>(0) != status ) {
    *status = istat;
  }
  
  return istat;
}


// =======================================================================================
/** @brief Read INI File.
 *  @param[in]  fspc full path to a configuration file.
 *  @param[out] status optional return code.
 *  @return code.
 *
 *  Read the configuration from a file, and merge into this ConfigDB. If status is null
 *  error message will be written to the logger. If status is not null then now message
 *  will be written and a return code will be set. Either way the return code is returned
 *  in the normal manner.
 */
// ---------------------------------------------------------------------------------------
int ConfigDB::readINI( const std::string fspc, int* status ) {
  // -------------------------------------------------------------------------------------
  int istat = 0;
  std::ifstream is = FileTool::openRead( fspc, &istat );
  if ( 0 == istat ) {
    istat = readINI( is );
    if ( 0 < istat ) {
      if ( static_cast<int*>(0) == status ) {
        logger->error( LOCATION, "Failed to parse %s", fspc.c_str() ); 
      }
    }
    is.close();
  } else {
    if ( static_cast<int*>(0) == status ) {
      logger->error( LOCATION, "Cannot open file %s for reading.", fspc.c_str() ); 
    }
  }
  
  if ( static_cast<int*>(0) != status ) {
    *status = istat;
  }
  
  return istat;
}



// =======================================================================================
// **                                  C O N F I G D B                                  **
// ======================================================================== END FILE =====
