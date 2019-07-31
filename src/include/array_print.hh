// ====================================================================== BEGIN FILE =====
// **                               A R R A Y _ P R I N T                               **
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
/** @brief  Array Printing.
 *  @file   array_print.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Apr-24 Original release.
 *
 *  Provides the interface for various copy and clone single dimension arrays.
 */
// =======================================================================================


#ifndef __HH_ARRAYPRINT_TRNCMP
#define __HH_ARRAYPRINT_TRNCMP


#include <trncmp.hh>

#ifndef DEFAULT_PRINT_FORMAT
#define DEFAULT_PRINT_FORMAT    "%g"      ///< Default element format
#endif

#ifndef DEFAULT_PRINT_DELIM
#define DEFAULT_PRINT_DELIM      " "      ///< Default element separator
#endif

#ifndef DEFAULT_PRINT_COL_DELIM
#define DEFAULT_PRINT_COL_DELIM  " "      ///< Default column separator
#endif

#ifndef DEFAULT_PRINT_ROW_DELIM
#define DEFAULT_PRINT_ROW_DELIM  "\n"     ///< Default row separator
#endif


// =======================================================================================
/** @brief To String.
 *  @param[in] A    pointer to an array.
 *  @param[in] n    number of array elements.
 *  @param[in] sfmt edit descriptor.
 *  @param[in] sdel column delimeter.
 *
 *  Format an array for printing and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
template<class T>
std::string toString  ( T* A, size_t n,
                        std::string sfmt = DEFAULT_PRINT_FORMAT,
                        std::string sdel = DEFAULT_PRINT_DELIM ) {
  // -------------------------------------------------------------------------------------
  if (static_cast<T*>(0) == A) throw std::invalid_argument("array is NULL");
  if (0 == n) throw std::invalid_argument("zero length array");

  std::string df  = sdel + sfmt;
  const char* fmt = sfmt.c_str();
  const char* del = df.c_str();

  char buffer[64];
  snprintf( buffer, 64, fmt, A[0] );
  std::string tstr = buffer;

  for ( size_t i=1; i<n; i++ ) {
    snprintf( buffer, 64, del, A[i] );
    tstr.append( buffer );
  }

  return tstr;
}


// =======================================================================================
/** @brief To String.
 *  @param[in] A    pointer to an array.
 *  @param[in] nr   number of array elements.
 *  @param[in] nc   number of array elements.
 *  @param[in] sfmt edit descriptor.
 *  @param[in] cdel column delimeter.
 *  @param[in] rdel row delimeter.
 *
 *  Format an array for printing and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
template<class T>
std::string toString  ( T** A, size_t nr, size_t nc,
                        std::string sfmt = DEFAULT_PRINT_FORMAT,
                        std::string cdel = DEFAULT_PRINT_COL_DELIM,
                        std::string rdel = DEFAULT_PRINT_ROW_DELIM ) {
  // -------------------------------------------------------------------------------------
  if (static_cast<T**>(0) == A) throw std::invalid_argument("array is NULL");
  if (0 == nr) throw std::invalid_argument("zero row length array");
  if (0 == nc) throw std::invalid_argument("zero col length array");

  std::string tstr = toString( A[0], nc, sfmt, cdel );

  for ( size_t i=1; i<nr; i++ ) {
    tstr.append( rdel );
    tstr.append( toString( A[i], nc, sfmt, cdel ) );
  }

  return tstr;
}








// =======================================================================================
/** @brief To NumPy String.
 *  @param[in] A    pointer to an array.
 *  @param[in] n    number of array elements.
 *  @param[in] sfmt edit descriptor.
 *
 *  Format an array for us as a numpy array and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
template<class T>
std::string toString_numpy( T* A, size_t n, std::string sfmt = DEFAULT_PRINT_FORMAT ) {
  // -------------------------------------------------------------------------------------
  std::string tstr = "np.array( [ ";
  tstr.append( toString( A, n, sfmt, ", " ) );
  tstr.append( " ] )" );
  return tstr;
}


// =======================================================================================
/** @brief To NumPy String.
 *  @param[in] A    pointer to an array.
 *  @param[in] nr   number of array rows.
 *  @param[in] nc   number of array columns.
 *  @param[in] sfmt edit descriptor.
 *
 *  Format an array for us as a numpy array and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
template<class T>
std::string toString_numpy( T** A, size_t nr, size_t nc,
                            std::string sfmt = DEFAULT_PRINT_FORMAT ) {
  // -------------------------------------------------------------------------------------
  std::string tstr = "np.array( [[ ";
  tstr.append( toString( A, nr, nc, sfmt, ", ", "], [ " ) );
  tstr.append( " ]] )" );
  return tstr;
}


// =======================================================================================
/** @brief To Octave String.
 *  @param[in] A    pointer to an array.
 *  @param[in] n    number of array elements.
 *  @param[in] sfmt edit descriptor.
 *
 *  Format an array for us as an octave array and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
template<class T>
std::string toString_octave( T* A, size_t n, std::string sfmt = DEFAULT_PRINT_FORMAT ) {
  // -------------------------------------------------------------------------------------
  std::string tstr = "[ ";
  tstr.append( toString( A, n, sfmt, ", " ) );
  tstr.append( " ]" );
  return tstr;
}


// =======================================================================================
/** @brief To Octave String.
 *  @param[in] A    pointer to an array.
 *  @param[in] nr   number of array rows.
 *  @param[in] nc   number of array columns.
 *  @param[in] sfmt edit descriptor.
 *
 *  Format an array for us as an octave matrix and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
template<class T>
std::string toString_octave( T** A, size_t nr, size_t nc,
                             std::string sfmt = DEFAULT_PRINT_FORMAT ) {
  // -------------------------------------------------------------------------------------
  std::string tstr = "[ ";
  tstr.append( toString( A, nr, nc, sfmt, ", ", "; " ) );
  tstr.append( " ]" );
  return tstr;
}


// =======================================================================================
/** @brief To Sage String.
 *  @param[in] A    pointer to an array.
 *  @param[in] n    number of array elements.
 *  @param[in] sfmt edit descriptor.
 *
 *  Format an array for us as a sage array and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
template<class T>
std::string toString_sage( T* A, size_t n, std::string sfmt = DEFAULT_PRINT_FORMAT ) {
  // -------------------------------------------------------------------------------------
  std::string tstr = "Matrix( SR, [ ";
  tstr.append( toString( A, n, sfmt, ", " ) );
  tstr.append( " ] )" );
  return tstr;
}


// =======================================================================================
/** @brief To Sage String.
 *  @param[in] A    pointer to an array.
 *  @param[in] nr   number of array rows.
 *  @param[in] nc   number of array columns.
 *  @param[in] sfmt edit descriptor.
 *
 *  Format an array for us as a sage matrix and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
template<class T>
std::string toString_sage( T** A, size_t nr, size_t nc, std::string sfmt = DEFAULT_PRINT_FORMAT ) {
  // -------------------------------------------------------------------------------------
  std::string tstr = "Matrix( SR, [[ ";
  tstr.append( toString( A, nr, nc, sfmt, ", ", "], [ " ) );
  tstr.append( " ]] )" );
  return tstr;
}


#endif


// =======================================================================================
// **                               A R R A Y _ P R I N T                               **
// ======================================================================== END FILE =====
