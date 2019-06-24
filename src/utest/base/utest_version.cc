// ====================================================================== BEGIN FILE =====
// **                             U T E S T _ V E R S I O N                             **
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
/** @brief  Automated testing for version.
 *  @file   utest_version.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Apr-22
 *
 *  Provides automated testing for version.
 */
// =======================================================================================


#include <limits.h>
#include "trncmp.hh"
#include "gtest/gtest.h"


namespace {


TEST(version, Positive) {
  EXPECT_STREQ("3.0.1", trncmpVersion());
}


TEST(version, Negative) {
  EXPECT_STRNE("3.1.1", trncmpVersion());
}


} // end namespace


// =======================================================================================
// **                             U T E S T _ V E R S I O N                             **
// ======================================================================== END FILE =====
