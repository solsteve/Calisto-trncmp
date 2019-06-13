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
#include <iterator>


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
  class NoSuchKey : public std::exception {                         // ConfigDB::NoSuchKey
    // -----------------------------------------------------------------------------------
   protected:
    std::string key;
    
   public:
    NoSuchKey( std::string k );
    virtual const char* what() const noexcept;
  }; // end class NoSuchKey;

  
  // =====================================================================================
  class NoSuchSection : public std::exception {                 // ConfigDB::NoSuchSection
    // -----------------------------------------------------------------------------------
   protected:
    std::string key;
    
   public:
    NoSuchSection( std::string k );
    virtual const char* what() const noexcept;
  }; // end class NoSuchSection;

  
 public:
  // =====================================================================================
  /** @brief Entry.
   *
   *  Basic record in Config Database.
   */
  // -------------------------------------------------------------------------------------
  class Entry {                                                         // ConfigDB::Entry
    // -----------------------------------------------------------------------------------
   protected:
    std::string key;
    std::string value;
    std::string comment;

   public:

    Entry                  ( std::string k, std::string v, std::string c="" );
    Entry                  ( std::string ln );
    Entry                  ( void );
    ~Entry                 ( void );

    void        clear      ( void );
    void        copy       ( Entry& src );
    void        copy       ( Entry* src );
    void        set        ( std::string k, std::string v, std::string c="" );
    std::string toString   ( void );
    int         fromString ( std::string test, bool report=true );
   
    std::string getKey     ( void );
    std::string getValue   ( void );
    std::string getComment ( void );
    
    void        setKey     ( std::string );
    void        setValue   ( std::string );
    void        setComment ( std::string );

  }; // class ConfigDB::Entry



  
 public:
  // =====================================================================================
  /** @brief Comments.
   *
   *  Table of comments.
   */
  // -------------------------------------------------------------------------------------
  class Comments {                                                   // ConfigDB::Comments
    // -----------------------------------------------------------------------------------

   protected:
    std::vector<std::string>*          array;
    std::vector<std::string>::iterator com_it;

   public:
    Comments            ( void );
    ~Comments           ( void );

    size_t      size    ( void );
    void        add     ( std::string c );
    std::string get     ( size_t i );

    bool        isIn    ( std::string c );

    void        rewind  ( void );
    bool        hasNext ( void );
    std::string next    ( void );

   private:
    EMPTY_PROTOTYPE(Comments);
  }; // end class ConfigDB::Comments





  
  

 public:
  // =====================================================================================
  /** @brief Section.
   *
   *  The ConfigDB is divided into named sections.
   */
  // -------------------------------------------------------------------------------------
  class Section {                                                     // ConfigDB::Section
    // -----------------------------------------------------------------------------------
   protected:
    std::string                                       sec_name;
    Comments*                                         sec_comments;
    std::map<std::string, ConfigDB::Entry*>*          sec_map;
    std::map<std::string, ConfigDB::Entry*>::iterator sec_map_it;

    Comments*   comments   ( void );                                        /**/

   public:
    Section  ( std::string nm );                                            /**/
    ~Section ( void );                                                      /**/
    
    std::string getName    ( void );                                        /**/
    void        setName    ( std::string nm );                              /**/

    size_t      size       ( config_dim_type_e dim=ENTRIES );               /**/

    bool        hasKey     ( std::string key );                             /**/
    void        set        ( std::string key,
                             std::string value, std::string comment = "" ); /**/
    std::string get        ( std::string key );                             /**/
    std::string getComment ( std::string key );                             /**/

    void        add        ( Entry&   ent );                                /**/
    void        add        ( Entry*   ent );                                /**/
    void        merge      ( Section& sec );                                /**/
    void        merge      ( Section* sec );                                /**/

    bool        writeINI   ( std::ostream& os );                            /**/

    void        addComment ( std::string c );                               /**/
    std::string getComment ( size_t i );                                    /**/
    
    void        rewind     ( void );                                        /**/
    bool        hasNext    ( void );                                        /**/
    bool        next       ( Entry& ent );                                  /**/
    bool        next       ( Entry* ent ); // makes copy                    /**/

   private:
    EMPTY_PROTOTYPE( Section );
    
  }; // end class ConfigDB::Section



  
 public:
  // =====================================================================================
  // CONFIGDB MAIN METHODS                                                        ConfigDB
  // =====================================================================================

 protected:
  Comments*                                           file_comments;
  std::map<std::string, ConfigDB::Section*>*          sections;
  std::map<std::string, ConfigDB::Section*>::iterator sec_it;

  ini_line_type ParseLine_INI( std::string& ref, std::string* ret_val );   /**/
       
  Comments*   comments    ( void );                                        /**/

 public:
  ConfigDB  ( void );                                                      /**/
  ConfigDB  ( std::string fspc );                                          /**/

  // ----- direct --------------------------------------

  size_t      size        ( config_dim_type_e dim=SECTIONS );              /**/

  bool        hasSection  ( std::string sname );                           /**/
  Section*    get         ( std::string sname );                           /**/

  void        addComment  ( std::string com );                             /**/
  std::string getComment  ( size_t      idx );                             /**/
  std::string getComment  ( std::string sname, size_t idx );               /**/

  void        add         ( std::string sname );                           /**/
  void        add         ( Section&    sec );                             /**/
  void        add         ( Section*    sec );                             /**/

  bool        hasKey      ( std::string sname, std::string key );          /**/

  void        set         ( std::string sname, std::string key,
                            std::string value, std::string comment = "" ); /**/
  void        addComment  ( std::string sname, std::string com );          /**/

  std::string get         ( std::string sname, std::string key );          /**/
  std::string getComment  ( std::string sname, std::string key );          /**/

  void        rewind      ( void );                                        /**/
  bool        hasNext     ( void );                                        /**/
  std::string next        ( void );                                        /**/

  void        merge       ( ConfigDB&   cdb );                             /**/
  void        merge       ( ConfigDB*   cdb );                             /**/

  int         writeINI    ( std::ostream& os );                            /**/
  int         readINI     ( std::istream& is );                            /**/

  int         writeINI    ( const std::string fspc, int* status = 0 );     /**/
  int         readINI     ( const std::string fspc, int* status = 0 );     /**/

}; // end class ConfigDB

  
size_t size( ConfigDB*          cfg, config_dim_type_e dim=SECTIONS );
size_t size( ConfigDB&          cfg, config_dim_type_e dim=SECTIONS );
size_t size( ConfigDB::Section* sec, config_dim_type_e dim=ENTRIES );
size_t size( ConfigDB::Section& sec, config_dim_type_e dim=ENTRIES );



// =======================================================================================
/** @brief Copy.
 *  @param[in] src pointer to a source Entry.
 */
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::Entry::copy( ConfigDB::Entry* src ) {
  // -------------------------------------------------------------------------------------
  this->copy( *src );
}


// =======================================================================================
/** @brief Get Key.
 *  @return key.
 */
// ---------------------------------------------------------------------------------------
inline  std::string ConfigDB::Entry::getKey( void ) {
  // -------------------------------------------------------------------------------------
  return key;
}


// =======================================================================================
/** @brief Get Value.
 *  @return value.
 */
// ---------------------------------------------------------------------------------------
inline  std::string ConfigDB::Entry::getValue( void ) {
  // -------------------------------------------------------------------------------------
  return value;
}


// =======================================================================================
/** @brief Get Comment.
 *  @return comment.
 */
// ---------------------------------------------------------------------------------------
inline  std::string ConfigDB::Entry::getComment( void ) {
  // -------------------------------------------------------------------------------------
  return comment;
}


// =======================================================================================
/** @brief Set Key.
 *  @param[in] k key.
 */
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::Entry::setKey( const std::string k ) {
  // -------------------------------------------------------------------------------------
  key = k;
}


// =======================================================================================
/** @brief Set Value.
 *  @param[in] v value.
 */
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::Entry::setValue( const std::string v ) {
  // -------------------------------------------------------------------------------------
  value = v;
}


// =======================================================================================
/** @brief Set Comment
 *  @param[in] c comment.
 */
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::Entry::setComment( const std::string c ) {
  // -------------------------------------------------------------------------------------
  comment = c;
}








// =======================================================================================
/** @brief Size.
 *  @return number of comments.
 *
 *  Return the number of comment lines stored in this class.
 */
// ---------------------------------------------------------------------------------------
inline  size_t ConfigDB::Comments::size( void ) {
  // -------------------------------------------------------------------------------------
  return array->size();
}


// =======================================================================================
/** @brief Add.
 *  @param[in] c comment string.
 *
 *  Append a new comment line to this class.
 */
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::Comments::add( std::string c ) {
  // -------------------------------------------------------------------------------------
  array->push_back( c );
}








// =======================================================================================
/** @brief Get Name.
 *  @return the name of this section.
 *
 *  Get the name of this section.
 */
// ---------------------------------------------------------------------------------------
inline  std::string ConfigDB::Section::getName( void ) {
  // -------------------------------------------------------------------------------------
  return this->sec_name;
}


// =======================================================================================
/** @brief Set Name.
 *  @param[in] nm new name for this section.
 *
 *  Rename this section.
 */
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::Section::setName( std::string nm ) {
  // -------------------------------------------------------------------------------------
  this->sec_name = nm;
}


// =======================================================================================
/** @brief Get Comment Pointer.
 *  @return pointer to this section's comments.,
 *
 *  Recover the pointer to this section's comments.
 *  @note this is meant for library routines and should not be used directly.
 */
// ---------------------------------------------------------------------------------------
inline  ConfigDB::Comments* ConfigDB::Section::comments( void ) {
  // -------------------------------------------------------------------------------------
  return this->sec_comments;
}


// =======================================================================================
/** @brief Add.
 *  @param[in] c comment string.
 *
 *  Append a new comment line to this class.
 */
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::Section::addComment( std::string c ) {
  // -------------------------------------------------------------------------------------
  sec_comments->add( c );
}


// =======================================================================================
/** @brief Get by Index.
 *  @param[in] i index.
 *  @return comment at index.
 *
 *  Return the comment at the index.
 */
// ---------------------------------------------------------------------------------------
inline  std::string ConfigDB::Section::getComment( size_t i ) {
  // -------------------------------------------------------------------------------------
  return sec_comments->get( i );
}


// =======================================================================================
/** @brief Add Entry.
 *  @param[in] ent reference to an entry
 *
 *  If an entry exists associated with the key then update the value with val, otherwise
 *  create a new entry.
 */
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::Section::add( ConfigDB::Entry& ent ) {
  // -------------------------------------------------------------------------------------
  set( ent.getKey(), ent.getValue(), ent.getComment() );
}


// =======================================================================================
/** @brief Add Entry.
 *  @param[in] ent reference to an entry
 *
 *  If an entry exists associated with the key then update the value with val, otherwise
 *  create a new entry.
 */
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::Section::add( ConfigDB::Entry* ent ) {
  // -------------------------------------------------------------------------------------
  add( *ent );
}


// =======================================================================================
/** @brief Get Next Entry.
 *  @param[inout] ent pointer to an entry object.
 *  @return true is entry was returned.
 *
 *  Retrieve a copy of the next entry in this section. If an entry is found then the
 *  contents are copyied into argP: ent and this function returns a true. If no entry was
 *  found then this function returns a false and the arg entry contents remain unchanged.
 */
// ---------------------------------------------------------------------------------------
inline  bool ConfigDB::Section::next( ConfigDB::Entry* ent ) {
  // -------------------------------------------------------------------------------------
  return next( *ent );
}


// =======================================================================================
/** @brief Merge.
 *  @param[in] reference to a source section.
 *
 *  Merge copies of the entries and comments from the source section into this one.
 */
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::Section::merge( ConfigDB::Section* sec ) {
  // -------------------------------------------------------------------------------------
  merge( *sec );
}








// =======================================================================================
/** @brief Get Comment Pointer.
 *  @return pointer to this configuration's comments.
 *
 *  Recover the pointer to this configuration's comments.
 *  @note this is meant for library routines and should not be used directly.
 */
// ---------------------------------------------------------------------------------------
inline  ConfigDB::Comments* ConfigDB::comments( void ) {
  // -------------------------------------------------------------------------------------
  return this->file_comments;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  bool ConfigDB::hasKey( std::string sname, std::string key ) {
  // -------------------------------------------------------------------------------------
  return this->get( sname )->hasKey( key );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  std::string ConfigDB::get( std::string sname, std::string key ) {
  // -------------------------------------------------------------------------------------
  return this->get( sname )->get( key );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  std::string ConfigDB::getComment( std::string sname, std::string key ) {
  // -------------------------------------------------------------------------------------
  return this->get( sname )->getComment( key );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  std::string ConfigDB::getComment( std::string sname, size_t i ) {
  // -------------------------------------------------------------------------------------
  return this->get( sname )->getComment( i );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::addComment( std::string com ) {
  // -------------------------------------------------------------------------------------
  this->file_comments->add( com );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  std::string ConfigDB::getComment( size_t idx ) {
  // -------------------------------------------------------------------------------------
  return this->file_comments->get( idx );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  void ConfigDB::addComment( std::string sname, std::string com ) {
  // -------------------------------------------------------------------------------------
  this->add( sname );
  this->get( sname )->addComment( com );
}









#endif


// =======================================================================================
// **                                  C O N F I G D B                                  **
// ======================================================================== END FILE =====
