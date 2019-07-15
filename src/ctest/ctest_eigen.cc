#include <iostream>
#include <fstream>
#include <EigenSystem.hh>


using namespace std;



int TEST02( void ) {
  std::cout << "\n----- TRNCMP - EigenSystem (gen) ------------------\n";
  double data[] = {
		   -1.01,  3.98,  3.30,  4.43,  7.31,
		   0.86,  0.53,  8.26,  4.96, -6.43,
		   -4.60, -7.04, -3.89, -7.66, -6.16,
		   3.31,  5.29,  8.20, -7.33,  2.47,
		   -4.81,  3.55, -1.51,  6.18,  5.58 };

  EigenSystem* EG = EigenSystem::general( data, 5 );
  EG->compute();
  EG->display( std::cout, "%.2f" );

  delete EG;

  return 0;
}



int TEST03( void ) {
  std::cout << "\n----- TRNCMP - EigenSystem (sym as gen) -----------\n";
  double data[] = {    1.96,  -6.49,  -0.47,  -7.20,  -0.65,
		      -6.49,   3.80,  -6.39,   1.50,  -6.34,
		      -0.47,  -6.39,   4.17,  -1.51,   2.67,
		      -7.20,   1.50,  -1.51,   5.70,   1.80,
		      -0.65,  -6.34,   2.67,   1.80,  -7.10 };

  EigenSystem* EG = EigenSystem::general( data, 5 );
  EG->compute();
  EG->display( std::cout, "%10.6f" );

  delete EG;

  return 0;
}


int TEST04( void ) {
  std::cout << "\n----- TRNCMP - EigenSystem (sym) ------------------\n";
  double data[] = {    1.96,  -6.49,  -0.47,  -7.20,  -0.65,
		      -6.49,   3.80,  -6.39,   1.50,  -6.34,
		      -0.47,  -6.39,   4.17,  -1.51,   2.67,
		      -7.20,   1.50,  -1.51,   5.70,   1.80,
		      -0.65,  -6.34,   2.67,   1.80,  -7.10 };

  EigenSystem* EG = EigenSystem::symetric( data, 5 );
  EG->compute();
  EG->display( std::cout, "%.2f" );

  delete EG;

  return 0;
}



int main( void ) {
  TEST02();
  TEST03();
  TEST04();
  return 0;
}


/*
      1.96  -6.49  -0.47  -7.20  -0.65
    -6.49   3.80  -6.39   1.50  -6.34
    -0.47  -6.39   4.17  -1.51   2.67
    -7.20   1.50  -1.51   5.70   1.80
    -0.65  -6.34   2.67   1.80  -7.10

 Eigenvalues
 -11.07  -6.23   0.86   8.87  16.09

 Eigenvectors (stored columnwise)
  -0.30  -0.61   0.40  -0.37   0.49
  -0.51  -0.29  -0.41  -0.36  -0.61
  -0.08  -0.38  -0.66   0.50   0.40
   0.00  -0.45   0.46   0.62  -0.46
  -0.80   0.45   0.17   0.31   0.16

=========================================

    -1.01   0.86  -4.60   3.31  -4.81
     3.98   0.53  -7.04   5.29   3.55
     3.30   8.26  -3.89   8.20  -1.51
     4.43   4.96  -7.66  -7.33   6.18
     7.31  -6.43  -6.16   2.47   5.58


 Eigenvalues
 (  2.86, 10.76) (  2.86,-10.76) ( -0.69,  4.70) ( -0.69, -4.70) -10.46

 Left eigenvectors
 (  0.04,  0.29) (  0.04, -0.29) ( -0.13, -0.33) ( -0.13,  0.33)   0.04
 (  0.62,  0.00) (  0.62,  0.00) (  0.69,  0.00) (  0.69,  0.00)   0.56
 ( -0.04, -0.58) ( -0.04,  0.58) ( -0.39, -0.07) ( -0.39,  0.07)  -0.13
 (  0.28,  0.01) (  0.28, -0.01) ( -0.02, -0.19) ( -0.02,  0.19)  -0.80
 ( -0.04,  0.34) ( -0.04, -0.34) ( -0.40,  0.22) ( -0.40, -0.22)   0.18

 Right eigenvectors
 (  0.11,  0.17) (  0.11, -0.17) (  0.73,  0.00) (  0.73,  0.00)   0.46
 (  0.41, -0.26) (  0.41,  0.26) ( -0.03, -0.02) ( -0.03,  0.02)   0.34
 (  0.10, -0.51) (  0.10,  0.51) (  0.19, -0.29) (  0.19,  0.29)   0.31
 (  0.40, -0.09) (  0.40,  0.09) ( -0.08, -0.08) ( -0.08,  0.08)  -0.74
 (  0.54,  0.00) (  0.54,  0.00) ( -0.29, -0.49) ( -0.29,  0.49)   0.16












 */
