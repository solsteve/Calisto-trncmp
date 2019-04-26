// ====================================================================== BEGIN FILE =====
// **                                      M A I N                                      **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2019, Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
// **                                                                                   **
// **  -------------------------------------------------------------------------------  **
// **                                                                                   **
// **  This program is free software: you can redistribute it and/or modify it under    **
// **  the terms of the GNU General Public License as published by the Free Software    **
// **  Foundation, either version 3 of the License, or (at your option)                 **
// **  any later version.                                                               **
// **                                                                                   **
// **  This program is distributed in the hope that it will be useful, but WITHOUT      **
// **  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS    **
// **  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.   **
// **                                                                                   **
// **  You should have received a copy of the GNU General Public License along with     **
// **  this program. If not, see <http://www.gnu.org/licenses/>.                        **
// **                                                                                   **
// ----- Modification History ------------------------------------------------------------
//
/** @brief Conversion Application
 *  @file   main.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Apr-11
 *
 *  This is a stub for conversion.
 */
// =======================================================================================


#include <trncmp.hh>
#include <mylocal.hh>
#include <array_print.hh>


// =======================================================================================
/** @brief Entry point.
 *  @return 0 on success non-zero on failure
 *
 *  Main entry point for the conversion stub.
 */
// ---------------------------------------------------------------------------------------
int main( void ) {
  // -------------------------------------------------------------------------------------
  std::cout << trncmpAuthor() << " ILH" << std::endl;
  std::cout << "App version " << APPVER << std::endl;

  real8_t T2[] = { -11.73678219,  20.84680319,   2.51207001, -11.63547989,
                   -10.66277194, -52.54156325, -21.04650316,  50.23840075 };


  size_t n = sizeof(T2)/sizeof(T2[0]);
  
  std::cout << toString( T2, n ) << std::endl;
  std::cout << toString( T2, n, "%.4f" ) << std::endl;
  std::cout << toString( T2, n, "%.3f", "; " ) << std::endl;

  real8_t XX[3][4] = { { -4.16595553, -95.15606213,  10.09049046,  52.30506251},
                       { 89.04153076, -91.95091189, -15.21455717, -80.03042764},
                       { 80.6179393 ,  23.28697296, -71.07057362, -30.39738595} };

  size_t nr = sizeof(XX)/sizeof(XX[0]);
  size_t nc = sizeof(XX[0])/sizeof(XX[0][0]);

  real8_t *T3[nr];

  for ( size_t i=0; i<nr; i++ ) {
    T3[i] = XX[i];
  }

  std::cout << "N Row = " << nr << std::endl;
  std::cout << "N Col = " << nc << std::endl;

  std::cout << toString( T3, nr, nc ) << std::endl << std::endl;
  std::cout << toString( T3, nr, nc, "%7.3f" ) << std::endl << std::endl;
  std::cout << toString( T3, nr, nc, "%7.3f", "," ) << std::endl << std::endl;
  std::cout << toString( T3, nr, nc, "%7.3f", ", ", "; " ) << std::endl << std::endl;

  std::cout << toString( T2, n, "%7.3f", " " ) << std::endl << std::endl;
  std::cout << toString_numpy( T2, n, "%7.3f" ) << std::endl << std::endl;
  std::cout << toString_octave( T2, n, "%7.3f" ) << std::endl << std::endl;
  std::cout << toString_sage( T2, n, "%7.3f" ) << std::endl << std::endl;

  std::cout << toString( T3, nr, nc, "%7.3f", " ", "\n" ) << std::endl << std::endl;
  std::cout << toString_numpy( T3, nr, nc, "%7.3f" ) << std::endl << std::endl;
  std::cout << toString_octave( T3, nr, nc, "%7.3f" ) << std::endl << std::endl;
  std::cout << toString_sage( T3, nr, nc, "%7.3f" ) << std::endl << std::endl;

  return 0;
}


// =======================================================================================
// **                                      M A I N                                      **
// ======================================================================== END FILE =====
