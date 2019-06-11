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
