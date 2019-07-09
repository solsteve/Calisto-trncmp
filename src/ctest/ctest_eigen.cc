#include <iostream>
#include <fstream>
#include <EigenSystem.hh>


using namespace std;

// dgeev_ is a symbol in the LAPACK library files
extern "C" {
extern int dgeev_(char*,char*,int*,double*,int*,double*, double*, double*, int*, double*, int*, double*, int*, int*);
}








int TEST01( void ) {

  int n;
  double data[] = { 0.35, 0.45, -0.14, -0.17,
		    0.09, 0.07, -0.54, 0.35,
		    -0.44, -0.33, -0.03, 0.17,
		    0.25, -0.32, -0.13, 0.11 };
  n = 4;
  
  // allocate data
  char Nchar='N';
  char Vchar='V';
  double *eigReal=new double[n];
  double *eigImag=new double[n];
  double *vl=new double[n*n];
  double *vr=new double[n*n];
  int one=1;
  int lwork=48*n;
  double *work=new double[lwork];
  int info;

  // calculate eigenvalues using the DGEEV subroutine
  dgeev_(&Nchar,&Vchar,&n,data,&n,eigReal,eigImag,
        vl,&one,vr,&n,
        work,&lwork,&info);


  // check for errors
  if (info!=0){
    cout << "Error: dgeev returned error code " << info << endl;
    return -1;
  }

  // output eigenvalues to stdout
  cout << "--- Eigenvalues ---" << endl;
  double* ptr = vr;
  for (int i=0;i<n;i++){
    cout << "( " << eigReal[i] << " , " << eigImag[i] << " )  [";
    for ( int j=0; j<n; j++ ) {
      cout << " " << *ptr;
      ptr++;
    }
    cout << " ]\n";
  }
  cout << endl;

  // deallocate

  delete [] eigReal;
  delete [] eigImag;
  delete [] work;
  delete [] vr;
  delete [] vl;


  return 0;
}


int TEST02( void ) {
  std::cout << "\n----- TRNCMP - EigenSystem (gen) ------------------\n";
  double data[] = { 0.35, 0.45, -0.14, -0.17, 0.12,
		    0.09, 0.07, -0.54, 0.35, -0.43,
		    -0.44, -0.33, -0.03, 0.17, 0.95,
		    0.25, -0.32, -0.13, 0.11, 0.02,
		    0.56,  0.53,  0.77, -0.97, 0.93 };

  EigenSystem* EG = EigenSystem::general( data, 5 );
  EG->compute();
  EG->display( std::cout, "%10.6f" );

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
  EG->display( std::cout, "%10.6f" );

  delete EG;

  return 0;
}



int main( void ) {
  TEST01();
  TEST02();
  TEST03();
  TEST04();
  return 0;
}
