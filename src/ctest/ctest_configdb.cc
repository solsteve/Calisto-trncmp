// ====================================================================== BEGIN FILE =====
// **                            C T E S T _ C O N F I G D B                            **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2019, Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
// **                                                                                   **
// **  -------------------------------------------------------------------------------  **
// **                                                                                   **
// **  This program is free software: you can redistribute it and/or modify it under    **
// **  the terms of the GNU General Public License as published by the Free Software    **
// **  Foundation, either version 3 of the License, or (at your option)                 **
// **  any later version.                                                               **
// **                                                                                   **
// **  This program is distributed in the hope that it will be useful, but WITHOUT      **
// **  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS    **
// **  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.   **
// **                                                                                   **
// **  You should have received a copy of the GNU General Public License along with     **
// **  this program. If not, see <http://www.gnu.org/licenses/>.                        **
// **                                                                                   **
// ----- Modification History ------------------------------------------------------------
//
/** @brief Test the Version
 *  @file   ctest_version.cc
 *  @author Stephen W. Soliday
 *  @date   2019-May-10
 *
 *  This is a test of configdb
 */
// =======================================================================================


#include <ConfigDB.hh>


// =======================================================================================
void Results( ConfigDB::Entry ent, std::string line ) {
  // -------------------------------------------------------------------------------------
  std::cout << "K = [" << ent.getKey() << "] "
            << "V = [" << ent.getValue() << "] "
            << "C = [" << ent.getComment() << "] "
            << "L = {" << line << "}\n";
}


#define TestEntry( rv, ent, line ) { ent.clear(); rv=ent.fromString( line ); if (0==rv) { Results( ent, line ); } }

// =======================================================================================
void Test01( void ) {
  // -------------------------------------------------------------------------------------
  ConfigDB::Entry E;

  int k = 0;

  TestEntry( k, E, "girl = heather ; all mine" );
  TestEntry( k, E, "girl = heather" );
  TestEntry( k, E, "girl = 'heather marie' ; special" );
  TestEntry( k, E, "girl = \"heather marie\" ; special" );
  TestEntry( k, E, "heather = fun" );
  TestEntry( k, E, "heather : fun" );
  
  TestEntry( k, E, "  " );
  TestEntry( k, E, "heather" );
  TestEntry( k, E, ": heather" );
  TestEntry( k, E, "   = heather" );
  TestEntry( k, E, "heather = " );
  TestEntry( k, E, "heather = ; what" );
  TestEntry( k, E, "heather = great ;" );
}

// =======================================================================================
/** @brief Entry point.
 *  @return 0 on success non-zero on failure
 *
 *  Main entry point for the version test.
 */
// ---------------------------------------------------------------------------------------
int main( void ) {
  // -------------------------------------------------------------------------------------
  
  std::cout << "\n==================================================================\n\n";
  Test01();
  
  return 0;
}


// =======================================================================================
// **                             C T E S T _ V E R S I O N                             **
// ======================================================================== END FILE =====
