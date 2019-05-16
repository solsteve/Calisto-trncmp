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
 *  Provides the interface for a configuration database based on a multi-level
 *  key value pair map.
 */
// =======================================================================================


#ifndef __CONFIGDB_TRNCMP_HH
#define __CONFIGDB_TRNCMP_HH

#include <trncmp.hh>
#include <TLogger.hh>
#include <vector>
#include <map>

typedef enum { SECTIONS, COMMENTS, ENTRIES } config_dim_type_e;

// =======================================================================================
/** @brief Configuration Database.
 *
 *  This class provides a configuration database of section key and value hierarchy.
 */
// ---------------------------------------------------------------------------------------
class ConfigDB {
  // -------------------------------------------------------------------------------------
 protected:
  
  TLOGGER_HEADER(logger); ///< reference to logger instance
  
  // -------------------------------------------------------------------------------------
  typedef enum {
  // -------------------------------------------------------------------------------------
    INI_UNKNOWN,
    INI_BLANK_LINE,
    INI_LINE_COMMENT,
    INI_SECTION_NAME,
    INI_OTHER_LINE,
    INI_EOF
  } ini_line_type;

 public:
  // =====================================================================================
  /** @brief .
   *
   *  .
   */
  // -------------------------------------------------------------------------------------
  class Entry {                                                         // ConfigDB::Entry
    // -----------------------------------------------------------------------------------
   protected:
    std::string key;
    std::string value;
    std::string comment;

   public:

    Entry  ( void );
    Entry  ( std::string ln );
    Entry  ( std::string k, std::string v );
    Entry  ( std::string k, std::string v, std::string c="" );
    ~Entry ( void );

    void        clear      ( void );
    void        copy       ( Entry* );
    void        set        ( std::string k, std::string v, std::string c="" );
    std::string toString   ( void );
    int         fromString ( std::string test );
   
    std::string getKey     ( void );
    std::string getValue   ( void );
    std::string getComment ( void );
    
    void        setKey     ( std::string );
    void        setValue   ( std::string );
    void        setComment ( std::string );
    
  }; // class ConfigDB::Entry


 public:
  // =====================================================================================
  /** @brief .
   *
   *  .
   */
  // -------------------------------------------------------------------------------------
  class Comments {                                                   // ConfigDB::Comments
    // -----------------------------------------------------------------------------------

   protected:
    std::vector<std::string>* array;

   public:
    Comments         ( void );
    ~Comments        ( void );

    size_t      size ( void );
    void        add  ( std::string c );
    std::string get  ( size_t i );

   private:
    Comments(const Comments&);
    Comments& operator=(const Comments&);
  }; // end class ConfigDB::Comments


 public:
  // =====================================================================================
  /** @brief .
   *
   *  .
   */
  // -------------------------------------------------------------------------------------
  class Section {                                                     // ConfigDB::Section
    // -----------------------------------------------------------------------------------
   protected:
    std::string                              sec_name;
    std::map<std::string, ConfigDB::Entry*>* sec_map;
    Comments*                                sec_comments;

   public:
    Section  ( std::string nm );
    ~Section ( void );
    
    // ----- direct --------------------------------------

    std::string getName    ( void );
    void        setName    ( std::string  );
    Comments*   comments   ( void );

    // ----- pass through --------------------------------






    

    
    bool        hasKey     ( std::string key );
    void        set        ( std::string key, std::string value, std::string comment = "" );
    std::string get        ( std::string key );
    
    void        add        ( Entry*   ent );
    void        merge      ( Section* sec );
    
    bool        writeINI   ( std::ostream& os );
    
   private:
    Section(const Section&);
    Section& operator=(const Section&);
    
  }; // end class ConfigDB::Section

 public:
  // =====================================================================================
  // CONFIGDB MAIN METHODS                                                        ConfigDB
  // =====================================================================================

 protected:
  std::map<std::string, ConfigDB::Section*>* sections;
  Comments*     file_comments;

  ini_line_type ParseLine_INI( std::string& ref, std::string* ret_val );
       

 public:
  ConfigDB  ( void );
  ConfigDB  ( std::string fspc );

  // ----- direct --------------------------------------

  bool        hasSection  ( std::string sname );
  Section*    get         ( std::string sname );
  Comments*   getComments ( void );

  void        merge      ( ConfigDB* cdb );

  int         writeINI   ( std::ostream& os );
  int         readINI    ( std::istream& is );

  int         writeINI   ( const std::string fspc, int* status );
  int         readINI    ( const std::string fspc, int* status );

  
  
  // ----- pass through --------------------------------
  
  Comments*   getComment ( std::string sname );

  bool        hasKey     ( std::string sname, std::string key );
  std::string get        ( std::string sname, std::string key );
  std::string getComment ( std::string sname, std::string key );

  void        set        ( std::string sname, std::string key,
                           std::string value, std::string comment = "" );
  
  void        merge      ( std::string sname, Section* sec );
}; // end class ConfigDB

  
size_t size( ConfigDB*          cfg, config_dim_type_e dim=SECTIONS );
size_t size( ConfigDB&          cfg, config_dim_type_e dim=SECTIONS );
size_t size( ConfigDB::Section* sec, config_dim_type_e dim=ENTRIES );
size_t size( ConfigDB::Section& sec, config_dim_type_e dim=ENTRIES );







// =======================================================================================
/** @brief
 *  @param
 *  @return
 *
 *
 */
// ---------------------------------------------------------------------------------------
inline  std::string ConfigDB::Entry::getKey( void ) {
  // -------------------------------------------------------------------------------------
  return key;
}

// =======================================================================================
/** @brief
 *  @param
 *  @return
 *
 *
 */
// ---------------------------------------------------------------------------------------
inline  std::string ConfigDB::Entry::getValue( void ) {
  // -------------------------------------------------------------------------------------
  return value;
}

// =======================================================================================
/** @brief
 *  @param
 *  @return
 *
 *
 */
// ---------------------------------------------------------------------------------------
inline  std::string ConfigDB::Entry::getComment( void ) {
  // -------------------------------------------------------------------------------------
  return comment;
}

// =======================================================================================
/** @brief
 *  @param
 *  @return
 *
 *
 */
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::Entry::setKey( const std::string k ) {
  // -------------------------------------------------------------------------------------
  key = k;
}

// =======================================================================================
/** @brief
 *  @param
 *  @return
 *
 *
 */
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::Entry::setValue( const std::string v ) {
  // -------------------------------------------------------------------------------------
  value = v;
}

// =======================================================================================
/** @brief
 *  @param
 *  @return
 *
 *
 */
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::Entry::setComment( const std::string c ) {
  // -------------------------------------------------------------------------------------
  comment = c;
}














#endif


// =======================================================================================
// **                                  C O N F I G D B                                  **
// ======================================================================== END FILE =====
