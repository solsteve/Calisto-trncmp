// ====================================================================== BEGIN FILE =====
// **                                  F I L E T O O L                                  **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2014-2019, Stephen W. Soliday                                      **
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
/** @brief  File Tool.
 *  @file   FileTool.hh
 *  @author Stephen W. Soliday
 *  @date   2014-Feb-08 Original release.
 *  @date   2019-May-07 CMake refactorization.
 *
 *  Provides the implementation for a set of file tools.
 */
// =======================================================================================


#ifndef __HH_FILETOOL_TRNCMP
#define __HH_FILETOOL_TRNCMP

#include <trncmp.hh>

namespace FileTool {

bool          dirExists  ( const std::string path );
bool          fileExists ( const std::string path );
std::string   findFile   ( const std::string root, const std::string path = ".:~" );
std::string   timeStamp  ( const bool use_seconds=false );

std::ifstream openRead(  const std::string fspc, int* status=static_cast<int*>(0) );
std::ofstream openWrite( const std::string fspc, int* status=static_cast<int*>(0) );

}; // end namespace FileTool


#endif


// =======================================================================================
// **                                  F I L E T O O L                                  **
// ======================================================================== END FILE =====
