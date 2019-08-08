// ====================================================================== BEGIN FILE =====
// **                               F I X E D N O R M A L                               **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2018-2019, Stephen W. Soliday                                      **
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
/** @brief Fixed / Normal Generator.
 *  @file   FixedNormal.hh
 *  @author Stephen W. Soliday
 *  @date   2018-Jan-03 Original (Java) release.
 *  @date   2019-Jun-28 C++ port.
 *
 *  Provides the methods for generating either a fixed number or a normal distribution.
 */
// =======================================================================================

#include <FixedNormal.hh>
#include <StringTool.hh>


#define INIT_VAR(a) fixed(true), mean_value(a), std_dev(a), min_value(a), max_value(a), dd(0)


TLOGGER_REFERENCE( FixedNormal, logger );


// =======================================================================================
/** @brief Initialization.
 *  @param[in] flag true=fixed, false=normal.
 *  @param[in] mean the mean     value returned by this object.
 *  @param[in] std  the standard deviation of values returned by this object.
 *  @param[in] minv the minimum value returned by this object.
 *  @param[in] maxv the maximum value returned by this object.
 */
// ---------------------------------------------------------------------------------------
void FixedNormal::init( bool flag, real8_t mean, real8_t std, real8_t minv, real8_t maxv ) {
  // -------------------------------------------------------------------------------------
    fixed      = flag;
    mean_value = mean;
    std_dev    = std;
    min_value  = minv;
    max_value  = maxv;
    dd         = Dice::getInstance();
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] x the fixed value returned by this object.
 *
 *  Construct this object to return the same fixed value with each call to next().
 */
// ---------------------------------------------------------------------------------------
FixedNormal::FixedNormal( real8_t x ) : INIT_VAR(0.0) {
  // -------------------------------------------------------------------------------------
  init( true, x );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] mean the mean     value returned by this object.
 *  @param[in] std  the standard deviation of values returned by this object.
 *
 *  Construct this object to return a normally distributed random variable with each
 *  call to next().
 */
// ---------------------------------------------------------------------------------------
FixedNormal::FixedNormal( real8_t mean, real8_t std ) : INIT_VAR(0.0) {
  // -------------------------------------------------------------------------------------
  init( false, mean, std, mean - D_THREE*std, mean + D_THREE*std );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] mean the mean     value returned by this object.
 *  @param[in] std  the standard deviation of values returned by this object.
 *  @param[in] minv the minimum value returned by this object.
 *  @param[in] maxv the maximum value returned by this object.
 *
 *  Construct this object to return a normally distributed random variable with each
 *  call to next().
 */
// ---------------------------------------------------------------------------------------
FixedNormal::FixedNormal( real8_t mean, real8_t std, real8_t minv, real8_t maxv ) : INIT_VAR(0.0) {
  // -------------------------------------------------------------------------------------
  init( false, mean, std, minv, maxv );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] param list of parameters.
 *  @param[in] n     number of parameters (1,2, or 4)
 *
 *  If the list only contains one item then a fixed generator is created.
 *  If the list contains two items then the minimum and maximum values will be 
 *  mean +/- 3*std.
 */
// ---------------------------------------------------------------------------------------
FixedNormal::FixedNormal( real8_t* param, size_t n ) : INIT_VAR(0.0) {
  // -------------------------------------------------------------------------------------
  switch(n) {
    case 1:
      init( true,
            param[0] );
      break;
      
    case 2:
      init( false,
            param[0],
            param[1],
            param[0] - D_THREE*param[1],
            param[0] + D_THREE*param[1] );
      break;
      
    case 4:
      init( false,
            param[0],
            param[1],
            param[2],
            param[3] );
      break;

    default:
      logger->error( LOCATION, "Improper interval format, used" );
      break;
  }
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] param string consisting of either a fixed value or a list of [mean, std]
 *
 *  If the list only contains one item then a fixed generator is created.
 *  If the list contains two items then the minimum and maximum values will be 
 *  mean +/- 3*std.
 */
// ---------------------------------------------------------------------------------------
FixedNormal::FixedNormal( std::string param ) : INIT_VAR(0.0) {
  // -------------------------------------------------------------------------------------
  size_t n = 0;
  real8_t* list = StringTool::asReal8List( n, param );
  switch(n) {
    case 1:
      init( true,
            list[0] );
      break;
      
    case 2:
      init( false,
            list[0],
            list[1],
            list[0] - D_THREE*list[1],
            list[0] + D_THREE*list[1] );
      break;
      
    case 4:
      init( false,
            list[0],
            list[1],
            list[2],
            list[3] );
      break;
      
    default:
      logger->error( LOCATION, "Improper interval format, used" );
      break;
  }
  delete[] list;
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
FixedNormal::~FixedNormal( void ) {
  // -------------------------------------------------------------------------------------

  fixed      = false;
  mean_value = D_ZERO;
  std_dev    = D_ZERO;
  min_value  = D_ZERO;
  max_value  = D_ZERO;
  dd         = static_cast<Dice*>(0);
}


// =======================================================================================
/** @brief Get next real.
 *  @return if fixed=true return the mean,
 *          if false return normally distributed random number.
 */
// ---------------------------------------------------------------------------------------
real8_t FixedNormal::next( void ) {
  // -------------------------------------------------------------------------------------
  if ( fixed ) {
    return mean_value;
  }
	
  double x = mean_value + std_dev*dd->normal();

  while ( ( x < min_value ) || ( x > max_value ) ) {
    x = mean_value + std_dev*dd->normal();
  }

  return x;
}


// =======================================================================================
/** @brief Get next integer.
 *  @return if fixed=true return the mean,
 *          if false return normally distributed random number.
 */
// ---------------------------------------------------------------------------------------
int32_t FixedNormal::nextInt( void ) {
  // -------------------------------------------------------------------------------------
  if ( fixed ) {
    return (int32_t) floor( mean_value + 0.5 );
  }
	
  real8_t x = floor( mean_value + std_dev*dd->normal() + 0.5 );

  while ( ( x < min_value ) || ( x > max_value ) ) {
    x = floor( mean_value + std_dev*dd->normal() + 0.5 );
  }

  return (int32_t) x;
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
void FixedNormal::report( std::ostream& ps ) {
  // -------------------------------------------------------------------------------------
  ps << "Use Fixed " << fixed      << "\n"
     << "Mean      " << mean_value << "\n"
     << "Std Dev   " << std_dev    << "\n"
     << "Min Val   " << min_value  << "\n"
     << "Max Val   " << max_value  << "\n";

}

// =======================================================================================
// **                               F I X E D N O R M A L                               **
// ======================================================================== END FILE =====
