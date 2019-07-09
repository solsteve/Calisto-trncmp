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

TLOGGER_REFERENCE( EigenSystem, logger );

extern "C" {
  extern int dgeev_( char *jobvl, char *jobvr, int32_t *n,
		     real8_t *a,  int32_t *lda,  real8_t *wr, real8_t *wi,
		     real8_t *vl, int32_t *ldvl, real8_t *vr, int32_t *ldvr,
		     real8_t *work, int32_t *lwork, int32_t *info );

  extern int dsyev_( char *jobz, char *uplo, int32_t *n,
		     real8_t *a,    int32_t *lda,   real8_t *w,
		     real8_t *work, int32_t *lwork, int32_t *info );
}

// =======================================================================================
/** @brief Constructor.
 *  @param[in] n   The order of the input matrix.
 *  @param[in] sym Flag, true is input matrix is symetric.
 */
// ---------------------------------------------------------------------------------------
EigenSystem::EigenSystem( int32_t n, bool sym ) :
  is_sym(sym), N(n), A(0), LDA(n), WR(0), WI(0),
  VL(0), LDVL(1), VR(0), LDVR(n),
  WORK(0), LWORK(-1), INFO(0) {
  // -------------------------------------------------------------------------------------
  A     = new real8_t[LDA*N];
  WR    = new real8_t[N];
  WI    = new real8_t[N];
  VL    = new real8_t[N];
  VR    = new real8_t[LDVL*N];
  
  char    Nchar='N';
  char    Vchar='V';
  real8_t dumA[1];
  real8_t dumWR[1];
  real8_t dumWI[1];
  real8_t dumVL[1];
  real8_t dumVR[1];
  real8_t wkopt[1];

  dgeev_( &Nchar, &Vchar, &N, dumA, &LDA, dumWR, dumWI,
	  dumVL, &LDVL, dumVR, &LDVR,
	  wkopt, &LWORK, &INFO );

  if ( 0 == INFO ) {
    LWORK = (int32_t)floor(wkopt[0]);

    WORK = new real8_t[LWORK];
    INFO = 0;
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
void EigenSystem::setUpper( real8_t* data ) {
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
void EigenSystem::setLower( real8_t* data ) {
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
  char    Nchar='N';
  char    Vchar='V';
  if ( is_sym ) {
    MARK;
    //logger->error( LOCATION, "Symetric eigenvalue not yet implemented." );
  } else {
    dgeev_( &Nchar, &Vchar, &N, A, &LDA, WR, WI,
	    VL, &LDVL, VR, &LDVR, WORK, &LWORK, &INFO );
  }
}


void EigenSystem::display( std::ostream& os, std::string fmt ) {
  os << "Order: " << N << "\n";
  real8_t *ptr = VR;
  for ( int32_t i=0; i<N; i++ ) {
    os << "( ";
    os << c_fmt( fmt, WR[i] );
    os << ", ";
    os << c_fmt( fmt, WI[i] );
    os << " ) [";
    os << c_fmt( fmt, *ptr );
    ptr++;
    for ( int32_t j=1; j<N; j++ ) {
      os << ", ";
      os << c_fmt( fmt, *ptr );
      ptr++;
    }
    os << " ]\n";
  }
}












// =======================================================================================
// **                             E I G E N S Y S T E M                                 **
// ======================================================================== END FILE =====
