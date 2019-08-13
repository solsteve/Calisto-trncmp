// ====================================================================== BEGIN FILE =====
// **                                       P C A                                       **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2018-19, Stephen W. Soliday                                        **
// **                         stephen.soliday@trncmp.org                                **
// **                         http://research.trncmp.org                                **
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
/** @brief  Principle Component Analysis.
 *  @file   PCA.hh
 *  @author Stephen W. Soliday
 *  @date   2018-Apr-20 Original release.
 *  @date   2019-Aug-06 Port from Java to C++.
 *  Provides the interface for performing Principle Component Analysis.
 */
// =======================================================================================


#ifndef __HH_PCA_TRNCMP
#define __HH_PCA_TRNCMP

#include <LinAlg.hh>
#include <TLogger.hh>

// =======================================================================================
class PCA {
  // -------------------------------------------------------------------------------------
 protected:
  EMPTY_PROTOTYPE( PCA );

  TLOGGER_HEADER(logger);    ///< Reference to logger instance

  int32_t  num_var;           ///< Number of variables
  Vector   mu;                ///< Sample mean
  Vector   variance;          ///< Principle axis variance
  Matrix   covariance;        ///< Covariance
  Matrix   rotation;          ///< Reverse Transformation matrix
  real8_t* rwork;             ///< Rotation work vector

 public:
  PCA  ( void );
  ~PCA ( void );

  int  fromSamples    ( Table& table );
  int  fromCovariance ( Matrix& cov, Vector& mean );
  int  transform      ( Table&  out, Table&  in );
  int  transform      ( Vector& out, Vector& in );
  int  recover        ( Table&  out, Table&  in );
  int  recover        ( Vector& out, Vector& in );
  void report         ( std::ostream& os, const std::string& sfmt = "%g" );

}; // end class PCA


#endif


// =======================================================================================
// **                                       P C A                                       **
// ======================================================================== END FILE =====

