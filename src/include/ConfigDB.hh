// ====================================================================== BEGIN FILE =====
// **                                  C O N F I G D B                                  **
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


#ifndef __HH_CONFIGDB_TRNCMP
#define __HH_CONFIGDB_TRNCMP

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
 private:
  EMPTY_PROTOTYPE( ConfigDB );
  
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

    bool        getBool    ( std::string key );                             /**/
    int8_t      getInt8    ( std::string key );                             /**/
    int16_t     getInt16   ( std::string key );                             /**/
    int32_t     getInt32   ( std::string key );                             /**/
    int64_t     getInt64   ( std::string key );                             /**/
    u_int8_t    getUInt8   ( std::string key );                             /**/
    u_int16_t   getUInt16  ( std::string key );                             /**/
    u_int32_t   getUInt32  ( std::string key );                             /**/
    u_int64_t   getUInt64  ( std::string key );                             /**/
    size_t      getIndex   ( std::string key );                             /**/
    real4_t     getReal4   ( std::string key );                             /**/
    real8_t     getReal8   ( std::string key );                             /**/

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
  ~ConfigDB ( void );                                                      /**/

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
