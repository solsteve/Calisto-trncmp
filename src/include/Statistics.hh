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
 *  @file   Statistics.hh
 *  @author Stephen W. Soliday
 *  @date   2015-Jan-26 Original release.
 *  @date   2019-Jul-26 CMake refactorization.
 *
 *  Provides the interface for one and two dimensional statistics.
 */
// =======================================================================================

#ifndef __HH_STATISTICS_TRNCMP
#define __HH_STATISTICS_TRNCMP

#include <Table.hh>
#include <Matrix.hh>

// =======================================================================================
class Statistics {
  // -------------------------------------------------------------------------------------
protected:
  TLOGGER_HEADER( logger );

public:
  
  // =====================================================================================
  class running {                                                   // Statistics::running
    // -----------------------------------------------------------------------------------
  protected:
    real8_t     min_val;        ///< Minimum sampled value.
    real8_t     max_val;        ///< Maximum sampled value.
    real8_t     mean_val;       ///< Running mean of the sampled values.
    real8_t     mean_val_sq;    ///< Running mean of the squares of the sampled values.
    bool        is_first;       ///< Set to true untile the first value is sampled.
    size_t      num_samp;       ///< Number of values sampled.
    size_t      min_idx;        ///< Index of the minimum value sampled.
    size_t      max_idx;        ///< Index of the maximum value sampled.

  public:
    running        ( void );
    ~running       ( void );

    size_t  count  ( void );
    real8_t minv   ( void );
    real8_t maxv   ( void );
    real8_t mean   ( void );
    real8_t var    ( void );
    real8_t stdev  ( void );
    size_t  minidx ( void );
    size_t  maxidx ( void );

    void    reset  ( void );

    void    report ( std::ostream& os, const std::string sfmt = "%g" );
   
    template<class T> void update ( T v );
    template<class T> void batch  ( T* a, size_t n );
    
  }; // end class Statistics::running


  // =====================================================================================
  class single {                                                     // Statistics::single
    // -----------------------------------------------------------------------------------
  public:
    size_t  t_count;   ///< Number of samples
    bool    t_level1;  ///< flag indicating that level one is complete
    bool    t_level2;  ///< flag indicating that level two is complete
    
    // ----- level 1 ---------------------------------------------------------------------
    real8_t t_minv;    ///< Minimum sample value
    real8_t t_maxv;    ///< Maximum sample value
    size_t  t_minidx;  ///< Index of minimum value
    size_t  t_maxidx;  ///< Index of maximum value
    real8_t t_mean;    ///< Mean value of sample
    real8_t t_var;     ///< Sample variance
    
    // ----- level 2 ---------------------------------------------------------------------
    real8_t t_std;     ///< Standard deviation of the mean
    real8_t t_adev;    ///< Absolute deviation of the mean
    real8_t t_skew;    ///< Sample skew
    real8_t t_kurt;    ///< Sample kurt

  public:
    size_t   count  ( void ) { return t_count;  };
    real8_t  minv   ( void ) { return t_minv;   };
    real8_t  maxv   ( void ) { return t_maxv;   };
    size_t   minidx ( void ) { return t_minidx; };
    size_t   maxidx ( void ) { return t_maxidx; };
    real8_t  mean   ( void ) { return t_mean;   };
    real8_t  var    ( void ) { return t_var;    };
    real8_t  std    ( void ) { return t_std;    };
    real8_t  adev   ( void ) { return t_adev;   };
    real8_t  skew   ( void ) { return t_skew;   };
    real8_t  kurt   ( void ) { return t_kurt;   };

    single  ( void );
    ~single ( void );

    void     clear   ( void );
    void     report  ( std::ostream& os, const std::string sfmt = "%g" );

    bool     compile ( const real8_t* data, const size_t num_samples );
    bool     extra   ( const real8_t* data, const size_t num_samples );

  }; // end class Statistics::single


  // =====================================================================================
  class multi {                                                       // Statistics::multi
    // -----------------------------------------------------------------------------------
   protected:

    size_t   t_nvar;         ///< number of dimensions.
    bool     t_level1;       ///< flag indicating that level one was complete.
    bool     t_level2a;      ///< flag indicating that level two A was complete.
    bool     t_level2b;      ///< flag indicating that level two B was complete.
    
    // ----- level 1 & 2a ----------------------------------------------------------------
    single** S;              ///< Array of single class.

    // ----- level 3 ---------------------------------------------------------------------
    
  public:
    Matrix*  covariance;     ///< Covariance  matrix.
    Matrix*  correlation;    ///< Correlation matrix.
    Matrix*  inv_cov;        ///< Inverse covariance.

    size_t   nvar   ( void )       { return t_nvar;              };
    size_t   count  ( void )       { return S[0]->count();    };
    real8_t  minv   ( size_t idx ) { return S[idx]->minv();   };
    real8_t  maxv   ( size_t idx ) { return S[idx]->maxv();   };
    size_t   minidx ( size_t idx ) { return S[idx]->minidx(); };
    size_t   maxidx ( size_t idx ) { return S[idx]->maxidx(); };
    real8_t  mean   ( size_t idx ) { return S[idx]->mean();   };
    real8_t  var    ( size_t idx ) { return S[idx]->var();    };
    real8_t  std    ( size_t idx ) { return S[idx]->std();    };
    real8_t  adev   ( size_t idx ) { return S[idx]->adev();   };
    real8_t  skew   ( size_t idx ) { return S[idx]->skew();   };
    real8_t  kurt   ( size_t idx ) { return S[idx]->kurt();   };

    size_t   minv   ( real8_t* t, const size_t n=0 );
    size_t   maxv   ( real8_t* t, const size_t n=0 );
    size_t   minidx ( size_t*  t, const size_t n=0 );
    size_t   maxidx ( size_t*  t, const size_t n=0 );
    size_t   mean   ( real8_t* t, const size_t n=0 );
    size_t   var    ( real8_t* t, const size_t n=0 );
    size_t   std    ( real8_t* t, const size_t n=0 );
    size_t   adev   ( real8_t* t, const size_t n=0 );
    size_t   skew   ( real8_t* t, const size_t n=0 );
    size_t   kurt   ( real8_t* t, const size_t n=0 );

    multi  ( size_t n );
    ~multi ( void );

    void     clear     ( void );
    void     report    ( std::ostream& os, const std::string sfmt = "%g" );

    bool     compile   ( Table& table );
    bool     extra     ( Table& table );
    bool     correlate ( Table& table );
    bool     invert_covariance( void );
    
  }; // end class Statistics::multi


  // =====================================================================================
  class histogram {                                               // Statistics::histogram
    // -----------------------------------------------------------------------------------
  protected:
    EMPTY_PROTOTYPE( histogram );

    size_t   nbin;       ///< Number of bins
    size_t*  hbin;       ///< The bins
    real8_t* hctr;       ///< Numeric center of each bin
    size_t   nsamp;      ///< Number of samples

    void  init      ( const real8_t* centers, const size_t n );
    
  public:
    histogram      (                                             const size_t n );
    histogram      ( const real8_t  lower,  const real8_t upper, const size_t n );
    histogram      ( const real8_t* centers,                     const size_t n );

    ~histogram     ( void );

    void    reset  ( void );
    void    add    ( const size_t  x );
    void    add    ( const real8_t x );
    void    add    ( const real8_t* A, const size_t n );

    size_t  size   ( void ) const;
    size_t  count  ( void ) const;
    size_t  bin    ( const size_t idx ) const;
    size_t  max    ( void ) const;
    real8_t center ( const size_t idx ) const;

    size_t  map    ( const real8_t x ) const; ///< Esentially 1-D k-means clustering
  }; // end class Statistics::histogram

  
}; // end class Statistics


// =======================================================================================
/** @brief Update.
 *  @param[in] v sample value.
 */
// ---------------------------------------------------------------------------------------
template<class T>
void Statistics::running::update( T v ) {
  // -------------------------------------------------------------------------------------
  real8_t x = (real8_t) v;
  if ( is_first ) {
    min_val     = x;
    max_val     = x;
    mean_val    = x;
    mean_val_sq = x*x;
    is_first    = false;
    num_samp    = 1;
    min_idx     = 0;
    max_idx     = 0;
  } else {
    if ( x < min_val ) { min_val = x;  min_idx = num_samp; }
    if ( x > max_val ) { max_val = x;  max_idx = num_samp; }

    real8_t t  = (real8_t)num_samp * mean_val;
    real8_t t2 = (real8_t)num_samp * mean_val_sq;
    num_samp++;
    mean_val    = (x   + t ) / (real8_t)num_samp;
    mean_val_sq = (x*x + t2) / (real8_t)num_samp;      
  }

}


// =======================================================================================
/** @brief Batch Update.
 *  @param[in] a pointer to an array of sample values.
 *  @param[in] n number of ellements in the sample array.
 */
// ---------------------------------------------------------------------------------------
template<class T>
void Statistics::running::batch( T* a, size_t n ) {
  // -------------------------------------------------------------------------------------
  for ( size_t i=0; i<n; i++ ) {
    update( a[i] );
  }
}


// =======================================================================================
/** @brief Minimum.
 *  @return minimum sampled value.
 */
// ---------------------------------------------------------------------------------------
inline  size_t Statistics::running::count( void ) {
  // -------------------------------------------------------------------------------------
  return num_samp;
}


// =======================================================================================
/** @brief Minimum.
 *  @return minimum sampled value.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Statistics::running::minv( void ) {
  // -------------------------------------------------------------------------------------
  return min_val;
}


// =======================================================================================
/** @brief maximum.
 *  @return maximum sampled value.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Statistics::running::maxv( void ) {
  // -------------------------------------------------------------------------------------
  return max_val;
}


// =======================================================================================
/** @brief Mean.
 *  @return mean of the sampled values.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Statistics::running::mean( void ) {
  // -------------------------------------------------------------------------------------
  return mean_val;
}


// =======================================================================================
/** @brief Standard Deviation.
 *  @return mean of the standard deviation of the sampled values.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Statistics::running::stdev( void ) {
  // -------------------------------------------------------------------------------------
  return sqrt( var() );
}


// =======================================================================================
/** @brief Minimum.
 *  @return index of the minimum sampled value.
 */
// ---------------------------------------------------------------------------------------
inline  size_t Statistics::running::minidx( void ) {
  // -------------------------------------------------------------------------------------
  return min_idx;
}


// =======================================================================================
/** @brief Maximum.
 *  @return index of the maximum sampled value.
 */
// ---------------------------------------------------------------------------------------
inline  size_t Statistics::running::maxidx( void ) {
  // -------------------------------------------------------------------------------------
  return max_idx;
}








// =======================================================================================
/** @brief Add.
 *  @param[in] x sample. 
 */
// ---------------------------------------------------------------------------------------
inline  void Statistics::histogram::add( const real8_t x ) {
  // -------------------------------------------------------------------------------------
  add( map(x) );
}


// =======================================================================================
/** @brief Size.
 *  @return number of bins.
 */
// ---------------------------------------------------------------------------------------
inline  size_t   Statistics::histogram::size( void ) const {
  // -------------------------------------------------------------------------------------
  return nbin;
}


// =======================================================================================
/** @brief Count.
 *  @return number of samples.
 *
 *  Sum of all of the bins.
 */
// ---------------------------------------------------------------------------------------
inline  size_t  Statistics::histogram::count( void ) const {
  // -------------------------------------------------------------------------------------
  return nsamp;
}


// =======================================================================================
/** @brief Bin.
 *  @param[in] idx bin index.
 *  @return then number of samples contained in bin idx.
 */
// ---------------------------------------------------------------------------------------
inline  size_t  Statistics::histogram::bin( const size_t idx ) const {
  // -------------------------------------------------------------------------------------
  return hbin[idx];
}


// =======================================================================================
/** @brief Center.
 *  @param[in] idx bin index.
 *  @return value of a bin's center.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Statistics::histogram::center( const size_t idx ) const {
  // -------------------------------------------------------------------------------------
  return hctr[idx];
}


#endif


// =======================================================================================
// **                                S T A T I S T I C S                                **
// ======================================================================== END FILE =====
