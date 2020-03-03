// ====================================================================== BEGIN FILE =====
// **                           U T E S T _ P A R T I T I O N                           **
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
/** @brief  Automated testing for fuzzy::Partition class methods.
 *  @file   utest_partition.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-16
 *
 *  Provides automated testing for the fuzzy::Partition class and methods.
 */
// =======================================================================================

#include <limits.h>
#include <fuzzy/Partition.hh>
#include <Array.hh>
#include <FileTool.hh>
#include <gtest/gtest.h>

namespace {

inline real8_t RA( const real8_t a, const real8_t b ) { return Abs(a-b); }
inline real8_t TA( const real8_t a, const real8_t b ) { return Abs(a-b)/2.0; }


// =======================================================================================
TEST( test_part_create, empty_one ) {
  // -------------------------------------------------------------------------------------
  real8_t dat[1] = { 7.0 };

  fuzzy::Partition P0;
  fuzzy::Partition P1(1);
  fuzzy::Partition P2(1,3.0,7.0);
  fuzzy::Partition P3(1,dat);

  EXPECT_EQ( 1, P0.nIn() );
  EXPECT_EQ( 0, P0.nOut() );
  EXPECT_EQ( 0, P0.size() );

  EXPECT_EQ( 1, P1.nIn() );
  EXPECT_EQ( 1, P1.nOut() );
  EXPECT_EQ( 1, P1.size() );

  EXPECT_DOUBLE_EQ( -1.0, P1.get(0).getLeft() );
  EXPECT_DOUBLE_EQ(  0.0, P1.get(0).getCenter() );
  EXPECT_DOUBLE_EQ(  1.0, P1.get(0).getRight() );
      
  EXPECT_EQ( 1, P2.nIn() );
  EXPECT_EQ( 1, P2.nOut() );
  EXPECT_EQ( 1, P2.size() );

  EXPECT_DOUBLE_EQ(  3.0, P2.get(0).getLeft() );
  EXPECT_DOUBLE_EQ(  5.0, P2.get(0).getCenter() );
  EXPECT_DOUBLE_EQ(  7.0, P2.get(0).getRight() );
      
  EXPECT_EQ( 1, P3.nIn() );
  EXPECT_EQ( 1, P3.nOut() );
  EXPECT_EQ( 1, P3.size() );

  EXPECT_DOUBLE_EQ(  6.0, P3.get(0).getLeft() );
  EXPECT_DOUBLE_EQ(  7.0, P3.get(0).getCenter() );
  EXPECT_DOUBLE_EQ(  8.0, P3.get(0).getRight() );
}


// =======================================================================================
TEST( test_part_create, empty_two ) {
  // -------------------------------------------------------------------------------------
  real8_t dat[] = { 7.0, 9.0 };

  fuzzy::Partition P0;
  fuzzy::Partition P1(2);
  fuzzy::Partition P2(2,3.0,7.0);
  fuzzy::Partition P3(2,dat);

  EXPECT_EQ( 1, P0.nIn() );
  EXPECT_EQ( 0, P0.nOut() );
  EXPECT_EQ( 0, P0.size() );

  EXPECT_EQ( 1, P1.nIn() );
  EXPECT_EQ( 2, P1.nOut() );
  EXPECT_EQ( 2, P1.size() );

  EXPECT_DOUBLE_EQ( RA(P1.get(0).getLeft(),   P1.get(0).getCenter()),
                    TA(P1.get(0).getCenter(), P1.get(0).getRight()) );

  EXPECT_DOUBLE_EQ( TA(P1.get(1).getLeft(),   P1.get(1).getCenter()),
                    RA(P1.get(1).getCenter(), P1.get(1).getRight()) );

  EXPECT_DOUBLE_EQ( -2.0, P1.get(0).getLeft() );
  EXPECT_DOUBLE_EQ( -1.0, P1.get(0).getCenter() );
  EXPECT_DOUBLE_EQ(  1.0, P1.get(0).getRight() );
  EXPECT_DOUBLE_EQ( -1.0, P1.get(1).getLeft() );
  EXPECT_DOUBLE_EQ(  1.0, P1.get(1).getCenter() );
  EXPECT_DOUBLE_EQ(  2.0, P1.get(1).getRight() );
      
  EXPECT_EQ( 1, P2.nIn()  );
  EXPECT_EQ( 2, P2.nOut() );
  EXPECT_EQ( 2, P2.size() );

  EXPECT_DOUBLE_EQ( RA(P2.get(0).getLeft(),   P2.get(0).getCenter()),
                    TA(P2.get(0).getCenter(), P2.get(0).getRight()) );

  EXPECT_DOUBLE_EQ( TA(P2.get(1).getLeft(),   P2.get(1).getCenter()),
                    RA(P2.get(1).getCenter(), P2.get(1).getRight()) );

  EXPECT_DOUBLE_EQ(  1.0, P2.get(0).getLeft() );
  EXPECT_DOUBLE_EQ(  3.0, P2.get(0).getCenter() );
  EXPECT_DOUBLE_EQ(  7.0, P2.get(0).getRight() );
  EXPECT_DOUBLE_EQ(  3.0, P2.get(1).getLeft() );
  EXPECT_DOUBLE_EQ(  7.0, P2.get(1).getCenter() );
  EXPECT_DOUBLE_EQ(  9.0, P2.get(1).getRight() );
      
  EXPECT_EQ( 1, P3.nIn() );
  EXPECT_EQ( 2, P3.nOut() );
  EXPECT_EQ( 2, P3.size() );

  EXPECT_DOUBLE_EQ( RA(P3.get(0).getLeft(),   P3.get(0).getCenter()),
                    TA(P3.get(0).getCenter(), P3.get(0).getRight()) );

  EXPECT_DOUBLE_EQ( TA(P3.get(1).getLeft(),   P3.get(1).getCenter()),
                    RA(P3.get(1).getCenter(), P3.get(1).getRight()) );

  EXPECT_DOUBLE_EQ(  6.0, P3.get(0).getLeft() );
  EXPECT_DOUBLE_EQ(  7.0, P3.get(0).getCenter() );
  EXPECT_DOUBLE_EQ(  9.0, P3.get(0).getRight() );
  EXPECT_DOUBLE_EQ(  7.0, P3.get(1).getLeft() );
  EXPECT_DOUBLE_EQ(  9.0, P3.get(1).getCenter() );
  EXPECT_DOUBLE_EQ( 10.0, P3.get(1).getRight() );
}


// =======================================================================================
TEST( test_part_create, empty_three ) {
  // -------------------------------------------------------------------------------------
  real8_t dat[] = { 3.0, 5.0, 9.0 };

  fuzzy::Partition P0;
  fuzzy::Partition P1(3);
  fuzzy::Partition P2(3, 6.0, 10.0);
  fuzzy::Partition P3(3, dat);

  EXPECT_EQ( 1, P0.nIn() );
  EXPECT_EQ( 0, P0.nOut() );
  EXPECT_EQ( 0, P0.size() );

  EXPECT_EQ( 1, P1.nIn() );
  EXPECT_EQ( 3, P1.nOut() );
  EXPECT_EQ( 3, P1.size() );

  EXPECT_DOUBLE_EQ( RA(P1.get(0).getLeft(),   P1.get(0).getCenter()),
                    TA(P1.get(0).getCenter(), P1.get(0).getRight()) );

  EXPECT_DOUBLE_EQ( TA(P1.get(2).getLeft(),   P1.get(2).getCenter()),
                    RA(P1.get(2).getCenter(), P1.get(2).getRight()) );

  EXPECT_DOUBLE_EQ( -1.5, P1.get(0).getLeft() );
  EXPECT_DOUBLE_EQ( -1.0, P1.get(0).getCenter() );
  EXPECT_DOUBLE_EQ(  0.0, P1.get(0).getRight() );
  
  EXPECT_DOUBLE_EQ( -1.0, P1.get(1).getLeft() );
  EXPECT_DOUBLE_EQ(  0.0, P1.get(1).getCenter() );
  EXPECT_DOUBLE_EQ(  1.0, P1.get(1).getRight() );
  
  EXPECT_DOUBLE_EQ(  0.0, P1.get(2).getLeft() );
  EXPECT_DOUBLE_EQ(  1.0, P1.get(2).getCenter() );
  EXPECT_DOUBLE_EQ(  1.5, P1.get(2).getRight() );
      
  EXPECT_EQ( 1, P2.nIn()  );
  EXPECT_EQ( 3, P2.nOut() );
  EXPECT_EQ( 3, P2.size() );

  EXPECT_DOUBLE_EQ( RA(P2.get(0).getLeft(),   P2.get(0).getCenter()),
                    TA(P2.get(0).getCenter(), P2.get(0).getRight()) );

  EXPECT_DOUBLE_EQ( TA(P2.get(2).getLeft(),   P2.get(2).getCenter()),
                    RA(P2.get(2).getCenter(), P2.get(2).getRight()) );

  EXPECT_DOUBLE_EQ(  5.0, P2.get(0).getLeft() );
  EXPECT_DOUBLE_EQ(  6.0, P2.get(0).getCenter() );
  EXPECT_DOUBLE_EQ(  8.0, P2.get(0).getRight() );
  
  EXPECT_DOUBLE_EQ(  6.0, P2.get(1).getLeft() );
  EXPECT_DOUBLE_EQ(  8.0, P2.get(1).getCenter() );
  EXPECT_DOUBLE_EQ( 10.0, P2.get(1).getRight() );
  
  EXPECT_DOUBLE_EQ(  8.0, P2.get(2).getLeft() );
  EXPECT_DOUBLE_EQ( 10.0, P2.get(2).getCenter() );
  EXPECT_DOUBLE_EQ( 11.0, P2.get(2).getRight() );
      
  EXPECT_EQ( 1, P3.nIn() );
  EXPECT_EQ( 3, P3.nOut() );
  EXPECT_EQ( 3, P3.size() );

  EXPECT_DOUBLE_EQ( RA(P3.get(0).getLeft(),   P3.get(0).getCenter()),
                    TA(P3.get(0).getCenter(), P3.get(0).getRight()) );

  EXPECT_DOUBLE_EQ( TA(P3.get(2).getLeft(),   P3.get(2).getCenter()),
                    RA(P3.get(2).getCenter(), P3.get(2).getRight()) );

  EXPECT_DOUBLE_EQ(  2.0, P3.get(0).getLeft() );
  EXPECT_DOUBLE_EQ(  3.0, P3.get(0).getCenter() );
  EXPECT_DOUBLE_EQ(  5.0, P3.get(0).getRight() );
  
  EXPECT_DOUBLE_EQ(  3.0, P3.get(1).getLeft() );
  EXPECT_DOUBLE_EQ(  5.0, P3.get(1).getCenter() );
  EXPECT_DOUBLE_EQ(  9.0, P3.get(1).getRight() );
  
  EXPECT_DOUBLE_EQ(  5.0, P3.get(2).getLeft() );
  EXPECT_DOUBLE_EQ(  9.0, P3.get(2).getCenter() );
  EXPECT_DOUBLE_EQ( 11.0, P3.get(2).getRight() );
}


// =======================================================================================
TEST( test_part_create, empty_five ) {
  // -------------------------------------------------------------------------------------
  real8_t dat[] = { 3.0, 5.0, 8.0, 12.0, 13.0 };

  fuzzy::Partition P0;
  fuzzy::Partition P1(5);
  fuzzy::Partition P2(5, 6.0, 14.0);
  fuzzy::Partition P3(5, dat);

  EXPECT_EQ( 1, P0.nIn() );
  EXPECT_EQ( 0, P0.nOut() );
  EXPECT_EQ( 0, P0.size() );

  EXPECT_EQ( 1, P1.nIn() );
  EXPECT_EQ( 5, P1.nOut() );
  EXPECT_EQ( 5, P1.size() );

  EXPECT_DOUBLE_EQ( RA(P1.get(0).getLeft(),   P1.get(0).getCenter()),
                    TA(P1.get(0).getCenter(), P1.get(0).getRight()) );

  EXPECT_DOUBLE_EQ( TA(P1.get(4).getLeft(),   P1.get(4).getCenter()),
                    RA(P1.get(4).getCenter(), P1.get(4).getRight()) );

  EXPECT_DOUBLE_EQ( -1.25, P1.get(0).getLeft() );
  EXPECT_DOUBLE_EQ( -1.0, P1.get(0).getCenter() );
  EXPECT_DOUBLE_EQ( -0.5, P1.get(0).getRight() );
  
  EXPECT_DOUBLE_EQ( -1.0, P1.get(1).getLeft() );
  EXPECT_DOUBLE_EQ( -0.5, P1.get(1).getCenter() );
  EXPECT_DOUBLE_EQ(  0.0, P1.get(1).getRight() );
  
  EXPECT_DOUBLE_EQ( -0.5, P1.get(2).getLeft() );
  EXPECT_DOUBLE_EQ(  0.0, P1.get(2).getCenter() );
  EXPECT_DOUBLE_EQ(  0.5, P1.get(2).getRight() );
      
  EXPECT_DOUBLE_EQ(  0.0, P1.get(3).getLeft() );
  EXPECT_DOUBLE_EQ(  0.5, P1.get(3).getCenter() );
  EXPECT_DOUBLE_EQ(  1.0, P1.get(3).getRight() );
      
  EXPECT_DOUBLE_EQ(  0.5, P1.get(4).getLeft() );
  EXPECT_DOUBLE_EQ(  1.0, P1.get(4).getCenter() );
  EXPECT_DOUBLE_EQ(  1.25, P1.get(4).getRight() );
      
  EXPECT_EQ( 1, P2.nIn()  );
  EXPECT_EQ( 5, P2.nOut() );
  EXPECT_EQ( 5, P2.size() );

  EXPECT_DOUBLE_EQ( RA(P2.get(0).getLeft(),   P2.get(0).getCenter()),
                    TA(P2.get(0).getCenter(), P2.get(0).getRight()) );

  EXPECT_DOUBLE_EQ( TA(P2.get(4).getLeft(),   P2.get(4).getCenter()),
                    RA(P2.get(4).getCenter(), P2.get(4).getRight()) );

  EXPECT_DOUBLE_EQ(  5.0, P2.get(0).getLeft() );
  EXPECT_DOUBLE_EQ(  6.0, P2.get(0).getCenter() );
  EXPECT_DOUBLE_EQ(  8.0, P2.get(0).getRight() );
  
  EXPECT_DOUBLE_EQ(  6.0, P2.get(1).getLeft() );
  EXPECT_DOUBLE_EQ(  8.0, P2.get(1).getCenter() );
  EXPECT_DOUBLE_EQ( 10.0, P2.get(1).getRight() );
  
  EXPECT_DOUBLE_EQ(  8.0, P2.get(2).getLeft() );
  EXPECT_DOUBLE_EQ( 10.0, P2.get(2).getCenter() );
  EXPECT_DOUBLE_EQ( 12.0, P2.get(2).getRight() );
      
  EXPECT_DOUBLE_EQ( 10.0, P2.get(3).getLeft() );
  EXPECT_DOUBLE_EQ( 12.0, P2.get(3).getCenter() );
  EXPECT_DOUBLE_EQ( 14.0, P2.get(3).getRight() );
      
  EXPECT_DOUBLE_EQ( 12.0, P2.get(4).getLeft() );
  EXPECT_DOUBLE_EQ( 14.0, P2.get(4).getCenter() );
  EXPECT_DOUBLE_EQ( 15.0, P2.get(4).getRight() );
      
  EXPECT_EQ( 1, P3.nIn() );
  EXPECT_EQ( 5, P3.nOut() );
  EXPECT_EQ( 5, P3.size() );

  EXPECT_DOUBLE_EQ( RA(P3.get(0).getLeft(),   P3.get(0).getCenter()),
                    TA(P3.get(0).getCenter(), P3.get(0).getRight()) );

  EXPECT_DOUBLE_EQ( TA(P3.get(4).getLeft(),   P3.get(4).getCenter()),
                    RA(P3.get(4).getCenter(), P3.get(4).getRight()) );

  EXPECT_DOUBLE_EQ(  2.0, P3.get(0).getLeft() );
  EXPECT_DOUBLE_EQ(  3.0, P3.get(0).getCenter() );
  EXPECT_DOUBLE_EQ(  5.0, P3.get(0).getRight() );
  
  EXPECT_DOUBLE_EQ(  3.0, P3.get(1).getLeft() );
  EXPECT_DOUBLE_EQ(  5.0, P3.get(1).getCenter() );
  EXPECT_DOUBLE_EQ(  8.0, P3.get(1).getRight() );
  
  EXPECT_DOUBLE_EQ(  5.0, P3.get(2).getLeft() );
  EXPECT_DOUBLE_EQ(  8.0, P3.get(2).getCenter() );
  EXPECT_DOUBLE_EQ( 12.0, P3.get(2).getRight() );
  
  EXPECT_DOUBLE_EQ(  8.0, P3.get(3).getLeft() );
  EXPECT_DOUBLE_EQ( 12.0, P3.get(3).getCenter() );
  EXPECT_DOUBLE_EQ( 13.0, P3.get(3).getRight() );
  
  EXPECT_DOUBLE_EQ( 12.0, P3.get(4).getLeft() );
  EXPECT_DOUBLE_EQ( 13.0, P3.get(4).getCenter() );
  EXPECT_DOUBLE_EQ( 13.5, P3.get(4).getRight() );
}


// =======================================================================================
TEST( test_part_functions, mu ) {
  // -------------------------------------------------------------------------------------
  real8_t X[] = { 6.00, 7.00, 8.00, 9.00, 10.00, 11.00, 13.00, 15.00, 17.00, 19.00, 20.00 };

  int32_t n_samp = sizeof(X) / sizeof(X[0]);

  real8_t d[] = { 1.00, 1.00, 0.75, 0.50,  0.25,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,
                  0.00, 0.00, 0.25, 0.50,  0.75,  1.00,  0.75,  0.50,  0.25,  0.00,  0.00,
                  0.00, 0.00, 0.00, 0.00,  0.00,  0.00,  0.25,  0.50,  0.75,  1.00,  1.00 };

  Array<real8_t> M( 3, n_samp, d );

  real8_t ctrs[] = { 7.0, 11.0, 19.0 };
  fuzzy::Partition P( 3, ctrs );

  real8_t mu[3];

  for ( int32_t i=0; i<n_samp; i++ ) {
    P.mu( mu, X[i] );
    for ( int32_t j=0; j<3; j++ ) {
      EXPECT_DOUBLE_EQ( M.get(j,i), mu[j] );
    }
  }

}


// =======================================================================================
TEST( test_part_functions, area ) {
  // -------------------------------------------------------------------------------------
  real8_t tD[] = { 1.000, 0.750, 0.500, 0.250, 0.000 };
  int32_t nd  = sizeof(tD) / sizeof(tD[0]);

  real8_t D[3];

  real8_t test[nd][nd][nd] = 
      { { {  18.000, 16.750, 15.000, 12.750, 10.000,},
          {  17.625, 16.375, 14.625, 12.375,  9.625,},
          {  16.500, 15.250, 13.500, 11.250,  8.500,},
          {  14.625, 13.375, 11.625,  9.375,  6.625,},
          {  12.000, 10.750,  9.000,  6.750,  4.000,} },
        
        { {  17.375, 16.125, 14.375, 12.125,  9.375,},
          {  17.000, 15.750, 14.000, 11.750,  9.000,},
          {  15.875, 14.625, 12.875, 10.625,  7.875,},
          {  14.000, 12.750, 11.000,  8.750,  6.000,},
          {  11.375, 10.125,  8.375,  6.125,  3.375,} },
        
        { {  16.500, 15.250, 13.500, 11.250,  8.500,},
          {  16.125, 14.875, 13.125, 10.875,  8.125,},
          {  15.000, 13.750, 12.000,  9.750,  7.000,},
          {  13.125, 11.875, 10.125,  7.875,  5.125,},
          {  10.500,  9.250,  7.500,  5.250,  2.500,} },
        
        { {  15.375, 14.125, 12.375, 10.125,  7.375,},
          {  15.000, 13.750, 12.000,  9.750,  7.000,},
          {  13.875, 12.625, 10.875,  8.625,  5.875,},
          {  12.000, 10.750,  9.000,  6.750,  4.000,},
          {   9.375,  8.125,  6.375,  4.125,  1.375,} },
        
        { {  14.000, 12.750, 11.000,  8.750,  6.000,},
          {  13.625, 12.375, 10.625,  8.375,  5.625,},
          {  12.500, 11.250,  9.500,  7.250,  4.500,},
          {  10.625,  9.375,  7.625,  5.375,  2.625,},
          {   8.000,  6.750,  5.000,  2.750,  0.000,} } };

  real8_t ctrs[] = { 7.0, 11.0, 19.0 };
  fuzzy::Partition P( 3, ctrs );

  
  for ( int32_t a=0; a<nd; a++ ) {
    D[0] = tD[a];
    for ( int32_t b=0; b<nd; b++ ) {
      D[1] = tD[b];
      for ( int32_t c=0; c<nd; c++ ) {
        D[2] = tD[c];
        real8_t area = P.area( D );
        EXPECT_DOUBLE_EQ( test[a][b][c], area );
        fprintf( stdout, "%7.3f\n", test[a][b][c] );
      }
    }
  }

}



// =======================================================================================
TEST( test_part_functions, coa ) {
  // -------------------------------------------------------------------------------------
  real8_t tD[] = { 1.000, 0.750, 0.500, 0.250, 0.000 };
  int32_t nd  = sizeof(tD) / sizeof(tD[0]);

  real8_t D[3];

  real8_t test[nd][nd][nd] =
      { { {  14.000000000000, 13.517412935323, 12.822222222222, 11.823529411765, 10.266666666667,},
          {  14.056737588652, 13.567430025445, 12.860398860399, 11.838383838384, 10.225108225108,},
          {  14.212121212121, 13.699453551913, 12.950617283951, 11.844444444444, 10.019607843137,},
          {  14.461538461538, 13.900311526480, 13.060931899642, 11.760000000000,  9.383647798742,},
          {  14.833333333333, 14.178294573643, 13.148148148148, 11.370370370370,  7.166666666667,} },
  
        { {  14.278177458034, 13.798449612403, 13.107246376812, 12.109965635739, 10.533333333333,},
          {  14.343137254902, 13.857142857143, 13.154761904762, 12.134751773050, 10.500000000000,},
          {  14.524934383202, 14.017094017094, 13.275080906149, 12.172549019608, 10.317460317460,},
          {  14.827380952381, 14.274509803922, 13.446969696970, 12.152380952381,  9.708333333333,},
          {  15.304029304029, 14.666666666667, 13.661691542289, 11.891156462585,  7.333333333333,} },
  
        { {  14.676767676768, 14.202185792350, 13.518518518519, 12.525925925926, 10.921568627451,},
          {  14.754521963824, 14.274509803922, 13.580952380952, 12.567049808429, 10.902564102564,},
          {  14.977777777778, 14.478787878788, 13.750000000000, 12.658119658120, 10.761904761905,},
          {  15.365079365079, 14.828070175439, 14.024691358025, 12.751322751323, 10.211382113821,},
          {  16.015873015873, 15.414414414414, 14.466666666667, 12.746031746032,  7.533333333333,} },
  
        { {  15.219512195122, 14.755162241888, 14.087542087542, 13.111111111111, 11.480225988701,},
          {  15.316666666667, 14.848484848485, 14.173611111111, 13.179487179487, 11.488095238095,},
          {  15.603603603604, 15.122112211221, 14.421455938697, 13.362318840580, 11.432624113475,},
          {  16.125000000000, 15.620155038760, 14.870370370370, 13.666666666667, 11.041666666667,},
          {  17.066666666667, 16.543589743590, 15.738562091503, 14.242424242424,  7.757575757576,} },
    
        { {  15.952380952381, 15.509803921569, 14.878787878788, 13.952380952381, 12.333333333333,},
          {  16.079510703364, 15.636363636364, 15.003921568627, 14.069651741294, 12.400000000000,},
          {  16.466666666667, 16.022222222222, 15.385964912281, 14.425287356322, 12.555555555556,},
          {  17.207843137255, 16.773333333333, 16.153005464481, 15.178294573643, 12.761904761905,},
          {  18.666666666667, 18.333333333333, 17.933333333333, 17.484848484848,  1.000000000000,} } };


  real8_t ctrs[] = { 7.0, 11.0, 19.0 };
  fuzzy::Partition P( 3, ctrs );

  for ( int32_t a=0; a<nd; a++ ) {
    D[0] = tD[a];
    for ( int32_t b=0; b<nd; b++ ) {
      D[1] = tD[b];
      for ( int32_t c=0; c<nd; c++ ) {
        D[2] = tD[c];
        real8_t coa = P.coa( D );
        EXPECT_NEAR( test[a][b][c], coa, 1.0e-10 );
      }
    }
  }

#if 0
  std::cout << "{ ";
  for ( int32_t a=0; a<nd; a++ ) {
    D[0] = tD[a];
    std::cout << "{ ";
    for ( int32_t b=0; b<nd; b++ ) {
      D[1] = tD[b];
      std::cout << "{ ";
      for ( int32_t c=0; c<nd; c++ ) {
        D[2] = tD[c];
        real8_t coa = P.coa( D );
        std::cout << c_fmt( " %15.12f,", coa );
      }
      std::cout << "},\n";
    }
    std::cout << "},\n";
  }
  std::cout << "};\n";
#endif

}


// =======================================================================================
TEST( test_part_storage, load_store ) {
  // -------------------------------------------------------------------------------------
  real8_t ctrs1[] = { 7.0, 11.0, 19.0, 22.0, 25.0, 33.0 };
  real8_t ctrs2[] = { 1.0,  2.0,  3.0,  4.0,  5.0,  6.0 };
  const int32_t nc = sizeof(ctrs1) / sizeof(ctrs1[0]);
  fuzzy::Partition P1( nc, ctrs1 );
  fuzzy::Partition P2( nc, ctrs2 );

  for ( int32_t i=0; i<nc; i++ ) {
    EXPECT_DOUBLE_EQ( ctrs1[i], P1.get(i).getCenter() );
    EXPECT_DOUBLE_EQ( ctrs2[i], P2.get(i).getCenter() );
  }

  real8_t* buffer = P1.create_buffer();

  P1.store( buffer );

  P2.load( buffer );

  for ( int32_t i=0; i<nc; i++ ) {
    EXPECT_DOUBLE_EQ( ctrs1[i], P2.get(i).getCenter() );
  }

  delete[] buffer;
}


// =======================================================================================
TEST( test_part_storage, read_write ) {
  // -------------------------------------------------------------------------------------
  real8_t ctrs1[] = { 7.0, 11.0, 19.0, 22.0, 25.0, 33.0 };
  const int32_t nc = sizeof(ctrs1) / sizeof(ctrs1[0]);
  fuzzy::Partition P1( nc, ctrs1 );
  fuzzy::Partition P2;

  for ( int32_t i=0; i<nc; i++ ) {
    EXPECT_DOUBLE_EQ( ctrs1[i], P1.get(i).getCenter() );
  }

  std::ofstream ofs = FileTool::openWrite( "/tmp/part" );
  P1.write( ofs );
  ofs.close();

  std::ifstream ifs = FileTool::openRead( "/tmp/part" );
  P2.read( ifs );
  ofs.close();

  for ( int32_t i=0; i<nc; i++ ) {
    EXPECT_DOUBLE_EQ( ctrs1[i], P2.get(i).getCenter() );
  }
}


} // end namespace


// =======================================================================================
// **                           U T E S T _ P A R T I T I O N                           **
// ======================================================================== END FILE =====
