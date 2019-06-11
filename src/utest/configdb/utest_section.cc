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
