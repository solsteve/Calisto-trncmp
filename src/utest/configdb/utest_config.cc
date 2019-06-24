// ====================================================================== BEGIN FILE =====
// **                              U T E S T _ C O N F I G                              **
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
/** @brief  Automated testing for ConfigDB.
 *  @file   utest_config.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-10
 *
 *  Provides automated testing for the configuration database.
 */
// =======================================================================================


#include <limits.h>
#include <ConfigDB.hh>
#include "gtest/gtest.h"


namespace {


// =======================================================================================
TEST(test_config_set, Positive) {
  // -------------------------------------------------------------------------------------
  ConfigDB cfg;

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

  // -------------------------------------------------------------------------------------

  EXPECT_EQ( 2, cfg.size() );

  size_t nc = cfg.size(COMMENTS);
  
  EXPECT_EQ( 3, nc );

  EXPECT_STREQ( "File level comment",       cfg.getComment(0).c_str() );
  EXPECT_STREQ( "second line file comment", cfg.getComment(1).c_str() );
  EXPECT_STREQ( "third line file comment",  cfg.getComment(2).c_str() );

  EXPECT_STREQ( "the cage", cfg.get( "First", "episode" ).c_str() );
  EXPECT_STREQ( "first pilot episode", cfg.getComment( "First", "episode" ).c_str() );
  EXPECT_STREQ( "number one", cfg.get( "First", "exec" ).c_str() );
  EXPECT_STREQ( "played by majel barret", cfg.getComment( "First", "exec" ).c_str() );
  EXPECT_STREQ( "2", cfg.get( "First", "parts" ).c_str() );
  
  EXPECT_STREQ( "Constitution", cfg.get( "Second", "class" ).c_str() );
  EXPECT_STREQ( "inaugral", cfg.getComment( "Second", "class" ).c_str() );
  
  EXPECT_STREQ( "NCC 1701", cfg.get( "Second", "reg" ).c_str() );
  
  EXPECT_STREQ( "Enterprise", cfg.get( "Second", "ship" ).c_str() );
  EXPECT_STREQ( "heavy cruiser", cfg.getComment( "Second", "ship" ).c_str() );
  
  ConfigDB::Section* S1 = cfg.get( "First" );
  ConfigDB::Section* S2 = cfg.get( "Second" );

  EXPECT_EQ( 3, S1->size(COMMENTS) );
  EXPECT_EQ( 1, S2->size(COMMENTS) );

  EXPECT_STREQ( "Section level comment", S1->getComment(0).c_str() );
  EXPECT_STREQ( "second line section comment", S1->getComment(1).c_str() );
  EXPECT_STREQ( "third line section comment", S1->getComment(2).c_str() );

  EXPECT_STREQ( "Star Trek facts", S2->getComment(0).c_str() );
}


} // end namespace


// =======================================================================================
// **                              U T E S T _ C O N F I G                              **
// ======================================================================== END FILE =====
