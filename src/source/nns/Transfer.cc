













// ====================================================================== BEGIN FILE =====
// **                             N N S : : T R A N S F E R                             **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2011-2019, Stephen W. Soliday                                      **
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
/** @brief  Tarnsfer Functions.
 *  @file   nns/Transfer.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-12.
 *
 *  Provides the methods for basic transfer functions.
 */
// =======================================================================================


#include <nns/Transfer.hh>


namespace nns {


// =======================================================================================
Transfer* Transfer::createPtr( transfer_e  ttype ) {
  // -------------------------------------------------------------------------------------
  switch( ttype ) {
    case RELU:     return new ReLU();
    case TANH:     return new TanH();
    case GAUSSIAN: return new Sigmoid();
    case SIGMOID:
    default:
      break;
  }
  return new Sigmoid();
}






// =======================================================================================
Transfer* Transfer::createPtr( std::string str ) {
  // -------------------------------------------------------------------------------------
  const char test = str[0];
  if ( 'R' == test ) { return createPtr( RELU ); }
  if ( 'r' == test ) { return createPtr( RELU ); }
  
  if ( 'T' == test ) { return createPtr( TANH ); }
  if ( 't' == test ) { return createPtr( TANH ); }
  
  if ( 'G' == test ) { return createPtr( GAUSSIAN ); }
  if ( 'g' == test ) { return createPtr( GAUSSIAN ); }
  
  // ----- default -------------------------------------
  return createPtr( SIGMOID );
}


}; // end namespace nns


// =======================================================================================
// **                                N N S : : L A Y E R                                **
// ======================================================================== END FILE =====
