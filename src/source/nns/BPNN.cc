// ====================================================================== BEGIN FILE =====
// **                                 N N S : : B P N N                                 **
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
 *  @file   BPN.cch
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-01.
 *
 *  Provides the methods for a vector implementation of a BLAS enabled
 *  back-propagation neural network.
 */
// =======================================================================================


#include <nns/BPNN.hh>
#include <FileTool.hh>


namespace nns {


TLOGGER_REFERENCE( BPNN, logger );


#define INIT_VAR2(_a) nIn(_a), nOut(_a), nLayer(_a), L(_a)


// =======================================================================================
/** @brief Resize.
 *  @param[in] n_in  number of inputs.
 *  @param[in] n_hid list of node count per layer.
 *  @param[in] n     number of layers.
 */
// ---------------------------------------------------------------------------------------
void BPNN::resize( const int32_t  n_in,
                   const int32_t* n_hid, const int32_t n ) {
  // -------------------------------------------------------------------------------------
  destroy();
  nIn    = n_in;
  nOut   = n_hid[n-1];
  nLayer = n;
  L = new Layer*[n];
  L[0] = new Layer( nIn, n_hid[0] );
  for ( int32_t i=1; i<n; i++ ) {
    L[i] = new Layer( n_hid[i-1], n_hid[i] );
  }
}


// =======================================================================================
/** @brief Destroy.
 *
 *  Free all internal allocation and reset all pointers to NULL.
 */
// ---------------------------------------------------------------------------------------
void BPNN::destroy( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<Layer**>(0) != L ) {
    for ( int32_t i=0; i<nLayer; i++ ) {
      if ( static_cast<Layer*>(0) != L[i] ) {
        delete L[i];
      }
      L[i] = static_cast<Layer*>(0);
    }
    delete[] L;
  }
  nIn    = 0;
  nOut   = 0;
  nLayer = 0;
  L      = static_cast<Layer**>(0);
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
BPNN::BPNN( void ) : INIT_VAR2(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] n_in  number of inputs.
 *  @param[in] n_hid number of hiddin layer nodes.
 *  @param[in] n_out number of outputs.
 *
 *  Create a three layer (two weight matricies) NN.
 */
// ---------------------------------------------------------------------------------------
BPNN::BPNN( const int32_t n_in, const int32_t n_hid, const int32_t n_out ) : INIT_VAR2(0) {
  // -------------------------------------------------------------------------------------
  resize( n_in, n_hid, n_out );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] n_in  number of inputs.
 *  @param[in] n_hid list of node count per layer.
 *  @param[in] n     number of layers.
 */
// ---------------------------------------------------------------------------------------
BPNN::BPNN( const int32_t n_in, const int32_t* n_hid, const int32_t n ) : INIT_VAR2(0) {
  // -------------------------------------------------------------------------------------
  resize( n_in, n_hid, n );
}


// =======================================================================================
/** @brief Constructor
 *  @param[in] inf reference to an input stream.
 */
// ---------------------------------------------------------------------------------------
BPNN::BPNN( std::ifstream& inf ) : INIT_VAR2(0) {
  // -------------------------------------------------------------------------------------
  read( inf );
}


// =======================================================================================
/** @brief Constructor
 *  @param[in] fspc full path to a configuration file.
 */
// ---------------------------------------------------------------------------------------
BPNN::BPNN( std::string fspc ) : INIT_VAR2(0) {
  // -------------------------------------------------------------------------------------
  read( fspc );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
BPNN::~BPNN( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Resize.
 *  @param[in] n_in  number of inputs.
 *  @param[in] n_hid number of hiddin layer nodes.
 *  @param[in] n_out number of outputs.
 *
 *  Create a three layer (two weight matricies) NN.
 */
// ---------------------------------------------------------------------------------------
void BPNN::resize( const int32_t n_in, const int32_t n_hid, const int32_t n_out ) {
  // -------------------------------------------------------------------------------------
  int32_t temp[2] = { n_hid, n_out };
  resize( n_in, temp, 2 );
}


// =======================================================================================
/** @brief Read from Stream.
 *  @param[in] inf reference to an input stream.
 *  @return true if an error occured.
 *
 *  Read the configuration for this network from a file stream.
 */
// ---------------------------------------------------------------------------------------
bool BPNN::read( std::ifstream& inf ) {
  // -------------------------------------------------------------------------------------
  destroy();
  int32_t ni, nl;
  inf >> ni >> nl;
  nIn    = ni;
  nLayer = nl;
  L = new Layer*[nLayer];
  for ( int32_t i=0; i<nl; i++ ) {
    L[i] = new Layer( inf );
  }
  nOut = L[nl-1]->nOut;

  return false;
}


// =======================================================================================
/** @brief Write to Stream.
 *  @param[in] outf reference to an output stream.
 *  @return true if an error occured.
 *
 *  Write the configuration for this network to a file stream.
 *  First line contains the number of inputs and the number of layers.
 *  Each following line is defined in BPNN::Layer::write
 */
// ---------------------------------------------------------------------------------------
bool BPNN::write( std::ofstream& outf, std::string sfmt ) {
  // -------------------------------------------------------------------------------------
  outf << nIn << " " << nLayer << "\n";
  for ( int32_t i=0; i<nLayer; i++ ) {
    L[i]->write( outf, sfmt );
  }

  return false;
}


// =======================================================================================
/** @brief Read from File.
 *  @param[in] fspc full path to a BPNN config file.
 *  @return true if an error occured.
 *
 *  Read the configuration for this network from a file.
 */
// ---------------------------------------------------------------------------------------
bool BPNN::read( std::string fspc ) {
  // -------------------------------------------------------------------------------------
  int istat;
  std::ifstream inf = FileTool::openRead( fspc, &istat );

  if ( 0 != istat ) {
    logger->error( "Cannot open %s for reading." );
    return true;
  }

  bool rv = read( inf );
  
  inf.close();
  return rv;
}


// =======================================================================================
/** @brief Write to File.
 *  @param[in] fspc full path to a BPNN config file.
 *  @return true if an error occured.
 *
 *  Write the configuration for this network to a file.
 *  First line contains the number of inputs and the number of layers.
 *  Each following line is defined in BPNN::Layer::write
 */
// ---------------------------------------------------------------------------------------
bool BPNN::write( std::string fspc, std::string sfmt ) {
  // -------------------------------------------------------------------------------------
  int istat;
  std::ofstream outf = FileTool::openWrite( fspc, &istat );

  if ( 0 != istat ) {
    logger->error( "Cannot open %s for writing." );
    return true;
  }

  
  bool rv = write( outf, sfmt );
  
  outf.close();
  return rv;
}


// =======================================================================================
/** @brief Debug.
 *
 *  Load the weights with values that allow a human to read thier node and connection
 *  indicies.
 */
// ---------------------------------------------------------------------------------------
void BPNN::debug( void ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nLayer; i++ ) {
    L[i]->debug( i );
  }
}


// =======================================================================================
/** @brief Randomize.
 *  @param[in] dd pointer to a Dice instance.
 *
 *  Randomize each layer in this BPNN.
 */
// ---------------------------------------------------------------------------------------
void BPNN::randomize( Dice* dd ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nLayer; i++ ) {
    L[i]->randomize( dd );
  }
}


// =======================================================================================
/** @brief Reset.
 *
 *  Reset each layer in this BPNN.
 */
// ---------------------------------------------------------------------------------------
void BPNN::reset( void ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nLayer; i++ ) {
    L[i]->reset();
  }
}

// =======================================================================================
/** @brief Execute.
 *  @param[in]  input  pointer to an input  vector.
 *  @param[out] output pointer to an output vector.
 *
 *  Process an input vector in feed froward direction to produce and output vector.
 */
// ---------------------------------------------------------------------------------------
void BPNN::execute( real8_t* input, real8_t* output ) {
  // -------------------------------------------------------------------------------------
  L[0]->forward( input );
  for ( int32_t i=1; i<nLayer; i++ ) {
    L[i]->forward( L[i-1]->a );
  }
  copy( output, L[nLayer-1]->a, nOut );
}


// =======================================================================================
/** @brief Cost Function.
 *  @param[in]  output pointer to the desired output.
 *  @param[in]  test   pointer to the actual output.
 *  @param[out] delta  pointer the the output deltas
 *  @param[in]  n      number of elements in the output vector.
 *  @return mean of the square of the deltas.
 *
 *  Implement the basic cost function.
 */
// ---------------------------------------------------------------------------------------
real8_t BPNN::cost( real8_t* output, real8_t* desired, real8_t* delta, const int32_t n ) {
  // -------------------------------------------------------------------------------------
  real8_t mse = D_ZERO;
  for ( int32_t i=0; i<n; i++ ) {
    const real8_t diff = output[i] - desired[i];
    delta[i] = diff;
    mse += (diff*diff);
  }
  return mse;
}


// =======================================================================================
/** @brief Train.
 *  @param[in]  input   pointer to the input vector.
 *  @param[out] output  pointer to the actual network output.
 *  @param[in]  desired pointer to the desired output vector.
 *  @return mean square difference between the actual and desired outputs.
 *
 *  Process a backwards step, begining with the evaluation of the cost function.
 *  Each iteration of this fucntion will accumulate a delta weight matrix.
 *  These deltas are zeroed by a call to reset() or update().
 */ 
// ---------------------------------------------------------------------------------------
real8_t BPNN::train( real8_t* input, real8_t* output, real8_t* desired ) {
  // -------------------------------------------------------------------------------------
  execute( input, output );
  real8_t mse = cost( output, desired, L[nLayer-1]->d, nOut );
  for ( int32_t i=nLayer-1; 0<i; i-- ) {
    L[i]->backward( L[i-1]->a, L[i-1]->d );
  }
  L[0]->backward( input );

  return mse;
}


// =======================================================================================
/** @brief Update Weights.
 *  @param[in] eta tarinig coefficient.
 *
 *  Apply the deltas for the weights and bias for each Layer.
 */
// ---------------------------------------------------------------------------------------
void BPNN::update( const real8_t eta ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nLayer; i++ ) {
    L[i]->update(eta);
  }
}


}; // end namespace nns


// =======================================================================================
// **                                 N N S : : B P N N                                 **
// ======================================================================== END FILE =====
