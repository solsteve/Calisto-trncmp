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
real8_t Dice::normal( void ) {
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


u_int32_t Dice::TEST_SEED_MATTER[] = { 0x29341EA3, 0x9257677C, 0xCC98B1D1, 0x7C5EB68C,
                                       0x13ED5BC5, 0x3C91F88F, 0xE1A42570, 0x24CA88CD,
                                       0xAE36E97A, 0x59BADCBB, 0x4B9ED120, 0x952318E6,
                                       0xDD62B887, 0xCFC13ED9, 0x0F6A241B, 0x43970DA6,
                                       0xDF52E725, 0x4F6FE0ED, 0xCF9D4A7B, 0xA8742AE2,
                                       0x3B0590CF, 0xE20ACC41, 0x10A25D9B, 0xD59349FF,
                                       0x10BEE39E, 0x33CE2526, 0xD8029C5B, 0xFC6D3D65,
                                       0xD08E3996, 0x6FCFC48D, 0x2FD4F96B, 0x1AAEC36F,
                                       0x8C8758A6, 0xB6762DB6, 0x4E090027, 0x3EF534D9,
                                       0xE0A99EAD, 0x8D6AB5BF, 0xB2B4EC1F, 0xECB4E0FE,
                                       0x23FF01B3, 0x98E9FE45, 0xBCDB83C0, 0xC3032653,
                                       0xF54673AB, 0xC3B4DA6F, 0x9863616D, 0x92DCEA4F,
                                       0xAF804791, 0x477C9341, 0x52473426, 0x8A613705,
                                       0x0586770E, 0x18D1FC70, 0x49BE7A8F, 0xFE41C347,
                                       0x67C25BBA, 0x591C9AAB, 0x1C14DC7A, 0x7E06CAE4,
                                       0xBCD6341A, 0xD43EA256, 0x4EFB3301, 0x8BF9E86C,
                                       0x9CDDB5FC, 0x125595CD, 0x0504B634, 0xF20F8BF0,
                                       0xCEF38DA0, 0xA23444E3, 0x8A487F6F, 0xA2DF8EAF,
                                       0xB9F34D32, 0x39E4D38D, 0xEC83036E, 0xE5EEF9A0,
                                       0xF872415F, 0x91C45553, 0x57E19952, 0xB099335D,
                                       0xCC10AAFD, 0x95DBA094, 0x6AE8F26D, 0xB7C74FB7,
                                       0x8DAC62E2, 0xB9EDB1A4, 0xA26BEEB4, 0xA4C48F8B,
                                       0x379AABE0, 0x22143A99, 0x762CA98F, 0x3232CEC7,
                                       0xE81A2625, 0xC764D117, 0x07DE1333, 0x15FD7BA8,
                                       0x18B42626, 0x91498B38, 0xAB48DFF2, 0x9C14097D,
                                       0xD96C285B, 0xB9349E91, 0xDBE6EE16, 0xEEFB7BF5,
                                       0xFA081769, 0x23688A29, 0x7D09823E, 0x144BBBA1,
                                       0x747191C3, 0xDCFB07B2, 0x1C523161, 0x3463A633,
                                       0xAF5EA35F, 0x3079E01F, 0xC5008012, 0x7F544D91,
                                       0xA2FCEA11, 0x5725F031, 0xAC21D16A, 0x82D6EEB7,
                                       0xB42A808D, 0x1112DF13, 0xD969E555, 0xAED72630,
                                       0xA1F48743, 0xAE425853, 0x129B2B71, 0x7E16BAEC,
                                       0xA90BF14B, 0x997409E9, 0x942E6742, 0x4D8C3CC9,
                                       0x055DFC67, 0xF5F7AA63, 0x5A559F24, 0x080EAA7D,
                                       0x35698DAF, 0xC9DFCBDD, 0x305DCD53, 0xA7DE67AA,
                                       0x7AC124DF, 0xF537C8B0, 0xC6EFCB09, 0x8A419281,
                                       0x2C8E3A9D, 0x97DEEF8E, 0x28BFD824, 0xAE558715,
                                       0x2BB99103, 0xC3E94007, 0xB1498DEB, 0x501BAE88,
                                       0x4F073AA5, 0x48EF87CD, 0x1D1288B8, 0x284EA626,
                                       0xA2DE48D8, 0x3DE6FC26, 0x2A2A1005, 0xA5C48D02 };

// =======================================================================================
Dice* Dice::TestDice( void ) {
  // -------------------------------------------------------------------------------------
  Dice* dd = Dice::getInstance();
  dd->seed_set( reinterpret_cast<void*>(Dice::TEST_SEED_MATTER), dd->seed_size() );
  return dd;
}


// =======================================================================================
// **                                      D I C E                                      **
// ======================================================================== END FILE =====
