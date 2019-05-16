#/ ====================================================================== BEGIN FILE =====
#/ **                           TicTacToe - C M A K E L I S T                           **
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

project ( tictactoe CXX )

set ( APP1_NAME "build_table" )

set ( CMAKE_CXX_DIRECTORY ${PROJECT_BINARY_DIR}/temp )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable ( ${APP1_NAME} build_table.cc state.cc state_table.cc )

target_link_libraries ( ${APP1_NAME} callisto )

install (TARGETS ${APP1_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

#/ =======================================================================================
#/ **                            Convert - C M A K E L I S T                            **
#/ =========================================================================== end FILE ==
