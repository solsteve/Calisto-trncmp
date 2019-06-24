// ====================================================================== BEGIN FILE =====
// **                             U T E S T _ C O M M E N T                             **
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
/** @brief  Automated testing for ConfigDB::Comment.
 *  @file   utest_commnet.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-06
 *
 *  Provides automated testing for configuration database commnets.
 */
// =======================================================================================


#include <limits.h>
#include <ConfigDB.hh>
#include "gtest/gtest.h"


namespace {


// =======================================================================================

TEST(test_comment_create, Positive) {

  ConfigDB::Comments com;

  EXPECT_EQ( 0, com.size() );

  com.add( "first comment" );
  com.add( "second comment" );

  EXPECT_EQ( 2, com.size() );

  com.add( "third comment" );
  com.add( "fourth comment" );

  EXPECT_TRUE( com.isIn(  "third comment" ) );
  EXPECT_FALSE( com.isIn( "third coment" ) );

  EXPECT_EQ( 4, com.size() );

  EXPECT_STREQ("first comment",  com.get(0).c_str() );
  EXPECT_STREQ("second comment", com.get(1).c_str() );
  EXPECT_STREQ("third comment",  com.get(2).c_str() );
  EXPECT_STREQ("fourth comment", com.get(3).c_str() );

  com.rewind();
  EXPECT_TRUE( com.hasNext() );
  while ( com.hasNext() ) {
    com.next();
  }
  EXPECT_FALSE( com.hasNext() );

  try {
    EXPECT_STREQ("WTF", com.get(4).c_str() );
  } catch( std::out_of_range& e ) {
    EXPECT_STREQ("Expected index less than 4 Got 4", e.what() );
  }

  try {
    EXPECT_STREQ("WTF", com.get(9).c_str() );
  } catch( std::out_of_range& e ) {
    EXPECT_STREQ("Expected index less than 4 Got 9", e.what() );
  }
}


} // end namespace


// =======================================================================================
// **                             U T E S T _ C O M M E N T                             **
// ======================================================================== END FILE =====
