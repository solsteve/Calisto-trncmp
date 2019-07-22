// ====================================================================== BEGIN FILE =====
// **                                C T E S T _ B L A S                                **
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
/** @brief  Test LAPACK/BLAS ROUTINES
 *  @file   ctest_blas.hh
 *  @author Stephen W. Soliday
 *  @date   2014-01-27  Original release.
 *  @date   2019-Jun-14 CMake refactorization.
 *
 *  Provides the interface for precision time keeping.
 */
// =======================================================================================

#include <Matrix.hh>

// =======================================================================================
void TEST01( void ) {
  // -------------------------------------------------------------------------------------
  real8_t CM[] = { 1.1, 2.1, 3.1,
		   1.2, 2.2, 3.2, 
		   1.3, 2.3, 3.3, 
		   1.4, 2.4, 3.4, 
		   1.5, 2.5, 3.5 };

  MARK;
  Matrix M = Matrix::column_major(3,5,CM);
  MARK;
  std::cout<< toString( M ) << "\n";
  MARK;
}

// =======================================================================================
int main( void ) {
  // -------------------------------------------------------------------------------------
  TEST01();
  return 0;
}


// =======================================================================================
// **                                C T E S T _ B L A S                                **
// ======================================================================== END FILE =====
