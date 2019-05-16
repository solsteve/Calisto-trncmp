// ====================================================================== BEGIN FILE =====
// **                              C T E S T _ S T R E A M                              **
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
/** @brief Test the Version
 *  @file   ctest_version.cc
 *  @author Stephen W. Soliday
 *  @date   2019-May-06
 *
 *  This is a test of formating in streams.
 */
// =======================================================================================


#include <trncmp.hh>
#include <string.h>
#include <StringTool.hh>


// =======================================================================================
// ---------------------------------------------------------------------------------------
int main( void ) {
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






  
  return 0;
}



// =======================================================================================
// **                              C T E S T _ S T R E A M                              **
// ======================================================================== END FILE =====
