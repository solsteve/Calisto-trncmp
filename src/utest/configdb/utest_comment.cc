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
