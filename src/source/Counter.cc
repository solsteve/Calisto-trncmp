// ====================================================================== BEGIN FILE =====
// **                                   C O U N T E R                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2011, 2019  Stephen W. Soliday                                     **
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
/** @brief  Counter.
 *  @file   Counter.cc
 *  @author Stephen W. Soliday
 *  @date   2011-Jan-28 Original release.
 *  @date   2019-May-15 CMake refactorization.
 *
 *  Provides the methods for an arbitrary base counter.
 */
// =======================================================================================


#include <Counter.hh>

// =======================================================================================
/** @brief New.
 *  @param b base
 *  @param n number of digits.
 *  @return pointer to the new counter's structure.
 *
 *   Allocate storage for the counter's structure.
 */
// ---------------------------------------------------------------------------------------
Counter::Counter( size_t b, size_t n ) : buffer(0), counting_base(0), numberofdigits(0) {
  // -------------------------------------------------------------------------------------
  init(b,n);
}

// =======================================================================================
/** @brief Delete.
 *
 *   Free the allcoated space for the counter. This function will zero out the memory.
 */
// ---------------------------------------------------------------------------------------
Counter::~Counter( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}

// =======================================================================================
/** @brief Space.
 *
 */
// ---------------------------------------------------------------------------------------
size_t Counter::space( void ) {
  // -------------------------------------------------------------------------------------
  size_t S = 1;
  for (size_t i=0; i<numberofdigits; i++ ) {
    S *= counting_base;
  }
  return S;
}

// =======================================================================================
/** @brief Load.
 *
 */
// ---------------------------------------------------------------------------------------
size_t* Counter::load( size_t* src ) {
  // -------------------------------------------------------------------------------------
  size_t *S = src;
  for (size_t i=0; i<numberofdigits; i++ ) {
    buffer[i] = *S++;
  }
  return S;
}

// =======================================================================================
/** @brief Load.
 *
 */
// ---------------------------------------------------------------------------------------
size_t* Counter::store( size_t* dst ) {
  // -------------------------------------------------------------------------------------
  size_t *D = dst;
  for (size_t i=0; i<numberofdigits; i++ ) {
    *D++ = buffer[i];
  }
  return D;
}

// =======================================================================================
/** @brief Initialize.
 *  @param b base
 *  @param n number of digits.
 *
 *   Allocate storage for the counter's structure.
 */
// ---------------------------------------------------------------------------------------
void Counter::init( size_t b, size_t n ) {
  // -------------------------------------------------------------------------------------
  buffer         = new size_t[n];
  counting_base  = b;
  numberofdigits = n;
  reset();
}

// =======================================================================================
/** @brief Destroy.
 *
 *  Free the allcoated space for the counter. This function will zero out the memory.
 */
// ---------------------------------------------------------------------------------------
void Counter::destroy( void ) {
  // -------------------------------------------------------------------------------------
  if ((size_t*)0 != buffer) {
    reset();
    delete buffer;
  }

  buffer         = (size_t*)0;
  counting_base  = 0;
  numberofdigits = 0;
}

// =======================================================================================
/** @brief Display.
 *  @param outf reference to an output stream.
 *
 *   Display the counter.
 */
// ---------------------------------------------------------------------------------------
void Counter::print( std::ostream& outf ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=numberofdigits-1; i>0; i--) {
    outf << buffer[i] << " ";
  }
  outf << buffer[0];
}

// =======================================================================================
/** @brief Copy.
 *  @param that pointer to the source counter's structure.
 *
 *   Copy the contents of the counter.
 */
// ---------------------------------------------------------------------------------------
void Counter::copy( Counter* src ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<Counter*>(0) == src ) {
    throw std::invalid_argument( "Pointer to source is NULL" );
  }

  if ( this->numberofdigits != src->numberofdigits ) {
    throw std::invalid_argument( "Counters have different number of digits" );
  }

  for (size_t i=0; i<numberofdigits; i++) {
    this->buffer[i] = src->buffer[i];
  }
}

// =======================================================================================
/** @brief Clone.
 *  @return pointer to the cloned counter's structure.
 *
 *  Clone an counter. This function allocates memory.
 */
// ---------------------------------------------------------------------------------------
Counter* Counter::clone( void ) {
  // -------------------------------------------------------------------------------------
  Counter* T = new Counter(counting_base, numberofdigits);
  T->copy(this);
  return T;
}

// =======================================================================================
/** @brief Reset.
 *
 *   Set the digits of the counter to zero.
 */
// ---------------------------------------------------------------------------------------
void Counter::reset( void ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=0; i<numberofdigits; i++) { buffer[i] = 0; }
}

// =======================================================================================
/** @brief Increment.
 *  @param d index of a digit to increment.
 *  @return 0=rolled over, 1=less than max value
 *
 *   Increment a specific digit.
 */
// ---------------------------------------------------------------------------------------
int Counter::inc( size_t d ) {
  // -------------------------------------------------------------------------------------
  if (d == numberofdigits) {
    reset();
    return 0;
  }

  buffer[d]++;
  if (buffer[d] >= counting_base) {
    buffer[d] = 0;
    return inc( d+1 );
  }

  return 1;
}

// =======================================================================================
/** @brief Increment.
 *  @return 0=rolled over, 1=less than max value
 *
 *   Increment the digits.
 */
// ---------------------------------------------------------------------------------------
int Counter::inc( void ) {
  // -------------------------------------------------------------------------------------
  return inc(0);
}

// =======================================================================================
/** @brief Max value.
 *  @return maximum expressible value.
 *
 *   numberOfDigits**counting_base - 1
 */
// ---------------------------------------------------------------------------------------
size_t Counter::maxValue( void ) {
  // -------------------------------------------------------------------------------------
  size_t M = 1;
  for (size_t i=0; i<numberofdigits; i++ ) {
    M *= counting_base;
  }
  return M-1;
}

// =======================================================================================
/** @brief Space.
 *
 */
// ---------------------------------------------------------------------------------------
size_t Counter::toDecimal( void ) {
  // -------------------------------------------------------------------------------------
  size_t S = 0;
  size_t M = 1;
  for (size_t i=0; i<numberofdigits; i++ ) {
    S += buffer[i] * M;
    M *= counting_base;
  }
  return S;
}

// =======================================================================================
/** @brief Space.
 *
 */
// ---------------------------------------------------------------------------------------
void Counter::fromDecimal( size_t x ) {
  // -------------------------------------------------------------------------------------
  size_t reg = x;
  reset();
  for (size_t i=0; i<numberofdigits; i++ ) {
    buffer[i] = reg % counting_base;
    reg /= counting_base;
  }
  
}
