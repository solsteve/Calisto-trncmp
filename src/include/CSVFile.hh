// ====================================================================== BEGIN FILE =====
// **                                   C S V F I L E                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2021, Stephen W. Soliday                                           **
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
/** @brief  CSV File.
 *  @file   CSVFile.hh
 *  @author Stephen W. Soliday
 *  @date   2021-Mar-28.
 *
 *  Provides the interface for a CSV File.
 */
// =======================================================================================


#ifndef __HH_CSVFILE_TRNCMP
#define __HH_CSVFILE_TRNCMP

#include <TLogger.hh>
#include <StringTool.hh>

// =======================================================================================
class CSVFile {
  // -------------------------------------------------------------------------------------
 private:
  EMPTY_PROTOTYPE( CSVFile );
    
 public:

  static size_t NOT_FOUND;

  // =====================================================================================
  class Record {
    // -----------------------------------------------------------------------------------
   private:
    EMPTY_PROTOTYPE( Record );
    
   protected:
    std::string* fields;      ///< array of fields.
    size_t       num_fields;  ///< number of fields.
    Record*      next_record; ///< pointer to the next record.

   public:
    Record            ( size_t n );
    ~Record           ( void );

    size_t       size ( void );
    std::string& at   ( size_t idx );
    Record*      next ( void );
    void         next ( Record* R );

    size_t       find ( std::string str );
    
  }; // end class CSVFile::Record

 protected:
  Record*  head;
  Record*  tail;
  Record** index;
  size_t   num_fields;
  size_t   num_records;
  Record*  head_label;

  Record* append( void );

 public:
  CSVFile            ( std::string fspc );
  ~CSVFile           ( void );

  Record*     first  ( void );
  size_t      size   ( const int dim=0 );
  Record*     get    ( size_t recn );
  std::string header ( size_t idx );
  
  std::string get      ( size_t recn, size_t fldn );
  int32_t     getInt32 ( size_t recn, size_t fldn );
  real8_t     getReal8 ( size_t recn, size_t fldn );

  std::string get      ( size_t recn, std::string label );
  int32_t     getInt32 ( size_t recn, std::string label );
  real8_t     getReal8 ( size_t recn, std::string label );
  
}; // end class CSVFile;



// =======================================================================================
/** @brief Size.
 *  @return number of fields.
 *
 *  Obtain the number of fields in this Record.
 */
// ---------------------------------------------------------------------------------------
inline  size_t CSVFile::Record::size( void ) {
  // -------------------------------------------------------------------------------------
  return num_fields;
}


// =======================================================================================
/** @brief At.
 *  @param[in] idx index of the field.
 *  @return reference to the indexed field.
 *
 *  Obtain the number of fields in this Record.
 */
// ---------------------------------------------------------------------------------------
inline  std::string& CSVFile::Record::at( size_t idx ) {
  // -------------------------------------------------------------------------------------
  return fields[idx];
}


// =======================================================================================
/** @brief Next Record.
 *  @return pointer to the next record.
 */
// ---------------------------------------------------------------------------------------
inline  CSVFile::Record* CSVFile::Record::next( void ) {
  // -------------------------------------------------------------------------------------
  return next_record;
}


// =======================================================================================
/** @brief Next Record.
 *  @return pointer to the next record.
 */
// ---------------------------------------------------------------------------------------
inline  void CSVFile::Record::next( CSVFile::Record* R ) {
  // -------------------------------------------------------------------------------------
   next_record = R;
}








// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  CSVFile::Record* CSVFile::first( void ) {
  // -------------------------------------------------------------------------------------
  return head;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  size_t CSVFile::size( const int dim ) {
  // -------------------------------------------------------------------------------------
  return ((0==dim) ? (num_records) : (num_fields));
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  CSVFile::Record* CSVFile::get( size_t recn ) {
  // -------------------------------------------------------------------------------------
  return index[recn];
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  std::string CSVFile::header( size_t idx ) {
  // -------------------------------------------------------------------------------------
  return head_label->at( idx );
}




// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  std::string  CSVFile::get( size_t recn, size_t fldn ) {
  // -------------------------------------------------------------------------------------
  return index[recn]->at( fldn );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  int32_t CSVFile::getInt32( size_t recn, size_t fldn ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asInt32( this->get( recn, fldn ) );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  real8_t CSVFile::getReal8( size_t recn, size_t fldn ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asReal8( this->get( recn, fldn ) );
}




// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  std::string  CSVFile::get( size_t recn, std::string label ) {
  // -------------------------------------------------------------------------------------
  return index[recn]->at( head_label->find(label) );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  int32_t CSVFile::getInt32( size_t recn, std::string label ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asInt32( this->get( recn, label ) );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  real8_t CSVFile::getReal8( size_t recn, std::string label ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asReal8( this->get( recn, label ) );
}


#endif


// =======================================================================================
// **                                   C S V F I L E                                   **
// ======================================================================== END FILE =====
