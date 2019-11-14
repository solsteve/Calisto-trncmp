// ====================================================================== BEGIN FILE =====
// **                             C T E S T _ P S G R A P H                             **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019, Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
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
/** @brief Test the PSGraph class.
 *  @file   ctest_psgraph.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-26
 *
 *  This is a test of the PSGraph class.
 */
// =======================================================================================

#include <PSGraph.hh>



// =======================================================================================
// ---------------------------------------------------------------------------------------
int test01( void ) {
  // -------------------------------------------------------------------------------------
  PSGraph* ps = new PSGraph(2);

  PSGraph::Draw* pd01 = new PSGraph::Draw( 8.5, 3.0, -85.0, -30.0, 85.0, 30.0 );
  PSGraph::Draw* pd02 = new PSGraph::Draw( 4.0, 3.0, -10.0, -10.0, 10.0, 10.0 );
  PSGraph::Draw* pd03 = new PSGraph::Draw( 4.0, 2.0, -10.0, -10.0, 10.0, 10.0 );
  PSGraph::Draw* pd04 = new PSGraph::Draw( 4.0, 0.5, -10.0, -10.0, 10.0, 10.0 );

  PSGraph::Draw* pd11 = new PSGraph::Draw( 4.5, 3.5, -10.0, -10.0, 10.0, 10.0 );
  PSGraph::Draw* pd12 = new PSGraph::Draw( 4.5, 2.5, -10.0, -10.0, 10.0, 10.0 );
  PSGraph::Draw* pd13 = new PSGraph::Draw( 4.0, 6.5, 0.0, 0.0, 4.0, 6.5 );

  pd01->drawBorder();
  pd02->drawBorder();
  pd03->drawBorder();
  pd04->drawBorder();

  pd11->drawBorder();
  pd12->drawBorder();
  pd13->drawBorder();

  pd01->setRGB( 1.0, 0.0, 0.0 );
  pd01->drawEllipse( 0.0, 0.0, 30.0, 10.0, 45.0 );
  pd01->fillEllipse( 40.0, 0.0, 30.0, 10.0, -45.0 );
  pd01->drawCircle(  0.0, 0.0, 10.0, 7 );
  pd01->fillCircle( -30.0, 0.0, 10.0 );

  pd02->setRGB( PSGraph::Color::blue );
  pd02->drawLine( -9.0, -9.0, 9.0, 9.0 );

  pd04->write( "Heather", -10.0, -10.0, 10.0, 10.0 );

  pd03->write( "Rebekah", -8.0, -8.0, 2.0, 1.0, 30 );

  pd01->saveColor();

  pd01->setRGB( PSGraph::Color::cyan );
  pd01->write_inch( "Stephen", 0.0, 0.0, 2.0, 1.0, 30.0 );

  pd01->setRGB( PSGraph::Color::green );
  pd01->write_inch( "Stephen", 0.0, 0.0, 2.0, 1.0 );

  pd01->restoreColor();
  pd01->drawRay( -85.0, 30.0, 60.0, DEG2RAD(-45.0) ); // radians

  pd11->setFont( PSGraph::NORMAL );
  pd11->write_inch( "Roman Font",  0.5, 2.5, 2.0, 0.5 );
  pd11->setFont( PSGraph::BOLD );
  pd11->write_inch( "Bold Font",   0.5, 1.5, 2.0, 0.5 );
  pd11->setFont( PSGraph::ITALIC );
  pd11->write_inch( "Italic Font", 0.5, 0.5, 2.0, 0.5 );

  pd12->drawRectangle( -8.0, -8.0, -1.0, -1.0 );
  pd12->fillRectangle(  4.0,  4.0,  6.0,  5.0 );


  double px1[] = { 0.8, 0.7, 1.4, 1.5, 3.2, 1.7, 2.0 };
  double py1[] = { 1.6, 2.6, 3.5, 4.2, 3.5, 2.5, 0.8 };
  size_t pn1 = sizeof(px1)/sizeof(px1[0]);

  double px2[] = { 1.2, 1.5, 2.2, 2.8, 3.3, 2.3 };
  double py2[] = { 5.0, 6.2, 5.2, 5.8, 5.3, 4.4 };
  size_t pn2 = sizeof(px2)/sizeof(px2[0]);

  pd13->drawPolygon( px1, py1, pn1 );
  pd13->setRGB( PSGraph::Color::blue );
  pd13->fillPolygon( px2, py2, pn2 );

  ps->add( pd01, 0, 1.0, 1.0 );
  ps->add( pd02, 0, 1.0, 4.5 );
  ps->add( pd03, 0, 5.5, 5.5 );
  ps->add( pd04, 0, 5.5, 4.5 );

  ps->add( pd11, 1, 5.5, 1.0 );
  ps->add( pd12, 1, 5.5, 5.0 );
  ps->add( pd13, 1, 1.0, 1.0 );

  ps->pswrite( "psgraph-Cpp.ps" );
  
  delete ps;

  delete pd01;
  delete pd02;
  delete pd03;
  delete pd04;

  delete pd11;
  delete pd12;
  delete pd13;
}


static real8_t clr[8][3] = {
  { 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  { 0.0, 1.0, 0.0 },
  { 0.0, 1.0, 1.0 },
  { 1.0, 0.0, 0.0 },
  { 1.0, 0.0, 1.0 },
  { 1.0, 1.0, 0.0 },
  { 1.0, 1.0, 1.0 },
};

static int perm[][9] = {
  {0,1,3,2,6,7,5,4,0},
  {0,1,3,7,5,4,6,2,0},
  {0,1,5,4,6,7,3,2,0},
  {0,1,5,7,3,2,6,4,0},
  {0,2,3,1,5,7,6,4,0},
  {0,2,3,7,6,4,5,1,0},
  {0,2,6,4,5,7,3,1,0},
  {0,2,6,7,3,1,5,4,0},
  {0,4,5,1,3,7,6,2,0},
  {0,4,5,7,6,3,2,1,0},
  {0,4,6,2,3,7,5,1,0},
  {0,4,6,7,5,1,3,2,0},
};

static int N = sizeof(perm)/sizeof(perm[0]);



int intc( real8_t x ) {
  int v = (int)floor(x * 2.56e2 + D_HALF );
  if ( v < 0 ) v = 0;
  if (255 < v ) v = 255;
  return v;
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
void test02( void ) {
  // -------------------------------------------------------------------------------------
  PSGraph* ps = new PSGraph(1);
  real8_t fn = (real8_t) N;
  PSGraph::Draw* pd = new PSGraph::Draw( 11.0, 8.5, 0.0, 0.0, 32.0, fn );

  std::cout << N << std::endl;

  pd->drawBorder();

  for (int j=0; j<N; j++) {
    real8_t x0 = D_ZERO;
    real8_t x1 = x0+D_ONE;
    real8_t y0 = (real8_t)j;
    real8_t y1 = y0+D_ONE;
    for (int i=0; i<8; i++) {
      int P1 = perm[8][i];
      int P2 = perm[8][i+1];
      real8_t R1 = clr[P1][0];
      real8_t G1 = clr[P1][1];
      real8_t B1 = clr[P1][2];
      real8_t R2 = clr[P2][0];
      real8_t G2 = clr[P2][1];
      real8_t B2 = clr[P2][2];
      real8_t R3 = D_HALF*(R1+R2);
      real8_t G3 = D_HALF*(G1+G2);
      real8_t B3 = D_HALF*(B1+B2);
      pd->setRGB( R1, G1, B1 );
      fprintf( stdout, "%3.1f %3.1f %3.1f == %3d %3d %3d\n", R1, G1, B1, intc(R1), intc(G1), intc(B1) );
      fprintf( stdout, "%3.1f %3.1f %3.1f == %3d %3d %3d\n", R3, G3, B3, intc(R3), intc(G3), intc(B3) );
      pd->fillRectangle(x0,y0,x1,y1);
      pd->fillRectangle(x0+16,y0,x1+16,y1);
      x0 += D_ONE;
      x1 += D_ONE;
      pd->setRGB( R3, G3, B3 );
      pd->fillRectangle(x0,y0,x1,y1);
      pd->fillRectangle(x0+16,y0,x1+16,y1);
      x0 += D_ONE;
      x1 += D_ONE;
    }
    std::cout << "---------------------" << std::endl;
    break;
  }
  
  ps->add( pd, 0, 0.0, 0.0 );

  ps->pswrite( "rainbow.ps" );

  delete ps;
  delete pd;
}



// =======================================================================================
// ---------------------------------------------------------------------------------------
int main( void ) {
  // -------------------------------------------------------------------------------------
  test02();
  return 0;
}

// =======================================================================================
// **                             C T E S T _ P S G R A P H                             **
// ======================================================================== END FILE =====
