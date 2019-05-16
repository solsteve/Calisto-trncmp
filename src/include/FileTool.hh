// ====================================================================== BEGIN FILE =====
// **                                  F I L E T O O L                                  **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2013, 2019  Stephen W. Soliday                                     **
// **                            stephen.soliday@trncmp.org                             **
// **                            http://research.trncmp.org                             **
// **                                                                                   **
// **  -------------------------------------------------------------------------------  **
// **                                                                                   **
// **  This file, and associated source code, is not free software; you may not         **
// **  redistribute it and/or modify it. This library is currently in an on going       **
// **  development phase by its author and has, as yet, not been publicly distributed.  **
// **  Development of this library has been at the sole cost in both time and funding   **
// **  by its author. Until such a public release is made the author retains ALL RIGHTS **
// **  to this software. It is expected that if and when this library is deemed         **
// **  releasable it will be released under the GNU Public license for non-commercial   **
// **  use or with a restricted rights for government use. At that time each source     **
// **  file will contain either/both the standard GPL statement/disclaimer, and/or the  **
// **  DFARS Restricted Rights Legend.                                                  **
// **                                                                                   **
// **  This library exists at the present time WITHOUT ANY WARRANTY; without even the   **
// **  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.         **
// **  As you are not supposed to be in possession of this file if you use it,          **
// **  you use this code AT YOUR OWN RISK.                                              **
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
