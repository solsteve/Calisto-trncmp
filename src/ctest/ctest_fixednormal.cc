// ====================================================================== BEGIN FILE =====
// **                         C T E S T _ F I X E D N O R M A L                         **
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
/** @brief Test the FixedNormal class.
 *  @file   ctest_fixednormal.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-28
 *
 *  This is a test of the FixedNormal class.
 */
// =======================================================================================

#include <FixedNormal.hh>
#include <RunStat.hh>

// =======================================================================================
void expect_fixed( std::string title, real8_t mu, real8_t* param, size_t n ) {
  // -------------------------------------------------------------------------------------
  size_t  err = 0;
  real8_t avg = D_ZERO;
  for ( size_t i=0; i<n; i++ ) {
    avg += param[i];
    if ( param[i] < mu ) { err += 1; }
    if ( param[i] > mu ) { err += 1; }
  }
  avg /= (real8_t)n;

  std::cout << "\n" << title << "\n"
            << "expected " << mu << " got " << avg << "\n"
            << "match failed " << err << " times\n\n";
}


// =======================================================================================
void expect_fixed( std::string title, int32_t mu, int32_t* param, size_t n ) {
  // -------------------------------------------------------------------------------------
  size_t  err = 0;
  real8_t avg = D_ZERO;
  for ( size_t i=0; i<n; i++ ) {
    avg += (real8_t)param[i];
    if ( param[i] != mu ) { err += 1; }
  }
  avg /= (real8_t)n;

  std::cout << "\n" << title << "\n"
            << "expected " << mu << " got " << avg << "\n"
            << "match failed " << err << " times\n\n";
}


// =======================================================================================
void expect_normal( std::string title,
                    real8_t mu, real8_t std, real8_t mn, real8_t mx,
                    real8_t* param, size_t n ) {
  // -------------------------------------------------------------------------------------
  RunStat R;
  
  for ( size_t i=0; i<n; i++ ) {
    R.update( param[i] );
  }

  std::cout << "\n" << title << "\n"
            << "expected " << mu  << " got " << R.mean()  << "\n"
            << "expected " << std << " got " << R.stdev() << "\n"
            << "expected " << mn  << " got " << R.minv()  << "\n"
            << "expected " << mx  << " got " << R.maxv()  << "\n"
            << "\n";
}


// =======================================================================================
void expect_normal( std::string title,
                    int32_t mu, int32_t std, int32_t mn, int32_t mx,
                    int32_t* param, size_t n ) {
  // -------------------------------------------------------------------------------------
  RunStat R;
  
  for ( size_t i=0; i<n; i++ ) {
    R.update( param[i] );
  }

  std::cout << "\n" << title << "\n"
            << "expected " << mu  << " got " << R.mean()  << "\n"
            << "expected " << std << " got " << R.stdev() << "\n"
            << "expected " << mn  << " got " << R.minv()  << "\n"
            << "expected " << mx  << " got " << R.maxv()  << "\n"
            << "\n";
}


// =======================================================================================
int main( void ) {
  // -------------------------------------------------------------------------------------
  const real8_t MEAN   = 5.0;
  const real8_t STDV   = 3.0;
  const real8_t SMINV  = MEAN - (D_THREE * STDV);
  const real8_t SMAXV  = MEAN + (D_THREE * STDV);
  const real8_t MINV   = MEAN - (D_TWO * STDV);
  const real8_t MAXV   = MEAN + (D_TWO * STDV);
  const size_t  N_SAMP = 10000000;
  
  {
    FixedNormal FN(MEAN);
    real8_t* test = new real8_t[N_SAMP];
    for ( size_t i=0; i<N_SAMP; i++ ) {
      test[i] = FN.next();
    }
    expect_fixed( "Fixed Real", MEAN, test, N_SAMP );
    delete[] test;
  }

  {
    FixedNormal FN(MEAN);
    int32_t* test = new int32_t[N_SAMP];
    for ( size_t i=0; i<N_SAMP; i++ ) {
      test[i] = FN.nextInt();
    }
    expect_fixed( "Fixed Integer", (int32_t)MEAN, test, N_SAMP );
    delete[] test;
  }

  {
    FixedNormal FN(MEAN,STDV);
    real8_t* test = new real8_t[N_SAMP];
    for ( size_t i=0; i<N_SAMP; i++ ) {
      test[i] = FN.next();
    }
    expect_normal( "Normal Real(mu,sig)", MEAN, STDV, SMINV, SMAXV, test, N_SAMP );
    delete[] test;
  }

  {
    FixedNormal FN(MEAN,STDV);
    int32_t* test = new int32_t[N_SAMP];
    for ( size_t i=0; i<N_SAMP; i++ ) {
      test[i] = FN.nextInt();
    }
    expect_normal( "Normal Integer(mu,sig)", (int32_t)MEAN, (int32_t)STDV,
                   (int32_t)SMINV, (int32_t)SMAXV, test, N_SAMP );
    delete[] test;
  }

  {
    FixedNormal FN(MEAN,STDV,MINV,MAXV);
    real8_t* test = new real8_t[N_SAMP];
    for ( size_t i=0; i<N_SAMP; i++ ) {
      test[i] = FN.next();
    }
    expect_normal( "Normal Real(mu,sig,min,max)", MEAN, STDV, MINV, MAXV, test, N_SAMP );
    delete[] test;
  }

  {
    FixedNormal FN(MEAN,STDV,MINV,MAXV);
    int32_t* test = new int32_t[N_SAMP];
    for ( size_t i=0; i<N_SAMP; i++ ) {
      test[i] = FN.nextInt();
    }
    expect_normal( "Normal Integer(mu,sig,min,max)", (int32_t)MEAN, (int32_t)STDV,
                   (int32_t)MINV, (int32_t)MAXV, test, N_SAMP );
    delete[] test;
  }

  {
    real8_t P[] = { MEAN, STDV, MINV, MAXV };
    FixedNormal FN(P,1);
    real8_t* test = new real8_t[N_SAMP];
    for ( size_t i=0; i<N_SAMP; i++ ) {
      test[i] = FN.next();
    }
    expect_fixed( "Normal Real(P1)", MEAN, test, N_SAMP );
    delete[] test;
  }

  {
    real8_t P[] = { MEAN, STDV, MINV, MAXV };
    FixedNormal FN(P,2);
    real8_t* test = new real8_t[N_SAMP];
    for ( size_t i=0; i<N_SAMP; i++ ) {
      test[i] = FN.next();
    }
    expect_normal( "Normal Real(P1,P2)", MEAN, STDV, SMINV, SMAXV, test, N_SAMP );
    delete[] test;
  }

  {
    real8_t P[] = { MEAN, STDV, MINV, MAXV };
    FixedNormal FN(P,4);
    real8_t* test = new real8_t[N_SAMP];
    for ( size_t i=0; i<N_SAMP; i++ ) {
      test[i] = FN.next();
    }
    expect_normal( "Normal Real(P1,P2,P3,P4)", MEAN, STDV, MINV, MAXV, test, N_SAMP );
    delete[] test;
  }


  {
    std::string P = "[ 5 ]";
    FixedNormal FN(P);
    real8_t* test = new real8_t[N_SAMP];
    for ( size_t i=0; i<N_SAMP; i++ ) {
      test[i] = FN.next();
    }
    expect_fixed( "Normal Real([5])", 5.0, test, N_SAMP );
    delete[] test;
  }

  {
    std::string P = "[ 5, 3 ]";
    FixedNormal FN(P);
    real8_t* test = new real8_t[N_SAMP];
    for ( size_t i=0; i<N_SAMP; i++ ) {
      test[i] = FN.next();
    }
    expect_normal( "Normal Real([5,3])", 5.0, 3.0, -4.0, 14.0, test, N_SAMP );
    delete[] test;
  }

  {
    std::string P = "[ 5, 3, -2, 12 ]";
    FixedNormal FN(P);
    real8_t* test = new real8_t[N_SAMP];
    for ( size_t i=0; i<N_SAMP; i++ ) {
      test[i] = FN.next();
    }
    expect_normal( "Normal Real([5,3,-2,12])", 5.0, 3.0, -2.0, 12.0, test, N_SAMP );
    delete[] test;
  }


  
  return 0;
}


// =======================================================================================
// **                         C T E S T _ F I X E D N O R M A L                         **
// ======================================================================== END FILE =====
