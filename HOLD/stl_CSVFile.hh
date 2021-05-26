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
 *  @date   2021-Mar-10.
 *
 *  Provides the interface for a CSV File.
 */
// =======================================================================================


#ifndef __HH_CSVFILE_TRNCMP
#define __HH_CSVFILE_TRNCMP

#include <TLogger.hh>
#include <vector>
#include <map>
#include <StringTool.hh>

// =======================================================================================
class CSVFile {
  // -------------------------------------------------------------------------------------
 protected:
  
  // =====================================================================================
  class Column { //                                                        CSVFile::Column
    // -----------------------------------------------------------------------------------
   private:
    EMPTY_PROTOTYPE( Column );

   protected:
    std::string               col_name;  ///< Name of this column
    std::vector<std::string>* field;     ///< vector of fields in this column

   public:
    Column              ( std::string nm );
    ~Column             ( void );
    size_t       size   ( void );

    void         append ( std::string fld );

    std::string  get    ( const size_t idx );
    std::string  name   ( void );
    
  }; // end CSVFile::Column

  std::vector<std::string>*                headings;
  std::map<std::string, CSVFile::Column*>* columns;
  
 public:
  CSVFile              ( std::string fspc );
  
  ~CSVFile             ( void );

  std::string get      ( std::string cname, const size_t idx );

  size_t      size     ( const int dim );

  int32_t     getInt32 ( std::string cname, const size_t idx );
  real8_t     getReal8 ( std::string cname, const size_t idx );
  
}; // end CSVFile

// =======================================================================================
/**
 * @brief Constructor.
 * @param nm name of this column.
 *
 * Construct a CSV file column.
 */
// ---------------------------------------------------------------------------------------
inline CSVFile::Column::Column  ( std::string nm ) {
  // -------------------------------------------------------------------------------------
  col_name = nm;
  field = new std::vector<std::string>();
}


// =======================================================================================
/**
 * @brief Destructor.
 *
 * Free the allocations made in this CSV file column.
 */
// ---------------------------------------------------------------------------------------
inline CSVFile::Column::~Column ( void ) {
  // -------------------------------------------------------------------------------------
  delete field;
}


// =======================================================================================
/**
 * @brief Append.
 * @param fld new string to add to the end of this field.
 *
 * Append a field to the bottom of this column.
 */
// ---------------------------------------------------------------------------------------
inline void CSVFile::Column::append( std::string fld ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/**
 * @brief Get.
 * @param idx index to a field in this column.
 * @return a sting at the idx position in this column.
 *
 * Get a string field that is at idx position in this column.
 */
// ---------------------------------------------------------------------------------------
inline std::string CSVFile::Column::get( const size_t idx ) {
  // -------------------------------------------------------------------------------------
  return field->at( idx );
}

      
// =======================================================================================
// ---------------------------------------------------------------------------------------
inline size_t CSVFile::Column::size( void ) {
  // -------------------------------------------------------------------------------------
  return field->size();
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
inline size_t CSVFile::size( const int dim = 0 ) {
  // -------------------------------------------------------------------------------------
  if ( 0 == (dim%2) ) {
    return columns->at(0)->size();
  }
  return headings->size();
}


// =======================================================================================
/**
 * @brief 
 * @param 
 * @return 
 *
 * 
 */
// ---------------------------------------------------------------------------------------
inline std::string CSVFile::get( std::string cname, const size_t idx ) {
  // -------------------------------------------------------------------------------------
  return (*columns)[ cname ]->get( idx );
}


// =======================================================================================
/**
 * @brief 
 * @param 
 * @return 
 *
 * 
 */
// ---------------------------------------------------------------------------------------
inline int32_t CSVFile::getInt32( std::string cname, const size_t idx ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asInt32( this->get( cname, idx ) );
}

  
// =======================================================================================
/**
 * @brief 
 * @param 
 * @return 
 *
 * 
 */
// ---------------------------------------------------------------------------------------
inline real8_t CSVFile::getReal8( std::string cname, const size_t idx ) {
  // -------------------------------------------------------------------------------------
  return StringTool::asReal8( this->get( cname, idx ) );
}


#endif

