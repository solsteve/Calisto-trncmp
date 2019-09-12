#/ ====================================================================== BEGIN FILE =====
#/ **                             Source - C M A K E L I S T                            **
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
#/ @date    2019-04-11
#/
#/ =======================================================================================
project ( src CXX )

file(GLOB LIB_SRC_FILES source/*.cc source/nns/*.cc)
file(GLOB LIB_HDR_FILES include/*.hh include/astro/*.hh include/nns/*.hh)

add_library( callisto STATIC ${LIB_SRC_FILES} )
target_include_directories( callisto PUBLIC include )

add_subdirectory ( ctest )
add_subdirectory ( utest )

install (TARGETS callisto
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib )

install (FILES ${LIB_HDR_FILES} DESTINATION include)


#/ =======================================================================================
#/ **                             Source - C M A K E L I S T                            **
#/ =========================================================================== END FILE ==
