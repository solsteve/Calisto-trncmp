// ====================================================================== BEGIN FILE =====
// **                             U T E S T _ S E C T I O N                             **
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
/** @brief  Automated testing for ConfigDB::Section.
 *  @file   utest_section.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-09
 *
 *  Provides automated testing for the configuration database section.
 */
// =======================================================================================


#include <limits.h>
#include <ConfigDB.hh>
#include "gtest/gtest.h"


namespace {


// =======================================================================================

TEST(test_section_create, Positive) {

  ConfigDB::Section sec("TEST");

  EXPECT_STREQ("TEST", sec.getName().c_str() );

  sec.setName( "PLAN" );

  EXPECT_STREQ("PLAN", sec.getName().c_str() );

  EXPECT_EQ( 0,sec.size(COMMENTS)  );

  sec.addComment( "first comment" );
  sec.addComment( "second comment" );

  EXPECT_EQ( 2, sec.size(COMMENTS) );
}

// =======================================================================================

TEST(test_section_comment, Positive) {

  ConfigDB::Section sec("TEST");

  EXPECT_EQ( 0, sec.size(COMMENTS) );

  sec.addComment( "first comment" );
  sec.addComment( "second comment" );

  EXPECT_STREQ( "first comment",  sec.getComment(0).c_str() );
  EXPECT_STREQ( "second comment", sec.getComment(1).c_str() );
  
  EXPECT_EQ( 2, sec.size(COMMENTS) );
}

// =======================================================================================

TEST(test_section_keys, Positive) {
  ConfigDB::Section sec("TEST");

  EXPECT_EQ( 0, sec.size() );

  sec.set( "alpha", "tank",  "soviet" );
  sec.set( "beta", "plane", "british" );

  EXPECT_EQ( 2, sec.size() );

  sec.set( "gamma", "boat" );
  sec.set( "delta", "truck", "american" );

  EXPECT_EQ( 4, sec.size() );

  ConfigDB::Entry ent( "theta=submarine ; underboat" );
  sec.add( ent );

  EXPECT_EQ( 5, sec.size() );

  sec.set( "gamma", "ship" );

  EXPECT_EQ( 5, sec.size() );

  EXPECT_STREQ( "tank",      sec.get("alpha").c_str() );
  EXPECT_STREQ( "plane",     sec.get("beta").c_str() );
  EXPECT_STREQ( "ship",      sec.get("gamma").c_str() );
  EXPECT_STREQ( "truck",     sec.get("delta").c_str() );
  EXPECT_STREQ( "submarine", sec.get("theta").c_str() );

  EXPECT_TRUE( sec.hasKey( "alpha" ) );
  EXPECT_TRUE( sec.hasKey( "beta" ) );
  EXPECT_TRUE( sec.hasKey( "gamma" ) );
  EXPECT_TRUE( sec.hasKey( "delta" ) );
  EXPECT_FALSE( sec.hasKey( "epsilon" ) );
  try {
    EXPECT_STREQ( "truck", sec.get("epsilon").c_str() );
  } catch( ConfigDB::NoSuchKey& e ) {
    EXPECT_STREQ( "No such key: epsilon", e.what() );
  }

  sec.rewind();

  EXPECT_TRUE( sec.hasNext() );
      
  while( sec.next(ent) ) {
    //std::cout << "Key[" << ent.getKey() << "] => (" << ent.toString() << ")\n";
  }

  EXPECT_FALSE( sec.hasNext() );


  
}


} // end namespace


// =======================================================================================
// **                             U T E S T _ S E C T I O N                             **
// ======================================================================== END FILE =====
