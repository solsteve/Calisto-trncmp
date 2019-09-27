#/ ====================================================================== BEGIN FILE =====
#/ **                             fuzzy - C M A K E L I S T                             **
#/ =======================================================================================
#/ **                                                                                   **
#/ **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
#/ **                                                                                   **
#/ **  Copyright (c) 2019, Stephen W. Soliday                                           **
#/ **                      stephen.soliday@trncmp.org                                   **
#/ **                      http://research.trncmp.org                                   **
#/ **                                                                                   **
#/ **  -------------------------------------------------------------------------------  **
#/ **                                                                                   **
#/ **  Callisto is free software: you can redistribute it and/or modify it under the    **
#/ **  terms of the GNU General Public License as published by the Free Software        **
#/ **  Foundation, either version 3 of the License, or (at your option)                 **
#/ **  any later version.                                                               **
#/ **                                                                                   **
#/ **  Callisto is distributed in the hope that it will be useful, but WITHOUT          **
#/ **  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS    **
#/ **  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.   **
#/ **                                                                                   **
#/ **  You should have received a copy of the GNU General Public License along with     **
#/ **  Callisto. If not, see <https:#/www.gnu.org/licenses/>.                           **
#/ **                                                                                   **
#/ ----- Modification History ------------------------------------------------------------
#/
#/ @brief   Build environment.
#/
#/ @details Provides a common build environment.
#/
#/ @author  Stephen W. Soliday
#/ @date    2019-Apr-28
#/
#/ =======================================================================================

project( fuzzy CXX )

add_executable(${PROJECT_NAME} ../main.cc
  utest_fset
  utest_group
  utest_partition
  )

target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main callisto ${lapackblas_libraries})
add_test(All${PROJECT_NAME}InBase ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION test
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

#/ =======================================================================================
#/ **                             fuzzy - C M A K E L I S T                             **
#/ =========================================================================== END FILE ==
