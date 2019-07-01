// ====================================================================== BEGIN FILE =====
// **                             C T E S T _ D R O P O F F                             **
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
/** @brief Test the DropOff class.
 *  @file   ctest_dropoff.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-28
 *
 *  This is a test of the DropOff class.
 */
// =======================================================================================

#include <DropOff.hh>


// =======================================================================================
int main( void ) {
  // -------------------------------------------------------------------------------------
  const real8_t Vo      = 18;
  const real8_t Vf      = 1;
  const size_t  samples = 100;
  
  DropOff A( Vo, Vf, samples, DropOff::LINEAR );
  DropOff B( Vo, Vf, samples, DropOff::EXPONENTIAL );
  DropOff C( Vo, Vf, samples, DropOff::GAUSSIAN );

  std::ofstream ofs( "dropoff.dat" );
  
  for ( size_t i=0; i<samples; i++ ) {
    real8_t a = A.next();
    real8_t b = B.next();
    real8_t c = C.next();
    ofs << i  << "\t"
	<< a  << "\t"
	<< b  << "\t"
	<< c  << "\t"
	<< Vo << "\t"
	<< Vf << "\n";
  }

  ofs.close();

  return 0;
}


// =======================================================================================
// **                             C T E S T _ D R O P O F F                             **
// ======================================================================== END FILE =====
