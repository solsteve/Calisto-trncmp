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
 *  Provides the methods for a configuration database based on a multi-level
 *  key value pair map.
 */
// =======================================================================================


#include <ConfigDB.hh>
#include <StringTool.hh>
#include <FileTool.hh>
#include <sstream>


TLOGGER_REFERENCE( ConfigDB, logger );


// =======================================================================================
// ---------------------------------------------------------------------------------------
ConfigDB::NoSuchKey::NoSuchKey( std::string k ) : std::exception(), key(k) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
const char* ConfigDB::NoSuchKey::what() const noexcept {
  // -------------------------------------------------------------------------------------
  static char message[64];
  snprintf( message, 63, "No such key: %s", key.c_str() );
  return message;
}




// =======================================================================================
// ---------------------------------------------------------------------------------------
ConfigDB::NoSuchSection::NoSuchSection( std::string k ) : std::exception(), key(k) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
const char* ConfigDB::NoSuchSection::what() const noexcept {
  // -------------------------------------------------------------------------------------
  static char message[64];
  snprintf( message, 63, "No such section: [%s]", key.c_str() );
  return message;
}




// =======================================================================================
/** @brief Constructor.
 *  @param[in] k key.
 *  @param[in] v value.
 *  @param[in] c optional comment.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::Entry::Entry( std::string k, std::string v, std::string c )
    : key(k), value(v), comment(c) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
ConfigDB::Entry::Entry( std::string ln ) : key(), value(), comment() {
  // -------------------------------------------------------------------------------------
  fromString( ln );
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::Entry::Entry( void ) : key(), value(), comment() {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 *
 *  Clean up allocations.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::Entry::~Entry( void ) {
  // -------------------------------------------------------------------------------------
  clear();
}


// =======================================================================================
/** @brief
 */
// ---------------------------------------------------------------------------------------
void ConfigDB::Entry::clear( void ) {
  // -------------------------------------------------------------------------------------
  key.erase();
  value.erase();
  comment.erase();
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] src pointer to a source Entry.
 */
// ---------------------------------------------------------------------------------------
void ConfigDB::Entry::copy( ConfigDB::Entry& src ) {
  // -------------------------------------------------------------------------------------
  this->key     = src.key;
  this->value   = src.value;
  this->comment = src.comment;
}


// =======================================================================================
/** @brief Set All.
 *  @param[in] k key.
 *  @param[in] v value.
 *  @param[in] c comment.
 *
 */
// ---------------------------------------------------------------------------------------
void ConfigDB::Entry::set( std::string k, std::string v, std::string c ) {
  // -------------------------------------------------------------------------------------
  this->key     = k;
  this->value   = v;
  this->comment = c;
}


// =======================================================================================
/** @brief
 *  @return
 *
 *  Format a Entry
 */
// ---------------------------------------------------------------------------------------
std::string ConfigDB::Entry::toString( void ) {
  // -------------------------------------------------------------------------------------
  if ( 0 < key.size() ) {
    std::stringbuf    buffer;
    std::ostream os (&buffer);
    
    os << key << " = " << value;
    
    if ( 0 < comment.size() ) {
      os << " ; " << comment;
    }
    
    return buffer.str();
  }

  return "";
  //return "<EMPTY>";
}


// =======================================================================================
/** @brief PArse from a String.
 *  @param[in] test parsable string.
 *  @param[in] report include use of the logger.
 *  @return non zero on failure.
 */
// ---------------------------------------------------------------------------------------
int ConfigDB::Entry::fromString( std::string test, bool report ) {
  // -------------------------------------------------------------------------------------
  if ( 0 == StringTool::trim( test ).size() ) {
    if ( report ) {
      logger->error( "Line {%s} appears to be empty", test.c_str() );
    }
    return 1;    
  }
  
  size_t sep = test.find_first_of("=:");

  if ( std::string::npos == sep ) {
    if ( report ) {
      logger->error( "Line {%s} is not parsable. It must contain an = or :", test.c_str() );
    }
    return 2;
  }

  key = StringTool::trim( test.substr( 0, sep ) );
  if ( 0 == key.size() ) {
    if ( report ) {
      logger->error( "Line {%s} does not appear to contain a key", test.c_str() );
    }
    return 3;    
  }
  
  std::string rhs = StringTool::trim( test.substr( sep+1 ) );
  if ( 0 == rhs.size() ) {
    if ( report ) {
      logger->error( "Line {%s} does not appear to have data after =", test.c_str() );
    }
    return 4;    
  }

  std::string temp_value;
  sep = rhs.find( ';', 0 );
  if (std::string::npos == sep) { // ----- no comments -----------------------------
    temp_value = StringTool::trim( rhs );
  } else {
    temp_value   = StringTool::trim( rhs.substr( 0, sep ));

    comment = StringTool::trim( rhs.substr( sep+1 ) );
    if ( 0 == comment.size() ) {
      if ( report ) {
        logger->warn( "Line {%s} comment is empty", test.c_str() );
        comment.erase();
      }
    }
  }

  if (( '"' == temp_value[0] ) ||
      ( '\'' == temp_value[0] )) { // ----- value may be in quotes --------------------

    value = StringTool::containedBy( temp_value, "'\"", "'\"" );
    if ( 0 == value.size() ) {
      if ( report ) {
        logger->error( "Line {%s} quotes contain no value", test.c_str() );
      }
      return 5;    
    }
  } else {
    value = temp_value;
  }

  if ( 0 == value.size() ) {
    if ( report ) {
      logger->error( "Line {%s} no value", test.c_str() );
    }
    return 6;    
  }

  return 0;
}








// =======================================================================================
/** @brief Constructor.
 *
 *  Allocates a vector of strings to store comments.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::Comments::Comments( void ) : array(0), com_it() {
  // -------------------------------------------------------------------------------------
  array = new std::vector<std::string>();
}


// =======================================================================================
/** @brief Destructor.
 *
 *  deallocates comment vector.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::Comments::~Comments( void ) {
  // -------------------------------------------------------------------------------------
  delete array;
}


// =======================================================================================
/** @brief Get by Index.
 *  @param[in] i index.
 *  @return comment at index.
 *
 *  Return the comment at the index.
 */
// ---------------------------------------------------------------------------------------
std::string ConfigDB::Comments::get( size_t i ) {
  // -------------------------------------------------------------------------------------
  if ( i+1 > array->size() ) {
    std::string msg( c_fmt( "Expected index less than %d Got ", array->size() ) );
    msg.append( c_fmt( "%d", i ) );
    throw( std::out_of_range( msg ) );
  }
  
  return array->at(i);
}


// =======================================================================================
/** @brief Is In.
 *  @param[in] c test string.
 *  @return true if test string matches one of the section comments.
 *
 *  Determine if a comment already exists.
 */
// ---------------------------------------------------------------------------------------
bool ConfigDB::Comments::isIn( std::string c ) {
  // -------------------------------------------------------------------------------------
  for ( std::vector<std::string>::iterator it=array->begin() ;
        it != array->end() ; ++it ) {
    if ( 0 == c.compare( *it ) ) {
      return true;
    }
  }
  return false;
}


// =======================================================================================
/** @brief Rewind.
 *
 *  Rewind the section comment iterator.
 */
// ---------------------------------------------------------------------------------------
void ConfigDB::Comments::rewind( void ) {
  // -------------------------------------------------------------------------------------
  com_it = array->begin();
}


// =======================================================================================
/** @brief Has Next.
 *  @return true if the iterator will produce more comments.
 *
 *  Check if more comments can be retrieved by the comment iterator.
 */
// ---------------------------------------------------------------------------------------
bool ConfigDB::Comments::hasNext( void ) {
  // -------------------------------------------------------------------------------------
  if ( com_it == array->end() ) {
    return false;
  }
  return true;  
}


// =======================================================================================
/** @brief Get Next.
 *  @return a copy of the next section comment.
 *
 *  Request the next section comment.
 */
// ---------------------------------------------------------------------------------------
std::string ConfigDB::Comments::next( void ) {
  // -------------------------------------------------------------------------------------
  if ( com_it == array->end() ) {
    return "";
  }
  return std::string( *com_it++ );
}













// =======================================================================================
/** @brief Construction.
 *  @param[in] nm section name.
 *
 *  Construct a named section.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::Section::Section( std::string nm )
    : sec_name(nm), sec_comments(0), sec_map(0), sec_map_it() {
  // -------------------------------------------------------------------------------------
  sec_map      = new std::map<std::string, ConfigDB::Entry*>();
  sec_comments = new ConfigDB::Comments();
}


// =======================================================================================
/** @brief Destructor.
 *
 *  Release allocation.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::Section::~Section( void ) {
  // -------------------------------------------------------------------------------------
  sec_name.erase();
  delete sec_map;
  delete sec_comments;

  sec_map      = static_cast<std::map<std::string, ConfigDB::Entry*>*>(0);
  sec_comments = static_cast<ConfigDB::Comments*>(0);
}


// =======================================================================================
/** @brief Size.
 *  @param[in] dim which size to return (default: number of key/value pairs)
 *  @return requested size.
 *
 *  By defualt return the number of key/value pairs in this section.
 *  If dim is present return either the number of key/value pair or the number of
 *  comment lines.
 */
// ---------------------------------------------------------------------------------------
size_t ConfigDB::Section::size( config_dim_type_e dim ) {
  // -------------------------------------------------------------------------------------
  size_t sz = 0;
  
  switch( dim ) {
    default:
    case SECTIONS:
      throw( std::invalid_argument( EXPECTED( "Unsupported DIM",
                                              "COMMENTS or ENTRIES",
                                              "SECTIONS" ) ) );
    case COMMENTS:
      sz = sec_comments->size();
      break;

    case ENTRIES:
      sz = sec_map->size();
      break;
  }

  return sz;
}


// =======================================================================================
/** @brief Has Key.
 *  @param[in] key test key.
 *  @return true if a record exists associated with the key.
 *
 *  Check to see if there is a record associated with the supplied key.
 */
// ---------------------------------------------------------------------------------------
bool ConfigDB::Section::hasKey( std::string key ) {
  // -------------------------------------------------------------------------------------
  return ( sec_map->end() == sec_map->find( key ) ? (false) : (true) );
}


// =======================================================================================
/** @brief Set Value.
 *  @param[in] key key.
 *  @param[in] val value.
 *  @param[in] com comment (default: null).
 *
 *  If an entry exists associated with the key then update the value with val, otherwise
 *  create a new entry.
 */
// ---------------------------------------------------------------------------------------
void ConfigDB::Section::set( std::string key, std::string val, std::string com ) {
  // -------------------------------------------------------------------------------------
  (*sec_map)[ key ] = new Entry( key, val, com );
}


// =======================================================================================
/** @brief Get Value.
 *  @param[in] key key.
 *  @return value associated with key.
 *
 *  Return the value of an entry associated with key.
 */
// ---------------------------------------------------------------------------------------
std::string ConfigDB::Section::get( std::string key ) {
  // -------------------------------------------------------------------------------------
  try {
    Entry* ent = sec_map->at( key );
    return ent->getValue();
  } catch( std::out_of_range& e ) {
    throw ConfigDB::NoSuchKey( key );
  }
  return "";
}


// =======================================================================================
/** @brief Get Value.
 *  @param[in] key key.
 *  @return comment associated with key.
 *
 *  Return the comment of an entry associated with key.
 */
// ---------------------------------------------------------------------------------------
std::string ConfigDB::Section::getComment( std::string key ) {
  // -------------------------------------------------------------------------------------
  try {
    Entry* ent = sec_map->at( key );
    return ent->getComment();
  } catch( std::out_of_range& e ) {
    throw ConfigDB::NoSuchKey( key );
  }
  return "";
}


// =======================================================================================
/** @brief Rewind Entry Iterator.
 *
 *  Reinitialize the entry iterator regardless of its current state. The next call to
 *  next will retirive a copy of the first Entry in this Section.
 */
// ---------------------------------------------------------------------------------------
void ConfigDB::Section::rewind( void ) {
  // -------------------------------------------------------------------------------------
  sec_map_it = sec_map->begin();
}


// =======================================================================================
/** @brief Has Next Entry.
 *  @return true is an entry is available.
 *
 *  If there is another entry avaiable return a true without actually retrieving a copy.
 */
// ---------------------------------------------------------------------------------------
bool ConfigDB::Section::hasNext( void ) {
  // -------------------------------------------------------------------------------------
  if ( sec_map_it == sec_map->end() ) {
    return false;
  }
  return true;
}


// =======================================================================================
/** @brief Get Next Entry.
 *  @param[inout] ent reference to an entry object.
 *  @return true is entry was returned.
 *
 *  Retrieve a copy of the next entry in this section. If an entry is found then the
 *  contents are copyied into argP: ent and this function returns a true. If no entry was
 *  found then this function returns a false and the arg entry contents remain unchanged.
 */
// ---------------------------------------------------------------------------------------
bool ConfigDB::Section::next( ConfigDB::Entry& ent ) {
  // -------------------------------------------------------------------------------------
  if ( sec_map_it == sec_map->end() ) {
    return false;
  }
  ent.copy( sec_map_it->second );
  ++sec_map_it;
  return true;
}


// =======================================================================================
/** @brief Merge.
 *  @param[in] reference to a source section.
 *
 *  Merge copies of the entries and comments from the source section into this one.
 */
// ---------------------------------------------------------------------------------------
void ConfigDB::Section::merge( ConfigDB::Section& sec ) {
  // -------------------------------------------------------------------------------------
  ConfigDB::Entry ent;
  sec.rewind();
  while( sec.next(ent) ) {
    add( ent );
  }
  
  ConfigDB::Comments* com = sec.comments();
    
  com->rewind();

  while ( com->hasNext() ) {
    std::string test = com->next();
    if ( ! sec_comments->isIn( test ) ) {
      addComment( test );
    }
  }

}


// =======================================================================================
/** @brief Write INI File.
 *  @param[in] os reference to an oiutput stream.
 *  @return true if error occurs.
 */
// ---------------------------------------------------------------------------------------
bool ConfigDB::Section::writeINI( std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  sec_comments->rewind();

  os << "[" << getName() << "]\n";
  
  while ( sec_comments->hasNext() ) {
    os << "  ; " << sec_comments->next() << "\n";
  }

  ConfigDB::Entry ent;

  rewind();

  while( next(ent) ) {
    os << "  " << ent.toString() << "\n";
  }

  os << "\n";

  return false;
}








// =======================================================================================
/** @brief Constructor.
 *
 *  Construct an empty ConfigDB instance.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::ConfigDB( void ) : file_comments(0), sections(0), sec_it() {
  // -------------------------------------------------------------------------------------
  sections      = new std::map<std::string, ConfigDB::Section*>();
  file_comments = new ConfigDB::Comments();
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] fspc path to a configuration file.
 *
 *  Construct an empty ConfigDB instance, and parse the file at fspc.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::ConfigDB( const std::string fspc ) : file_comments(0), sections(0), sec_it() {
  // -------------------------------------------------------------------------------------
  sections      = new std::map<std::string, ConfigDB::Section*>();
  file_comments = new ConfigDB::Comments();
  readINI( fspc, static_cast<int*>(0) );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::~ConfigDB( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<Comments*>(0) == file_comments ) {
    logger->debug( "ConfigDB::~ConfigDB - free file_comments" );
    delete file_comments;
  }

  if ( 0 == sections ) {
    logger->debug( "ConfigDB::~ConfigDB - free sections" );
    delete sections;
  }
}


// =======================================================================================
/** @brief Has Section.
 *  @param[in] sname test section name.
 *  @return true if a section exists associated with the section name.
 *
 *  Check to see if there is a section associated with the supplied name.
 */
// ---------------------------------------------------------------------------------------
bool ConfigDB::hasSection( std::string sname ) {
  // -------------------------------------------------------------------------------------
  return ( sections->end() == sections->find( sname ) ? (false) : (true) );
}


// =======================================================================================
/** @brief Add Section.
 *  @param[in] sname name of the new (or existing) section.
 *
 *  Add a new empty section. If a section with this name exists no action is taken.
 */
// ---------------------------------------------------------------------------------------
void  ConfigDB::add( std::string sname ) {
  // -------------------------------------------------------------------------------------
  if ( ! hasSection( sname ) ) {
    (*sections)[sname] = new ConfigDB::Section( sname );
  }
}


// =======================================================================================
/** @brief Add Section.
 *  @param[in] sec reference to a source section
 *
 *  Check this configuration for a section with the same name as the source. If found
 *  merge the source into it. If not create a new section as a copy of the source.
 */
// ---------------------------------------------------------------------------------------
void  ConfigDB::add( ConfigDB::Section& sec ) {
  // -------------------------------------------------------------------------------------
  std::string sname = sec.getName();
  add( sname );
  get( sname )->merge( sec );
}


// =======================================================================================
/** @brief Add Section.
 *  @param[in] sec reference to a source section
 *
 *  Check this configuration for a section with the same name as the source. If found
 *  merge the source into it. If not create a new section as a copy of the source.
 */
// ---------------------------------------------------------------------------------------
void  ConfigDB::add( ConfigDB::Section* sec ) {
  // -------------------------------------------------------------------------------------
  add( *sec );
}



// =======================================================================================
/** @brief Get Value.
 *  @param[in] key key.
 *  @return value associated with key.
 *
 *  Return the value of an entry associated with key.
 */
// ---------------------------------------------------------------------------------------
ConfigDB::Section* ConfigDB::get( std::string sname ) {
  // -------------------------------------------------------------------------------------
  try {
    return sections->at( sname );
  } catch( std::out_of_range& e ) {
    throw ConfigDB::NoSuchSection( sname );
  }
  return static_cast<ConfigDB::Section*>(0);
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void ConfigDB::set( std::string sname, std::string key,
                    std::string value, std::string comment ) {
  // -------------------------------------------------------------------------------------
  if ( ! hasSection( sname ) ) {
    add( sname );
  }
  get( sname )->set( key, value, comment );
}


// =======================================================================================
/** @brief Size.
 *  @param[in] dim which size to return (default: number of sectionss)
 *  @return requested size.
 *
 *  By defualt return the number of sections in this configuration.
 *  If dim is present return either the number of sections or the number of
 *  comment lines.
 */
// ---------------------------------------------------------------------------------------
size_t ConfigDB::size( config_dim_type_e dim ) {
  // -------------------------------------------------------------------------------------
  size_t sz = 0;
  
  switch( dim ) {
    default:
    case ENTRIES:
      throw( std::invalid_argument( EXPECTED( "Unsupported DIM",
                                              "COMMENTS or SECTIONS",
                                              "ENTRIES" ) ) );
    case COMMENTS:
      sz = file_comments->size();
      break;

    case SECTIONS:
      sz = sections->size();
      break;
  }

  return sz;
}


// =======================================================================================
/** @brief Rewind.
 *
 *  Rewind the section iterator.
 */
// ---------------------------------------------------------------------------------------
void ConfigDB::rewind( void ) {
  // -------------------------------------------------------------------------------------
  sec_it = sections->begin();
}


// =======================================================================================
/** @brief Has Next.
 *  @return true if the iterator will produce more section names.
 *
 *  Check if more section names can be retrieved by the section iterator.
 */
// ---------------------------------------------------------------------------------------
bool ConfigDB::hasNext( void ) {
  // -------------------------------------------------------------------------------------
  if ( sec_it == sections->end() ) {
    return false;
  }
  return true;  
}


// =======================================================================================
/** @brief Get Next.
 *  @return then name of the next section referenced by the iterator.
 *
 *  Request the next section name in the iteration.
 */
// ---------------------------------------------------------------------------------------
std::string ConfigDB::next( void ) {
  // -------------------------------------------------------------------------------------
  if ( sec_it == sections->end() ) {
    return "";
  }

  std::string sn = (*sec_it++).second->getName();
  return sn;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void ConfigDB::merge( ConfigDB& cdb ) {
  // -------------------------------------------------------------------------------------
  ConfigDB::Comments* com = cdb.comments();
    
  com->rewind();

  while ( com->hasNext() ) {
    std::string test = com->next();
    if ( ! file_comments->isIn( test ) ) {
      file_comments->add( test );
    }
  }

  cdb.rewind();
  while ( cdb.hasNext() ) {
    std::string sname = cdb.next();
    ConfigDB::Section* sec = cdb.get( sname );
    add( sec );
  }
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void ConfigDB::merge( ConfigDB* cdb ) {
  // -------------------------------------------------------------------------------------
  merge( *cdb );
}


// =======================================================================================
/** @brief Write INI File.
 *  @param[in] os output stream to write on.
 *  @return code.
 *
 *  Write the configuration onto an output stream.
 */
// ---------------------------------------------------------------------------------------
int ConfigDB::writeINI( std::ostream& os ) {
  // -------------------------------------------------------------------------------------

  // ----- write file level comments -------------------------

  if ( static_cast<Comments*>(0) != file_comments ) {
    size_t nc = file_comments->size();
    for ( size_t i=0; i<nc; i++ ) {
      os << "; " << file_comments->get(i) << "\n";
    }
  }

  rewind();

  while( hasNext() ) {
    std::string sname = next();
    get( sname )->writeINI( os );
  }
  
  return 0;
}



// =======================================================================================
/** @brief Read INI File.
 *  @param[in] is input stream to read from.
 *  @return code.
 *
 *  Read the configuration from an input stream. This function may be called multiple
 *  times. Each time will add to the current ConfigDB.
 */
// ---------------------------------------------------------------------------------------
int ConfigDB::readINI( std::istream& is ) {
  // -------------------------------------------------------------------------------------
  char buffer[512];
  std::string sname;
  bool        inSection = false;

  while( ! is.eof() ) {
    is.getline( buffer, 512 );
    std::string line = StringTool::trim( buffer );
    if ( 0 < line.size() ) {
      switch(line[0]) {
        // ----- new sction name ---------------------------------------------------------
        case '[':
        case '{':
        case '(': {
          sname     = StringTool::containedBy( line, "[{(", "}}]" );
          inSection = true;
          add( sname );
        } break;
          
          // ----- comment line ----------------------------------------------------------        
        case ';':
        case '!':
        case '#': {
          std::string com = StringTool::trim( line.substr( 1 ) );
          if ( inSection ) {
            addComment( sname, com );
          } else {
            addComment( com );
          }
        } break;
          
          // ----- possible KVC ----------------------------------------------------------         
        default: {
          Entry ent(line);
          set( sname, ent.getKey(), ent.getValue(), ent.getComment() );
        } break;
      }
    }
  }
  return 0;
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
/** Get Bool.
 *  @param key string key to map the results.
 *  @return value stored with the key.
 *
 *  Returns the value stored with the key as a Bool.
 */
// ---------------------------------------------------------------------------------------
bool ConfigDB::Section::getBool( std::string key ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asBool( this->get( key ) );
}


// =======================================================================================
/** Get Int8.
 *  @param key string key to map the results.
 *  @return value stored with the key.
 *
 *  Returns the value stored with the key as a .
 */
// ---------------------------------------------------------------------------------------
int8_t ConfigDB::Section::getInt8( std::string key ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asInt8( this->get( key ) );
}


// =======================================================================================
/** Get Int16.
 *  @param key string key to map the results.
 *  @return value stored with the key.
 *
 *  Returns the value stored with the key as a Int16.
 */
// ---------------------------------------------------------------------------------------
int16_t ConfigDB::Section::getInt16( std::string key ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asInt16( this->get( key ) );
}


// =======================================================================================
/** Get Int32.
 *  @param key string key to map the results.
 *  @return value stored with the key.
 *
 *  Returns the value stored with the key as a Int32.
 */
// ---------------------------------------------------------------------------------------
int32_t ConfigDB::Section::getInt32( std::string key ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asInt32( this->get( key ) );
}


// =======================================================================================
/** Get Int64.
 *  @param key string key to map the results.
 *  @return value stored with the key.
 *
 *  Returns the value stored with the key as a Int64.
 */
// ---------------------------------------------------------------------------------------
int64_t ConfigDB::Section::getInt64( std::string key ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asInt64( this->get( key ) );
}


// =======================================================================================
/** Get UInt8.
 *  @param key string key to map the results.
 *  @return value stored with the key.
 *
 *  Returns the value stored with the key as a UInt8.
 */
// ---------------------------------------------------------------------------------------
uint8_t ConfigDB::Section::getUInt8( std::string key ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asUInt8( this->get( key ) );
}


// =======================================================================================
/** Get UInt16.
 *  @param key string key to map the results.
 *  @return value stored with the key.
 *
 *  Returns the value stored with the key as a UInt16.
 */
// ---------------------------------------------------------------------------------------
uint16_t ConfigDB::Section::getUInt16( std::string key ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asUInt16( this->get( key ) );
}


// =======================================================================================
/** Get UInt32.
 *  @param key string key to map the results.
 *  @return value stored with the key.
 *
 *  Returns the value stored with the key as a UInt32.
 */
// ---------------------------------------------------------------------------------------
uint32_t ConfigDB::Section::getUInt32( std::string key ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asUInt32( this->get( key ) );
}


// =======================================================================================
/** Get UInt64.
 *  @param key string key to map the results.
 *  @return value stored with the key.
 *
 *  Returns the value stored with the key as a UInt64.
 */
// ---------------------------------------------------------------------------------------
uint64_t ConfigDB::Section::getUInt64( std::string key ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asUInt64( this->get( key ) );
}


// =======================================================================================
/** Get .
 *  @param key string key to map the results.
 *  @return value stored with the key.
 *
 *  Returns the value stored with the key as a .
 */
// ---------------------------------------------------------------------------------------
size_t ConfigDB::Section::getIndex( std::string key ) {
  // -------------------------------------------------------------------------------------
  return (size_t) StringTool::asUInt32( this->get( key ) );
}


// =======================================================================================
/** Get Real4.
 *  @param key string key to map the results.
 *  @return value stored with the key.
 *
 *  Returns the value stored with the key as a Real4.
 */
// ---------------------------------------------------------------------------------------
real4_t  ConfigDB::Section::getReal4( std::string key ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asReal4( this->get( key ) );
}


// =======================================================================================
/** Get Real8.
 *  @param key string key to map the results.
 *  @return value stored with the key.
 *
 *  Returns the value stored with the key as a Real8.
 */
// ---------------------------------------------------------------------------------------
real8_t ConfigDB::Section::getReal8( std::string key ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asReal8( this->get( key ) );
}

// =======================================================================================
// **                                  C O N F I G D B                                  **
// ======================================================================== END FILE =====
