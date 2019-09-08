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
 *  @file   BPN.cch
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-01.
 *
 *  Provides the methods for a vector implementation of a BLAS enabled
 *  back-propagation neural network.
 */
// =======================================================================================


#include <BPNN.hh>
#include <FileTool.hh>


TLOGGER_REFERENCE( BPNN, logger );


#define INIT_VAR1(_a) nIn(_a), nOut(_a), nBuf(_a), W_buffer(_a), dW_buffer(_a), \
    W(_a), b(_a), dW(_a), db(_a), z(_a), a(_a), E(_a), d(_a)
#define INIT_VAR2(_a) nIn(_a), nOut(_a), nLayer(_a), L(_a)

void display( real8_t*a, int32_t na ) {
  fprintf( stdout, "%5.2f", a[0] );
  for ( int32_t i=1; i<na; i++ ) { fprintf( stdout, " %5.2f", a[i] ); }
  fprintf( stdout, "\n" );
}

void display( real8_t*a, int32_t na, real8_t*b, int32_t nb ) {
  fprintf( stdout, "%5.2f", a[0] );
  for ( int32_t i=1; i<na; i++ ) { fprintf( stdout, " %5.2f", a[i] ); }
  for ( int32_t i=0; i<nb; i++ ) { fprintf( stdout, " %7.4f", b[i] ); }
  fprintf( stdout, "\n" );
}

void display( real8_t*a, int32_t na, real8_t*b, int32_t nb, real8_t*c, int32_t nc ) {
  fprintf( stdout, "%5.2f", a[0] );
  for ( int32_t i=1; i<na; i++ ) { fprintf( stdout, " %5.2f", a[i] ); }
  for ( int32_t i=0; i<nb; i++ ) { fprintf( stdout, " %7.4f", b[i] ); }
  for ( int32_t i=0; i<nc; i++ ) { fprintf( stdout, " %7.4f", c[i] ); }
  fprintf( stdout, "\n" );
}




// =======================================================================================
/** @brief Resize.
 *  @param[in] n_in  number of connections/inputs.
 *  @param[in] n_out number of nodes/outputs.
 *
 *  Allocate internal storage.
 */
// ---------------------------------------------------------------------------------------
void BPNN::Layer::resize( const int32_t n_in, const int32_t n_out ) {
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
void BPNN::Layer::destroy( void ) {
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
BPNN::Layer::Layer( void ) : INIT_VAR1(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @briefConstructor.
 *  @param[in] n_in  number of connections/inputs.
 *  @param[in] n_out number of nodes/outputs.
 *
 *  Construct a layer from number of inputs/outputs
 */
// ---------------------------------------------------------------------------------------
BPNN::Layer::Layer( const int32_t n_in, const int32_t n_out ) : INIT_VAR1(0) {
  // -------------------------------------------------------------------------------------
  resize( n_in, n_out );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] inf reference to an input file stream.
 *
 *  Read meta data and weights from an input stream.
 */
// ---------------------------------------------------------------------------------------
BPNN::Layer::Layer( std::ifstream& inf ) : INIT_VAR1(0) {
  // -------------------------------------------------------------------------------------
  read( inf );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
BPNN::Layer::~Layer( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}


// =======================================================================================
/** @brief Read File.
 *  @param[in] inf reference to an input file stream.
 *  @return true if error occured.
 *
 *  Read meta data and weights from an input stream.
 */
// ---------------------------------------------------------------------------------------
bool BPNN::Layer::read( std::ifstream& inf ) {
  // -------------------------------------------------------------------------------------
  int32_t ni, no;
  real8_t x;
  inf >> ni >> no;
  resize( ni, no );
  int32_t idx = 0;
  for ( int32_t i=0; i<nOut; i++ ) {
    inf >> x; b[i] = x;
    for ( int32_t j=0; j<nIn; j++ ) {
      inf >> x; W_buffer[idx++] = x;
    }
  }

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
bool BPNN::Layer::write( std::ofstream& outf, std::string sfmt ) {
  // -------------------------------------------------------------------------------------
  const char* fmt = sfmt.c_str();
  outf << nIn << " " << nOut << "\n";
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
// ---------------------------------------------------------------------------------------
void BPNN::Layer::debug( int32_t i ) {
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
// ---------------------------------------------------------------------------------------
void BPNN::Layer::randomize( Dice* dd ) {
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
// ---------------------------------------------------------------------------------------
void BPNN::debug( void ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nLayer; i++ ) {
    L[i]->debug( i );
  }
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void BPNN::randomize( Dice* dd ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nLayer; i++ ) {
    L[i]->randomize( dd );
  }
}













// =======================================================================================
// ---------------------------------------------------------------------------------------
void BPNN::Layer::reset( void ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nBuf; i++ ) {
    dW_buffer[i] = D_ZERO;
  }
  for ( int32_t i=0; i<nOut; i++ ) {
    db[i] = D_ZERO;
  }
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t* BPNN::Layer::forward( real8_t* input ) {
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
    a[i] = BPNN::activate( z[i] );
  }

  return a;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void BPNN::Layer::backward( real8_t* input, real8_t* delta ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nOut; i++ ) {
    E[i] = d[i] * BPNN::derivative( a[i] );
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
// ---------------------------------------------------------------------------------------
void BPNN::Layer::update( const real8_t eta ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nBuf; i++ ) {
    W_buffer[i] -= (eta*dW_buffer[i]);
  }
  for ( int32_t i=0; i<nOut; i++ ) {
    b[i] -= (eta*db[i]);
  }
  reset();
}






// =======================================================================================
// ---------------------------------------------------------------------------------------
void BPNN::reset( void ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nLayer; i++ ) {
    L[i]->reset();
  }
}

// =======================================================================================
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
// ---------------------------------------------------------------------------------------
real8_t BPNN::cost( real8_t* output, real8_t* test, real8_t* delta, const int32_t n ) {
  // -------------------------------------------------------------------------------------
  real8_t mse = D_ZERO;
  for ( int32_t i=0; i<n; i++ ) {
    const real8_t diff = output[i] - test[i];
    delta[i] = diff;
    mse += (diff*diff);
  }
  return mse;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t BPNN::train( real8_t* input, real8_t* output, real8_t* test ) {
  // -------------------------------------------------------------------------------------
  execute( input, output );
  real8_t mse = cost( output, test, L[nLayer-1]->d, nOut );
  for ( int32_t i=nLayer-1; 0<i; i-- ) {
    L[i]->backward( L[i-1]->a, L[i-1]->d );
  }
  L[0]->backward( input );

  return mse;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
void BPNN::update( const real8_t eta ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<nLayer; i++ ) {
    L[i]->update(eta);
  }
}


// =======================================================================================
// **                                      B P N N                                      **
// ======================================================================== END FILE =====
