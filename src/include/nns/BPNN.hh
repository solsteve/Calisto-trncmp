// ====================================================================== BEGIN FILE =====
// **                                      B P N N                                      **
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
/** @brief  Back Propagation Neural Network.
 *  @file   BPN.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-01.
 *
 *  Provides the interface for a vector implementation of a BLAS enabled
 *  back-propagation neural network.
 */
// =======================================================================================


#ifndef __HH_BPNN_TRNCMP
#define __HH_BPNN_TRNCMP

#include <nns/Layer.hh>

namespace nns {

// =======================================================================================
class BPNN {                                                                       // BPNN
  // -------------------------------------------------------------------------------------
 protected:
  TLOGGER_HEADER( logger );
  EMPTY_PROTOTYPE( BPNN );

  int32_t   nIn;    ///< number of inputs/connections
  int32_t   nOut;   ///< number of outputs/nodes
  int32_t   nLayer; ///< number of layers
  Layer**   L;      ///< list of layers

  void destroy( void );
  
 public:
 
  BPNN( void );
  BPNN( const int32_t n_in, const int32_t  n_hid, const int32_t n_out );
  BPNN( const int32_t n_in, const int32_t* n_hid, const int32_t n );
  BPNN( std::string fspc );
  BPNN( std::ifstream& inf );

  int32_t nInput  ( void ) const { return this->nIn;  };
  int32_t nOutput ( void ) const { return this->nOut; };

  ~BPNN( void );

  void resize ( const int32_t n_in, const int32_t  n_hid, const int32_t n_out );
  void resize ( const int32_t n_in, const int32_t* n_hid, const int32_t n );

  void setTransfer ( const int32_t ln, std::string str );
  void setTransfer ( const int32_t ln, transfer_e  ttype = SIGMOID );

  bool read   ( std::ifstream& inf );
  bool write  ( std::ofstream& outf, std::string sfmt = "%23.16e" );

  bool read   ( std::string fspc );
  bool write  ( std::string fspc, std::string sfmt = "%23.16e" );

  void debug     ( void );
  void randomize ( Dice* dd = static_cast<Dice*>(0) );

  void    reset     ( void );
  real8_t cost      ( real8_t* output, real8_t* test, real8_t* delta, const int32_t n );
  void    execute   ( real8_t* input, real8_t* output );
  real8_t train     ( real8_t* input, real8_t* output, real8_t* test );
  void    update    ( const real8_t eta );

  static real8_t activate( const real8_t x );
  static real8_t derivative( const real8_t a );

}; // end class BPNN


// =======================================================================================
inline void BPNN::setTransfer( const int32_t ln, std::string str ) {
  // -------------------------------------------------------------------------------------
  L[ln]->setTransfer( str );
}

// =======================================================================================
inline void BPNN::setTransfer( const int32_t ln, transfer_e  ttype ) {
  // -------------------------------------------------------------------------------------
  L[ln]->setTransfer( ttype );
}


}; // end namespace nns


#endif 

// =======================================================================================
// **                                      B P N N                                      **
// ======================================================================== END FILE =====
