// ====================================================================== BEGIN FILE =====
// **                              E V O : : T O O L K I T                              **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 1995-2019, Stephen W. Soliday                                      **
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
/** @brief ToolKit.
 *  @file   evo/ToolKit.hh
 *  @author Stephen W. Soliday
 *  @date   2014-Jun-27 Original C++ release
 *  @date   2019-Sep-27 CMake refactorization.
 *
 *  Provides an interface for basic operators.
 */
// =======================================================================================


#include <evo/ToolKit.hh>


namespace evo {


/// Static singleton instance.
ToolKit* ToolKit::theInstance = static_cast<ToolKit*>(0);


// =======================================================================================
/** @brief Constructor.
 *  @param[in] d pointer to a Dice instance.
 */
// ---------------------------------------------------------------------------------------
ToolKit::ToolKit( Dice* d ) : dd(d) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
ToolKit::~ToolKit( void ) {
  // -------------------------------------------------------------------------------------
  dd = static_cast<Dice*>(0);
}


// =======================================================================================
/** @brief Get Instance.
 *  @return a pointer to the static instance of the ToolKit class.
 *
 *  Get the static instance of the ToolKit class, creating it if needed.
 */
// ---------------------------------------------------------------------------------------
ToolKit* ToolKit::getInstance( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<ToolKit*>(0) == ToolKit::theInstance ) {
    ToolKit::theInstance = new ToolKit( Dice::getInstance() );
  }
  return ToolKit::theInstance; 
}


// =======================================================================================
/** @brief Get Instance.
 *  @param[in] pointer to a Dice instance.
 *  @return a pointer to the static instance of the ToolKit class.
 *
 *  Get the static instance of the ToolKit class, creating it if needed.
 */
// ---------------------------------------------------------------------------------------
ToolKit* ToolKit::getInstance( Dice* d ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<ToolKit*>(0) == ToolKit::theInstance ) {
    ToolKit::theInstance = new ToolKit( d );
  }
  return ToolKit::theInstance; 
}


// =======================================================================================
/** @brief Delete Instance.
 *
 *  Delete the static instance of the Dice class.
 */
// ---------------------------------------------------------------------------------------
void ToolKit::delInstance( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<ToolKit*>(0) != ToolKit::theInstance ) {
    delete ToolKit::theInstance;
    ToolKit::theInstance =  static_cast<ToolKit*>(0);
  }
}






// =======================================================================================
/** @brief Randomize.
 *  @param[in,out] a       pointer to array.
 *  @param[in]     n       number of elements.
 *  @param[in]     min_val minimum value.
 *  @param[in]     max_val maximum value.
 *
 *  Fill the array a with uniformly distributed random numbers.
 */
// ---------------------------------------------------------------------------------------
void ToolKit::randomize( real8_t* a, int32_t n, const real8_t min_val, const real8_t max_val ) {
  // -------------------------------------------------------------------------------------
  const real8_t D = max_val - min_val;
  for ( int32_t i=0; i<n; i++ ) {
    a[i] = min_val + D*dd->uniform();
  }
}


// =======================================================================================
/** @brief Randomize.
 *  @param[in,out] a       pointer to array.
 *  @param[in]     n       number of elements.
 *  @param[in]     min_val minimum value.
 *  @param[in]     max_val maximum value.
 *
 *  Fill the array a with uniformly distributed random numbers.
 */
// ---------------------------------------------------------------------------------------
void ToolKit::randomize( int32_t* a, int32_t n, const int32_t min_val, const int32_t max_val ) {
  // -------------------------------------------------------------------------------------
  int32_t rng = 1 + max_val - min_val;
  for ( int32_t i=0; i<n; i++ ) {
    a[i] = min_val + static_cast<int32_t>(dd->index(rng));
  }
}


// =======================================================================================
/** @brief Randomize.
 *  @param[in,out] a pointer to array.
 *  @param[in]     n number of elements.
 *
 *  Fill the array a with uniformly distributed random numbers.
 */
// ---------------------------------------------------------------------------------------
void ToolKit::randomize( int32_t* a, int32_t n ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<n; i++ ) {
    a[i] = static_cast<int32_t>(dd->index(n));
  }
}






// =======================================================================================
/** @brief Bracket.
 *  @param[in,out] a       pointer to an array.
 *  @param[in]     n       number of elements.
 *  @param[in]     min_val minimum value.
 *  @param[in]     max_val maximum value.
 *  @param[in]     src     pointer to a bias.
 *
 *  Bracketing randomly sets each value to its maximum or minimum.
 *  The array src will bias the min/max.
 *  For example if the max value is 255 and a source value of 96 will
 *  tend towards min (0) 62.5 percent of the time and max(255) 37.5 percent of the time.
 *  @note If you want the bracketing to be biased set the src pointer.
 */
// ---------------------------------------------------------------------------------------
void ToolKit::bracket( real8_t* a, int32_t n, const real8_t min_val, const real8_t max_val,
                       real8_t* src ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<real8_t*>(0) == src ) {
    for ( int32_t i=0; i<n; i++ ) {
      a[i] = (dd->boolean()) ? (max_val) : (min_val);
    }
  } else {
    const real8_t d = (max_val - min_val);
    for ( int32_t i=0; i<n; i++ ) {
      const real8_t thres = (src[i] - min_val) / d;
      a[i] = (dd->boolean(thres)) ? (min_val) : (max_val);
    }
  }
}


// =======================================================================================
/** @brief Bracket.
 *  @param[in,out] a       pointer to an array.
 *  @param[in]     n       number of elements.
 *  @param[in]     min_val minimum value.
 *  @param[in]     max_val maximum value.
 *  @param[in]     src     pointer to a bias.
 *
 *  Bracketing randomly sets each value to its maximum or minimum.
 *  The array src will bias the min/max.
 *  For example if the max value is 255 and a source value of 96 will
 *  tend towards min (0) 62.5 percent of the time and max(255) 37.5 percent of the time.
 *  @note If you want the bracketing to be biased set the src pointer.
 */
// ---------------------------------------------------------------------------------------
void ToolKit::bracket( int32_t* a, int32_t n, const int32_t min_val, const int32_t max_val,
                       int32_t* src ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<int32_t*>(0) == src ) {
    for ( int32_t i=0; i<n; i++ ) {
      a[i] = (dd->boolean()) ? (max_val) : (min_val);
    }
  } else {
    const real8_t d = static_cast<real8_t>(max_val - min_val);
    const real8_t m = static_cast<real8_t>(min_val);
    for ( int32_t i=0; i<n; i++ ) {
      const real8_t thres = (src[i] - m) / d;
      a[i] = (dd->boolean(thres)) ? (min_val) : (max_val);
    }
  }
}






// =======================================================================================
/** @brief Add noise.
 *  @param[in,out] a       pointer to data array.
 *  @param[in]     n       number of array elements.
 *  @param[in]     sigma   standard deviation from the mean.
 *  @param[in]     min_val minimum value.
 *  @param[in]     max_val maximum value.
 *  @param[in]     src     pointer to the encoding to bias with. (default none)
 *
 *  Gaussian noise centered on the source data.
 *  @note If you want the noise centered on the destination set the src to NULL.
 */
// ---------------------------------------------------------------------------------------
void ToolKit::noise( real8_t* a, int32_t n, const real8_t sigma,
                     const real8_t min_val, const real8_t max_val, real8_t* src ) {
  // -------------------------------------------------------------------------------------
  real8_t* S = (static_cast<real8_t*>(0) == src) ? (a) : (src);
  for ( int32_t i=0; i<n; i++ ) {
    const real8_t x = S[i] + sigma*dd->normal();
    a[i] = ((x < max_val) ? ((x > min_val) ? (x) : (min_val)) : (max_val));
  }
}


// =======================================================================================
/** @brief Add noise.
 *  @param[in,out] a       pointer to data array.
 *  @param[in]     n       number of array elements.
 *  @param[in]     sigma   standard deviation from the mean.
 *  @param[in]     min_val minimum value.
 *  @param[in]     max_val maximum value.
 *  @param[in]     src     pointer to the encoding to bias with. (default none)
 *
 *  Gaussian noise centered on the source data.
 *  @note If you want the noise centered on the destination set the src to NULL.
 */
// ---------------------------------------------------------------------------------------
void ToolKit::noise( int32_t* a, int32_t n, const real8_t sigma,
                     const int32_t min_val, const int32_t max_val, int32_t* src ) {
  // -------------------------------------------------------------------------------------
  int32_t* S = (static_cast<int32_t*>(0) == src) ? (a) : (src);
    for ( int32_t i=0; i<n; i++ ) {
      const real8_t x = static_cast<real8_t>(S[i]) + sigma*dd->normal();
      int32_t ix = static_cast<int32_t>(floor(x+D_HALF));
      a[i] = ((ix < max_val) ? ((ix > min_val) ? (ix) : (min_val)) : (max_val));
    }
}








// =======================================================================================
/** @brief Crossover.
 *  @param[in] c1 pointer to the first  child  array.
 *  @param[in] c2 pointer to the second child  array.
 *  @param[in] p1 pointer to the first  parent array.
 *  @param[in] p2 pointer to the second parent array.
 *  @param[in] n  number of array elements.
 *  @param[in] t  parametric.
 *  @param[in] min_val min_value.
 *  @param[in] max_val max_value.
 *
 *  Perform parametric crossover.
 *  Floating point and integer encodings:
 *     Perform n-dimensional parametric crossover.
 *        c1 = ( 1 - t ) * p1 + ( t ) * p2  ;  where t is a uniform random variable
 *        c2 = ( 1 - t ) * p2 + ( t ) * p1  ;  such that    0 <= t < 1
 */
// ---------------------------------------------------------------------------------------
void ToolKit::crossover( real8_t* c1, real8_t* c2, real8_t* p1, real8_t* p2,
                         const int32_t n, const real8_t t,
                   const real8_t min_val, const real8_t max_val ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<n; i++ ) {
    c1[i] = parametric( p1[i], p2[i], t, min_val, max_val );
    c2[i] = parametric( p2[i], p1[i], t, min_val, max_val );
  }
}


// =======================================================================================
/** @brief Crossover.
 *  @param[in] c1 pointer to the first  child  array.
 *  @param[in] c2 pointer to the second child  array.
 *  @param[in] p1 pointer to the first  parent array.
 *  @param[in] p2 pointer to the second parent array.
 *  @param[in] n  number of array elements.
 *  @param[in] t  parametric.
 *  @param[in] min_value min_val.
 *  @param[in] max_value max_val.
 *
 *  Perform parametric crossover.
 *  Floating point and integer encodings:
 *     Perform n-dimensional parametric crossover.
 *        c1 = ( 1 - t ) * p1 + ( t ) * p2  ;  where t is a uniform random variable
 *        c2 = ( 1 - t ) * p2 + ( t ) * p1  ;  such that    0 <= t < 1
 */
// ---------------------------------------------------------------------------------------
void ToolKit::crossover( int32_t* c1, int32_t* c2, int32_t* p1, int32_t* p2,
                         const int32_t n, const real8_t t,
                   const int32_t min_val, const int32_t max_val ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<n; i++ ) {
    c1[i] = parametric( p1[i], p2[i], t, min_val, max_val );
    c2[i] = parametric( p2[i], p1[i], t, min_val, max_val );
  }
}


// =======================================================================================
  /** @brief Mutate.
   *  @param c     pointer to the destination array.
   *  @param sigma standard deviation from the mean.
   *  @param p     pointer to the source array.
   *
   *  Generate Gaussian noise centered on the source array.
   *  @note If you want to mutate in place set the parent to NULL.
   */
// ---------------------------------------------------------------------------------------
void ToolKit::mutate( real8_t* c, const int32_t n, const real8_t sigma, const real8_t perc,
                      const real8_t min_val, const real8_t max_val,
                      real8_t* p ) {
// ---------------------------------------------------------------------------------------
  real8_t* src = (static_cast<real8_t*>(0) == p) ? (c) : (p);
  for ( int32_t i=0; i<n; i++ ) {
    if ( dd->boolean(perc) ) {
      const real8_t x = src[i] + sigma*dd->normal();
      c[i] = ((x < max_val) ? ((x > min_val) ? (x) : (min_val)) : (max_val));
    } else {
      c[i] = src[i];
    }
  }
}


// =======================================================================================
/** @brief Mutate.
 *  @param c     pointer to the destination array.
 *  @param sigma standard deviation from the mean.
 *  @param p     pointer to the source array.
 *
 *  Generate Gaussian noise centered on the source array.
 *  @note If you want to mutate in place set the parent to NULL.
 */
// ---------------------------------------------------------------------------------------
void ToolKit::mutate( int32_t* c, const int32_t n, const real8_t sigma, const real8_t perc,
                      const int32_t min_val, const int32_t max_val,
                      int32_t* p ) {
  // ---------------------------------------------------------------------------------------
  int32_t* src = (static_cast<int32_t*>(0) == p) ? (c) : (src);
  for ( int32_t i=0; i<n; i++ ) {
    if ( dd->boolean(perc) ) {
      const real8_t x = static_cast<real8_t>(src[i]) + sigma*dd->normal();
      int32_t ix = static_cast<int32_t>(floor(x+D_HALF));
      c[i] = ((ix < max_val) ? ((ix > min_val) ? (ix) : (min_val)) : (max_val));
    } else {
      c[i] = src[i];
    }
  }
}


// =======================================================================================
/** @brief
 *  @param[in]
 *
 *
 */
// ---------------------------------------------------------------------------------------
void ToolKit::permute( int32_t* a, int32_t n, const real8_t sigma, int32_t* src ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<int32_t*>(0) != src ) {
    for ( int32_t i=0; i<n; i++ ) {
      a[i] = src[i];
    }
  }
  
  real8_t t = static_cast<real8_t>(n) * sigma;
  int32_t m = static_cast<int32_t>(floor(D_HALF + t));

  for ( int32_t i=0; i<m; i++ ) {
    const size_t j = dd->index(static_cast<size_t>(n));
    const size_t k = dd->index(static_cast<size_t>(n));
    if ( j != k ) {
      const int32_t temp = a[j];
      a[j] = a[k];
      a[k] = temp;
    }
  }
}


}; // end namespace evo


// =======================================================================================
// **                              E V O : : T O O L K I T                              **
// =========================================================================== END FILE ==
