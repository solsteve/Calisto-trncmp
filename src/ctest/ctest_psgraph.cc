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
int main( void ) {
  // -------------------------------------------------------------------------------------
  PSGraph* ps = new PSGraph(2);

  PSGraph::Draw* pd01 = new PSGraph::Draw( 8.5, 3.0, -85.0, -30.0, 85.0, 30.0 );
  PSGraph::Draw* pd02 = new PSGraph::Draw( 4.0, 3.0, -10.0, -10.0, 10.0, 10.0 );
  PSGraph::Draw* pd03 = new PSGraph::Draw( 4.0, 2.0, -10.0, -10.0, 10.0, 10.0 );
  PSGraph::Draw* pd04 = new PSGraph::Draw( 4.0, 0.5, -10.0, -10.0, 10.0, 10.0 );

  PSGraph::Draw* pd11 = new PSGraph::Draw( 4.5, 3.5, -10.0, -10.0, 10.0, 10.0 );
  PSGraph::Draw* pd12 = new PSGraph::Draw( 4.5, 2.5, -10.0, -10.0, 10.0, 10.0 );
  PSGraph::Draw* pd13 = new PSGraph::Draw( 4.0, 6.5, 0.0, 0.0, 4.0, 6.5 );

//  pd01->drawBorder();
//  pd02->drawBorder();
//  pd03->drawBorder();
//  pd04->drawBorder();

//  pd11->drawBorder();
//  pd12->drawBorder();
//  pd13->drawBorder();

//  pd01->setRGB( 1.0, 0.0, 0.0 );
//  pd01->drawEllipse( 0.0, 0.0, 30.0, 10.0, 45.0 );
//  pd01->drawCircle(  0.0, 0.0, 10.0, 7 );

//  pd02->setRGB( Color::blue );
  pd02->drawLine( -9.0, -9.0, 9.0, 9.0 );

//  pd04->write( "Heather", -10.0, -10.0, 10.0, 10.0 );

//  pd03->write( "Rebekah", -8.0, -8.0, 2.0, 1.0, 30 );

//  pd01->saveColor();

//  pd01->setRGB( Color::cyan );
//  pd01->write_inch( "Stephen", 0.0, 0.0, 2.0, 1.0, 30.0 );

//  pd01->setRGB( Color::green );
//  pd01->write_inch( "Stephen", 0.0, 0.0, 2.0, 1.0 );

//  pd01->restoreColor();
//  pd01->drawRay( -85.0, 30.0, 60.0, DEG2RAD(-45.0) ); // radians

//  pd11->setFont( NORMAL );
//  pd11->write_inch( "Roman Font",  0.5, 2.5, 2.0, 0.5 );
//  pd11->setFont( BOLD );
//  pd11->write_inch( "Bold Font",   0.5, 1.5, 2.0, 0.5 );
//  pd11->setFont( ITALIC );
//  pd11->write_inch( "Italic Font", 0.5, 0.5, 2.0, 0.5 );

//  pd12->drawRectangle( -8.0, -8.0, -1.0, -1.0 );
//  pd12->drawRectangle( 4.0, 4.0, 6.0, 5.0, true );


  double px1[] = { 0.8, 0.7, 1.4, 1.5, 3.2, 1.7, 2.0 };
  double py1[] = { 1.6, 2.6, 3.5, 4.2, 3.5, 2.5, 0.8 };
  size_t pn1 = sizeof(px1)/sizeof(px1[0]);

  double px2[] = { 1.2, 1.5, 2.2, 2.8, 3.3, 2.3 };
  double py2[] = { 5.0, 6.2, 5.2, 5.8, 5.3, 4.4 };
  size_t pn2 = sizeof(px2)/sizeof(px2[0]);

//  pd13->drawPolygon( px1, py1, pn1 );
//  pd13->setRGB( Color::blue );
//  pd13->drawPolygon( px2, py2, pn2, true );

  ps->add( pd01, 0, 1.0, 1.0 );
  ps->add( pd02, 0, 1.0, 4.5 );
  ps->add( pd03, 0, 5.5, 5.5 );
  ps->add( pd04, 0, 5.5, 4.5 );

  ps->add( pd11, 1, 5.5, 1.0 );
  ps->add( pd12, 1, 5.5, 5.0 );
  ps->add( pd13, 1, 1.0, 1.0 );

  ps->pswrite( "psgraph-Cpp.ps" );
  
  delete pd01;
  delete pd02;
  delete pd03;
  delete pd04;

  delete pd11;
  delete pd12;
  delete pd13;

  delete ps;

  return 0;
}


// =======================================================================================
// **                             C T E S T _ P S G R A P H                             **
// ======================================================================== END FILE =====
