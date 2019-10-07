#include <trncmp.hh>

#include <omp.h>

void  build( int* a, int n, int mp ) {
  int mpx = mp + 1;
  for ( int j=0; j<n; j++ ) {
    a[j] = mpx * j;
  }
}


int main( void ) {

  int NT = 6;
  int NM = 40;
  
  int** part = new int*[NT];

  for ( int32_t i=0; i<NT; i++ ) {
    part[i] = new int[NM];
  }

  // ====================================
#pragma omp parallel shared(part)
  { // ----------------------------------
    int id = omp_get_thread_num();
    if ( id < NT ) {
      build( part[id], NM, id );
    }
  } // ==================================

  
  for ( int32_t i=0; i<NT; i++ ) {
    std::cout << i << ":";
    for ( int j=0; j<NM; j++ ) {
      std::cout << " " << part[i][j];
    }
    std::cout << "\n";
  }
  

  return 0;
}
