#include <limits.h>
#include "trncmp.hh"
#include "StringTool.hh"
#include "gtest/gtest.h"


namespace {


// =======================================================================================

TEST( test_toString, Positive ) {
  bool      flag  = true;
  bool      nflag = false;
  real8_t   dpi   = D_PI * (real8_t)100;
  real4_t   fpi   = F_PI * (real4_t)10;

  int64_t   I64   = 12454785214LL;
  int32_t   I32   = -123457L;
  int16_t   I16   = -12014;
  int8_t    I8    = 93;
  
  u_int64_t U64   = 12478785214LL;
  u_int32_t U32   = 15622345L;
  u_int16_t U16   = 42387;
  u_int8_t  U8    = 193;

  EXPECT_STREQ(".true.",      StringTool::toString(flag).c_str() );
  EXPECT_STREQ(".false.",     StringTool::toString(nflag).c_str() );
  
  EXPECT_STREQ("314.159265",  StringTool::toString(dpi, "%10.6f").c_str());
  EXPECT_STREQ("31.416",      StringTool::toString(fpi, "%6.3f").c_str());

  EXPECT_STREQ("12454785214", StringTool::toString(I64).c_str());
  EXPECT_STREQ("-123457",     StringTool::toString(I32).c_str());
  EXPECT_STREQ("-12014",      StringTool::toString(I16).c_str());
  EXPECT_STREQ("93",          StringTool::toString(I8).c_str());
 
  EXPECT_STREQ("12478785214", StringTool::toString(U64).c_str());
  EXPECT_STREQ("15622345",    StringTool::toString(U32).c_str());
  EXPECT_STREQ("42387",       StringTool::toString(U16).c_str());
  EXPECT_STREQ("193",         StringTool::toString(U8).c_str());
}

// ---------------------------------------------------------------------------------------

TEST( test_toString_array, Positive ) {
  std::string* slst = new std::string[3];
  slst[0] = "Heather";
  slst[1] = "Anthea";
  slst[2] = "Cassiopeia";
  
  EXPECT_STREQ("[ Heather, Anthea, Cassiopeia ]", StringTool::toString(slst,3).c_str() );

  real8_t dlst[] = { 123.456, 234.567, 345.678 };
  EXPECT_STREQ("[ 123.456, 234.567, 345.678 ]", StringTool::toString(dlst,3,"%.3f").c_str() );

  real4_t flst[] = { 234.567f, 123.456f, 345.678f };
  EXPECT_STREQ("[ 234.567, 123.456, 345.678 ]", StringTool::toString(flst,3,"%.3f").c_str() );

  
  int64_t L64[] = { 4273989587LL, -1298479844LL, 9858948244LL };
  EXPECT_STREQ("[ 4273989587, -1298479844, 9858948244 ]", StringTool::toString(L64,3).c_str() );

  int64_t L32[] = { 427398L, -129847L, -985894L };
  EXPECT_STREQ("[ 427398, -129847, -985894 ]", StringTool::toString(L32,3).c_str() );

  int64_t L16[] = { 4327, 1294, 9851 };
  EXPECT_STREQ("[ 4327, 1294, 9851 ]", StringTool::toString(L16,3).c_str() );

  int64_t L8[] = { 43, -94, 51 };
  EXPECT_STREQ("[ 43, -94, 51 ]", StringTool::toString(L8,3).c_str() );

  u_int64_t H64[] = { 76654324556LL, 125757425LL, 357447577LL };
  EXPECT_STREQ("[ 76654324556, 125757425, 357447577 ]",
               StringTool::toString(H64,3).c_str() );

  u_int32_t H32[] = { 125545L, 5421545L, 4455545L };
  EXPECT_STREQ("[ 125545, 5421545, 4455545 ]", StringTool::toString(H32,3).c_str() );

  u_int16_t H16[] = { 8742, 43514, 7953 };
  EXPECT_STREQ("[ 8742, 43514, 7953 ]", StringTool::toString(H16,3).c_str() );

  u_int8_t H8[]  = { 163, 100, 254 };
  EXPECT_STREQ("[ 163, 100, 254 ]", StringTool::toString(H8,3).c_str() );
  
  delete[] slst;
}

// ---------------------------------------------------------------------------------------

TEST( test_toHex, Positive ) {
  u_int64_t U64   = 0x20d7c6342c147d4cLL;
  u_int32_t U32   = 0x620d7c63L;
  u_int16_t U16   = 0x4a2a;
  u_int8_t  U8    = 0xfe;

  EXPECT_STREQ("20d7c6342c147d4c", StringTool::toHex(U64).c_str());
  EXPECT_STREQ("620d7c63",         StringTool::toHex(U32).c_str());
  EXPECT_STREQ("4a2a",             StringTool::toHex(U16).c_str());
  EXPECT_STREQ("fe",               StringTool::toHex(U8).c_str());

  u_int64_t H64[] = { 0xa38e068c39bb4ec4LL, 0x646381e39a4e9LL, 0x29da07d5b58c9255LL };
  EXPECT_STREQ("[ a38e068c39bb4ec4, 000646381e39a4e9, 29da07d5b58c9255 ]",
               StringTool::toHex(H64,3).c_str() );

  u_int32_t H32[] = { 0x46ff37ecL, 0xb8b39450L, 0xdfd60b7fL };
  EXPECT_STREQ("[ 46ff37ec, b8b39450, dfd60b7f ]", StringTool::toHex(H32,3).c_str() );

  u_int16_t H16[] = { 0x32e6, 0x0947, 0x93f8 };
  EXPECT_STREQ("[ 32e6, 0947, 93f8 ]", StringTool::toHex(H16,3).c_str() );

  u_int8_t H8[]  = { 0x81, 0x3a, 0xf9 };
  EXPECT_STREQ("[ 81, 3a, f9 ]", StringTool::toHex(H8,3).c_str() );
}

// =======================================================================================

TEST( test_asType, Positive ) {
  EXPECT_DOUBLE_EQ( (real8_t)123.456, StringTool::asReal8( "123.456" ) );
  EXPECT_FLOAT_EQ(  (real4_t)123.456, StringTool::asReal4( "123.456" ) );

  EXPECT_EQ( (int64_t)12345678, StringTool::asInt64( "12345678" ) );
  EXPECT_EQ( (int32_t)123456,   StringTool::asInt32( "123456" ) );
  EXPECT_EQ( (int16_t)12345,    StringTool::asInt16( "12345" ) );
  EXPECT_EQ( (int8_t)123,       StringTool::asInt8( "123" ) );

  EXPECT_EQ( (u_int64_t)712345678, StringTool::asUInt64( "712345678" ) );
  EXPECT_EQ( (u_int32_t)7123456,   StringTool::asUInt32( "7123456" ) );
  EXPECT_EQ( (u_int16_t)64532,     StringTool::asUInt16( "64532" ) );
  EXPECT_EQ( (u_int8_t)223,        StringTool::asUInt8( "223" ) );

  EXPECT_TRUE(  StringTool::asBool( ".true." ) );
  EXPECT_FALSE( StringTool::asBool( ".false." ) );

  EXPECT_TRUE(  StringTool::asBool( "True" ) );
  EXPECT_FALSE( StringTool::asBool( "False" ) );

  EXPECT_TRUE(  StringTool::asBool( "yes" ) );
  EXPECT_FALSE( StringTool::asBool( "no" ) );
}

// =======================================================================================

TEST( test_trim, Positive ) {
  std::string A = "asdf    ";
  std::string B = "   jklz";
  std::string C = "  mnbv    ";
  
  EXPECT_STREQ( "asdf", StringTool::trim(A).c_str() );
  EXPECT_STREQ( "jklz", StringTool::trim(B).c_str() );
  EXPECT_STREQ( "mnbv", StringTool::trim(C).c_str() );
}

// ---------------------------------------------------------------------------------------

TEST( test_contain, Positive ) {
  std::string L = "[{(";
  std::string R = ")}]";

  std::string A = "(Heather)";
  std::string B = "   [Anthea} ";
  std::string C = "  {  Cassiopeia  )";

  EXPECT_STREQ( "Heather",        StringTool::containedBy(A,L,R).c_str() );
  EXPECT_STREQ( "Anthea",         StringTool::containedBy(B,L,R).c_str() );
  EXPECT_STREQ( "  Cassiopeia  ", StringTool::containedBy(C,L,R).c_str() );
}

// ---------------------------------------------------------------------------------------

TEST( test_findin, Positive ) {
  //               0123456789
  std::string A = "asdfghjklq";

  EXPECT_EQ( (size_t)0, StringTool::find_in( A, 'a' ) );
  EXPECT_EQ( (size_t)4, StringTool::find_in( A, 'g' ) );
  EXPECT_EQ( (size_t)6, StringTool::find_in( A, 'j' ) );
  EXPECT_EQ( (size_t)9, StringTool::find_in( A, 'q' ) );
}

TEST( test_findin, Negative ) {
  //               0123456789
  std::string A = "asdfghjklq";

  EXPECT_EQ( StringTool::NOT_FOUND, StringTool::find_in( A, 'x' ) );
}

// =======================================================================================

TEST( test_split, Positive ) {
  std::string test = " Heather , Anthea, Cassiopeia ";

  StringTool::Splitter SP( test, ',' );
  size_t n = SP.size();
  EXPECT_EQ( (size_t)3, n );
  EXPECT_STREQ( "Heather",    SP[0].c_str() );
  EXPECT_STREQ( "Anthea",     SP.at(1).c_str() );
  EXPECT_STREQ( "Cassiopeia", SP[2].c_str() );
}


} // end namespace
