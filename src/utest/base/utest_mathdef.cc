#include <limits.h>
#include "trncmp.hh"
#include "gtest/gtest.h"

namespace {

// =======================================================================================

TEST( linear8, Positive ) {
  real8_t slope =  3.4;
  real8_t inter = -1.1;

  real8_t x1    = -5.3;
  real8_t x2    =  4.2;
  
  real8_t y1    = -19.12;
  real8_t y2    =  13.18;

  EXPECT_DOUBLE_EQ( y1, linear( slope, inter, x1 ) );
  EXPECT_DOUBLE_EQ( y2, linear( slope, inter, x2 ) );

  real8_t m = 0.0;
  real8_t b = 0.0;

  EXPECT_FALSE( linear( m, b, x1, y1, x2, y2 ) );
      
  EXPECT_DOUBLE_EQ( slope, m );
  EXPECT_DOUBLE_EQ( inter, b );
}

TEST( linear8, Negative ) {
  real8_t x1    =   2.34;
  real8_t x2    =   2.34;
  
  real8_t y1    = -19.12;
  real8_t y2    =  13.18;

  real8_t m = 10.0;
  real8_t b = 10.0;

  EXPECT_TRUE( linear( m, b, x1, y1, x2, y2 ) );
      
  EXPECT_DOUBLE_EQ( MAX_POS_DOUBLE, m );
  EXPECT_DOUBLE_EQ( D_ZERO,         b );
}

// ---------------------------------------------------------------------------------------

TEST( linear4, Positive ) {
  real4_t slope =  3.4f;
  real4_t inter = -1.1f;

  real4_t x1    = -5.3f;
  real4_t x2    =  4.2f;
  
  real4_t y1    = -19.12f;
  real4_t y2    =  13.18f;

  EXPECT_FLOAT_EQ( y1, linear( slope, inter, x1 ) );
  EXPECT_FLOAT_EQ( y2, linear( slope, inter, x2 ) );

  real4_t m = 10.0f;
  real4_t b = 10.0f;

  EXPECT_FALSE( linear( m, b, x1, y1, x2, y2 ) );
      
  EXPECT_FLOAT_EQ( slope, m );
  EXPECT_FLOAT_EQ( inter, b );
}

TEST( linear4, Negative ) {
  real4_t x1    =   2.34f;
  real4_t x2    =   2.34f;
  
  real4_t y1    = -19.12f;
  real4_t y2    =  13.18f;

  real4_t m = 10.0f;
  real4_t b = 10.0f;

  EXPECT_TRUE( linear( m, b, x1, y1, x2, y2 ) );
      
  EXPECT_FLOAT_EQ( MAX_POS_FLOAT, m );
  EXPECT_FLOAT_EQ( F_ZERO,        b );
}

} // end namespace

