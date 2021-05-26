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
 *  @file   CSVFile.cc
 *  @author Stephen W. Soliday
 *  @date   2021-Mar-28.
 *
 *  Provides the interface for a CSV File.
 */
// =======================================================================================


#include <CSVFile.hh>

#define R_INIT_VAR(a) fields(a), num_fields(a), next_record(a)
#define C_INIT_VAR(a) head(a), tail(a), index(a), num_fields(a), num_records(a), head_label(a)

size_t CSVFile::NOT_FOUND = 9999999;

// =======================================================================================
/** @brief Constructor.
 *  @param[in] n number of fields.
 */
// ---------------------------------------------------------------------------------------
CSVFile::Record::Record( size_t n ) : R_INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  num_fields = n;
  fields     = new std::string[ n ];
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
CSVFile::Record::~Record( void ) {
  // -------------------------------------------------------------------------------------
  next_record = static_cast<CSVFile::Record*>(0);
  delete [] fields;
}










// =======================================================================================
/**
 * @brief Constructor.
 * @param fspc path to a CSV file.
 *
 * 
 */
// ---------------------------------------------------------------------------------------
CSVFile::CSVFile( std::string fspc ) : C_INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  
  std::string   line, word;
  
  std::ifstream fin(fspc);
  
  std::getline(fin, line); 
  std::stringstream s1(line);
  std::stringstream s2(line);

  // -------------------------------------------------------------------------------------

  num_fields = 0;
  while (std::getline(s1, word, ',')) { 
    num_fields += 1;
  } 

  head_label = new Record( num_fields );
  for ( size_t i=0; i<num_fields; i++ ) {
    std::getline(s2, word, ',');
    head_label->at(i) = word;
  }

  // -------------------------------------------------------------------------------------

  num_records = 0;
  while( std::getline(fin, line) ) {
    std::stringstream s3(line);
    Record* rec = append();
    for ( size_t i=0; i<num_fields; i++ ) {
      std::getline(s3, word, ',');
      rec->at(i) = word;
    }
    num_records += 1;
  }

  fin.close();

  // -------------------------------------------------------------------------------------

  index = new Record*[num_records];
  
  Record* rec = head;
  for ( size_t i=0; i<num_records; i++ ) {
    index[i] = rec;
    rec = rec->next();
  }
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
CSVFile::~CSVFile( void ) {
  // -------------------------------------------------------------------------------------
   for ( size_t i=0; i<num_records; i++ ) {
     delete index[i];
     index[i] = static_cast<Record*>(0);
   }
   delete[] index;
   index = static_cast<Record**>(0);
   head  = static_cast<Record*>(0);
   tail  = static_cast<Record*>(0);
   delete head_label;
   head_label = static_cast<Record*>(0);
   num_fields = 0;
   num_records = 0;
}
  



// =======================================================================================
/**
 * @brief Append.
 * @return pointer to a new Record.
 *
 * Create and attach a new Record.
 */
// ---------------------------------------------------------------------------------------
CSVFile::Record* CSVFile::append( void ) {
  // -------------------------------------------------------------------------------------
  CSVFile::Record* new_rec = new CSVFile::Record( num_fields );
  
  if ( static_cast<CSVFile::Record*>(0) == head ) {
    head = new_rec;
    tail = new_rec;
  } else {
    tail->next( new_rec );
    tail = new_rec;
  }

  return new_rec;
}



// =======================================================================================
// ---------------------------------------------------------------------------------------
size_t CSVFile::Record::find( std::string str ) {
  // -------------------------------------------------------------------------------------
  for ( size_t i=0; i<num_fields; i++ ) {
    if ( 0 == str.compare( fields[i] ) ) {
      return i;
    }
  }
  return CSVFile::NOT_FOUND;
}








  

// =======================================================================================
// **                                     A R R A Y                                     **
// ======================================================================== END FILE =====
