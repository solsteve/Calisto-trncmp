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
#include <StringTool.hh>


// =======================================================================================
void Results( ConfigDB::Entry& ent, std::string line ) {
  // -------------------------------------------------------------------------------------
  std::cout << "K = [" << ent.getKey() << "] "
            << "V = [" << ent.getValue() << "] "
            << "C = [" << ent.getComment() << "] "
            << "L = {" << line << "} ToStr: ["
            << ent.toString()
            << "]\n";
}


#define TestEntry( rv, ent, line ) {   \
    ent.clear();                        \
    rv=ent.fromString( line );           \
    if (0==rv) { Results( ent, line ); }  \
  }

// =======================================================================================
void Test01( void ) {
  // -------------------------------------------------------------------------------------
  ConfigDB::Entry E;

  int k = 0;

  std::cerr << "\nThese will work ------------------------------------\n\n";
  TestEntry( k, E, "girl = heather ; all mine" );
  TestEntry( k, E, "girl = heather" );
  TestEntry( k, E, "girl = heather marie ; special" );
  TestEntry( k, E, "girl = 'heather marie' ; special" );
  TestEntry( k, E, "girl = \"heather marie\" ; special" );
  TestEntry( k, E, "heather = fun" );
  TestEntry( k, E, "heather : fun" );
  
  std::cerr << "\nThese will fail to work ----------------------------\n\n";
  TestEntry( k, E, "  " );
  TestEntry( k, E, "heather" );
  TestEntry( k, E, ": heather" );
  TestEntry( k, E, "   = heather" );
  TestEntry( k, E, "heather = " );
  TestEntry( k, E, "heather = ; what" );

  std::cerr << "\nThese will give a warning but pass -----------------\n\n";
  TestEntry( k, E, "heather = great ;" );

  std::cerr << "\n----------------------------------------------------\n\n";
}


// =======================================================================================
void Test02( void ) {
  // -------------------------------------------------------------------------------------
  ConfigDB::Entry E1( "wife", "heather", "keeper of pens" );
  ConfigDB::Entry E2( "daughter", "rebekah" );
  ConfigDB::Entry E3( "son = stephen ; the and" );
  ConfigDB::Entry E4;

  std::cout << "E1: [" << E1.toString() << "]\n";
  std::cout << "E2: [" << E2.toString() << "]\n";
  std::cout << "E3: [" << E3.toString() << "]\n";
  std::cout << "E4: [" << E4.toString() << "]\n\n";

  E2.copy(E1);
  E3.clear();
  E4.set( "old", "steve" );

  std::cout << "E2: [" << E2.toString() << "]\n";
  std::cout << "E3: [" << E3.toString() << "]\n";
  std::cout << "E4: [" << E4.toString() << "]\n\n";

  std::cout << "Expect [wife]           got [" << E1.getKey()     << "]\n";
  std::cout << "       [heather]        got [" << E1.getValue()   << "]\n";
  std::cout << "       [keeper of pens] got [" << E1.getComment() << "]\n\n";
}

// =======================================================================================
void Test03( void ) {
  // -------------------------------------------------------------------------------------
  ConfigDB::Section sec("MySec");
  
  sec.addComment( "first comment" );
  sec.addComment( "second comment" );

  sec.set( "alpha", "tank",  "soviet" );
  sec.set( "beta", "plane", "british" );

  sec.addComment( "third comment" );

  sec.set( "gamma", "boat" );
  sec.set( "delta", "truck", "american" );

  sec.writeINI( std::cout );
}

// =======================================================================================
void Test04( void ) {
  // -------------------------------------------------------------------------------------
  ConfigDB cfg;
  ConfigDB recover;

  cfg.addComment("File level comment");
  cfg.addComment("second line file comment");
  
  cfg.addComment( "First", "Section level comment" );
  cfg.addComment( "First", "second line section comment" );
  
  cfg.set( "First", "episode", "the cage", "first pilot episode" );
  cfg.set( "First", "parts", "2" );

  cfg.addComment( "First", "third line section comment" );
  
  cfg.set( "First", "exec", "number one", "played by majel barret" );

  cfg.addComment( "Second", "Star Trek facts" );

  cfg.addComment("third line file comment");

  cfg.set( "Second", "ship",  "Enterprise",   "heavy cruiser" );
  cfg.set( "Second", "reg",   "NCC 1701",     "" );
  cfg.set( "Second", "class", "Constitution", "inaugral" );

  cfg.writeINI( std::cout );
  cfg.writeINI( "/tmp/test.ini" );

  recover.readINI( "/tmp/test.ini" );

  std::cout << "\n----- re read from file ------------------------------\n\n";

  recover.writeINI( std::cout );
  
  
  
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
  
  std::cout << "\n===== Test01 =============================================================\n\n";
  Test01();
  
  std::cout << "\n===== Test02 =============================================================\n\n";
  Test02();
  
  std::cout << "\n===== Test03 =============================================================\n\n";
  Test03();
  
  std::cout << "\n===== Test04 =============================================================\n\n";
  Test04();
  
  return 0;
}


// =======================================================================================
// **                             C T E S T _ V E R S I O N                             **
// ======================================================================== END FILE =====
