// ====================================================================== BEGIN FILE =====
// **                                N N S : : L A Y E R                                **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2011-2020, Stephen W. Soliday                                      **
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
/** @brief  Feed Forward Neural Network Layers.
 *  @file   layer.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Jul-18.
 *
 *  Provides the methods for a vector implementation of a BLAS enabled
 *  back-propagation neural network layer.
 */
// =======================================================================================


#include <nns/layer.hh>
#include <Dice.hh>


namespace nns {

#define DEFAULT_BATCH_SIZE  256


#define INIT_VAR1(_a) num_con(_a), num_nod(_a), max_batch(DEFAULT_BATCH_SIZE), \
    act_name("Sigma")

#define INIT_VAR2(_a) num_con(_a), num_nod(_a), num_bat(DEFAULT_BATCH_SIZE),   \
    W(_a), b(_a), dW(_a), db(_a), Z(_a), a(_a), d(_a), E(_a), act_name("None"), G(_a), Gp(_a)


// =======================================================================================
/** @brief Allocate 2D array.
 *  @param[in] n_row number of rows.
 *  @param[in] n_col number of columns.
 *  @return pointer to the first row.
 *
 *  Create an allocation for a 2D array. The buffer will be stored at the first row
 *  address A[0]. Each row pointer will point to an offset into this buffer every n_col.
 */
// ---------------------------------------------------------------------------------------
real8_t** new_2D( size_t n_row, size_t n_col ) {
  // -------------------------------------------------------------------------------------
  real8_t*  buffer = new real8_t[ n_row * n_col ];
  real8_t** rows   = new real8_t*[ n_row ];
  real8_t*  P      = buffer;
  for (size_t i=0; i<n_row; i++) {
    rows[i] = P;
    P += n_col;
  }
  return rows;
}


// =======================================================================================
/** @brief Deallocate 2D array.
 *  @param[in] array pointer to the first row of the array.
 *
 *  Deallocate the buffer used for this 2D array.
 */
// ---------------------------------------------------------------------------------------
void del_2D( real8_t** array ) {
  // -------------------------------------------------------------------------------------
  real8_t* buffer = array[0];
  array[0] = static_cast<real8_t*>(0);
  delete array;
  delete buffer;
}








// =======================================================================================
/** @brief Builder's void constructor.
 *
 *  Initialize the configuration variables.
 */
// ---------------------------------------------------------------------------------------
Layer::Builder::Builder( void ) : INIT_VAR1(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Builder's void deconstructor.
 */
// ---------------------------------------------------------------------------------------
Layer::Builder::~Builder( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Build a layer from file.
 */
// ---------------------------------------------------------------------------------------
Layer* Layer::Builder::build( std::ifstream& inf ) {
  // -------------------------------------------------------------------------------------
  Layer* L = new Layer();
  L->read( inf );
  return L;
}


// =======================================================================================
/** @brief Build a layer from file.
 */
// ---------------------------------------------------------------------------------------
Layer* Layer::Builder::build( void ) {
  // -------------------------------------------------------------------------------------
  Layer* L = new Layer();
  L->resize( num_con, num_nod, max_batch );
  L->set_activate( act_name );
  return L;
}








// =======================================================================================
/** @brief Layer's void constructor.
 *
 *  Initialize the configuration variables.
 */
// ---------------------------------------------------------------------------------------
Layer::Layer( void ) : INIT_VAR2(0) {
  // -------------------------------------------------------------------------------------
}

// =======================================================================================
/** @brief Layers's void deconstructor.
 */
// ---------------------------------------------------------------------------------------
Layer::~Layer( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}


// =======================================================================================
/** @brief Destroy.
 *
 *  Free all allocation for this Layer.
 */
// ---------------------------------------------------------------------------------------
void Layer::destroy( void ) {
  // -------------------------------------------------------------------------------------
  if ( 0 < num_nod ) {
    del_2D(  W );
    del_2D( dW );
    del_2D(  Z );
    del_2D(  a );
    del_2D(  E );
    del_2D(  d );
            
    delete  b;
    delete db;
  }

  W  = static_cast<real8_t**>(0);
  dW = static_cast<real8_t**>(0);
  Z  = static_cast<real8_t**>(0);
  a  = static_cast<real8_t**>(0);
  d  = static_cast<real8_t**>(0);
  E  = static_cast<real8_t**>(0);

  b  = static_cast<real8_t*>(0);
  db = static_cast<real8_t*>(0);

  num_con = 0;
  num_nod = 0;
  num_bat = 0;

  act_name = "None";
  G  = static_cast<activate_t>(0);
  Gp = static_cast<activate_gradient_t>(0);
}


// =======================================================================================
/** @brief resize.
 *  @param[in] n_con
 *  @param[in] n_nod
 *  @param[in] m_bat
 *
 *  Create allocation for this Layer.
 */
// ---------------------------------------------------------------------------------------
void Layer::resize( size_t n_con, size_t n_nod, size_t m_bat ) {
  // -------------------------------------------------------------------------------------
  if ( ( m_bat  > num_bat ) ||
       ( n_con != num_con ) ||
       ( n_nod != num_nod ) ) {
    destroy();

    num_con = n_con;
    num_nod = n_nod;
    num_bat = m_bat;
    
    W  = new_2D( n_con, n_nod );
    b  = new real8_t[   n_nod ];
    dW = new_2D( n_con, n_nod );
    db = new real8_t[   n_nod ];
    Z  = new_2D( m_bat, n_nod );
    a  = new_2D( m_bat, n_nod );
    E  = new_2D( m_bat, n_nod );
    d  = new_2D( m_bat, n_con );
  }

}


// =======================================================================================
/** @brief Initialize Weights.
 *  @param[in] debug initalize with row and column index
 *
 *  Initialize weights with Xavier initialization. Bias are set to zero.
 *  If debug is true, weights are set to 100*row + col/100
 */
// ---------------------------------------------------------------------------------------
void Layer::initialize( bool debug ) {
  // -------------------------------------------------------------------------------------
  if ( debug ) {
    //std::cerr << "Initialize: DEBUG\n";
    for ( size_t n=0; n<num_nod; n++ ) {
      real8_t fn = static_cast<real8_t>(n+1);
      b[n] = fn;
      for ( size_t c=0; c<num_con; c++ ) {
        real8_t fc = static_cast<real8_t>(c+1);
        W[c][n] = (fc*100.0) + (fn/100.0);
      }
    }
  } else {
    //std::cerr << "Initialize: Xavier\n";
    Dice* dd = Dice::getInstance();
    real8_t scale = sqrt( 6.0e0 / static_cast<real8_t>( num_con * num_nod ) );

    for ( size_t c=0; c<num_con; c++ ) {
      for ( size_t n=0; n<num_nod; n++ ) {
        W[c][n] = scale * dd->normal();
      }
    }

    for ( size_t n=0; n<num_nod; n++ ) {
      b[n] = D_ZERO;
    }
  }
}


// =======================================================================================
/** @brief Set Activation Function.
 *  @param[in] name name of the activation function. @see nns::Activate
 *
 *  Use a name to set both activation and gradient.
 */
// ---------------------------------------------------------------------------------------
void Layer::set_activate( std::string name ) {
  // -------------------------------------------------------------------------------------
  act_name = name;
  G        = getActivation( act_name );
  Gp       = getActivationGradient( act_name );
}


// =======================================================================================
/** @brief Reset Weight Deltas.
 *
 *  Reset all weight and bias deltas to zero.
 */
// ---------------------------------------------------------------------------------------
void Layer::reset( void ) {
  // -------------------------------------------------------------------------------------
  for ( size_t c=0; c<num_con; c++ ) {
    for ( size_t n=0; n<num_nod; n++ ) {
      dW[c][n] = D_ZERO;
    }
  }
  for ( size_t n=0; n<num_nod; n++ ) {
    db[n] = D_ZERO;
  }
}


// =======================================================================================
/** @brief
 *  @param[in]
 *
 *  
 */
// ---------------------------------------------------------------------------------------
void Layer::forward( real8_t** input, size_t bs ) {
  // -------------------------------------------------------------------------------------
  for ( size_t bat=0; bat<bs; bat++ ) { // loop over batch

    for ( size_t n=0; n<num_nod; n++ ) { // loop over nodes
      real8_t sum = b[n];
      for ( size_t c=0; c<num_con; c++ ) { // loop over connections
        sum +=  ( input[bat][c] * W[c][n] );
      } // end
      Z[bat][n] = sum;
    } // end node
  } // end batch
}


// =======================================================================================
/** @brief
 *  @param[in]
 *
 *  
 */
// ---------------------------------------------------------------------------------------
void Layer::backward( real8_t** previous, real8_t** delta, size_t bs ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Update Weights.
 *  @param[in] alpha training constant.
 *
 *  Use the deltas to update both the weights and bias. Reset the deltas to zero.
 */
// ---------------------------------------------------------------------------------------
void Layer::update( real8_t alpha ) {
  // -------------------------------------------------------------------------------------
  for ( size_t c=0; c<num_con; c++ ) {
    for ( size_t n=0; n<num_nod; n++ ) {
      W[c][n] += ( alpha * dW[c][n] );
      dW[c][n] = D_ZERO;
    }
  }
  
  for ( size_t n=0; n<num_nod; n++ ) {
    b[n] += ( alpha * db[n] );
    db[n] = D_ZERO;
  }
}


// =======================================================================================
/** @brief Store Weights
 *  @param[out] dst pointer to the destination location to store the weights.
 *  @return pointer to the next location in the buffer.
 *  
 *  Store the weights and bias in a location pointed to by dst. (con+1)*nod elements
 *  of the buffer will be used. Where con=number of connections and nod=number of nodes in
 *  this layer.
 *
 *  Storage is arranged as follows: the first element is the bias for the first node.
 *  This is followed by the connection weights for that node. Then the bias for the
 *  second node and its connection weights. The pointer returned will be the next buffer
 *  element after each is used.
 */
// ---------------------------------------------------------------------------------------
real8_t* Layer::store( real8_t *dst ) {
  // -------------------------------------------------------------------------------------
  real8_t* P = dst;
  for ( size_t n=0; n<num_nod; n++ ) {
    *P++ = b[n];
    for ( size_t c=0; c<num_con; c++ ) {
      *P++ = W[c][n];
    }
  }
  return P;
}


// =======================================================================================
/** @brief Load Weights.
 *  @param[in] buffer pointer to the source location to retrieve the weights.
 *  @return pointer to the next location in the buffer.
 *  
 *  Load the weights and bias from a location pointed to by src. (con+1)*nod elements
 *  of the buffer will be used. Where con=number of connections and nod=number of nodes in
 *  this layer.
 *
 *  Storage is arranged as follows: the first element is the bias for the first node.
 *  This is followed by the connection weights for that node. Then the bias for the
 *  second node and its connection weights. The pointer returned will be the next buffer
 *  element after each is used.
 */
// ---------------------------------------------------------------------------------------
real8_t* Layer::load( real8_t *src ) {
  // -------------------------------------------------------------------------------------
  real8_t* P = src;
  for ( size_t n=0; n<num_nod; n++ ) {
    b[n] = *P++;
    for ( size_t c=0; c<num_con; c++ ) {
      W[c][n] = *P++;
    }
  }
  return P;
}


// =======================================================================================
/** @brief Set maximum batch size.
 *  @param[in] bs new maximum batch size.
 *
 *  Set the allocation to accomodate a maximum batchsize.
 */
// ---------------------------------------------------------------------------------------
void Layer::set_max_batch_size ( const size_t bs ) {
  // -------------------------------------------------------------------------------------
  size_t nc = num_con;
  size_t nn = num_nod;
  resize( nc, nn, bs );
}


// =======================================================================================
/** @brief Read Configuration
 *  @param[in] inf file input stream.
 *
 *  Read the configuration for this Layer from a file input stream.
 */
// ---------------------------------------------------------------------------------------
void Layer::read ( std::ifstream& inf ) {
  // -------------------------------------------------------------------------------------
  size_t      n_con, n_nod;
  std::string name;
  
  inf >> n_con >> n_nod >> name;

  resize( n_con, n_nod, DEFAULT_BATCH_SIZE );

  set_activate( name );

  for ( size_t n=0; n<num_nod; n++ ) {
    inf >> b[n];
    for ( size_t c=0; c<num_con; c++ ) {
      inf >> W[c][n];
    }
  }
}


// =======================================================================================
/** @brief Write Configuration
 *  @param[in] outf file output stream.
 *  @param fmt edit descriptor.
 *
 *  Write the configuration for this Layer on a file output stream.
 */
// ---------------------------------------------------------------------------------------
void Layer::write( std::ofstream& outf, std::string fmt ) {
  // -------------------------------------------------------------------------------------
  
  outf << num_con << " " << num_nod << " " << act_name << "\n";

  for ( size_t n=0; n<num_nod; n++ ) {
    outf << c_fmt( fmt, b[n] ) << "\n";
    for ( size_t c=0; c<num_con; c++ ) {
      outf << c_fmt( fmt, W[c][n] ) << "\n";
    }
  }
  
}


}; // end namespace nns


// =======================================================================================
// **                                N N S : : L A Y E R                                **
// ======================================================================== END FILE =====
