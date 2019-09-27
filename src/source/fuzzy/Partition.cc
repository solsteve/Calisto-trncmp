// ====================================================================== BEGIN FILE =====
// **                          F U Z Z Y : : P A R T I T I O N                          **
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
/** @brief  Fuzzy Partition.
 *  @file   fuzzy/Partition.hh
 *  @author Stephen W. Soliday
 *  @date   2014-Jun-27 Original C++ release.
 *  @date   2018-Aug-09 Ported to Java.
 *  @date   2019-Sep-13 CMake refactorization.
 *
 * Provides the methods for a fuzzy partition.
 *
 *   NEG    SN  ZERO  SP    POS
 *  ____                    ____ 1
 *      \   /\   /\   /\   /
 *       \ /  \ /  \ /  \ /
 *        X    X    X    X          This partition contains 5 fuzzy functions
 *       / \  / \  / \  / \         1 LeftTrapezoid 3 Triangle, and 1 RightTrapezoid
 *  ____/   \/   \/   \/   \____
 *  ============================ 0
 *
 */
// =======================================================================================

#include <fuzzy/Partition.hh>
#include <fuzzy/LeftTrapezoidSet.hh>
#include <fuzzy/RightTrapezoidSet.hh>
#include <fuzzy/TriangleSet.hh>


namespace fuzzy {


TLOGGER_REFERENCE( Partition, logger );


#define INIT_VAR(_a) fset(_a), num_set(_a), min_ctr(_a), max_ctr(_a)


// =======================================================================================
/** @brief Constructor.
 *
 *  Allocate an empty domain.
 */
// ---------------------------------------------------------------------------------------
Partition::Partition( void ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] n number of centers.
 *
 *  Construct a domain of fuzzy sets. The left and right sets are trapezoidal.
 *  The internal sets are triangular. The left is -1 and the right is +1
 */
// ---------------------------------------------------------------------------------------
Partition::Partition( const int32_t n ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  set( n );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] n number of centers.
 *  @param[in] ctrs pointer to a real array of center values.
 *
 *  Construct a domain of fuzzy sets. The left and right sets are trapezoidal.
 *  The internal sets are triangular. The centers are defined by (ctrs) the left
 *  and right extents are defined by the centers of the sets to the left and right.
 */
// ---------------------------------------------------------------------------------------
Partition::Partition( const int32_t n, const real8_t  left, const real8_t right ) :
    INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  set( n, left, right );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] n number of centers (sets).
 *  @param[in] left far left center values.
 *  @param[in] right far right center values.
 *
 *  Construct a domain of fuzzy sets. The left and right sets are trapezoidal.
 *  The internal sets are triangular. The centers are computed from the left
 *  and right extents and the number of sets.
 */
// ---------------------------------------------------------------------------------------
Partition::Partition( const int32_t n, real8_t* ctrs ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  set( n, ctrs );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] src reference to another Partition.
 *
 */
// ---------------------------------------------------------------------------------------
Partition::Partition( const Partition& psrc ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  copy( psrc );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Partition::~Partition( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}








// =======================================================================================
/** @brief Destroy.
 *
 *  If necessary free memory. Reset variables regardless.
 */
// ---------------------------------------------------------------------------------------
void Partition::destroy( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<Set**>(0) != fset ) {
    const int32_t n = num_set;
    for ( int32_t i=0; i<n; i++ ) {
      if ( static_cast<Set*>(0) != fset[i] ) {
        delete fset[i];
      }
      fset[i] = static_cast<Set*>(0);
    }
    delete[] fset;
  }

  fset    = static_cast<Set**>(0);
  num_set =  0;
  min_ctr = -D_ZERO;
  max_ctr =  D_ZERO;
}


// =======================================================================================
/** @brief Resize.
 *  @param n change the number of sets.
 *  @return true if the number of sets changed.
 *
 *  Change the number of sets. This function deletes and reallocates only if the number.
 *  of sets is different. The current left and right limits do not change.
 *  @note if the size changes the resulting sets have no positions, and therefor
 *        must be reset with set( ctrs[] ) or set( left, right )
 */
// ---------------------------------------------------------------------------------------
bool Partition::resize( const int32_t n ) {
  // -------------------------------------------------------------------------------------
  if ( 1 > n ) {
    logger->warn( "There needs to be at least one function only got %d", n );
    return false;
  }

  if ( n == num_set ) {
    logger->debug( "Resize called with no change" );
    return false;
  }

  destroy();

  fset    = new Set*[n];
  num_set = n;

  switch( n ) {
    case 0: { // ----- this is an error -----------------------------------
      logger->error( "You should not set the number of sets to zero" );
    } break;

    case 1: { // ----- special case n=1 -----------------------------------
      logger->debug( "resize n=1" );
      fset[0] = new TriangleSet();
    } break;

    case 2: { // ----- special case n=2 -----------------------------------
      logger->debug( "resize n=2" );
      fset[0] = new LeftTrapezoidSet();
      fset[1] = new RightTrapezoidSet();	
    } break;

    case 3: { // ----- special case n=3 -----------------------------------
      logger->debug( "resize n=3" );
      fset[0] = new LeftTrapezoidSet();
      fset[1] = new TriangleSet();
      fset[2] = new RightTrapezoidSet();	
    } break;

    default: { // ----- general case n>3 -----------------------------------
      logger->debug( "resize n=%d", n );
      fset[0] = new LeftTrapezoidSet();
      for ( int32_t i=1; i<n-1; i++ ) {
        fset[i] = new TriangleSet();
      }
      fset[n-1] = new RightTrapezoidSet();	
    } break;
  }

  return true;
}








// =======================================================================================
/** @brief Get Set.
 *  @param[in] i index of the Set.
 *  @return reference to the ith Set.
 */
// ---------------------------------------------------------------------------------------
Set& Partition::get( const int32_t i ) {
  // -------------------------------------------------------------------------------------
  return *(fset[i]);
}


// =======================================================================================
/** @brief Number of Inputs.
 *  @return number of inputs.
 *
 *  The number of inputs is always one.
 */
// ---------------------------------------------------------------------------------------
int32_t Partition::nIn( void ) const {
  // -------------------------------------------------------------------------------------
  return 1;
}


// =======================================================================================
/** @brief Number of Outputs.
 *  @return number of outputs.
 *
 *  The number of outputs is equal to the number of Sets.
 */
// ---------------------------------------------------------------------------------------
int32_t Partition::nOut( void ) const {
  // -------------------------------------------------------------------------------------
  return num_set;
}


// =======================================================================================
/** @brief Buffer Size.
 *  @return number of elements required to support load/store.
 *
 *  The number of elements is equal to the number of sets.
 */
// ---------------------------------------------------------------------------------------
int32_t Partition::size( void ) const {
  // -------------------------------------------------------------------------------------
  return num_set;
}


// =======================================================================================
/** @brief Create Buffer.
 *  @return pointer to an allocation with enough elements to support load/store.
 *
 *  @note the user must free this allocation when done.
 */
// ---------------------------------------------------------------------------------------
real8_t* Partition::create_buffer( void ) {
  // -------------------------------------------------------------------------------------
  return new real8_t[ size() ];
}



// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t Partition::getCenter( const int32_t idx ) const {
  // -------------------------------------------------------------------------------------
  return fset[idx]->getCenter();
}




// =======================================================================================
/** @brief Balance Centers.
 *
 *  Balance the centers such that the are evenly distributed between min_ctr & max_ctr.
 */
// ---------------------------------------------------------------------------------------
void Partition::balance( void ) {
  // -------------------------------------------------------------------------------------
  switch( num_set ) {
    case 0:  { // ----- this is an error -------------------------------------------------
      logger->error( "fuzzy::Partition.resize should have rejected this" );
      exit(1);
    } break;
      
    case 1:  { // ----- special case n=1 -------------------------------------------------
      // set one triangle set
      real8_t mid = D_HALF * ( min_ctr + max_ctr );
      fset[0]->set( min_ctr, mid, max_ctr );
    } break;
      
    case 2:  { // ----- special case n=2 -------------------------------------------------
      // set a left and right pair of trapezoid sets.
      fset[0]->set( min_ctr, max_ctr );     
      fset[1]->set( min_ctr, max_ctr );     
    } break;
      
    case 3:  { // ----- special case n=3 -------------------------------------------------
      // set a trapezoid-triangle-trapezoid classic combination.
      real8_t mid = D_HALF * (min_ctr + max_ctr);
      fset[0]->set( min_ctr, mid          );     
      fset[1]->set( min_ctr, mid, max_ctr );     
      fset[2]->set(          mid, max_ctr );     
    } break;
      
    default: { // ----- general case n>3 -------------------------------------------------
      real8_t delta = ( max_ctr - min_ctr ) / (real8_t) (num_set - 1);

      real8_t L = min_ctr;
      real8_t C = L + delta;
      real8_t R = C + delta;

      fset[0]->set( L, C );

      for ( int32_t i=1; i<num_set-1; i++ ) {
        fset[i]->set( L, C, R );
        L = C;
        C = R;
        R += delta;
      }

      fset[num_set-1]->set( L, C );
    } break;
  }
}








// =======================================================================================
/** @brief Set Centers.
 *  @param[in] n number of sets.
 *
 *  Balance the centers such that the are evenly distributed between -1 and +1.
 */
// ---------------------------------------------------------------------------------------
void Partition::set( const int32_t n ) {
  // -------------------------------------------------------------------------------------
  resize(n);
  min_ctr = -D_ONE;
  max_ctr =  D_ONE;
  balance();
}


// =======================================================================================
/** @brief Set Centers.
 *  @param[in] n    number of sets.
 *  @param[in] minc new minimum center value.
 *  @param[in] maxc new maximum center value.
 *
 *  Balance the centers such that the are evenly distributed between min_ctr & max_ctr.
 */
// ---------------------------------------------------------------------------------------
void Partition::set( const int32_t n, const real8_t minc, const real8_t maxc ) {
  // -------------------------------------------------------------------------------------
  resize(n);
  set( minc, maxc );
}


// =======================================================================================
/** @brief Set Centers.
 *  @param[in] n    number of sets.
 *  @param[in] ctrs pointer to a real array of center values.
 *
 *  The centers are defined by (ctrs) the left and right extents of each set are 
 *  defined by the centers of the sets to the left and right.
 */
// ---------------------------------------------------------------------------------------
void Partition::set( const int32_t n, real8_t* ctrs ) {
  // -------------------------------------------------------------------------------------
  resize(n);
  set( ctrs );
}








// =======================================================================================
/** @brief Set Centers.
 *  @param[in] ctrs pointer to a real array of center values.
 *
 *  The centers are defined by (ctrs) the left and right extents of each set are 
 *  defined by the centers of the sets to the left and right.
 */
// ---------------------------------------------------------------------------------------
void Partition::set( real8_t* ctrs ) {
  // -------------------------------------------------------------------------------------
  switch( num_set ) {
    case 0:  { // ----- this is an error -------------------------------------------------
      logger->error( "fuzzy::Partition.resize should have rejected this" );
      exit(1);
    } break;
      
    case 1:  { // ----- special case n=1 -------------------------------------------------
      // set one triangle set
      min_ctr = ctrs[0] - D_ONE;
      max_ctr = ctrs[0] + D_ONE;
      fset[0]->set( min_ctr, ctrs[0], max_ctr );
    } break;
      
    case 2:  { // ----- special case n=2 -------------------------------------------------
      // set a left and right pair of trapezoid sets.
      min_ctr = ctrs[0];
      max_ctr = ctrs[1];
      fset[0]->set( min_ctr, max_ctr );     
      fset[1]->set( min_ctr, max_ctr );     
    } break;
      
    case 3:  { // ----- special case n=3 -------------------------------------------------
      // set a trapezoid-triangle-trapezoid classic combination.
      min_ctr     = ctrs[0];
      real8_t mid = ctrs[1];
      max_ctr     = ctrs[2];
      fset[0]->set( min_ctr, mid          );     
      fset[1]->set( min_ctr, mid, max_ctr );     
      fset[2]->set(          mid, max_ctr );     
    } break;
      
    default: { // ----- general case n>3 -------------------------------------------------
      // the left and right are trapezoids and the rest are triangles.
      fset[0]->set( ctrs[0], ctrs[1] );
      for ( int32_t i=1; i<num_set-1; i++ ) {
        fset[i]->set( ctrs[i-1], ctrs[i], ctrs[i+1] );
      }
      fset[num_set-1]->set( ctrs[num_set-2], ctrs[num_set-1] );
    } break;
  }
}


// =======================================================================================
/** @brief Set Centers.
 *  @param[in] minc  new minimum center value.
 *  @param[in] maxc new maximum center value.
 *
 *  Balance the centers such that the are evenly distributed between min_ctr & max_ctr.
 */
// ---------------------------------------------------------------------------------------
void Partition::set( const real8_t minc, const real8_t maxc ) {
  // -------------------------------------------------------------------------------------
  min_ctr = minc;
  max_ctr = maxc;
  balance();
}





// =======================================================================================
/** @brief Copy.
 *  @param[in] src reference to another Partition.
 *
 */
// ---------------------------------------------------------------------------------------
void Partition::copy( const Partition& psrc ) {
  // -------------------------------------------------------------------------------------
  int32_t n = psrc.nOut();
  real8_t c[n];
  for ( int32_t i=0; i<n; i++ ) {
    c[i] = psrc.getCenter(i);
  }
  set( n, c );
}


// =======================================================================================
/** @brief Clone.
 *  @param[in] src reference to another Partition.
 *
 */
// ---------------------------------------------------------------------------------------
Partition* Partition::clone( void ) {
  // -------------------------------------------------------------------------------------
  return new Partition( *this );
}





// =======================================================================================
// ---------------------------------------------------------------------------------------
void Partition::mu( real8_t* degree, const real8_t x ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<num_set; i++ ) {
    degree[i] = fset[i]->mu(x);
  }
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t Partition::area( real8_t* degree ) {
  // -------------------------------------------------------------------------------------
  real8_t a = D_ZERO;
  for ( int32_t i=0; i<num_set; i++ ) {
    a += fset[i]->area(degree[i]);
  }
  return a;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t Partition::coa( real8_t* degree ) {
  // -------------------------------------------------------------------------------------
  real8_t sumAX = D_EPSILON;
  real8_t sumA  = D_EPSILON;
  for ( int32_t i=0; i<num_set; i++ ) {
    real8_t a = fset[i]->area(degree[i]);
    real8_t x = fset[i]->coa(degree[i]);
    sumAX += ( a * x );
    sumA  +=   a;
  }
  return sumAX / sumA;
}








// =======================================================================================
/** @brief Load.
 *  @param[in] src pointer to source data;
 *  @return ponter to next location.
 *
 *  set thye centers from an array of real8_t. Returning the next element.
 */
// ---------------------------------------------------------------------------------------
real8_t* Partition::load( real8_t* src ) {
  // -------------------------------------------------------------------------------------
  set( src );
  return (src+num_set);
}


// =======================================================================================
/** @brief Store.
 *  @param[out] dst pointer to destination data;
 *  @return ponter to next location.
 *
 * Store the centers to an array of real8_t. Returning the next element.
 */
// ---------------------------------------------------------------------------------------
real8_t* Partition::store( real8_t* dst ) {
  // -------------------------------------------------------------------------------------
  real8_t* D = dst;
  for ( int32_t i=0; i<num_set; i++ ) {
    *D++ = fset[i]->getCenter();
  }

  return D;
}


// =======================================================================================
/** @brief Write.
 *  @param[in] ofs reference to an output file stream.
 *  @param[in] fmt optional edit descriptor.
 *  @return true if error occurs.
 *
 *  Write the centers of the (n_set) fuzzy sets.
 */
// ---------------------------------------------------------------------------------------
bool Partition::write( std::ofstream& ofs, std::string fmt ) {
  // -------------------------------------------------------------------------------------
  ofs << num_set;
  for ( int32_t i=0; i<num_set; i++ ) {
    ofs << " " << c_fmt( fmt, fset[i]->getCenter() );
  }
  ofs << "\n";

  return false;
}


// =======================================================================================
/** @brief Read.
 *  @param[in] ifs reference to an input file stream.
 *  @return true if error occurs.
 *
 *  Read the centers of the (n_set) fuzzy sets.
 */
// ---------------------------------------------------------------------------------------
bool Partition::read( std::ifstream& ifs ) {
  // -------------------------------------------------------------------------------------
  int32_t nf;
  ifs >> nf;

  real8_t ctrs[nf];
    
  for ( int32_t i=0; i<nf; i++ ) {
    ifs >> ctrs[i];
  }

  this->set( nf, ctrs );

  return false;
}


}; // end namespace fuzzy


// =======================================================================================
// **                          F U Z Z Y : : P A R T I T I O N                          **
// ======================================================================== END FILE =====
