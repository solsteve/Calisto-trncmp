// ====================================================================== BEGIN FILE =====
// **                              C T E S T _ S T R E A M                              **
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
/** @brief Test the Stream functions.
 *  @file   ctest_stream.cc
 *  @author Stephen W. Soliday
 *  @date   2019-May-06
 *
 *  This is a test of formating in streams.
 */
// =======================================================================================


#include <trncmp.hh>
#include <string.h>
#include <StringTool.hh>
#include <array_print.hh>


// =======================================================================================
// ---------------------------------------------------------------------------------------
void TEST01( void ) {
  // -------------------------------------------------------------------------------------

  real8_t E = exp(1.0e0) * 10.0;
  real8_t P = -acos(-1.0e0) * 100.0;

  std::cout << "[" << c_fmt("%11.4e", E) << "]" << std::endl;
  std::cout << "[" << c_fmt("%11.6f", P) << "]" << std::endl;

  std::cout << "[" << c_fmt("%13.6e", E) << "] [" << c_fmt("%9.4f", P) << "]" << std::endl;

  char buffer[32];

  strcpy( buffer, "Heather" );

  std::string A( buffer );

  strcpy( buffer, "Cassiopeia" );
  
  std::string B( buffer );

  std::cout << "buf: [" << buffer << "]" << std::endl;
  std::cout << "A:   [" << A << "]" << std::endl;
  std::cout << "B:   [" << B << "]" << std::endl;

  std::cout << "PI = " << StringTool::toString( P ) << std::endl;
  std::cout << "PI = " << StringTool::toString( P, "%11.6f" ) << std::endl;

  std::string S( "12.36" );

  try {
    real8_t x = StringTool::asReal8( S );

    std::cout << "[" << S << "] = " << x << std::endl;

    std::cout << StringTool::asInt64( "123456" ) << std::endl;
    std::cout << StringTool::asInt64( "FC234d12", 16 ) << std::endl;

    
  } catch ( std::invalid_argument& e ) {
    std::cerr << e.what() << std::endl;
  }

#define SPACE(a) std::cout << #a << " = " << sizeof(a) << std::endl;

  SPACE(int8_t);
  SPACE(int16_t);
  SPACE(int32_t);
  SPACE(int64_t);

  SPACE(ssize_t);
  SPACE(size_t);

  SPACE(bool);

  SPACE(char);
  SPACE(short int);
  SPACE(int);
  SPACE(long int);
  SPACE(long long int);

  SPACE(unsigned char);
  SPACE(unsigned short int);
  SPACE(unsigned int);
  SPACE(unsigned long int);
  SPACE(unsigned long long int);
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t LABEL( int32_t i, int32_t r, int32_t c ) {
  // -------------------------------------------------------------------------------------
  real8_t idx = static_cast<real8_t>(i+1) / 100.0;
  real8_t row = static_cast<real8_t>(r) * 100.0;
  real8_t col = static_cast<real8_t>(c);

  return row + col + idx;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void TEST02( void ) {
  // -------------------------------------------------------------------------------------
  const int32_t NR = 4;
  const int32_t NC = 4;
  const int32_t NB = NR*NC;


  // ----- row-major ----------------------------------------
  real8_t rowmaj[NB];
  int32_t idx = 0;
  for ( int32_t r=1; r<=NR; r++ ) {
    for ( int32_t c=1; c<=NC; c++ ) {
      rowmaj[idx] = LABEL( idx, r, c );
      idx++;
    }
  }

  // ----- row-major ----------------------------------------
  real8_t colmaj[NB];
  idx = 0;
  for ( int32_t c=1; c<=NC; c++ ) {
    for ( int32_t r=1; r<=NR; r++ ) {
      colmaj[idx] = LABEL( idx, r, c );
      idx++;
    }
  }

  real8_t RR[NB];
  real8_t CC[NB];

  toRow(    RR, colmaj, NR, NC );
  toColumn( CC, rowmaj, NR, NC );
  
  std::cout << "R = " << toString( rowmaj, NB, "%07.2f" ) << "\n"
            << "C = " << toString( colmaj, NB, "%07.2f" ) << "\n\n";

  std::cout << "row-major\n" << toStringRowMajor(    rowmaj, NR, NC, "%07.2f" ) << "\n\n"
            << "col-major\n" << toStringColumnMajor( colmaj, NR, NC, "%07.2f" ) << "\n\n";
  
  std::cout << "row-major\n" << toStringRowMajor(    RR, NR, NC, "%07.2f" ) << "\n\n"
            << "col-major\n" << toStringColumnMajor( CC, NR, NC, "%07.2f" ) << "\n\n";

  std::cout << "R = " << toString( RR, NB, "%07.2f" ) << "\n"
            << "C = " << toString( CC, NB, "%07.2f" ) << "\n\n";

}


  // =======================================================================================
// ---------------------------------------------------------------------------------------
int main( void ) {
  // -------------------------------------------------------------------------------------
  TEST02();
}


// =======================================================================================
// **                              C T E S T _ S T R E A M                              **
// ======================================================================== END FILE =====
