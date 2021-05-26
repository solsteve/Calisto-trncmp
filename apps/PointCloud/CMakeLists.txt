#/ ====================================================================== BEGIN FILE =====
#/ **                           PointCloud - C M A K E L I S T                           **
#/ =======================================================================================
#/ **                                                                                   **
#/ **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
#/ **                                                                                   **
#/ **  Copyright (c) 2020, Stephen W. Soliday                                           **
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
#/ @date    2020-10-15
#/
#/ =======================================================================================

project ( PointCloud CXX )

file ( GLOB progs "*.cc" )
file ( GLOB extra "lib/*.cc" )

foreach ( ft ${progs} )
  get_filename_component ( _exec ${ft} NAME_WE )

  set ( CMAKE_CXX_DIRECTORY ${PROJECT_BINARY_DIR}/temp )

  include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ./lib )

  add_executable ( ${_exec} ${ft} ${extra} )
  
  target_link_libraries ( ${_exec} callisto )

  install (TARGETS ${_exec}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
  
endforeach ( )

#/ =======================================================================================
#/ **                            Convert - C M A K E L I S T                            **
#/ =========================================================================== END FILE ==
