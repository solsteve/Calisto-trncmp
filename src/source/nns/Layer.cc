// ====================================================================== BEGIN FILE =====
// **                                N N S : : L A Y E R                                **
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
/** @brief  Neural Network Layer.
 *  @file   Layer.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-12.
 *
 *  Provides the methods for a neural network layer.
 */
// =======================================================================================

#include <nns/Layer.hh>

namespace nns {


#define INIT_VAR1(_a) nIn(_a), nOut(_a), nBuf(_a), W_buffer(_a), dW_buffer(_a), \
    W(_a), b(_a), dW(_a), db(_a), z(_a), a(_a), E(_a), d(_a), \
    trans(_a)

TLOGGER_REFERENCE( Layer, logger );




// =======================================================================================
/** @brief Resize.
 *  @param[in] n_in  number of connections/inputs.
 *  @param[in] n_out number of nodes/outputs.
 *
 *  Allocate internal storage.
 */
// ---------------------------------------------------------------------------------------
void Layer::resize( const int32_t n_in, const int32_t n_out ) {
  // -------------------------------------------------------------------------------------
  destroy();
  nIn  = n_in;
  nOut = n_out;
  nBuf = nIn * nOut;

  W_buffer  = new real8_t[ nBuf ];
  dW_buffer = new real8_t[ nBuf ];

  W  = new real8_t*[ nOut ];
  dW = new real8_t*[ nOut ];

  real8_t* P1 =  W_buffer;
  real8_t* P2 = dW_buffer;
  for ( int32_t i=0; i<nOut; i++ ) {
    W[i]  = P1; P1 += nIn;
    dW[i] = P2; P2 += nIn;
  }

  b  = new real8_t[ nOut ];
  db = new real8_t[ nOut ];
  z  = new real8_t[ nOut ];
  a  = new real8_t[ nOut ];
  E  = new real8_t[ nOut ];
  d  = new real8_t[ nOut ];
}


// =======================================================================================
/** @brief Destroy.
 *
 *  Free all internal allocation and reset all pointers to NULL.
 */
// ---------------------------------------------------------------------------------------
void Layer::destroy( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<real8_t**>(0) != W ) {
    for ( int32_t i=0; i<nOut; i++ ) {
      W[i] = static_cast<real8_t*>(0);
    }
    delete[] W;
  }

  if ( static_cast<real8_t**>(0) != dW ) {
    for ( int32_t i=0; i<nOut; i++ ) {
      dW[i] = static_cast<real8_t*>(0);
    }
    delete[] dW;
  }

  if ( static_cast<real8_t*>(0) !=  W_buffer ) { delete[]  W_buffer; }
  if ( static_cast<real8_t*>(0) != dW_buffer ) { delete[] dW_buffer; }

  if ( static_cast<real8_t*>(0) != db ) { delete[] db; }
  if ( static_cast<real8_t*>(0) !=  b ) { delete[]  b; }
  if ( static_cast<real8_t*>(0) !=  z ) { delete[]  z; }
  if ( static_cast<real8_t*>(0) !=  a ) { delete[]  a; }
  if ( static_cast<real8_t*>(0) !=  E ) { delete[]  E; }
  if ( static_cast<real8_t*>(0) !=  d ) { delete[]  d; }

  // -------------------------------------------------------------------------------------

  nIn       = 0;
  nOut      = 0;
  nBuf      = 0;
  W_buffer  = static_cast<real8_t*>(0);
  dW_buffer = static_cast<real8_t*>(0);
  W         = static_cast<real8_t**>(0);
  b         = static_cast<real8_t*>(0);
  dW        = static_cast<real8_t**>(0);
  db        = static_cast<real8_t*>(0);
  z         = static_cast<real8_t*>(0);
  a         = static_cast<real8_t*>(0);
  E         = static_cast<real8_t*>(0);
  d         = static_cast<real8_t*>(0);
}


// =======================================================================================
/** @brief Constructor.
 *
 *  Construct a void layer.
 */
// ---------------------------------------------------------------------------------------
Layer::Layer( void ) : INIT_VAR1(0) {
  // -------------------------------------------------------------------------------------
  setTransfer();
}


// =======================================================================================
/** @briefConstructor.
 *  @param[in] n_in  number of connections/inputs.
 *  @param[in] n_out number of nodes/outputs.
 *
 *  Construct a layer from number of inputs/outputs
 */
// ---------------------------------------------------------------------------------------
Layer::Layer( const int32_t n_in, const int32_t n_out ) : INIT_VAR1(0) {
  // -------------------------------------------------------------------------------------
  resize( n_in, n_out );
  setTransfer();
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] inf reference to an input file stream.
 *
 *  Read meta data and weights from an input stream.
 */
// ---------------------------------------------------------------------------------------
Layer::Layer( std::ifstream& inf ) : INIT_VAR1(0) {
  // -------------------------------------------------------------------------------------
  read( inf );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Layer::~Layer( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}




// =======================================================================================
/** @brief Set Transfer Function.
 *  @param[in] str common name of the transfer function.
 *
 *  Try to set the transfer fucntion for a given name. The default if this procedure
 *  gives up will be the Sigmoid or Logistics equation.
 *
 *  @note possible values are sigmoid, relu, tanh, or gaussian.
 */
// ---------------------------------------------------------------------------------------
void Layer::setTransfer( std::string str ) {
  // -------------------------------------------------------------------------------------
  trans = Transfer::createPtr( str );
}


// =======================================================================================
/** @brief Set Transfer Function.
 *  @param[in] ttype transfer type enum.
 *
 *  Try to set the transfer fucntion using the enum: transfer_e.
 *
 *  @note the valid enums are SIGMOID, RELU, TANH, and GAUSSIN.
 */
// ---------------------------------------------------------------------------------------
void Layer::setTransfer( transfer_e  ttype ) {
  // -------------------------------------------------------------------------------------
  trans = Transfer::createPtr( ttype );
}




// =======================================================================================
/** @brief Read File.
 *  @param[in] inf reference to an input file stream.
 *  @return true if error occured.
 *
 *  Read meta data and weights from an input stream.
 */
// ---------------------------------------------------------------------------------------
bool Layer::read( std::ifstream& inf ) {
  // -------------------------------------------------------------------------------------
  int32_t ni, no;
  real8_t x;
  std::string ttype;
  inf >> ni >> no >> ttype;
  resize( ni, no );
  int32_t idx = 0;
  for ( int32_t i=0; i<nOut; i++ ) {
    inf >> x; b[i] = x;
    for ( int32_t j=0; j<nIn; j++ ) {
      inf >> x; W_buffer[idx++] = x;
    }
  }
  setTransfer( ttype );

  return false;
}


// =======================================================================================
/** @brief Write File.
 *  @param[in] inf reference to an input file stream.
 *  @return true if error occured.
 *
 *
 */
// ---------------------------------------------------------------------------------------
bool Layer::write( std::ofstream& outf, std::string sfmt ) {
  // -------------------------------------------------------------------------------------
  const char* fmt = sfmt.c_str();
  outf << nIn << " " << nOut << " " << trans->name() << "\n";
  int32_t idx = 0;
  for ( int32_t i=0; i<nOut; i++ ) {
    outf << c_fmt( fmt, b[i] ) << " ";
    for ( int32_t j=0; j<nIn; j++ ) {
      outf << " " << c_fmt( fmt, W_buffer[idx++] );
    }
    outf << "\n";
  }

  return false;
}


// =======================================================================================
/** @brief Debug.
 *
 *  Load the weights with values that allow a human to read thier node and connection
 *  indicies.
 */    
// ---------------------------------------------------------------------------------------
void Layer::debug( int32_t i ) {
  // -------------------------------------------------------------------------------------
  real8_t id = ((real8_t) (i+1) ) / 100.0;
  for ( int32_t nod=0; nod<nOut; nod++ ) {
    for ( int32_t con=0; con<nIn; con++ ) {
      (W[nod])[con] = 100.0*((real8_t) (nod+1)) + ((real8_t) (con+1)) + id;
    }
  }
  for ( int32_t nod=0; nod<nOut; nod++ ) {
    b[nod] = ((real8_t) (nod+1)) + id;
  }
}


// =======================================================================================
/** @brief Randomize.
 *  @param[in] dd pointer to a Dice instance.
 *
 *  randomize the weights and bias for this Layer.
 */
// ---------------------------------------------------------------------------------------
void Layer::randomize( Dice* dd ) {
  // -------------------------------------------------------------------------------------
  Dice* rnd = dd;
  if ( static_cast<Dice*>(0) == dd ) {
    rnd = Dice::getInstance();
    rnd->seed_set();
  }
  
  real8_t scl = D_ONE / sqrt( (real8_t) nOut );

  for ( int32_t i=0; i<nBuf; i++ ) {
    W_buffer[i] = scl * rnd->normal();
  }
  for ( int32_t i=0; i<nOut; i++ ) {
    b[i] = scl * rnd->normal();
  }
}


// =======================================================================================
/** @brief Reset.
 *
 *  Reset the delta Weight matrix and the delta bias vector for this Layer.
 */
// ---------------------------------------------------------------------------------------
void Layer::reset( void ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nBuf; i++ ) {
    dW_buffer[i] = D_ZERO;
  }
  for ( int32_t i=0; i<nOut; i++ ) {
    db[i] = D_ZERO;
  }
}


// =======================================================================================
/** @brief Forward.
 *  @param[in]  input  pointer to an input  vector.
 *  @return pointer to the non-lenear activation vector of this Layer.
 *
 *  Process a forward propagation through this Layer.
 */
// ---------------------------------------------------------------------------------------
real8_t* Layer::forward( real8_t* input ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nOut; i++ ) {
    real8_t  sum = b[i];
    real8_t* wgt = W[i];
    for ( int32_t j=0; j<nIn; j++ ) {
      sum += ( input[j] * wgt[j] );
    }
    z[i] = sum;
  }

  for ( int32_t i=0; i<nOut; i++ ) {
    a[i] = trans->activate( z[i] );
  }

  return a;
}


// =======================================================================================
/** @brief Backward.
 *  @param[in]  input  pointer to the input vector.
 *  @param[out] delta  pointer to the error presented to the previous layer.
 *
 *  Perform a back propagation through this Layer. Add to the accumlated deltas for this
 *  layers weights and bias.
 */
// ---------------------------------------------------------------------------------------
void Layer::backward( real8_t* input, real8_t* delta ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nOut; i++ ) {
    E[i] = d[i] * trans->gradient( a[i], z[i] );
  }

  if ( static_cast<real8_t*>(0) != delta ) {
    for ( int32_t i=0; i<nIn; i++ ) {
      real8_t sum = D_ZERO;
      for ( int32_t j=0; j<nOut; j++ ) {
        sum += (E[j] * (W[j])[i]);
      }
      delta[i] = sum;
    }
  }

  int32_t idx = 0;
  for ( int32_t i=0; i<nOut; i++ ) {
    db[i] += E[i];
  }

  idx = 0;
  for ( int32_t i=0; i<nOut; i++ ) {
    const real8_t ee = E[i];
    for ( int32_t j=0; j<nIn; j++ ) {
      dW_buffer[idx++] += (input[j] * ee);
    }
  }
}


// =======================================================================================
/** @brief Update Weights.
 *  @param[in] eta tarinig coefficient.
 *
 *  Apply the deltas for the weights and bias for this Layer.
 */
// ---------------------------------------------------------------------------------------
void Layer::update( const real8_t eta ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nBuf; i++ ) {
    W_buffer[i] -= (eta*dW_buffer[i]);
  }
  for ( int32_t i=0; i<nOut; i++ ) {
    b[i] -= (eta*db[i]);
  }
  reset();
}


}; // end namespace nns


// =======================================================================================
// **                                N N S : : L A Y E R                                **
// ======================================================================== END FILE =====
