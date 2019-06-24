// ====================================================================== BEGIN FILE =====
// **                               U T E S T _ E N T R Y                               **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019-, Stephen W. Soliday                                          **
// **                       stephen.soliday@trncmp.org                                  **
// **                       http://research.trncmp.org                                  **
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
/** @brief  Automated testing for ConfigDB::Entry.
 *  @file   utest_entry.cc
 *  @author Stephen W. Soliday
 *  @date   2019-May-26
 *
 *  Provides automated testing for configuration database entries.
 */
// =======================================================================================


#include <limits.h>
#include <ConfigDB.hh>
#include "gtest/gtest.h"


namespace {


// =======================================================================================

TEST(test_entry_toFrom, Positive) {
  ConfigDB::Entry E1;
  std::string     test_string("wife = heather ; keeper of pens");

  E1.fromString(test_string);

  EXPECT_STREQ( test_string.c_str(), E1.toString().c_str() );
}

// ---------------------------------------------------------------------------------------

TEST(test_entry_create, Positive) {
  ConfigDB::Entry E1( "wife", "heather", "keeper of pens" );
  ConfigDB::Entry E2( "daughter", "rebekah" );
  ConfigDB::Entry E3( "son = stephen ; the and" );
  ConfigDB::Entry E4;

  EXPECT_STREQ("wife = heather ; keeper of pens", E1.toString().c_str() );
  EXPECT_STREQ("daughter = rebekah",              E2.toString().c_str() );
  EXPECT_STREQ("son = stephen ; the and",         E3.toString().c_str() );
  EXPECT_STREQ("",                                E4.toString().c_str() );
}

// ---------------------------------------------------------------------------------------

TEST(test_entry_manipulate, Positive) {
  ConfigDB::Entry E1( "wife", "heather", "keeper of pens" );
  ConfigDB::Entry E2( "daughter", "rebekah" );
  ConfigDB::Entry E3;

  E2.copy( E1 );
  E1.clear();
  E3.set("son", "stephen", "the and");

  EXPECT_STREQ("",                                E1.toString().c_str() );
  EXPECT_STREQ("wife = heather ; keeper of pens", E2.toString().c_str() );
  EXPECT_STREQ("son = stephen ; the and",         E3.toString().c_str() );
}

// ---------------------------------------------------------------------------------------

TEST(test_entry_fields, Positive) {
  ConfigDB::Entry E1( "wife", "heather", "keeper of pens" );

  EXPECT_STREQ( "wife",           E1.getKey().c_str() );
  EXPECT_STREQ( "heather",        E1.getValue().c_str() );
  EXPECT_STREQ( "keeper of pens", E1.getComment().c_str() );

  E1.setKey("girl");
               
  EXPECT_STREQ( "girl",           E1.getKey().c_str() );
  EXPECT_STREQ( "heather",        E1.getValue().c_str() );
  EXPECT_STREQ( "keeper of pens", E1.getComment().c_str() );

  E1.setValue("marie");
               
  EXPECT_STREQ( "girl",           E1.getKey().c_str() );
  EXPECT_STREQ( "marie",          E1.getValue().c_str() );
  EXPECT_STREQ( "keeper of pens", E1.getComment().c_str() );

  E1.setComment("amigurumi");
               
  EXPECT_STREQ( "girl",           E1.getKey().c_str() );
  EXPECT_STREQ( "marie",          E1.getValue().c_str() );
  EXPECT_STREQ( "amigurumi",      E1.getComment().c_str() );

}


} // end namespace


// =======================================================================================
// **                               U T E S T _ E N T R Y                               **
// ======================================================================== END FILE =====
