// ====================================================================== BEGIN FILE =====
// **                             E I G E N S Y S T E M                                 **
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
/** @brief  Eigen System.
 *  @file   EigenSystem.hh
 *  @author Stephen W. Soliday
 *  @date 2019-Jul-08
 *
 *  Provides the methods for computing general and symetric eigen systems.
 */
// =======================================================================================

#include <EigenSystem.hh>
#include <lapack_interface.hh>

TLOGGER_REFERENCE( EigenSystem, logger );

// =======================================================================================
/** @brief Constructor.
 *  @param[in] n   The order of the input matrix.
 *  @param[in] sym Flag, true is input matrix is symetric.
 */
// ---------------------------------------------------------------------------------------
EigenSystem::EigenSystem( int32_t n, bool sym ) :
    is_sym(sym), N(n), A(0), LDA(n), WR(0), WI(0),
    VL(0), LDVL(n), VR(0), LDVR(1),
    WORK(0), LWORK(-1), INFO(0), vec_real(0), vec_imag(0) {
  // -------------------------------------------------------------------------------------
  char NVEC = 'N';
  char YVEC = 'V';
  char UPPR = 'U';
  A     = new real8_t[LDA*N];
  WR    = new real8_t[N];
  WI    = new real8_t[N];
  VL    = new real8_t[LDVL*N];
  VR    = new real8_t[LDVR*N];

  vec_real = new real8_t*[N];
  vec_imag = new real8_t*[N];

  real8_t* br = new real8_t[N*N];
  real8_t* bi = new real8_t[N*N];

  for ( int32_t i=0; i<N; i++ ) {
    vec_real[i] = (br + i*N);
    vec_imag[i] = (bi + i*N);
  } 
  
  real8_t wkopt;
  LWORK = -1;
  if ( sym ) {
    dsyev_( &YVEC, &UPPR, &N, A, &LDA, WR, &wkopt, &LWORK, &INFO );
  } else {
    dgeev_( &YVEC, &NVEC, &N, A, &LDA, WR, WI,
            VL, &LDVL, VR, &LDVR,
            &wkopt, &LWORK, &INFO );
  }

  if ( 0 == INFO ) {
    LWORK = (int32_t)floor(wkopt);
    WORK  = new real8_t[LWORK];
    INFO  = 0;
  } else {
    if ( 0 > INFO ) {
      logger->error( "%dth argument was illegal", -INFO );
      throw 1;
    }
  }
	  
}


// =======================================================================================
/** @brief  Destructor.
 */
// ---------------------------------------------------------------------------------------
EigenSystem::~EigenSystem( void ) {
  // -------------------------------------------------------------------------------------
  if (static_cast<real8_t*>(0) != A)    { delete[] A;    }
  if (static_cast<real8_t*>(0) != WR)   { delete[] WR;   }
  if (static_cast<real8_t*>(0) != WI)   { delete[] WI;   }
  if (static_cast<real8_t*>(0) != VL)   { delete[] VL;   }
  if (static_cast<real8_t*>(0) != VR)   { delete[] VR;   }
  if (static_cast<real8_t*>(0) != WORK) { delete[] WORK; }

  if (static_cast<real8_t**>(0) != vec_real) {
    real8_t* p = vec_real[0];
    if (static_cast<real8_t*>(0) != p) {
      delete[] p;
    }
    for ( int32_t i=0; i<N; i++ ) {
      vec_real[i] = static_cast<real8_t*>(0);
    }
    delete[] vec_real;
  }

  if (static_cast<real8_t**>(0) != vec_imag) {
    real8_t* p = vec_imag[0];
    if (static_cast<real8_t*>(0) != p) {
      delete[] p;
    }
    for ( int32_t i=0; i<N; i++ ) {
      vec_imag[i] = static_cast<real8_t*>(0);
    }
    delete[] vec_imag;
  }
}


// =======================================================================================
/** @brief Create Instance.
 *  @param[in] data pointer to the input matrix.
 *  @param[in] n    order of the nxn input matrix..
 *  @return pointer to the newly allocated instance.
 *
 *  Create a general NxN matrix from the pointer of pointers.
 */
// ---------------------------------------------------------------------------------------
EigenSystem* EigenSystem::general( real8_t **data, size_t n ) {
  // -------------------------------------------------------------------------------------
  EigenSystem* E = new  EigenSystem( (int32_t)n, false );
  E->set( data );
  return E;
}


// =======================================================================================
/** @brief Create Instance.
 *  @param[in] data pointer to the input matrix.
 *  @param[in] n    order of the nxn input matrix..
 *  @return pointer to the newly allocated instance.
 *
 *  Create a general NxN matrix from the data buffer in column major order.
 */
// ---------------------------------------------------------------------------------------
EigenSystem* EigenSystem::general( real8_t *data, size_t n ) {
  // -------------------------------------------------------------------------------------
  EigenSystem* E = new  EigenSystem( (int32_t)n, false );
  E->set( data );
  return E;
}


// =======================================================================================
/** @brief Create Instance.
 *  @param[in] data pointer to the input matrix.
 *  @param[in] n    order of the nxn input matrix..
 *  @return pointer to the newly allocated instance.
 *
 *  Create a symetric NxN matrix from the pointer of pointers.
 */
// ---------------------------------------------------------------------------------------
EigenSystem* EigenSystem::symetric( real8_t **data, size_t n ) {
  // -------------------------------------------------------------------------------------
  EigenSystem* E = new  EigenSystem( (int32_t)n, true );
  E->set( data );
  return E;
}


// =======================================================================================
/** @brief Create Instance.
 *  @param[in] data pointer to the input matrix.
 *  @param[in] n    order of the nxn input matrix..
 *  @return pointer to the newly allocated instance.
 *
 *  Create a symetric NxN matrix from the data buffer in column major order.
 */
// ---------------------------------------------------------------------------------------
EigenSystem* EigenSystem::symetric( real8_t  *data, size_t n ) {
  // -------------------------------------------------------------------------------------
  EigenSystem* E = new  EigenSystem( (int32_t)n, true );
  E->set( data );
  return E;
}


// =======================================================================================
/** @brief Create Instance.
 *  @param[in] data pointer to the input matrix.
 *  @param[in] n    order of the nxn input matrix..
 *  @return pointer to the newly allocated instance.
 *
 *  Create a symetric NxN matrix from the data buffer in upper triangle column major format.
 */
// ---------------------------------------------------------------------------------------
EigenSystem* EigenSystem::upper_triangle( real8_t  *data, size_t n ) {
  // -------------------------------------------------------------------------------------
  EigenSystem* E = new  EigenSystem( (int32_t)n, true );
  E->setUpper( data );
  return E;
}


// =======================================================================================
/** @brief Create Instance.
 *  @param[in] data pointer to the input matrix.
 *  @param[in] n    order of the nxn input matrix..
 *  @return pointer to the newly allocated instance.
 *
 *  Create a symetric NxN matrix from the data buffer in lower triangle column major format.
 */
// ---------------------------------------------------------------------------------------
EigenSystem* EigenSystem::lower_triangle( real8_t *data, size_t n ) {
  // -------------------------------------------------------------------------------------
  EigenSystem* E = new  EigenSystem( (int32_t)n, true );
  E->setLower( data );
  return E;
}


// =======================================================================================
/** @brief Set.
 *  @param[in] data pointer to the data buffer..
 *
 *  Load the data from the input matrix.
 *  Source data is arranged as a pointer of pointers with each outer pointer a row.
 */
// ---------------------------------------------------------------------------------------
void EigenSystem::set( real8_t **data ) {
  // -------------------------------------------------------------------------------------
  real8_t* ptr = A;
  for (int32_t r=0; r<N; r++ ) {
    for (int32_t c=0; c<N; c++ ) {
      *ptr++ = (data[r])[c];
    }
  }
}

// =======================================================================================
/** @brief Set.
 *  @param[in] data pointer to the data buffer..
 *
 *  Load the data from the input matrix.
 *  Source data is arranged as an array in column major order.
 */
// ---------------------------------------------------------------------------------------
void EigenSystem::set( real8_t *data ) {
  // -------------------------------------------------------------------------------------
  const int32_t n2 = N*N;
  for (int32_t i=0; i<n2; i++ ) {
    A[i] = data[i];
  }
}

// =======================================================================================
/** @brief Set.
 *  @param[in] data pointer to the data buffer..
 *
 *  Load the data from the input matrix.
 *  Source data is arranged as an upper triangle in column major order.
 */
// ---------------------------------------------------------------------------------------
void EigenSystem::setUpper( real8_t* ) {
  // -------------------------------------------------------------------------------------
  logger->error( LOCATION, "Set from Upper not yet available" );
}

// =======================================================================================
/** @brief Set.
 *  @param[in] data pointer to the data buffer..
 *
 *  Load the data from the input matrix.
 *  Source data is arranged as a lower triangle in column major order.
 */
// ---------------------------------------------------------------------------------------
void EigenSystem::setLower( real8_t* ) {
  // -------------------------------------------------------------------------------------
  logger->error( LOCATION, "Set from Lower not yet available" );  
}


// =======================================================================================
/** @brief Compute.
 *
 *  Compute the eigen values and the right eigen vectors.
 */
// ---------------------------------------------------------------------------------------
void EigenSystem::compute( void ) {
  // -------------------------------------------------------------------------------------
  char NVEC = 'N';
  char YVEC = 'V';
  char UPPR = 'U';
  if ( is_sym ) {
    dsyev_( &YVEC, &UPPR, &N, A, &LDA, WR, WORK, &LWORK, &INFO );
    if ( 0 == INFO ) {
      for ( int32_t i=0; i<N; i++ ) {
        for ( int32_t j=0; j<N; j++ ) {
          vec_real[j][i] = A[i+j*LDA];
          vec_imag[j][i] = D_ZERO;
        }
      }
    } else {
      if ( 0 < INFO ) {
	logger->error( "DGEEV: failed to compute eigenvalues." );
	throw 1;
      } else {
	logger->error( "DGEEV: %dth argument was illegal", -INFO );
	throw 1;
      }
    }
  } else {
    dgeev_( &YVEC, &NVEC, &N, A, &LDA, WR, WI,
	    VL, &LDVL, VR, &N, WORK, &LWORK, &INFO );
    if ( 0 == INFO ) {
      int32_t i, j;
      for ( i=0; i<N; i++ ) {
        j = 0;
        while ( j<N ) {
          if ( isZero( WI[j] ) ) {
            vec_real[j][i] = VL[i+j*LDVL];
            vec_imag[j][i] = D_ZERO;
            j += 1;
          } else {
            vec_real[j][i]   =  VL[i+j*LDVL];
            vec_imag[j][i]   =  VL[i+(j+1)*LDVL];
            vec_real[j+1][i] =  VL[i+j*LDVL];
            vec_imag[j+1][i] = -VL[i+(j+1)*LDVL];
            j += 2;
          }
        }
      }
    } else {
      if ( 0 < INFO ) {
	logger->error( "DGEEV: failed to compute eigenvalues." );
	throw 1;
      } else {
	logger->error( "DGEEV: %dth argument was illegal", -INFO );
	throw 1;
      }
    }
  }
}


// =======================================================================================
/** @brief Sort.
 *
 *  Sort the Eigen Vectors such that the corresponding eigen values are in
 *  descending order.
 */
// ---------------------------------------------------------------------------------------
void EigenSystem::sort( void ) {
  // -------------------------------------------------------------------------------------
  const int32_t n = N;
  const int32_t m = N - 1;
  
  for ( int32_t i=0; i<m; i++ ) {
    for ( int32_t j=i+1; j<n; j++ ) {
      if ( WR[j] > WR[i] ) {
        real8_t rtemp = WR[j];
        WR[j]    = WR[i];
        WR[i]    = rtemp;
        for ( int32_t k=0; k<n; k++ ) {
          const real8_t t = vec_real[i][k];
          vec_real[i][k]  = vec_real[j][k];
          vec_real[j][k]  = t;
        }
      }
    }
  }

}


// =======================================================================================
/** @brief Report.
 *  @param[in] os  reference to an otput stream.
 *  @param[in] fmt edit descriptor.
 */
// ---------------------------------------------------------------------------------------
void EigenSystem::display( std::ostream& os, std::string fmt ) {
  // -------------------------------------------------------------------------------------
  int32_t i, j;
  os << "Order: " << N << "\n";
  for ( i=0; i<N; i++ ) {
    os << "( ";
    os << c_fmt( fmt, WR[i] );
    if ( isNotZero( WI[i] ) ) {
      os << ", ";
      os << c_fmt( fmt, WI[i] );
    }
    os << " ) [";

    for ( j=0; j<N; j++ ) {
      os << "(";
      if ( isZero(vec_imag[i][j]) ) {
	os << c_fmt( fmt, vec_real[i][j] );
      } else {
	os << c_fmt( fmt, vec_real[i][j] );
	os << ", ";
	os << c_fmt( fmt, vec_imag[i][j] );
      }
      os << "),";
    }
    
    os << " ]\n";
  }
}


// =======================================================================================
// **                             E I G E N S Y S T E M                                 **
// ======================================================================== END FILE =====
