#include <trncmp.hh>
#include <Dice.hh>

#include <omp.h>

// =======================================================================================
class Point {
  // -------------------------------------------------------------------------------------
 public:
  real8_t x;
  real8_t y;
  real8_t z;
  int16_t flag;
  Point(void) : x(0.0), y(0.0), z(0.0), flag(0) {};
  ~Point(void) {};

  static real8_t dist2( Point& A, Point& B );
};

// =======================================================================================
inline real8_t Point::dist2( Point& A, Point& B ) {
  // -------------------------------------------------------------------------------------
  real8_t dx = A.x - B.x;
  real8_t dy = A.y - B.y;
  real8_t dz = A.z - B.z;
  return (dx*dx) + (dy*dy) + (dz*dz);
}

// =======================================================================================
class Cloud {
  // -------------------------------------------------------------------------------------
 public:
  size_t num_pts;
  Point* points;

  Cloud( size_t n );
  ~Cloud( void );

  void randomize();
};

// =======================================================================================
Cloud::Cloud( size_t n ) : num_pts(0), points(0) {
  // -------------------------------------------------------------------------------------
  points  = new Point[ n ];
  num_pts = n;
}

// =======================================================================================
Cloud::~Cloud( void ) {
  // -------------------------------------------------------------------------------------
  delete[] points;
}


// =======================================================================================
void Cloud::randomize( void ) {
  // -------------------------------------------------------------------------------------
  Dice* dd = Dice::getInstance();

  for ( size_t k=0; k<num_pts; k++ ) {
    points[k].x = 200.0 * dd->uniform() - 100.0;
    points[k].y = 200.0 * dd->uniform() - 100.0;
    points[k].z = 200.0 * dd->uniform() - 100.0;
  }
}

// =======================================================================================
size_t findClosest( size_t id, Cloud* G, Cloud* P ) {
  // -------------------------------------------------------------------------------------
  size_t  min_idx = 0;
  real8_t min_dist = Point::dist2( G->points[id], P->points[0] );

  size_t np = P->num_pts;
  for ( size_t idx=1; idx<np; idx++ ) {
    real8_t d = Point::dist2( G->points[id], P->points[idx] );
    if ( d < min_dist ) {
      min_dist = d;
      min_idx  = idx;
    }
  }
  return min_idx;
}

// =======================================================================================
void Test( size_t* idx, Cloud* P, Cloud* G ) {
  // -------------------------------------------------------------------------------------
  real8_t mse = 0.0;
  size_t np = G->num_pts;
  for ( size_t i=0; i<np; i++ ) {
    mse += Point::dist2( G->points[i], P->points[idx[i]] );
  }
  std::cout << "MSE = " << mse << std::endl;
}
  

// =======================================================================================
int main( void ) {
  // -------------------------------------------------------------------------------------
  Dice* dd = Dice::getInstance();

  const size_t GKB_POINTS  = 10000;
  const size_t PTN_POINTS  = 1000000;

  Cloud*  gkb      = new Cloud( GKB_POINTS );
  Cloud*  pnet     = new Cloud( PTN_POINTS );
  size_t* index    = new size_t[ PTN_POINTS ];
  int*    serviced = new int[ GKB_POINTS ];
  int*    used     = new int[ GKB_POINTS ];
  
  gkb->randomize();
  pnet->randomize();

  for ( size_t i=0; i<PTN_POINTS; i++ ) {
    index[i] = dd->index( PTN_POINTS );
  }  

  for ( size_t i=0; i<GKB_POINTS; i++ ) {
    serviced[i] = -1;
    used[i]     = 0;
  }

  Test( index, pnet, gkb );
  
  real8_t start_time = omp_get_wtime();

  size_t j;
  // ====================================
#pragma omp parallel for private(j) shared(GKB_POINTS,gkb,pnet,index,serviced,used)
  for ( j=0; j<GKB_POINTS; j++ ) {
    index[j] = findClosest( j, gkb, pnet );
    serviced[j] = omp_get_thread_num();
    used[j] += 1;
  }
  // ====================================

  real8_t elapsed = omp_get_wtime() - start_time;
  
  Test( index, pnet, gkb );

  std::cout << "Ran in " << c_fmt( "%.3f", elapsed ) << " seconds\n";


  delete index;
  delete serviced;
  delete used;

  delete gkb;
  delete pnet;

  return 0;
}
