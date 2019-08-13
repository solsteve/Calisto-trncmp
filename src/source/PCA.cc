// ====================================================================== BEGIN FILE =====
// **                                       P C A                                       **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2018-19, Stephen W. Soliday                                        **
// **                         stephen.soliday@trncmp.org                                **
// **                         http://research.trncmp.org                                **
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
/** @brief  Principle Component Analysis.
 *  @file   PCA.cc
 *  @author Stephen W. Soliday
 *  @date   2018-Apr-20 Original release.
 *  @date   2019-Aug-06 Port from Java to C++.
 *  Provides the methods for performing Principle Component Analysis.
 */
// =======================================================================================


#include <PCA.hh>
#include <EigenSystem.hh>


TLOGGER_REFERENCE( PCA, logger );


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
PCA::PCA( void ) : num_var(0), mu(), variance(), covariance(), rotation(), rwork(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
PCA::~PCA( void ) {
  // -------------------------------------------------------------------------------------
  if ( (real8_t*)0 != rwork ) {
    delete[] rwork;
  }
}


// =======================================================================================
/** @brief Compile.
 *  @param[in] table reference to table of samples.
 *  @return 0==success. non-zero==error.
 */
// ---------------------------------------------------------------------------------------
int PCA::fromSamples( Table& table ) {
  // -------------------------------------------------------------------------------------
  const int32_t ns = size( table, 0 );
  const int32_t nv = size( table, 1 );

  // ----- set number of variables -------------------------------------------------------
  num_var = nv;
  if ( (real8_t*)0 == rwork ) {
    rwork = new real8_t[num_var];
  }
  
  // ----- build mean vector -------------------------------------------------------------
  real8_t tempv[nv];
  table.mean( tempv, nv, 0 );
  mu.resize(nv);
  mu.load(tempv);

  // ----- build variance vector ---------------------------------------------------------
  real8_t* data = new real8_t[ns*nv];

  int32_t idx = 0;
  for ( int32_t c=0; c<nv; c++ ) {
    const real8_t mean = mu.get(c);
    for ( int32_t r=0; r<ns; r++ ) {
      data[idx++] = table.get(r,c) - mean;
    }
  }

  // ----- singular value decomposition --------------------------------------------------

  const char* JOBZ = "Overwrite";
  real8_t* S       = new real8_t[nv];
  real8_t  U[2];
  int32_t  ONE     = 1;
  real8_t* VT      = new real8_t[nv*nv];
  real8_t  WRKP[2] = {0.0, 0.0};
  int32_t  LWORK   = -1;
  int32_t* IWORK   = new int32_t[8*nv];
  int32_t  INFO    = 0;

  // ----- query work space requirments ---------------
  dgesdd_( JOBZ, &ns, &nv, data, &ns, S, U, &ONE, VT, &nv, WRKP, &LWORK, IWORK, &INFO );
  if ( 0 != INFO ) {
    logger->error( "unable to query lwork" );
    return 1;
  }

  LWORK = static_cast<int32_t>(WRKP[0]);
  real8_t* WORK = new real8_t[LWORK];

  INFO = 0;

  // ----- call SVD for eigen systems -----------------
  dgesdd_( JOBZ, &ns, &nv, data, &ns, S, U, &ONE, VT, &nv, WORK, &LWORK, IWORK, &INFO );
  if ( 0 != INFO ) {
    logger->error( "SVD failed to converge" );
    return 2;
  }

  rotation.resize( nv );
  rotation.load( VT, Matrix::COLUMN_MAJOR );

  // ----- compute variances --------------------------
  const real8_t fnsm1 = static_cast<real8_t>(ns-1);
  variance.resize( nv );
  for ( int32_t i=0; i<nv; i++ ) {
    variance(i) = S[i]*S[i] / fnsm1;
  }

  ::covariance( covariance, table, mu );

  return 0;
}


// =======================================================================================
/** @brief Compile.
 *  @param[in] cov  reference to an inpt covariance.
 *  @param[in] mean reference to a Vector of the sample means.
 *  @return 0==success. non-zero==error.
 */
// ---------------------------------------------------------------------------------------
int PCA::fromCovariance( Matrix& cov, Vector& mean ) {
  // -------------------------------------------------------------------------------------
  num_var = size( mean );
  if ( (real8_t*)0 == rwork ) {
    rwork = new real8_t[num_var];
  }
  mu.copy( mean );

  covariance.copy( cov );

  EigenSystem* ES = EigenSystem::symetric( cov );

  ES->compute();

  ES->sort();

  variance.resize( num_var );
  rotation.resize( num_var );

  for ( int32_t i=0; i<num_var; i++ ) {
    variance.set( i, ES->eval(i) );
    real8_t*      vec = ES->evec(i);
    for ( int32_t j=0; j<num_var; j++ ) {
      rotation.set( i, j, vec[j] );
    }
  }
  
  delete ES;
  return 0;
}


// =======================================================================================
/** @brief Transform.
 *  @param[out] out  reference to an output Vector.
 *  @param[in]  in   reference to an input Vector.
 *  @return 0==success. non-zer==error.
 *
 *  Mean shift the input Vector and apply the rotation transform.
 */
// ---------------------------------------------------------------------------------------
int PCA::transform( Vector& out, Vector& in ) {
  // -------------------------------------------------------------------------------------
  const int32_t nOut = size( rotation, 0 );
  const int32_t nIn  = size( rotation, 1 );
  if ( size( in ) != nIn ) {
    throw std::length_error( "Input vector is not compatible with this rotation" );
  }
  out.resize( nOut );

  for ( int32_t j=0; j<nIn; j++ ) {
    rwork[j] = in.get(j) - mu.get(j);
  }
  

  for ( int32_t i=0; i<nOut; i++ ) {
    real8_t sum = D_ZERO;
    for ( int32_t j=0; j<nIn; j++ ) {
      sum += ( rotation.get(i,j) * rwork[j] );
    }
    out(i) = sum;
  }
  
  return 0;
}


// =======================================================================================
/** @brief Transform.
 *  @param[out] out  reference to an output Table.
 *  @param[in]  in   reference to an input Table.
 *  @return 0==success. non-zer==error.
 *
 *  Mean shift the input Vector and apply the rotation transform.
 */
// ---------------------------------------------------------------------------------------
int PCA::transform( Table& out, Table& in ) {
  // -------------------------------------------------------------------------------------
  const int32_t nSamp = size( in, 0 );
  const int32_t nOut  = size( rotation, 0 );
  const int32_t nIn   = size( rotation, 1 );
  if ( size( in, 1 ) != nIn ) {
    throw std::length_error( "Input Table is not compatible with this rotation" );
  }
  out.resize( nSamp, nOut );

  for ( int32_t k=0; k<nSamp; k++ ) {
    for ( int32_t j=0; j<nIn; j++ ) {
      rwork[j] = in.get(k,j) - mu.get(j);
    }

    for ( int32_t i=0; i<nOut; i++ ) {
      real8_t sum = D_ZERO;
      for ( int32_t j=0; j<nIn; j++ ) {
        sum += ( rotation.get(i,j) * rwork[j] );
      }
      out(k,i) = sum;
    }
  }
  
  return 0;
}


// =======================================================================================
/** @brief Inverse Transform.
 *  @param[out] out  reference to an output Vector.
 *  @param[in]  in   reference to an input Vector.
 *  @return 0==success. non-zer==error.
 *
 *  Apply the inverse rotation transform, and then add the sample mean.
 */
// ---------------------------------------------------------------------------------------
int PCA::recover( Vector& out, Vector& in ) {
  // -------------------------------------------------------------------------------------
  const int32_t nOut = size( rotation, 1 );
  const int32_t nIn  = size( rotation, 0 );
  if ( size( in ) != nIn ) {
    throw std::length_error( "Input vector is not compatible with this rotation" );
  }
  out.resize( nOut );

  for ( int32_t i=0; i<nOut; i++ ) {
    real8_t sum = D_ZERO;
    for ( int32_t j=0; j<nIn; j++ ) {
      sum += ( rotation.get(j,i) * in.get(j) );
    }
    out(i) = sum + mu.get(i);
  }
  
  return 0;
}


// =======================================================================================
/** @brief Inverse Transform.
 *  @param[out] out  reference to an output Table.
 *  @param[in]  in   reference to an input  Table.
 *  @return 0==success. non-zer==error.
 *
 *  Apply the inverse rotation transform, and then add the sample mean.
 */
// ---------------------------------------------------------------------------------------
int PCA::recover( Table& out, Table& in ) {
  // -------------------------------------------------------------------------------------
  const int32_t nSamp = size( in, 0 );
  const int32_t nOut = size( rotation, 1 );
  const int32_t nIn  = size( rotation, 0 );
  if ( size( in,1 ) != nIn ) {
    throw std::length_error( "Input Table is not compatible with this rotation" );
  }
  out.resize( nSamp, nOut );

  for ( int32_t k=0; k<nSamp; k++ ) {
    for ( int32_t i=0; i<nOut; i++ ) {
      real8_t sum = D_ZERO;
      for ( int32_t j=0; j<nIn; j++ ) {
        sum += ( rotation.get(j,i) * in.get(k,j) );
      }
      out(k,i) = sum + mu.get(i);
    }
  }

  return 0;
}


// =======================================================================================
/** @brief Report.
 *  @param[in] os   reference to an otput stream.
 *  @param[in] sfmt edit descriptor.
 */
// ---------------------------------------------------------------------------------------
void PCA::report( std::ostream& os, const std::string& sfmt ) {
  // -------------------------------------------------------------------------------------
  os << "N Var: " << num_var << "\n"
     << "mean " << toString( mu, sfmt ) << "\n"
     << "var  " << toString( variance, sfmt ) << "\n"
     << "Covariance\n" << toString( covariance, sfmt ) << "\n"
     << "Rotation\n" << toString( rotation, sfmt ) << "\n\n";
}


// =======================================================================================
// **                                       P C A                                       **
// ======================================================================== END FILE =====

