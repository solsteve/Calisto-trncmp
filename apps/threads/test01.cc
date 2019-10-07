
#include <trncmp.hh>

#include <omp.h>

  static const long ns = 1000000000;


double SEQ( void ) {
  int i;
  double pi, sum = 0.0;

  const double step = 1.0 / (double) ns;
  real8_t start_time = omp_get_wtime();

  for ( i=0; i<ns; i++ ) {
    double x = ((double)i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }
  real8_t elapse_time = omp_get_wtime() - start_time;
  std::cout << elapse_time << "\n";

  return step*sum;
}


double PAR( void ) {
  int i;
  double pi, sum = 0.0;

  const double step = 1.0 / (double) ns;

  // ====================================
  real8_t start_time = omp_get_wtime();
#pragma omp parallel for reduction(+:sum)
  for ( i=0; i<ns; i++ ) {
    double x = ((double)i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }
  // ====================================
  real8_t elapse_time = omp_get_wtime() - start_time;
  std::cout << elapse_time << "\n";
  return step*sum;
}




int main( void ) {

  double S = SEQ();
  std::cout << c_fmt( "%.12f", S ) << "\n";

  double P = PAR();
  std::cout << c_fmt( "%.12f", P ) << "\n";
  

      

  return 0;
}
