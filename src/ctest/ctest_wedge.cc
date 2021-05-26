// ====================================================================== BEGIN FILE =====
// **                               C T E S T _ W E D G E                               **
// =======================================================================================
// **                                                                                   **
// **  Copyright (c) 2020, Stephen W. Soliday                                           **
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
/** @brief  Fast Wedge Calculation.
 *  @file   ctest_wedge.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Oct-23
 *
 *  This is a test of a fast wedge test.
 */
// =======================================================================================

#include <PSGraph.hh>
#include <Dice.hh>


// =======================================================================================
class Wedge {
  // -------------------------------------------------------------------------------------
 public:
  real8_t center;
  real8_t half_width;
  real8_t A1;
  real8_t A2;
  real8_t S1;
  real8_t C1;
  real8_t S2;
  real8_t C2;
  
  Wedge( void ) : center(0.0), half_width(0.0), A1(0.0), A2(0.0),
                  S1(0.0), C1(0.0), S2(0.0), C2(0.0) {}
  ~Wedge( void ) {};
  void setRadians( real8_t ctr, real8_t wdt );
  void setDegrees( real8_t ctr, real8_t wdt );
};

// =======================================================================================
void Wedge::setRadians( real8_t ctr, real8_t wdt ) {
  // -------------------------------------------------------------------------------------
  center = D_PI_2 - ctr;
  if ( center < 0.0e0 ) {
    center = D_2PI + center;
  }

  half_width = 5.0e-1 * wdt;

  A1 = center - half_width;
  A2 = center + half_width;

  S1 = sin( A1 );
  C1 = cos( A1 );
  S2 = sin( A2 );
  C2 = cos( A2 );
}

// =======================================================================================
void Wedge::setDegrees( real8_t ctr, real8_t wdt ) {
  // -------------------------------------------------------------------------------------
  setRadians( ctr * D_PI / 1.8e2, wdt * D_PI / 1.8e2 );
}


// =======================================================================================
class Point {
  // -------------------------------------------------------------------------------------
 public:
  real8_t x;
  real8_t y;
  bool    available;
  bool    flag;
  Point( void ) : x(0.0), y(0.0), available(false), flag(false) {};
  ~Point( void ) {};
};

// =======================================================================================
class Group {
  // -------------------------------------------------------------------------------------
 protected:
  Point* points;
  size_t num;

  Group(const Group&);
  Group& operator=(const Group&);

 public:
  Group( size_t n, Dice *dd );
  ~Group( void );

  size_t N( void ) const { return num; }
  Point& point( size_t idx ) { return points[idx]; }
};

// =======================================================================================
Group::Group( size_t n, Dice *dd ) : points(0), num(0) {
  // -------------------------------------------------------------------------------------
  num    = n;
  points = new Point[ num ];
  for ( size_t i=0; i<num; i++ ) {
    points[i].x = dd->uniform()*2.0 - 1.0;
    points[i].y = dd->uniform()*2.0 - 1.0;
    points[i].available = true;
    points[i].flag      = false;
  }
}

// =======================================================================================
Group::~Group( void ) {
  // -------------------------------------------------------------------------------------
  delete[] points;
  points = static_cast<Point*>(0);
  num = 0;
}




// =======================================================================================
// ---------------------------------------------------------------------------------------
void process_fast( real8_t cx, real8_t cy, Group& grp, Wedge* wedge ) {
  // -------------------------------------------------------------------------------------
  // +:0   -:4   *:4   /:0
  // -------------------------------------------------------------------------------------
  real8_t S1 = wedge->S1;
  real8_t S2 = wedge->S2;
  real8_t C1 = wedge->C1;
  real8_t C2 = wedge->C2;
  
  for ( int j=0; j<grp.N(); j++ ) {
    real8_t dx = grp.point(j).x - cx;
    real8_t dy = grp.point(j).y - cy;
    
    real8_t cross1 = dy*C1 - dx*S1;
    real8_t cross2 = dx*S2 - dy*C2;
    
    bool flag = true;
    if ( cross1 < D_ZERO ) flag = false;
    if ( cross2 < D_ZERO ) flag = false;
    grp.point(j).flag = flag;
  }
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void process_naive( real8_t cx, real8_t cy, Group& grp, Wedge* wedge ) {
  // +:0   -:2   *:0   /:0  arctan:1
  // -------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------
  real8_t ang1 = wedge->A1;
  real8_t ang2 = wedge->A2;
  
  for ( int j=0; j<grp.N(); j++ ) {
    real8_t dx   = grp.point(j).x - cx;
    real8_t dy   = grp.point(j).y - cy;

    real8_t ang = ArcTan( dy, dx );

    if ( ang > ang1 ) {
      if ( ang < ang2 ) {
        grp.point(j).flag = true;
      }
    }
  }  
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void wedge_test( PSGraph::Draw* pd, size_t np ) {
  // -------------------------------------------------------------------------------------
  Dice *dd = Dice::getInstance();
  dd->seed_set();

  Group grp( np, dd );

  real8_t angle = dd->uniform() *360.0;
  real8_t width = 10.0 + dd->uniform() * 20.0;

  Wedge* wedge = new Wedge();
  wedge->setDegrees( angle, width );

  real8_t cx = 0.0;
  real8_t cy = 0.0;

  real8_t w0_x = cx + wedge->C1;
  real8_t w0_y = cy + wedge->S1;
  real8_t w1_x = cx + wedge->C2;
  real8_t w1_y = cy + wedge->S2;

  real8_t w_cx = cx + cos(wedge->center);
  real8_t w_cy = cy + sin(wedge->center);

  pd->setRGB( PSGraph::Color::blue );
  pd->drawLine( cx, cy, w0_x, w0_y );
  pd->drawLine( cx, cy, w1_x, w1_y );
  
  pd->setRGB( PSGraph::Color::red );
  pd->drawLine( cx, cy, w_cx, w_cy );
  
  process_fast( cx, cy, grp, wedge );    
  
  for ( int j=0; j<grp.N(); j++ ) {
    real8_t x = grp.point(j).x;
    real8_t y = grp.point(j).y;

    if ( grp.point(j).flag ) {
      pd->setRGB( PSGraph::Color::green );
    } else {
      pd->setRGB( PSGraph::Color::black );
    }
    pd->fillCircle( x, y, 0.01 );
  }

  delete wedge;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
int main( void ) {
  // -------------------------------------------------------------------------------------
  PSGraph* ps = new PSGraph(1);
  
  PSGraph::Draw* pd = new PSGraph::Draw( 7.5, 7.5, -1.0, -1.0, 1.0, 1.0 );

  pd->setRGB( PSGraph::Color::blue );
  pd->drawBorder();

  pd->setRGB( PSGraph::Color::black );

  wedge_test( pd, 1000 );

  ps->add( pd, 0, 1.75, 0.5 );

  ps->pswrite( "wedge.ps" );
  
  //delete pd;
  delete ps;

  return 0;
}

// =======================================================================================
// **                             C T E S T _ P S G R A P H                             **
// ======================================================================== END FILE =====
