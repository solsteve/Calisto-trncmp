#/ ====================================================================== BEGIN FILE =====
#/ **                             CTests - C M A K E L I S T                            **
#/ =======================================================================================
#/ **                                                                                   **
#/ **  Copyright (c) 2019, Stephen W. Soliday                                           **
#/ **                      stephen.soliday@trncmp.org                                   **
#/ **                      http://research.trncmp.org                                   **
#/ **                                                                                   **
#/ **  -------------------------------------------------------------------------------  **
#/ **                                                                                   **
#/ **  This program is free software: you can redistribute it and/or modify it under    **
#/ **  the terms of the GNU General Public License as published by the Free Software    **
#/ **  Foundation, either version 3 of the License, or (at your option)                 **
#/ **  any later version.                                                               **
#/ **                                                                                   **
#/ **  This program is distributed in the hope that it will be useful, but WITHOUT      **
#/ **  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS    **
#/ **  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.   **
#/ **                                                                                   **
#/ **  You should have received a copy of the GNU General Public License along with     **
#/ **  this program. If not, see <http://www.gnu.org/licenses/>.                        **
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

project ( ctest CXX )

file ( GLOB csrc "ctest_*.cc" )

foreach ( ct ${csrc} )
  get_filename_component ( _exec ${ct} NAME_WE )

  set ( CMAKE_CXX_DIRECTORY ${PROJECT_BINARY_DIR}/temp )

  add_executable ( ${_exec} ${ct} )

  target_link_libraries ( ${_exec} callisto )

  install (TARGETS ${_exec}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
  
endforeach ( )

#/ =======================================================================================
#/ **                             CTests - C M A K E L I S T                            **
#/ =========================================================================== end FILE ==
