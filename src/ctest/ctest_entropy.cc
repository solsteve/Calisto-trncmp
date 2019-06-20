// ====================================================================== BEGIN FILE =====
// **                             C T E S T _ E N T R O P Y                             **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2019, Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
// **                                                                                   **
// **  -------------------------------------------------------------------------------  **
// **                                                                                   **
// **  This program is free software: you can redistribute it and/or modify it under    **
// **  the terms of the GNU General Public License as published by the Free Software    **
// **  Foundation, either version 3 of the License, or (at your option)                 **
// **  any later version.                                                               **
// **                                                                                   **
// **  This program is distributed in the hope that it will be useful, but WITHOUT      **
// **  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS    **
// **  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.   **
// **                                                                                   **
// **  You should have received a copy of the GNU General Public License along with     **
// **  this program. If not, see <http://www.gnu.org/licenses/>.                        **
// **                                                                                   **
// ----- Modification History ------------------------------------------------------------
//
/** @brief Test the Version
 *  @file   ctest_entropy.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-14
 *
 *  This is a test of AppOptions
 */
// =======================================================================================


#include <Entropy.hh>
#include <RunStat.hh>
#include <StopWatch.hh>

// =======================================================================================
int main( void ) {
  // -------------------------------------------------------------------------------------
  const size_t N_SAMP = 1000000000L;

  Entropy* ent = Entropy::DEFAULT();
  StopWatch W;

  { // -----------------------------------------------------------------------------------
    ent->seed_set();
    RunStat T("BYTE");
    W.reset();
    for ( size_t i=0; i<N_SAMP; i++ ) {
      T.update( ent->U8() );
    }
    std::cout << ((real8_t)N_SAMP / W.check())*1.0e-6 << " samples / second\n";

    T.report( );
    std::cout << 0 << " " << 0x7F << " " << 0xFF << "\n\n";
  }

  { // -----------------------------------------------------------------------------------
    ent->seed_set();
    RunStat T("WORD");
    W.reset();
    for ( size_t i=0; i<N_SAMP; i++ ) {
      T.update( ent->U16() );
    }
    std::cout << ((real8_t)N_SAMP / W.check())*1.0e-6 << " samples / second\n";

    T.report( );
    std::cout << 0 << " " << 0x7FFF << " " << 0xFFFF << "\n\n";
  }

  { // -----------------------------------------------------------------------------------
    ent->seed_set();
    RunStat T("DWRD *");
    W.reset();
    for ( size_t i=0; i<N_SAMP; i++ ) {
      T.update( ent->U32() );
    }
    std::cout << ((real8_t)N_SAMP / W.check())*1.0e-6 << " M samples / second\n";

    T.report( );
    std::cout << 0.0 << " " << (real8_t)(0x7FFFFFFFU) << " " << (real8_t)(0xFFFFFFFFU) << "\n\n";
  }

  { // -----------------------------------------------------------------------------------
    ent->seed_set();
    RunStat T("QWRD - xoshiro256**");
    W.reset();
    for ( size_t i=0; i<N_SAMP; i++ ) {
      T.update( ent->U64() );
    }
    std::cout << ((real8_t)N_SAMP / W.check())*1.0e-6 << " M samples / second\n";

    T.report( );
    std::cout << 0.0 << " " << (real8_t)(0x7FFFFFFFFFFFFFFFUL) << " " << (real8_t)(0xFFFFFFFFFFFFFFFFUL) << "\n\n";
  }

  { // -----------------------------------------------------------------------------------
    ent->seed_set();
    RunStat T("FLOAT");
    W.reset();
    for ( size_t i=0; i<N_SAMP; i++ ) {
      T.update( ent->R32() );
    }
    std::cout << ((real8_t)N_SAMP / W.check())*1.0e-6 << " M samples / second\n";

    T.report( );
    std::cout << "0 0.5 1\n\n";
  }

  { // -----------------------------------------------------------------------------------
    ent->seed_set();
    RunStat T("DOUBLE");
    W.reset();
    for ( size_t i=0; i<N_SAMP; i++ ) {
      T.update( ent->R64() );
    }
    std::cout << ((real8_t)N_SAMP / W.check())*1.0e-6 << " M samples / second\n";

    T.report( );
    std::cout << "0 0.5 1\n\n";
  }

  return 0;
}

// =======================================================================================
// **                              C T E S T _ A P P O P T                              **
// ======================================================================== END FILE =====
