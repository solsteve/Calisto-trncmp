// ====================================================================== BEGIN FILE =====
// **                                  F I L E T O O L                                  **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2014, 2019  Stephen W. Soliday                                     **
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


#include <FileTool.hh>
#include <sys/stat.h>

namespace FileTool {

// =======================================================================================
/** @brief Directory Exists.
 *  @param path full path to a directory to test.
 *  @return true if the directory exists.
 *
 *  Use a file system call to test the existance of the path to a directory.
 */
// ---------------------------------------------------------------------------------------
bool dirExists( const std::string path ) {
  // -------------------------------------------------------------------------------------
  struct stat path_stat;

  if (0 == ::stat(path.c_str(), &path_stat)) {
    if S_ISDIR(path_stat.st_mode) {
        return true;
      }
  }

  return false;
}


// =======================================================================================
/** @brief File Exists.
 *  @param path full path to a file to test.
 *  @return true if the file exists.
 *
 *  Use a file system call to test the existance of the path to a file.
 */
// ---------------------------------------------------------------------------------------
bool fileExists( const std::string path ) {
  // -------------------------------------------------------------------------------------
  struct stat path_stat;

  if (0 == ::stat(path.c_str(), &path_stat)) {
    if S_ISREG(path_stat.st_mode) {
        return true;
      }
  }

  return false;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
std::string findFile( const std::string root, const std::string path ) {
  // -------------------------------------------------------------------------------------
  return std::string( "Not Yet" );
  /*
    StringTool::Splitter SP( path, ':' );

    size_t n = SP.size();

    for (size_t i=0; i<n; i++) {
      std::string test = SP[i] + "/" + name;
      if ( true == fileExists( test ) ) {
	return test;
      }
    }

    return "";
  */
}


// =======================================================================================
  /** @brief Timestamp.
   *  @param use_seconds flag to include seconds in the time stamp.
   *  @return pointer to a character array containing the formated time stamp..
   *
   *  Generate a formated time stamp. YYYYMMDD-hhmmss Use the buffer provided.
   *  If the pointer to the buffer is null reuse the static allocation.
   */
// ---------------------------------------------------------------------------------------
std::string timeStamp( const bool use_seconds ) {
  // -------------------------------------------------------------------------------------
  char      buffer[32];
  time_t    raw;
  struct tm temp;

  time( &raw );
  gmtime_r( &raw, &temp );

  if ( use_seconds ) {
    snprintf( buffer, 32,
             "%02d%02d%02d-%02d%02d%02d",
             (temp.tm_year+1900)%100, temp.tm_mon+1, temp.tm_mday,
             temp.tm_hour, temp.tm_min, temp.tm_sec );
  } else {
    snprintf( buffer, 32,
             "%02d%02d%02d-%02d%02d",
             (temp.tm_year+1900)%100, temp.tm_mon+1, temp.tm_mday,
             temp.tm_hour, temp.tm_min );
  }
  
  return std::string( buffer );
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
std::ifstream openRead( const std::string fspc, int* status ) {
  // -------------------------------------------------------------------------------------
  int           ierr = 0;
  std::ifstream ifs  = std::ifstream( fspc );
  if ( ! ifs ) {
    ierr = 1;
    if ( static_cast<int*>(0) == status ) {
      std::cerr << "Cannot open file " << fspc << " for reading." << std::endl;
    }
  }

  if ( static_cast<int*>(0) != status ) {
    *status = ierr;
  }
  
  return ifs;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
std::ofstream openWrite( const std::string fspc, int* status ) {
  // -------------------------------------------------------------------------------------
  int           ierr = 0;
  std::ofstream ofs  = std::ofstream( fspc );
  if ( ! ofs ) {
    ierr = 1;
    if ( static_cast<int*>(0) == status ) {
      std::cerr << "Cannot open file " << fspc << " for writing." << std::endl;
    }
  }
  
  if ( static_cast<int*>(0) != status ) {
    *status = ierr;
  }
    
  return ofs;
}


}; // end namespace FileTool


// =======================================================================================
// **                                  F I L E T O O L                                  **
// ======================================================================== END FILE =====
