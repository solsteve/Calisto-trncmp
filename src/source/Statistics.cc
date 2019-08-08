// ====================================================================== BEGIN FILE =====
// **                                S T A T I S T I C S                                **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2015-2019, Stephen W. Soliday                                      **
// **                           stephen.soliday@trncmp.org                              **
// **                           http://research.trncmp.org                              **
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
/** @brief  Statistics classes.
 *  @file   Statistics.cc
 *  @author Stephen W. Soliday
 *  @date   2015-Jan-26 Original release.
 *  @date   2019-Jul-26 CMake refactorization.
 *
 *  Provides the methods for one and two dimensional statistics.
 */
// =======================================================================================

#include <Statistics.hh>
#include <LinAlg.hh>
#include <array_print.hh>


TLOGGER_REFERENCE( Statistics, logger );


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
Statistics::running::running  ( void ) :
    min_val(0.0),   max_val(0.0), mean_val(0.0), mean_val_sq(0.0),
    is_first(true), num_samp(0),  min_idx(0),    max_idx(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Statistics::running::~running ( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Reset.
 *
 *  Clear the values and start over.
 *  @note this will not take effect until the first update after calling a rest.
 */
// ---------------------------------------------------------------------------------------
void Statistics::running::reset( void ) {
  // -------------------------------------------------------------------------------------
  is_first = true;
}


// =======================================================================================
/** @brief Variance.
 *  @return mean variance of the sampled values.
 */
// ---------------------------------------------------------------------------------------
real8_t Statistics::running::var( void ) {
  // -------------------------------------------------------------------------------------
  return mean_val_sq - (mean_val*mean_val);
}


// =======================================================================================
/** @brief Report.
 *  @param[in] os optional reference to an output stream (default: stdout)
 */
// ---------------------------------------------------------------------------------------
void Statistics::running::report( std::ostream& os, const std::string sfmt ) {
  // -------------------------------------------------------------------------------------
  const char* fmt = sfmt.c_str();
  os << "Samples:    " << c_fmt( fmt, count() ) << "\n"
     << "  mean      " << c_fmt( fmt, mean()  ) << "\n"
     << "  std dev   " << c_fmt( fmt, stdev() ) << "\n"
     << "  min       " << c_fmt( fmt, minv()  ) << "\n"
     << "  max       " << c_fmt( fmt, maxv()  ) << "\n"
     << "  min index " << c_fmt( fmt, minidx()) << "\n"
     << "  max index " << c_fmt( fmt, maxidx()) << "\n"
     << "\n";
}


















// =======================================================================================
/** @brief Constructor.
 *
 *  Allocate space for the statistics of a single dimensional sample set.
 */
// ---------------------------------------------------------------------------------------
Statistics::single::single( void ) :
    t_count(0),     t_level1(false), t_level2(false), t_minv(D_ZERO),
    t_maxv(D_ZERO), t_minidx(0),     t_maxidx(0),     t_mean(D_ZERO),
    t_var(D_ZERO),  t_std(D_ZERO),   t_adev(D_ZERO),  t_skew(D_ZERO),
    t_kurt(D_ZERO) {
  // -------------------------------------------------------------------------------------
}
  
// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Statistics::single::~single( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Zero out.
 */
// ---------------------------------------------------------------------------------------
void Statistics::single::clear( void ) {
  // -------------------------------------------------------------------------------------
  t_count  = 0;
  t_level1 = false;
  t_level2 = false;
  t_minv   = D_ZERO;
  t_maxv   = D_ZERO;
  t_minidx = 0;
  t_maxidx = 0;
  t_mean   = D_ZERO;
  t_var    = D_ZERO; 
  t_std    = D_ZERO; 
  t_adev   = D_ZERO;
  t_skew   = D_ZERO;
  t_kurt   = D_ZERO;
}


// =====================================================================================
/** @brief Report
 *  @param[in] os   reference to an output stream.
 *  @param[in] sfmt edit sescriptor for fields.
 */
// -------------------------------------------------------------------------------------
void Statistics::single::report( std::ostream& os, const std::string sfmt ) {
  // -----------------------------------------------------------------------------------

  if ( t_level1 ) {
    const char* fmt = sfmt.c_str();
    os << "Num:      " << c_fmt( "%lu", t_count  ) << "\n"
       << "MinValue: " << c_fmt( fmt,   t_minv   ) << "\n"
       << "MaxValue: " << c_fmt( fmt,   t_maxv   ) << "\n"
       << "MinIndex: " << c_fmt( "%lu", t_minidx ) << "\n"
       << "MaxIndex: " << c_fmt( "%lu", t_maxidx ) << "\n"
       << "Mean:     " << c_fmt( fmt,   t_mean   ) << "\n"
       << "Var:      " << c_fmt( fmt,   t_var    ) << "\n";
    if ( t_level2 ) {
      os << "Std Dev:  " << c_fmt( fmt, t_std  ) << "\n"
         << "Avg Dev:  " << c_fmt( fmt, t_adev ) << "\n"
         << "Skew:     " << c_fmt( fmt, t_skew ) << "\n"
         << "Kurt:     " << c_fmt( fmt, t_kurt ) << "\n";
    }
    os << "\n";
  }

}


// =======================================================================================
/** @brief Compile.
 *  @param[in] data        pointer to data.
 *  @param[in] num_samples number of samples.
 *  @return true if error occures.
 *
 *  Compile the statistics data structure for a single dimensional data set.
 */
// ---------------------------------------------------------------------------------------
bool Statistics::single::compile( const real8_t* data, const int32_t num_samples ) {
  // -------------------------------------------------------------------------------------
  t_level1 = false;
  
  t_mean   = D_ZERO;
  t_minv   = MAX_POS_DOUBLE;
  t_maxv   = MAX_NEG_DOUBLE;
  t_minidx = num_samples+1;
  t_maxidx = num_samples+1;
  t_count  = num_samples;

  for (int32_t i=0; i<num_samples; i++) {
    real8_t x = data[i];
    t_mean += x;
    if ( x < t_minv ) {
      t_minv   = x;
      t_minidx = i;
    }
    if ( x > t_maxv ) {
      t_maxv   = x;
      t_maxidx = i;
    }
  }

  real8_t fn = (real8_t)(t_count);
  t_mean /= fn;

  t_var = D_ZERO;

  for (int32_t i=0; i<num_samples; i++) {
    real8_t x = (data[i] - t_mean);
    t_var += (x*x);
  }

  t_var /= (fn-D_ONE);

  if ( num_samples < t_minidx ) {
    logger->error( LOCATION, "minimum value/index could not be found" );
    return true;
  }

  if ( num_samples < t_maxidx ) {
    logger->error( LOCATION, "maximum value/index could not be found" );
    return true;
  }

  t_level1 = true;

  return false;
}


// =======================================================================================
/** @brief Compile.
 *  @param data   pointer to data.
 *  @param num_samples number of samples.
 *  @return true if error occures.
 *
 *  Compile the extra statistics data structure for a single dimensional data set.
 */
// ---------------------------------------------------------------------------------------
bool Statistics::single::extra( const real8_t* data, const int32_t num_samples ) {
  // -------------------------------------------------------------------------------------
  t_level2 = false;

  if ( ! t_level1 ) {
    logger->warn( LOCATION, "this requires that you call compile first" );
    if ( this->compile( data, num_samples ) ) {
      logger->warn( LOCATION, "   I tried to do it for you, but it failed" );
      return true;
    }
    logger->warn( LOCATION, "   I did it for you" );
  }

  if ( num_samples != t_count ) {
    logger->warn( LOCATION, "you should run extra with the same data count as compile" );
  }

  t_std = sqrt(t_var);

  t_adev = D_ZERO;
  t_skew = D_ZERO;
  t_kurt = D_ZERO;

  if (isNotZero(t_std)) {
    for (int32_t i=0; i<num_samples; i++) {
      real8_t sd = data[i] - t_mean;
      real8_t x  = sd / t_std;
      real8_t x3 = x*x*x;
      t_adev += Abs(sd);
      t_skew += x3;
      t_kurt += (x3*x);
    }

    real8_t fn = (real8_t) t_count;

    t_adev /= fn;
    t_skew /= fn;
    t_kurt /= fn;
    t_kurt -= 3.0e0;
  } else {
    logger->error( LOCATION, "Standard deviation was ZERO, no values computed" );
    return true;
  }

  t_level2 = true;

  return false;
}








// =======================================================================================
/** @brief Constructor.
 *  @param[in] n number of columns in the sample set (dimensions)
 *
 *  Allocate space for the statistics of a multi dimensional sample set.
 */
// ---------------------------------------------------------------------------------------
Statistics::multi::multi( int32_t n ) :
    t_nvar(0), t_level1(false), t_level2a(false), t_level2b(false), S(0),
    covariance(0), correlation(0), inv_cov(0) {
  // -------------------------------------------------------------------------------------
  t_nvar = n;
  S = new single*[ t_nvar ];
  for ( int32_t i=0; i<t_nvar; i++ ) {
    S[i] = new single();
  }

  clear();
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Statistics::multi::~multi( void ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<t_nvar; i++ ) {
    delete S[i];
    S[i] = static_cast<single*>(0);
  }
  delete[] S;

  if ( static_cast<Matrix*>(0) != covariance )  { delete covariance;  }
  if ( static_cast<Matrix*>(0) != correlation ) { delete correlation; }
  if ( static_cast<Matrix*>(0) != inv_cov )     { delete  inv_cov;    }
}









// =====================================================================================
/** @brief Fill Array with Minimum Value.
 *  @param[out] t pointer to receiving arrray.
 *  @param[in]  n number of requested values (may not be greater than t_nvar)
 */
// -------------------------------------------------------------------------------------
int32_t Statistics::multi::minv( real8_t* t, const int32_t n ) {
  // -----------------------------------------------------------------------------------
  int32_t nv = t_nvar;
  if ( 0 < n ) {
    if ( n < nv ) {
      nv = n;
    } else {
      logger->error( "N=%d can not be greater than the number of variables %d", n, t_nvar );
      return 0;
    }
  }
  for ( int32_t i=0; i<nv; i++ ) {
    t[i] = S[i]->minv();
  }
  return nv;
}


// =====================================================================================
/** @brief Fill Array with Maximum Value.
 *  @param[out] t pointer to receiving arrray.
 *  @param[in]  n number of requested values (may not be greater than t_nvar)
 */
// -------------------------------------------------------------------------------------
int32_t Statistics::multi::maxv( real8_t* t, const int32_t n ) {
  // -----------------------------------------------------------------------------------
  int32_t nv = t_nvar;
  if ( 0 < n ) {
    if ( n < nv ) {
      nv = n;
    } else {
      logger->error( "N=%d can not be greater than the number of variables %d", n, t_nvar );
      return 0;
    }
  }
  for ( int32_t i=0; i<nv; i++ ) {
    t[i] = S[i]->maxv();
  }
  return nv;
}


// =====================================================================================
/** @brief Fill Array with Minimum Index.
 *  @param[out] t pointer to receiving arrray.
 *  @param[in]  n number of requested values (may not be greater than t_nvar)
 */
// -------------------------------------------------------------------------------------
int32_t Statistics::multi::minidx( int32_t* t, const int32_t n ) {
  // -----------------------------------------------------------------------------------
  int32_t nv = t_nvar;
  if ( 0 < n ) {
    if ( n < nv ) {
      nv = n;
    } else {
      logger->error( "N=%d can not be greater than the number of variables %d", n, t_nvar );
      return 0;
    }
  }
  for ( int32_t i=0; i<nv; i++ ) {
    t[i] = S[i]->minidx();
  }
  return nv;
}


// =====================================================================================
/** @brief Fill Array with Maximum Index.
 *  @param[out] t pointer to receiving arrray.
 *  @param[in]  n number of requested values (may not be greater than t_nvar)
 */
// -------------------------------------------------------------------------------------
int32_t Statistics::multi::maxidx( int32_t* t, const int32_t n ) {
  // -----------------------------------------------------------------------------------
  int32_t nv = t_nvar;
  if ( 0 < n ) {
    if ( n < nv ) {
      nv = n;
    } else {
      logger->error( "N=%d can not be greater than the number of variables %d", n, t_nvar );
      return 0;
    }
  }
  for ( int32_t i=0; i<nv; i++ ) {
    t[i] = S[i]->maxidx();
  }
  return nv;
}


// =====================================================================================
/** @brief Fill Array with Mean.
 *  @param[out] t pointer to receiving arrray.
 *  @param[in]  n number of requested values (may not be greater than t_nvar)
 */
// -------------------------------------------------------------------------------------
int32_t Statistics::multi::mean( real8_t* t, const int32_t n ) {
  // -----------------------------------------------------------------------------------
  int32_t nv = t_nvar;
  if ( 0 < n ) {
    if ( n < nv ) {
      nv = n;
    } else {
      logger->error( "N=%d can not be greater than the number of variables %d", n, t_nvar );
      return 0;
    }
  }
  for ( int32_t i=0; i<nv; i++ ) {
    t[i] = S[i]->mean();
  }
  return nv;
}


// =====================================================================================
/** @brief Fill Array with Variance.
 *  @param[out] t pointer to receiving arrray.
 *  @param[in]  n number of requested values (may not be greater than t_nvar)
 */
// -------------------------------------------------------------------------------------
int32_t Statistics::multi::var( real8_t* t, const int32_t n ) {
  // -----------------------------------------------------------------------------------
  int32_t nv = t_nvar;
  if ( 0 < n ) {
    if ( n < nv ) {
      nv = n;
    } else {
      logger->error( "N=%d can not be greater than the number of variables %d", n, t_nvar );
      return 0;
    }
  }
  for ( int32_t i=0; i<nv; i++ ) {
    t[i] = S[i]->var();
  }
  return nv;
}


// =====================================================================================
/** @brief Fill Array with Standard Deviation.
 *  @param[out] t pointer to receiving arrray.
 *  @param[in]  n number of requested values (may not be greater than t_nvar)
 */
// -------------------------------------------------------------------------------------
int32_t Statistics::multi::std( real8_t* t, const int32_t n ) {
  // -----------------------------------------------------------------------------------
  int32_t nv = t_nvar;
  if ( 0 < n ) {
    if ( n < nv ) {
      nv = n;
    } else {
      logger->error( "N=%d can not be greater than the number of variables %d", n, t_nvar );
      return 0;
    }
  }
  for ( int32_t i=0; i<nv; i++ ) {
    t[i] = S[i]->std();
  }
  return nv;
}


// =====================================================================================
/** @brief Fill Array with Absolute Deveation.
 *  @param[out] t pointer to receiving arrray.
 *  @param[in]  n number of requested values (may not be greater than t_nvar)
 */
// -------------------------------------------------------------------------------------
int32_t Statistics::multi::adev( real8_t* t, const int32_t n ) {
  // -----------------------------------------------------------------------------------
  int32_t nv = t_nvar;
  if ( 0 < n ) {
    if ( n < nv ) {
      nv = n;
    } else {
      logger->error( "N=%d can not be greater than the number of variables %d", n, t_nvar );
      return 0;
    }
  }
  for ( int32_t i=0; i<nv; i++ ) {
    t[i] = S[i]->adev();
  }
  return nv;
}


// =====================================================================================
/** @brief Fill Array with Skewness.
 *  @param[out] t pointer to receiving arrray.
 *  @param[in]  n number of requested values (may not be greater than t_nvar)
 */
// -------------------------------------------------------------------------------------
int32_t Statistics::multi::skew( real8_t* t, const int32_t n ) {
  // -----------------------------------------------------------------------------------
  int32_t nv = t_nvar;
  if ( 0 < n ) {
    if ( n < nv ) {
      nv = n;
    } else {
      logger->error( "N=%d can not be greater than the number of variables %d", n, t_nvar );
      return 0;
    }
  }
  for ( int32_t i=0; i<nv; i++ ) {
    t[i] = S[i]->skew();
  }
  return nv;
}


// =====================================================================================
/** @brief Fill Array with Kurtosis.
 *  @param[out] t pointer to receiving arrray.
 *  @param[in]  n number of requested values (may not be greater than t_nvar)
 */
// -------------------------------------------------------------------------------------
int32_t Statistics::multi::kurt( real8_t* t, const int32_t n ) {
  // -----------------------------------------------------------------------------------
  int32_t nv = t_nvar;
  if ( 0 < n ) {
    if ( n < nv ) {
      nv = n;
    } else {
      logger->error( "N=%d can not be greater than the number of variables %d", n, t_nvar );
      return 0;
    }
  }
  for ( int32_t i=0; i<nv; i++ ) {
    t[i] = S[i]->kurt();
  }
  return nv;
}


// =====================================================================================
/** @brief Zero out settings.
 */
// -------------------------------------------------------------------------------------
void Statistics::multi::clear( void ) {
  // -----------------------------------------------------------------------------------
  for ( int32_t i=0; i<t_nvar; i++ ) {
    S[i]->clear();
  }

  t_level1    = false;
  t_level2a   = false;
  t_level2b   = false;
}


// =====================================================================================
/** @brief Report
 *  @param[in] os   reference to an output stream.
 *  @param[in] sfmt edit sescriptor for fields.
 */
// -------------------------------------------------------------------------------------
void Statistics::multi::report( std::ostream& os, const std::string sfmt ) {
  // -----------------------------------------------------------------------------------
  if ( t_level1 ) {
    real8_t rTemp[ t_nvar ];
    int32_t  iTemp[ t_nvar ];
      
    os << "Number of samples   = " << count() << "\n"
       << "Number of variables = " << t_nvar   << "\n";

    const std::string ifmt  = "%d";

    minv( rTemp );   os << "Min Value = " << toString( rTemp, t_nvar, sfmt, " " ) << "\n";
    maxv( rTemp );   os << "Max Value = " << toString( rTemp, t_nvar, sfmt, " " ) << "\n";
    minidx( iTemp ); os << "Min Index = " << toString( iTemp, t_nvar, ifmt, " " ) << "\n";
    maxidx( iTemp ); os << "Max Index = " << toString( iTemp, t_nvar, ifmt, " " ) << "\n";
    mean( rTemp );   os << "Mean      = " << toString( rTemp, t_nvar, sfmt, " " ) << "\n";
    var( rTemp );    os << "Variance  = " << toString( rTemp, t_nvar, sfmt, " " ) << "\n";

    if ( t_level2a ) {
      std( rTemp );  os << "Std Dev   = " << toString( rTemp, t_nvar, sfmt, " " ) << "\n";
      adev( rTemp ); os << "Abs Dev   = " << toString( rTemp, t_nvar, sfmt, " " ) << "\n";
      skew( rTemp ); os << "Skew      = " << toString( rTemp, t_nvar, sfmt, " " ) << "\n";
      kurt( rTemp ); os << "Kurtosis  = " << toString( rTemp, t_nvar, sfmt, " " ) << "\n";

      if ( t_level2b ) {
	os << "Covariance:\n"
           << toString( *covariance, sfmt, " ", "\n" ) << "\n";
	os << "Correlation:\n"
           << toString( *correlation, sfmt, " ", "\n" ) << "\n";
      }
    }
    os << "\n";
  }
}

// =====================================================================================
/** @brief Compile.
 *  @param[in] table input data.
 *  @retrun true if an error occured.
 *
 *  Compile the basic statistics, to include, min/max mean and variance.
 */
// -------------------------------------------------------------------------------------
bool Statistics::multi::compile( Table& table ) {
  // -----------------------------------------------------------------------------------
  t_level1 = false;

  int32_t num_samples = table.size(0);
    
  for ( int32_t i=0; i<t_nvar; i++ ) {
    real8_t* buffer = table.col(i);
    if ( S[i]->compile( buffer, num_samples ) ) {
      logger->error( LOCATION, "Variable %d failed to compile level 1 stats", i+1 );
      return true;
    }
  }

  t_level1 = true;
  return false;
}


// =====================================================================================
/** @brief Compile extras.
 *  @param[in] table input data.
 *  @retrun true if an error occured.
 *
 *  Compile the extra statistics, to include, standard deviation, skew and kurt.
 */
// -------------------------------------------------------------------------------------
bool Statistics::multi::extra( Table& table ) {
  // -----------------------------------------------------------------------------------
  t_level2a = false;

  if ( ! t_level1 ) {
    logger->warn( LOCATION, "running EXTRA requires that COMPILE was first called" );
    logger->warn( LOCATION, "   I will attempt to do it for you," );
    if ( compile( table ) ) {
      logger->error( LOCATION, "   Sorry I failed, you need to fix it your self." );
      return true;
    }
    logger->warn( LOCATION, "   Okay that worked, now I will call EXTRA" );
  }

  int32_t num_samples = table.size(0);
    
  for ( int32_t i=0; i<t_nvar; i++ ) {
    real8_t* buffer = table.col(i);
    if ( S[i]->extra( buffer, num_samples ) ) {
      logger->error( LOCATION, "Variable %d failed to compile level 2 stats", i+1 );
      return true;
    }
  }

  t_level2a = true;
  return false;
}






// =====================================================================================
// -------------------------------------------------------------------------------------
bool Statistics::multi::correlate ( Table& table ) {
  // -----------------------------------------------------------------------------------
  t_level2b = false;

  if ( ! t_level1 ) {
    logger->warn( LOCATION, "this requires that you call compile first" );
    if ( this->compile( table ) ) {
      logger->warn( LOCATION, "   I tried to do it for you, but it failed" );
      return true;
    }
    logger->warn( LOCATION, "   I did it for you" );
  }

  real8_t temp_mu[ size( table, 1 ) ];
  mean( temp_mu );

  // ----- calculate the covariance matrix ---------------------------------------------
  if ( static_cast<Matrix*>(0) == covariance ) {
    covariance = new Matrix(t_nvar);
  }

  ::covariance( *covariance, table, temp_mu );

  // ----- calculate the correlation matrix --------------------------------------------
  if ( static_cast<Matrix*>(0) == correlation ) {
    correlation = new Matrix(t_nvar);
  }

  ::correlate( *correlation, *covariance );

  return (t_level2b = true);
}


// =====================================================================================
// -------------------------------------------------------------------------------------
bool Statistics::multi::invert_covariance( void ) {
  // -----------------------------------------------------------------------------------
  if ( ! t_level2b ) {
    logger->warn( LOCATION, "this requires that you call correlate first" );
    logger->warn( LOCATION, "   I can not do it for you" );
    return true;
  }

  if ( static_cast<Matrix*>(0) == inv_cov ) { inv_cov = new Matrix(t_nvar); }
  
  real8_t rv = inv_cov->inverse( *covariance );

  if ( isZero(rv) ) {
    if ( static_cast<Matrix*>(0) != inv_cov ) {
      delete inv_cov;
      inv_cov = static_cast<Matrix*>(0);
      return true;
    }
  }
  
  return false;
}














#define INIT_HVAR(a) nbin(a), hbin(a), hctr(a), nsamp(a)

// =======================================================================================
/** @brief Initialize.
 *  @param[in] centers pointer to an array of bin centers..
 *  @param[in] n number of bins.
 *
 *  Create the histogram bins and thier labled centers.
 */
// ---------------------------------------------------------------------------------------
void Statistics::histogram::init( const real8_t* centers, const int32_t n ) {
  // -------------------------------------------------------------------------------------
  nbin      = n;
  hbin      = new int32_t[n];
  hctr      = new real8_t[n];
  for ( int32_t i=0; i<n; i++ ) {
    hctr[i] = centers[i];
  }
  nsamp     = 0;
}


// =======================================================================================
/** @brief Contructor.
 *  @param[in] centers pointer to an array of bin centers..
 *  @param[in] n number of bins.
 *
 *  Create the histogram bins and thier labled centers.
 */
// ---------------------------------------------------------------------------------------
Statistics::histogram::histogram( const int32_t n ) : INIT_HVAR(0) {
  // -------------------------------------------------------------------------------------
  real8_t* temp = new real8_t[n];

  for (int32_t i=0; i<n; i++) {
    temp[i] = static_cast<real8_t>(i);
  }

  init( temp, n );

  delete[] temp;
}


// =======================================================================================
/** @brief Contructor.
 *  @param[in] centers pointer to an array of bin centers..
 *  @param[in] n number of bins.
 *
 *  Create the histogram bins and thier labled centers.
 */
// ---------------------------------------------------------------------------------------
Statistics::histogram::histogram( const real8_t lower, const real8_t upper,
				  const int32_t n ) : INIT_HVAR(0) {
  // -------------------------------------------------------------------------------------
  real8_t* temp = new real8_t[n];

  real8_t diff = Abs(upper - lower) / (real8_t)(n-1);

  temp[0] = Min( lower, upper );
  for (int32_t i=1; i<n; i++) {
    temp[i] = temp[i-1] + diff;
  }

  init( temp, n );

  delete[] temp;
}


// =======================================================================================
/** @brief Contructor.
 *  @param[in] centers pointer to an array of bin centers..
 *  @param[in] n number of bins.
 *
 *  Create the histogram bins and thier labled centers.
 */
// ---------------------------------------------------------------------------------------
Statistics::histogram::histogram( const real8_t* centers, const int32_t n ) : INIT_HVAR(0) {
  // -------------------------------------------------------------------------------------
  init( centers, n );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Statistics::histogram::~histogram( void ) {
  // -------------------------------------------------------------------------------------
  nbin      = 0;
  delete[] hbin;  hbin = static_cast<int32_t*>(0);
  delete[] hctr;  hctr = static_cast<real8_t*>(0);
  nsamp     = 0;
}


// =======================================================================================
/** @brief Reset.
 *
 *  Clear all bins.  
 */
// ---------------------------------------------------------------------------------------
void Statistics::histogram::reset( void ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nbin; i++ ) {
    hbin[i] = 0;
  }
  nsamp     = 0;
}


// =======================================================================================
/** @brief Maximum.
 *  @return index of the bin with the maximum samples.
 */
// ---------------------------------------------------------------------------------------
int32_t  Statistics::histogram::max( void ) const {
  // -------------------------------------------------------------------------------------
  int32_t idx = 0;
  int32_t mxc = 0;
  for ( int32_t i=0; i<nbin; i++ ) {
    if ( hbin[i] > mxc ) {
      mxc = hbin[i];
      idx = i;
    }
  }
  return idx;
}


// =======================================================================================
/** @brief Add.
 *  @param[in] x sample. 
 */
// ---------------------------------------------------------------------------------------
void Statistics::histogram::add( const int32_t idx ) {
  // -------------------------------------------------------------------------------------
  if ( idx < nbin ) {
    hbin[idx] += 1;
    nsamp     += 1;
  }
}


// =======================================================================================
/** @brief Add Multiple.
 *  @param[in] A pointer to an array of values to add.
 *  @param[in] n number of values to add.
 *
 *  Add an array of values to this histogram.
 */
// ---------------------------------------------------------------------------------------
void Statistics::histogram::add( const real8_t* A, const int32_t n ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<n; i++ ) {
    add( A[i] );
  }
}


// =======================================================================================
/** @brief Internal Distance Metric
 *  @param[in] a first point.
 *  @param[in] b second point.
 *  @return absolute value of the diffence in the numbers a and b.
 */
// ---------------------------------------------------------------------------------------
inline real8_t dist2( const real8_t a, const real8_t b ) {
  // -------------------------------------------------------------------------------------
  const real8_t x = a-b;
  return ( D_ZERO > x ) ? (-x) : (x);
}


// =======================================================================================
/** @brief Map.
 *  @param[in] x value to map.
 *
 *  Locate the bin that this value belongs to.
 */
// ---------------------------------------------------------------------------------------
int32_t Statistics::histogram::map( const real8_t x ) const {
  // -------------------------------------------------------------------------------------
  int32_t  idx   = 0;
  real8_t min_d = dist2( x, hctr[idx] );
  for ( int32_t i=1; i<nbin; i++ ) {
    real8_t test = dist2( x, hctr[i] );
    if ( test < min_d ) {
      min_d = test;
      idx   = i;
    }
  } 
  return idx;
}


// =======================================================================================
// **                                S T A T I S T I C S                                **
// ======================================================================== END FILE =====
