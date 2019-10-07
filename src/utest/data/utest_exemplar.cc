// ====================================================================== BEGIN FILE =====
// **                            U T E S T _ E X E M P L A R                            **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019-, Stephen W. Soliday                                          **
// **                       stephen.soliday@trncmp.org                                  **
// **                       http://research.trncmp.org                                  **
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
/** @brief  Automated testing for Exemplar class methods.
 *  @file   utest_exemplar.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-03
 *
 *  Provides automated testing for the Exemplar class and methods.
 */
// =======================================================================================

#include <limits.h>
#include <Exemplar.hh>
#include <gtest/gtest.h>
#include <Dice.hh>

namespace {

// =======================================================================================
inline real8_t ELEM( const int32_t lab, const int32_t i, const int32_t j ) {
  // -------------------------------------------------------------------------------------
  return ((real8_t)(100*lab)) + ((real8_t)(i+1)) + (((real8_t)(j+1))/100.0);
}


// =======================================================================================
inline real8_t ELEM( const int32_t i, const int32_t j ) {
  // -------------------------------------------------------------------------------------
  return ((real8_t)(i+1)) + (((real8_t)(j+1))/100.0);
}


// =======================================================================================
void makeSingle( Exemplar::Data& X, const int32_t ns, const int32_t ni ) {
  // -------------------------------------------------------------------------------------
  X.resize( ns, ni );
  for ( int32_t r=0; r<ns; r++ ) {
    for ( int32_t c=0; c<ni; c++ ) {
      X.set( r, c, ELEM( r, c ) );
    }
  }
}


// =======================================================================================
void makePair( Exemplar::Data& X, Exemplar::Data& Y ) {
  // -------------------------------------------------------------------------------------
  const int32_t ns = X.size(0);
  const int32_t ni = X.size(1);
  const int32_t no = Y.size(1);
  for ( int32_t r=0; r<ns; r++ ) {
    for ( int32_t c=0; c<ni; c++ ) {
      X.set( r, c, ELEM( 1, r, c ) );
    }
    for ( int32_t c=0; c<no; c++ ) {
      Y.set( r, c, ELEM( 2, r, c ) );
    }
  }
}


// =======================================================================================
void makeSingle( Exemplar::Data& X ) {
  // -------------------------------------------------------------------------------------
  const int32_t ns = X.size(0);
  const int32_t ni = X.size(1);
  for ( int32_t r=0; r<ns; r++ ) {
    for ( int32_t c=0; c<ni; c++ ) {
      X.set( r, c, ELEM( r, c ) );
    }
  }
}


// =======================================================================================
inline real8_t small( Dice* dd ) {
  // -------------------------------------------------------------------------------------
  return 1.0e-4 * floor( dd->normal() * 1.0e5 );
}


// =======================================================================================
void randomize( Exemplar& E, Dice* dd ) {
  // -------------------------------------------------------------------------------------
  const int32_t ns = E.nSample();
  const int32_t ni = E.nInput();
  const int32_t no = E.nOutput();
  for ( int32_t i=0; i<ns; i++ ) {
    for ( int32_t j=0; j<ni; j++ ) {
      E.setIn( i, j, small( dd ) );
    }
    if ( 0 < no ) {
      for ( int32_t j=0; j<no; j++ ) {
        E.setOut( i, j, small( dd ) );
      }
    }
  }
}

// =======================================================================================
TEST( test_meta, empty ) {
  // -------------------------------------------------------------------------------------
  // Test: Exemplar()
  // -------------------------------------------------------------------------------------
  Exemplar::Meta M;
  EXPECT_EQ( 0, M.n_sample );
  EXPECT_EQ( 0, M.n_input );
  EXPECT_EQ( 0, M.n_output );
}


// =======================================================================================
TEST( test_meta, create_destroy ) {
  // -------------------------------------------------------------------------------------
  // Test: Exemplar(s,i,o), Exemplar.destroy()
  // -------------------------------------------------------------------------------------
  Exemplar::Meta M( 4, 9, 16 );
  EXPECT_EQ(  4, M.n_sample );
  EXPECT_EQ(  9, M.n_input );
  EXPECT_EQ( 16, M.n_output );

  Exemplar::Meta P = M;
  M.destroy();

  EXPECT_EQ( 0, M.n_sample );
  EXPECT_EQ( 0, M.n_input );
  EXPECT_EQ( 0, M.n_output );

  EXPECT_EQ(  4, P.n_sample );
  EXPECT_EQ(  9, P.n_input );
  EXPECT_EQ( 16, P.n_output );
}


// =======================================================================================
TEST( test_meta, parse ) {
  // -------------------------------------------------------------------------------------
  // Test: Exemplar.toString(), Exemplar.fromString()
  // -------------------------------------------------------------------------------------
  {
    Exemplar::Meta M( 4, 9, 16 );
    EXPECT_EQ(  4, M.n_sample );
    EXPECT_EQ(  9, M.n_input );
    EXPECT_EQ( 16, M.n_output );
    std::string str = M.toString();
    EXPECT_STREQ( "4 9 16", str.c_str() );
    Exemplar::Meta P(6,2,3);
    EXPECT_EQ( 6, P.n_sample );
    EXPECT_EQ( 2, P.n_input );
    EXPECT_EQ( 3, P.n_output );
    P.fromString( str );
    EXPECT_EQ(  4, P.n_sample );
    EXPECT_EQ(  9, P.n_input );
    EXPECT_EQ( 16, P.n_output );
  }
    
  {
    Exemplar::Meta M( 4, 9 );
    EXPECT_EQ( 4, M.n_sample );
    EXPECT_EQ( 9, M.n_input );
    EXPECT_EQ( 0, M.n_output );
    std::string str = M.toString();
    EXPECT_STREQ( "4 9", str.c_str() );
    Exemplar::Meta P(6,2,3);
    EXPECT_EQ( 6, P.n_sample );
    EXPECT_EQ( 2, P.n_input );
    EXPECT_EQ( 3, P.n_output );
    P.fromString( str );
    EXPECT_EQ( 4, P.n_sample );
    EXPECT_EQ( 9, P.n_input );
    EXPECT_EQ( 0, P.n_output );
  }
}


// =======================================================================================
TEST( test_meta, read_write ) {
  // -------------------------------------------------------------------------------------
  // Test: Exemplar.toString(), Exemplar.fromString()
  // -------------------------------------------------------------------------------------
  {
    Exemplar::Meta M( 4, 9, 16 );
    EXPECT_EQ(  4, M.n_sample );
    EXPECT_EQ(  9, M.n_input );
    EXPECT_EQ( 16, M.n_output );
    M.write( "/tmp/write_meta" );
      
    Exemplar::Meta P(6,2,3);
    EXPECT_EQ( 6, P.n_sample );
    EXPECT_EQ( 2, P.n_input );
    EXPECT_EQ( 3, P.n_output );
      
    P.read( "/tmp/write_meta" );
    EXPECT_EQ(  4, P.n_sample );
    EXPECT_EQ(  9, P.n_input );
    EXPECT_EQ( 16, P.n_output );
  }
    
  {
    Exemplar::Meta M( 4, 9 );
    EXPECT_EQ( 4, M.n_sample );
    EXPECT_EQ( 9, M.n_input );
    EXPECT_EQ( 0, M.n_output );
    M.write( "/tmp/write_meta" );
      
    Exemplar::Meta P(6,2,3);
    EXPECT_EQ( 6, P.n_sample );
    EXPECT_EQ( 2, P.n_input );
    EXPECT_EQ( 3, P.n_output );
      
    P.read( "/tmp/write_meta" );
    EXPECT_EQ( 4, P.n_sample );
    EXPECT_EQ( 9, P.n_input );
    EXPECT_EQ( 0, P.n_output );
  }
}








// =======================================================================================
TEST( test_edata, construct ) {
  // -------------------------------------------------------------------------------------
  // Test: Exemplar::Data(), Exemplar::Data(ns,nv), Exemplar::Data::size()
  // -------------------------------------------------------------------------------------
  Exemplar::Data A;
  EXPECT_EQ( 0, A.size(0) );
  EXPECT_EQ( 0, A.size(1) );

  Exemplar::Data B(17,3);
  EXPECT_EQ( 17, B.size()  );
  EXPECT_EQ( 17, B.size(0) );
  EXPECT_EQ(  3, B.size(1) );
}


// =======================================================================================
TEST( test_edata, resize ) {
  // -------------------------------------------------------------------------------------
  // Test: Exemplar::Data::destroy(), Exemplar::Data::resize(ns,nv)
  // -------------------------------------------------------------------------------------
  Exemplar::Data A;
  EXPECT_EQ( 0, A.size(0) );
  EXPECT_EQ( 0, A.size(1) );

  A.resize(17,3);
  EXPECT_EQ( 17, A.size()  );
  EXPECT_EQ( 17, A.size(0) );
  EXPECT_EQ(  3, A.size(1) );

  A.destroy();
  EXPECT_EQ( 0, A.size(0) );
  EXPECT_EQ( 0, A.size(1) );

  
}



// =======================================================================================
TEST( test_edata, utest_internal ) {
  // -------------------------------------------------------------------------------------
  const int32_t small_ns = 5;
  const int32_t small_nv = 3;
  const int32_t big_ns   = 15;
  const int32_t big_nv   = 13;
  Exemplar::Data A(small_ns,small_nv);
  EXPECT_EQ( small_ns, A.size(0) );
  EXPECT_EQ(  small_nv, A.size(1) );

  makeSingle( A );
  for ( int32_t r=0; r<small_ns; r++ ) {
    for ( int32_t c=0; c<small_nv; c++ ) {
      //std::cout << ELEM(r,c) << "\t" << A.get( r, c ) << "\n";
      EXPECT_DOUBLE_EQ( ELEM(r,c), A.get( r, c ) );
    }
  }

  for ( int32_t c=0; c<small_nv; c++ ) {
    for ( int32_t r=0; r<small_ns; r++ ) {
      EXPECT_DOUBLE_EQ( ELEM(r,c), A.get( r, c ) );
    }
  }

  makeSingle( A, big_ns, big_nv );
  for ( int32_t r=0; r<big_ns; r++ ) {
    for ( int32_t c=0; c<big_nv; c++ ) {
      //std::cout << ELEM(r,c) << "\t" << A.get( r, c ) << "\n";
      EXPECT_DOUBLE_EQ( ELEM(r,c), A.get( r, c ) );
    }
  }

  for ( int32_t c=0; c<big_nv; c++ ) {
    for ( int32_t r=0; r<big_ns; r++ ) {
      EXPECT_DOUBLE_EQ( ELEM(r,c), A.get( r, c ) );
    }
  }
  
}

// =======================================================================================
TEST( test_edata, copy) {
  // -------------------------------------------------------------------------------------
  // Test: Exemplar::Data::copy()
  // -------------------------------------------------------------------------------------
  const int32_t ns = 37;
  const int32_t nv = 13;
  Exemplar::Data A( ns, nv );
  Exemplar::Data B( 3, 7 );
  makeSingle( A );

  EXPECT_EQ( ns, A.size(0) );
  EXPECT_EQ( nv, A.size(1) );
  EXPECT_EQ( 3,  B.size(0) );
  EXPECT_EQ( 7,  B.size(1) );

  B.copy( A );
  EXPECT_EQ( ns, B.size(0) );
  EXPECT_EQ( nv, B.size(1) );

  for ( int32_t i=0; i<ns; i++ ) {
    for ( int32_t j=0; j<nv; j++ ) {
      EXPECT_DOUBLE_EQ( A.get(i,j), B.get(i,j) );
    }
  }
  
}
  
// =======================================================================================
TEST( test_edata, get_set ) {
  // -------------------------------------------------------------------------------------
  // Test: Exemplar::Data::get(), Exemplar::Data::set()
  // -------------------------------------------------------------------------------------
  const int32_t small_ns = 5;
  const int32_t small_nv = 3;
  Exemplar::Data A(small_ns,small_nv);
  EXPECT_EQ( small_ns, A.size(0) );
  EXPECT_EQ( small_nv, A.size(1) );

  makeSingle( A );
  for ( int32_t r=0; r<small_ns; r++ ) {
    for ( int32_t c=0; c<small_nv; c++ ) {
      //std::cout << ELEM(r,c) << "\t" << A.get( r, c ) << "\n";
      EXPECT_DOUBLE_EQ( ELEM(r,c), A.get( r, c ) );
    }
  }

  A.set( 1, 2, 33.44 );
  A.set( 2, 1, 17.83 );

  EXPECT_DOUBLE_EQ( 33.44, A.get( 1, 2 ) );
  EXPECT_DOUBLE_EQ( 17.83, A.get( 2, 1 ) );

  A.set( 1, 2, ELEM( 1, 2 ) );
  A.set( 2, 1, ELEM( 2, 1 ) );

  for ( int32_t r=0; r<small_ns; r++ ) {
    real8_t *row = A.get( r );
    for ( int32_t c=0; c<small_nv; c++ ) {
      EXPECT_DOUBLE_EQ( ELEM(r,c), row[c] );
    }
  }
}






// =======================================================================================
TEST( test_exemplar, construct ) {
  // -------------------------------------------------------------------------------------
  // Test:  Exemplar(), Exemplar(Meta), Exemplar(ns,ni), Exemplar(ns,ni,no)
  //        nSample(), nInput(), nOutput, hasOutput()
  // -------------------------------------------------------------------------------------
  Exemplar::Meta MP( 5, 3, 2 );
  Exemplar::Meta MS( 7,4 );

  Exemplar EZ;
  Exemplar EP1( MP );
  Exemplar ES1( MS );

  EXPECT_EQ( 0, EZ.nSample() );
  EXPECT_EQ( 0, EZ.nInput() );
  EXPECT_EQ( 0, EZ.nOutput() );
  EXPECT_FALSE( EZ.hasOutput() );
 
  EXPECT_EQ( 5, EP1.nSample() );
  EXPECT_EQ( 3, EP1.nInput() );
  EXPECT_EQ( 2, EP1.nOutput() );
  EXPECT_TRUE(  EP1.hasOutput() );
 
  EXPECT_EQ( 7, ES1.nSample() );
  EXPECT_EQ( 4, ES1.nInput() );
  EXPECT_EQ( 0, ES1.nOutput() );
  EXPECT_FALSE( ES1.hasOutput() );

  Exemplar EP2( 31, 17, 13 );
  Exemplar ES2( 23, 11 );

  EXPECT_EQ( 31, EP2.nSample() );
  EXPECT_EQ( 17, EP2.nInput() );
  EXPECT_EQ( 13, EP2.nOutput() );
  EXPECT_TRUE(   EP2.hasOutput() );
 
  EXPECT_EQ( 23, ES2.nSample() );
  EXPECT_EQ( 11, ES2.nInput() );
  EXPECT_EQ( 0,  ES2.nOutput() );
  EXPECT_FALSE(  ES2.hasOutput() );
}


// =======================================================================================
TEST( test_exemplar, resize ) {
  // -------------------------------------------------------------------------------------
  // Test:  Exemplar().resize()
  // -------------------------------------------------------------------------------------
  {
    Exemplar E1;
    EXPECT_EQ( 0, E1.nSample() );
    EXPECT_EQ( 0, E1.nInput() );
    EXPECT_EQ( 0, E1.nOutput() );
    EXPECT_FALSE( E1.hasOutput() );
    
    E1.resize( 23, 14 );
    EXPECT_EQ( 23, E1.nSample() );
    EXPECT_EQ( 14, E1.nInput() );
    EXPECT_EQ(  0, E1.nOutput() );
    EXPECT_FALSE( E1.hasOutput() );
    
    E1.resize_output( 23, 18 );
    EXPECT_EQ( 23, E1.nSample() );
    EXPECT_EQ( 14, E1.nInput() );
    EXPECT_EQ( 18, E1.nOutput() );
    EXPECT_TRUE( E1.hasOutput() );
  }

  
  {
    Exemplar E1;
    EXPECT_EQ( 0, E1.nSample() );
    EXPECT_EQ( 0, E1.nInput() );
    EXPECT_EQ( 0, E1.nOutput() );
    EXPECT_FALSE( E1.hasOutput() );
    
    E1.resize( 41, 19, 11 );
    EXPECT_EQ( 41, E1.nSample() );
    EXPECT_EQ( 19, E1.nInput() );
    EXPECT_EQ( 11, E1.nOutput() );
    EXPECT_TRUE( E1.hasOutput() );
    
    E1.resize_input(  23, 8 );
    E1.resize_output( 23, 0 );
    EXPECT_EQ( 23, E1.nSample() );
    EXPECT_EQ(  8, E1.nInput() );
    EXPECT_EQ(  0, E1.nOutput() );
    EXPECT_FALSE( E1.hasOutput() );
  }

}

// =======================================================================================
TEST( test_exemplar, get_set ) {
  // -------------------------------------------------------------------------------------
  // Test:  setIn(), setOut(), getIn() getOut()
  // -------------------------------------------------------------------------------------
  const int32_t small_ns = 5;
  const int32_t small_ni = 4;
  const int32_t small_no = 3;

  const int32_t big_ns = 35;
  const int32_t big_ni = 24;
  const int32_t big_no = 13;

  Exemplar A(small_ns,small_ni,small_no);
  EXPECT_EQ( small_ns, A.nSample() );
  EXPECT_EQ( small_ni, A.nInput() );
  EXPECT_EQ( small_no, A.nOutput() );

  Exemplar::Data* AI = A.getIn();
  Exemplar::Data* AO = A.getOut();

  makePair( *AI, *AO );
  for ( int32_t r=0; r<small_ns; r++ ) {
    for ( int32_t c=0; c<small_ni; c++ ) {
      EXPECT_DOUBLE_EQ( ELEM( 1, r, c ), A.getIn( r, c ) );
    }
    for ( int32_t c=0; c<small_no; c++ ) {
      EXPECT_DOUBLE_EQ( ELEM( 2, r, c ), A.getOut( r, c ) );
    }
  }

  A.resize( big_ns, big_ni, big_no );
  makePair( *AI, *AO );
  for ( int32_t r=0; r<big_ns; r++ ) {
    real8_t* row = A.getIn(r);
    for ( int32_t c=0; c<big_ni; c++ ) {
      EXPECT_DOUBLE_EQ( ELEM( 1, r, c ), row[c] );
    }
    row = A.getOut(r);
    for ( int32_t c=0; c<big_no; c++ ) {
      EXPECT_DOUBLE_EQ( ELEM( 2, r, c ), row[c] );
    }
  }

}
  
// =======================================================================================
TEST( test_exemplar, copy ) {
  // -------------------------------------------------------------------------------------
  // Test:  copy
  // -------------------------------------------------------------------------------------
  Dice* dd = Dice::TestDice();

  const int32_t ns = 37;
  const int32_t ni = 11;
  const int32_t no = 7;
  
  Exemplar P( ns, ni, no );
  Exemplar PB, SI, SO;

  randomize( P, dd );

  PB.copy( P );
  SI.copy( P, INPUT );
  SO.copy( P, OUTPUT );

  EXPECT_EQ( ns, P.nSample() );
  EXPECT_EQ( ni, P.nInput() );
  EXPECT_EQ( no, P.nOutput() );
  
  EXPECT_EQ( ns, PB.nSample() );
  EXPECT_EQ( ni, PB.nInput() );
  EXPECT_EQ( no, PB.nOutput() );
  
  for ( int32_t r=0; r<ns; r++ ) {
    for ( int32_t c=0; c<ni; c++ ) {
      EXPECT_DOUBLE_EQ( P.getIn( r, c ), PB.getIn( r, c ) );
      EXPECT_DOUBLE_EQ( P.getIn( r, c ), SI.getIn( r, c ) );
    }
    for ( int32_t c=0; c<no; c++ ) {
      EXPECT_DOUBLE_EQ( P.getOut( r, c ), PB.getOut( r, c ) );
      EXPECT_DOUBLE_EQ( P.getOut( r, c ), SO.getIn( r, c ) );
    }
  }
}

#define EXPECT_DATA_EQ(_A,_B) {                         \
    int32_t _ns = _A->size(0);                          \
    int32_t _nv = _A->size(1);                          \
    for ( int32_t i=0; i<_ns; i++ ) {                   \
      for ( int32_t j=0; j<_nv; j++ ) {                 \
        EXPECT_DOUBLE_EQ( _A->get(i,j), _B->get(i,j) ); \
      } } }

#define EXPECT_META_EQ(_A,_B) {                 \
    EXPECT_EQ( _A.n_sample, _B.n_sample );      \
    EXPECT_EQ( _A.n_input,  _B.n_input  );      \
    EXPECT_EQ( _A.n_output, _B.n_output );      \
  }

// =======================================================================================
TEST( test_exemplar, read_write ) {
  // -------------------------------------------------------------------------------------
  // Test:  copy
  // -------------------------------------------------------------------------------------
  Dice* dd = Dice::TestDice();

  const int32_t ns = 37;
  const int32_t ni = 11;
  const int32_t no = 7;
  
  Exemplar P( ns, ni, no );
  Exemplar PB, SI, SO;

  randomize( P, dd );

  PB.copy( P );
  SI.copy( P, INPUT );
  SO.copy( P, OUTPUT );

  EXPECT_EQ( ns, P.nSample() );
  EXPECT_EQ( ni, P.nInput() );
  EXPECT_EQ( no, P.nOutput() );
  
  EXPECT_EQ( ns, PB.nSample() );
  EXPECT_EQ( ni, PB.nInput() );
  EXPECT_EQ( no, PB.nOutput() );
  
  for ( int32_t r=0; r<ns; r++ ) {
    for ( int32_t c=0; c<ni; c++ ) {
      EXPECT_DOUBLE_EQ( P.getIn( r, c ), PB.getIn( r, c ) );
      EXPECT_DOUBLE_EQ( P.getIn( r, c ), SI.getIn( r, c ) );
    }
    for ( int32_t c=0; c<no; c++ ) {
      EXPECT_DOUBLE_EQ( P.getOut( r, c ), PB.getOut( r, c ) );
      EXPECT_DOUBLE_EQ( P.getOut( r, c ), SO.getIn( r, c ) );
    }
  }

  // -------------------------------------------------------------------------------------
  {
    P.write_meta( "/tmp/MB1" );
    P.write_meta( "/tmp/MB2", BOTH );
    P.write_meta( "/tmp/MI",  INPUT );
    P.write_meta( "/tmp/MO",  OUTPUT );

    Exemplar::Meta MB1, MB2, MI, MO;
    MB1.read( "/tmp/MB1" );
    MB2.read( "/tmp/MB2" );
    MI.read( "/tmp/MI" );
    MO.read( "/tmp/MO" );

    EXPECT_EQ( ns, MB1.n_sample ); EXPECT_EQ( ni, MB1.n_input ); EXPECT_EQ( no, MB1.n_output );
    EXPECT_EQ( ns, MB2.n_sample ); EXPECT_EQ( ni, MB2.n_input ); EXPECT_EQ( no, MB2.n_output );
    EXPECT_EQ( ns, MI.n_sample );  EXPECT_EQ( ni, MI.n_input );  EXPECT_EQ( 0,  MI.n_output );
    EXPECT_EQ( ns, MO.n_sample );  EXPECT_EQ( no, MO.n_input );  EXPECT_EQ( 0,  MO.n_output );
  }

  // -------------------------------------------------------------------------------------
  {
    P.write( "/tmp/AB.m", "/tmp/AB.d", BOTH   );
    P.write( "/tmp/AI.m", "/tmp/AI.d", INPUT  );
    P.write( "/tmp/AO.m", "/tmp/AO.d", OUTPUT );

    P.write( "/tmp/BB.d",  NOMETA, BOTH   );
    P.write( "/tmp/BI.d",  NOMETA, INPUT  );
    P.write( "/tmp/BO.d",  NOMETA, OUTPUT );

    P.write( "/tmp/CB.md", META,   BOTH   );
    P.write( "/tmp/CI.md", META,   INPUT  );
    P.write( "/tmp/CO.md", META,   OUTPUT );

    P.write( "/tmp/DB.d",  NOMETA );
    P.write( "/tmp/EB.md", META   );

    P.write( "/tmp/FB.md", BOTH   );
    P.write( "/tmp/FI.md", INPUT  );
    P.write( "/tmp/FO.md", OUTPUT );

    P.write( "/tmp/GB.md", BOTH   );

    
    Exemplar::Meta M1( "/tmp/AB.m" ); EXPECT_META_EQ( M1, P.getMeta() );
    Exemplar::Meta M2( "/tmp/AI.m" ); EXPECT_META_EQ( M2, P.getMeta(INPUT) );
    Exemplar::Meta M3( "/tmp/AO.m" ); EXPECT_META_EQ( M3, P.getMeta(OUTPUT) );

    {
      Exemplar K( "/tmp/AB.m", "/tmp/AB.d" );
      EXPECT_DATA_EQ( P.getIn(),  K.getIn() );
      EXPECT_DATA_EQ( P.getOut(), K.getOut() );
    }

    {
      Exemplar K( "/tmp/AI.m", "/tmp/AI.d" );
      EXPECT_DATA_EQ( P.getIn(),  K.getIn() );
    }

    {
      Exemplar K( "/tmp/AO.m", "/tmp/AO.d" );
      EXPECT_DATA_EQ( P.getOut(),  K.getIn() );
    }

    {
      Exemplar K( "/tmp/AB.m", "/tmp/BB.d" );
      EXPECT_DATA_EQ( P.getIn(),  K.getIn() );
      EXPECT_DATA_EQ( P.getOut(), K.getOut() );
    }

    {
      Exemplar K( "/tmp/AI.m", "/tmp/BI.d" );
      EXPECT_DATA_EQ( P.getIn(),  K.getIn() );
    }

    {
      Exemplar K( "/tmp/AO.m", "/tmp/BO.d" );
      EXPECT_DATA_EQ( P.getOut(),  K.getIn() );
    }

    {
      Exemplar K( "/tmp/CB.md" );
      EXPECT_DATA_EQ( P.getIn(),  K.getIn() );
      EXPECT_DATA_EQ( P.getOut(), K.getOut() );
    }

    {
      Exemplar K( "/tmp/CI.md" );
      EXPECT_DATA_EQ( P.getIn(),  K.getIn() );
    }

    {
      Exemplar K( "/tmp/CO.md" );
      EXPECT_DATA_EQ( P.getOut(),  K.getIn() );
    }

    {
      Exemplar K( "/tmp/AB.m", "/tmp/DB.d" );
      EXPECT_DATA_EQ( P.getIn(),  K.getIn() );
      EXPECT_DATA_EQ( P.getOut(), K.getOut() );
    }

    {
      Exemplar K( "/tmp/EB.md" );
      EXPECT_DATA_EQ( P.getIn(),  K.getIn() );
      EXPECT_DATA_EQ( P.getOut(), K.getOut() );
    }

    {
      Exemplar K( "/tmp/FB.md" );
      EXPECT_DATA_EQ( P.getIn(),  K.getIn() );
      EXPECT_DATA_EQ( P.getOut(), K.getOut() );
    }

    {
      Exemplar K( "/tmp/FI.md" );
      EXPECT_DATA_EQ( P.getIn(),  K.getIn() );
    }

    {
      Exemplar K( "/tmp/FO.md" );
      EXPECT_DATA_EQ( P.getOut(),  K.getIn() );
    }

    {
      Exemplar K( "/tmp/GB.md" );
      EXPECT_DATA_EQ( P.getIn(),  K.getIn() );
      EXPECT_DATA_EQ( P.getOut(), K.getOut() );
    }

  }
  
}


} // end namespace


// =======================================================================================
// **                            U T E S T _ E X E M P L A R                            **
// ======================================================================== END FILE =====
