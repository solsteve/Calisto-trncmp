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
 *  @date   2021-Mar-10.
 *
 *  Provides the interface for a CSV File.
 */
// =======================================================================================


#include <CSVFile.hh>

// =======================================================================================
/**
 * @brief 
 * @param 
 * @return 
 *
 * 
 */
// ---------------------------------------------------------------------------------------
CSVFile::CSVFile( std::string fspc ) {
  // -------------------------------------------------------------------------------------
  
  headings = new std::vector<std::string>();
  
  columns = new std::map<std::string, CSVFile::Column*>();
  
  std::fstream fin;
  std::string  line, word;
  
  fin.open(fspc, std::ios::in);
  
  std::getline(fin, line); 
  std::stringstream s(line);
  
  while (std::getline(s, word, ',')) { 
    headings->push_back(word); 
  (*columns)[ word ] = new CSVFile::Column( word );
  std::cout << "[" << word << "]\n";
  } 

  
  MARK;

  for (std::map<std::string, CSVFile::Column*>::iterator it=columns->begin();
       it!=columns->end();
       ++it) {
    //std::cout << it->second->name() << std::endl;
  }

  MARK;

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
  MARK;
    delete columns;
  MARK;
    delete headings;
  MARK;
  }
  
