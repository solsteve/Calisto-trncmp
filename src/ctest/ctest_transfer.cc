// ====================================================================== BEGIN FILE =====
// **                            C T E S T _ T R A N S F E R                            **
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
/** @brief  Test nns/Transfer functions.
 *  @file   ctest_bpn.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-12
 */
// =======================================================================================

#include <nns/Transfer.hh>
#include <PSGraph.hh>

const int NG = 4;
const int PN = 1;

const int PLOT = 100;
  
const real8_t MINX[NG] = { -2.00, -2.00, -2.00, -2.00 };
const real8_t MAXX[NG] = {  2.00,  2.00,  2.00,  2.00 };
const real8_t MINY[NG] = {  0.00,  0.00, -1.00,  0.00 };
const real8_t MAXY[NG] = {  1.00,  1.00,  1.00,  1.00 };
const real8_t POSX[NG] = {  0.50,  5.75,  0.50,  5.75 };
const real8_t POSY[NG] = {  4.50,  4.50,  0.50,  0.50 };
const int     PAGE[NG] = { 0, 0, 0, 0 };

const real8_t WIDTH  = 4.75;
const real8_t HEIGHT = 3.50;
      
nns::transfer_e ttype[NG] = { nns::SIGMOID, nns::RELU, nns::TANH, nns::GAUSSIAN };





// =======================================================================================
void mark( PSGraph::Draw* pd, real8_t val, real8_t x, real8_t y ) {
  // -------------------------------------------------------------------------------------
  char buffer[16];
  sprintf( buffer, "%.2f", val );
  pd->write_inch( buffer, x, y, 0.5, 0.125 );
}


// =======================================================================================
int main( void ) {
  // -------------------------------------------------------------------------------------
  PSGraph*       ps = new PSGraph(PN);
  nns::Transfer* T[NG];
  PSGraph::Draw* pd[4];

  for ( int i=0; i<NG; i++ ) {
    T[i]  = nns::Transfer::createPtr( ttype[i] );
    pd[i] = new PSGraph::Draw( WIDTH, HEIGHT, MINX[i], MINY[i], MAXX[i], MAXY[i] );
  
    pd[i]->setRGB( PSGraph::Color::blue );
    pd[i]->drawBorder();

    pd[i]->setRGB( PSGraph::Color::red );

    pd[i]->drawLine( MINX[i], 0.0, MAXX[i], 0.0 );
    pd[i]->drawLine( 0.0, MINY[i], 0.0, MAXY[i] );
    
    real8_t last_x = MINX[i];
    real8_t delta  = (MAXX[i] - MINX[i]) / (real8_t)PLOT;

    real8_t last_y  = T[i]->activate( last_x );
    real8_t last_dy = T[i]->gradient( last_y, last_x );

    for ( int j=0; j<PLOT; j++ ) {
      real8_t x = last_x + delta;

      real8_t y  = T[i]->activate( x );
      real8_t dy = T[i]->gradient( y, x );

      pd[i]->setRGB( PSGraph::Color::black );
      pd[i]->drawLine( last_x, last_y, x, y );

      pd[i]->setRGB( PSGraph::Color::green );
      pd[i]->drawLine( last_x, last_dy, x, dy );

      last_x  = x;
      last_y  = y;
      last_dy = dy;
    }
    
    pd[i]->setRGB( PSGraph::Color::blue );
    pd[i]->write_inch( T[i]->name(), 0.25, HEIGHT-0.5, 1.0, 0.25 );

    real8_t xbase = HEIGHT*(0.0-MINY[i])/(MAXY[i]-MINY[i]);
    real8_t ybase = WIDTH*(0.0-MINX[i])/(MAXX[i]-MINX[i]);
    
    mark( pd[i], MINY[i], ybase + 0.125, 0.125 );
    mark( pd[i], MAXY[i], ybase + 0.125, HEIGHT-0.25 );

    mark( pd[i], MINX[i], 0.125,       xbase+0.125 );
    mark( pd[i], MAXX[i], WIDTH-0.625, xbase+0.125 );

  }





  
  for ( int i=0; i<NG; i++ ) {
    ps->add( pd[i], PAGE[i], POSX[i], POSY[i] );
  }

  ps->pswrite( "transfer.ps" );

  delete ps;

  for ( int i=0; i<4; i++ ) {
    delete pd[i];
    delete T[i];
  }
  
  return 0;
}

// =======================================================================================
// **                                C T E S T _ B P N N                                **
// ======================================================================== END FILE =====
