// ====================================================================== BEGIN FILE =====
// **                                      D I C E                                      **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 1990-2019, Stephen W. Soliday                                      **
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
/** @brief  Dice.
 *  @file   Dice.hh
 *  @author Stephen W. Soliday
 *  @date 1990-02-17 Original release.
 *  @date 2009-02-07 Major revision.
 *  @date 2016-10-11 Major revision.
 *  @date 2019-Jun-14 CMake refactorization.
 *
 *  Provides the methods for various random distributions.
 */
// =======================================================================================


#include <Dice.hh>

#include <fcntl.h>
#include <unistd.h>


#define VAR_INIT(a)  ent_engine(a), have_spare(false), rand1(0.0), rand2(0.0)

TLOGGER_REFERENCE( Dice, logger );


/// Static singleton instance.
Dice* Dice::theInstance = static_cast<Dice*>(0);


// =======================================================================================
/** @brief Constructor.
 *
 *  Instantiate an instance of the underlying randomize source. Apply the seed action.
 */
// ---------------------------------------------------------------------------------------
Dice::Dice( void ) : VAR_INIT(0) {
  // -------------------------------------------------------------------------------------
  ent_engine = Entropy::DEFAULT();
  seed_set();
}


// =======================================================================================
/** @brief Constructor.
 *
 *  Instantiate an instance of the underlying randomize source. Apply the seed action.
 */
// ---------------------------------------------------------------------------------------
Dice::Dice( std::string fspc ) : VAR_INIT(0) {
  // -------------------------------------------------------------------------------------
  ent_engine = Entropy::DEFAULT();
  seed_set(fspc);
}


// =======================================================================================
/** @brief Constructor.
 *
 *  Instantiate an instance of the underlying randomize source. Apply the seed action.
 */
// ---------------------------------------------------------------------------------------
Dice::Dice( void* sm, size_t n ) : VAR_INIT(0) {
  // -------------------------------------------------------------------------------------
  ent_engine = Entropy::DEFAULT();
  seed_set(sm,n);
}


// =======================================================================================
/** @brief Constructor.
 *
 *  Instantiate an instance of the underlying randomize source. Apply the seed action.
 */
// ---------------------------------------------------------------------------------------
Dice::Dice( Entropy* eng ) : VAR_INIT(0) {
  // -------------------------------------------------------------------------------------
  ent_engine = eng;
  seed_set();
}


// =======================================================================================
/** @brief Constructor.
 *
 *  Instantiate an instance of the underlying randomize source. Apply the seed action.
 */
// ---------------------------------------------------------------------------------------
Dice::Dice( Entropy* eng, std::string str ) : VAR_INIT(0) {
  // -------------------------------------------------------------------------------------
  ent_engine = eng;
  seed_set(str);
}


// =======================================================================================
/** @brief Constructor.
 *
 *  Instantiate an instance of the underlying randomize source. Apply the seed action.
 */
// ---------------------------------------------------------------------------------------
Dice::Dice( Entropy* eng, void* sm, size_t n ) : VAR_INIT(0) {
  // -------------------------------------------------------------------------------------
  ent_engine = eng;
  seed_set(sm,n);
}


// =======================================================================================
/** @brief Destructor.
 *
 *  Delete the randomize object and return the static pointer to its NULL state.
 */
// ---------------------------------------------------------------------------------------
Dice::~Dice( void ) {
  // -------------------------------------------------------------------------------------
  Entropy* ent = ent_engine;
  if ( ( Entropy* )0 != ent ) {
    delete ent;
    ent_engine = ( Entropy* )0;
  }
}


// =======================================================================================
/** @brief Get Instance.
 *  @return a pointer to the static instance of the randomize class.
 *
 *  Get the static instance of the Dice class, creating it if needed.
 */
// ---------------------------------------------------------------------------------------
Dice* Dice::getInstance( void ) {
  // -------------------------------------------------------------------------------------
  if ( ( Dice* )0 == Dice::theInstance ) {
    Dice::theInstance = new Dice();
  }
  return Dice::theInstance;
}


// =======================================================================================
/** @brief Get Instance.
 *  @param fspc file specification.
 *  @return a pointer to the static instance of the Dice class.
 *
 *  Get the static instance of the Dice class, creating it if needed.
 */
// ---------------------------------------------------------------------------------------
Dice* Dice::getInstance( std::string fspc ) {
  // -------------------------------------------------------------------------------------
  if ( ( Dice* )0 == Dice::theInstance ) {
    Dice::theInstance = new Dice(fspc);
  } else {
    Dice::theInstance->seed_set(fspc);
  }
  return Dice::theInstance;
}


// =======================================================================================
/** @brief Get Instance.
 *  @return a pointer to the static instance of the Dice class.
 *
 *  Get the static instance of the Dice class, creating it if needed.
 */
// ---------------------------------------------------------------------------------------
Dice* Dice::getInstance( void* sm, size_t n ) {
  // -------------------------------------------------------------------------------------
  if ( ( Dice* )0 == Dice::theInstance ) {
    Dice::theInstance = new Dice(sm, n);
  } else {
    Dice::theInstance->seed_set(sm,n);
  }
  return Dice::theInstance;
}


// =======================================================================================
/** @brief Get Instance.
 *  @return a pointer to the static instance of the randomize class.
 *
 *  Get the static instance of the Dice class, creating it if needed.
 */
// ---------------------------------------------------------------------------------------
Dice* Dice::getInstance( Entropy* eng ) {
  // -------------------------------------------------------------------------------------
  if ( ( Dice* )0 == Dice::theInstance ) {
    Dice::theInstance = new Dice(eng);
  }
  return Dice::theInstance;
}


// =======================================================================================
/** @brief Get Instance.
 *  @param fspc file specification.
 *  @return a pointer to the static instance of the Dice class.
 *
 *  Get the static instance of the Dice class, creating it if needed.
 */
// ---------------------------------------------------------------------------------------
Dice* Dice::getInstance( Entropy* eng, std::string fspc ) {
  // -------------------------------------------------------------------------------------
  if ( ( Dice* )0 == Dice::theInstance ) {
    Dice::theInstance = new Dice(eng, fspc);
  } else {
    Dice::theInstance->seed_set(fspc);
  }
  return Dice::theInstance;
}


// =======================================================================================
/** @brief Get Instance.
 *  @return a pointer to the static instance of the Dice class.
 *
 *  Get the static instance of the Dice class, creating it if needed.
 */
// ---------------------------------------------------------------------------------------
Dice* Dice::getInstance( Entropy* eng, void* sm, size_t n ) {
  // -------------------------------------------------------------------------------------
  if ( ( Dice* )0 == Dice::theInstance ) {
    Dice::theInstance = new Dice(eng, sm, n);
  } else {
    Dice::theInstance->seed_set(sm,n);
  }
  return Dice::theInstance;
}


// =======================================================================================
/** @brief Delete Instance.
 *
 *  Delete the static instance of the Dice class.
 */
// ---------------------------------------------------------------------------------------
void Dice::delInstance( void ) {
  // -------------------------------------------------------------------------------------
  if ( ( Dice* )0 != Dice::theInstance ) {
    delete Dice::theInstance;
    Dice::theInstance = ( Dice* )0;
  }
}


// =======================================================================================
/** @brief Reset Seed.
 *
 *  Reapply the seed function.
 */
// ---------------------------------------------------------------------------------------
void Dice::seed_set( void ) {
  // -------------------------------------------------------------------------------------
   ent_engine->seed_set();
}


// =======================================================================================
/** @brief Reset Seed.
 *  @param fspc file specification.
 *  @return true is error occurs.
 *
 *  Reapply the seed function by providing seed material.
 */
// ---------------------------------------------------------------------------------------
void Dice::seed_set( std::string fspc ) {
  // -------------------------------------------------------------------------------------
  //    std::cout << "seed_set from file\n";
  //** @todo make this thread safe */
    
  size_t ss = ent_engine->seed_size();
  u_int8_t* buffer = new u_int8_t[ ss ];

  int fd = open( fspc.c_str(), O_RDONLY );

  ssize_t rb = read( fd, (void*) buffer, ss );

  if ( rb < (ssize_t)ss ) {
    logger->info( "Binary seed file fell short. Needed %u got %d. "
		  "I will just repeat what I got.", ss, rb );
    size_t dif = ss - (size_t)rb;
    for ( size_t i=0; i<dif; i++ ) {
      buffer[ (size_t)rb + i ] = buffer[ i ];
    }
  }

  close( fd );

  ent_engine->seed_set( buffer, ss );

  delete buffer;
}


// =======================================================================================
/** @brief Reset Seed.
 *  @param src pointer to a source of seed material.
 *  @param n length of the seed material.
 *  @return
 *
 *  Reapply the seed function by providing seed material.
 */
// ---------------------------------------------------------------------------------------
void Dice::seed_set( void* src, size_t n ) {
  // -------------------------------------------------------------------------------------
  ent_engine->seed_set( src, n );
}


// =======================================================================================
/** @brief Boolean.
 *  @param thres divide between true/false.
 *  @return true if uniform random is less than the threshold, otherwise return false.
 *
 *  Return a true/false based on the threshold. By default it is 1/2 providing just as
 *  many trues and falses. If threshold is set to 0.3 then 3 times out of 10 this will
 *  return a true and 7 times out of 10 a false will be returned. If the threshold is
 *  0.75 then 3 times out of 4 this will return a true and 1 time out of 4 a false.
 */
// ---------------------------------------------------------------------------------------
bool Dice::boolean( real8_t thres ) {
  // -------------------------------------------------------------------------------------
  return ( ent_engine->R64() < thres) ? true : false;
}


// =======================================================================================
/** @brief Uniform.
 *  @return a number with a Gaussian distribution.
 *
 *  Return a Uniform distribution with a mean of 0, and
 *  a range of [ 0, 1 )
 */
// ---------------------------------------------------------------------------------------
real8_t Dice::uniform( void ) {
  // -------------------------------------------------------------------------------------
  return ent_engine->R64();
}


// =======================================================================================
/** @brief Gaussian.
 *  @return a number with a Gaussian distribution.
 *
 *  Use Box-Muller algorithm to generate numbers with a normal distribution.
 *  The mean is 0.0, the standard deviation is 1.0 and limits +/- 6.15 * StdDev,
 *  based on experimental results of rolling 1 trillion values.
 */
// ---------------------------------------------------------------------------------------
real8_t Dice::gaussian( void ) {
  // -------------------------------------------------------------------------------------
  Entropy* ent = ent_engine;

  if(have_spare) {
    have_spare = false;
    return sqrt(rand1) * sin(rand2);
  }
  
  have_spare = true;
  
  rand1 = ent->R64();
  if(rand1 < 1e-100) { rand1 = 1e-100; }
  rand1 = -D_TWO * log(rand1);
  rand2 = D_2PI*ent->R64();
  
  return sqrt(rand1) * cos(rand2);
}


// =======================================================================================
/** @brief Random Index.
 *  @param maxVal upper limit.
 *  @return value 0 <= r < maxval with a uniform distribution.
 *
 *  Return an index (unsigned int) with a uniform random distribution.
 */
// ---------------------------------------------------------------------------------------
size_t Dice::index( size_t maxVal ) {
  // -------------------------------------------------------------------------------------
  size_t x = ( size_t ) floor( uniform() * ( real8_t )maxVal  + 0.5 );
  if ( x < maxVal ) { return x; }
  return maxVal-1;
}


// =======================================================================================
// **                                      D I C E                                      **
// ======================================================================== END FILE =====
