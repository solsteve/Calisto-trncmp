#/ ====================================================================== BEGIN FILE =====
#/ **                            NerveNet - C M A K E L I S T                           **
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
#/ @date    2019-Sep-07
#/
#/ =======================================================================================

project ( nervenet CXX )

set ( APP1_NAME "make_network" )
set ( APP2_NAME "train_network" )
set ( APP3_NAME "validate_network" )
set ( APP4_NAME "execute_network" )

set ( CMAKE_CXX_DIRECTORY ${PROJECT_BINARY_DIR}/temp )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_executable ( ${APP1_NAME} make_network.cc )
add_executable ( ${APP2_NAME} train_network.cc )
add_executable ( ${APP3_NAME} validate_network.cc )
add_executable ( ${APP4_NAME} execute_network.cc )

target_link_libraries ( ${APP1_NAME} callisto )
target_link_libraries ( ${APP2_NAME} callisto )
target_link_libraries ( ${APP3_NAME} callisto )
target_link_libraries ( ${APP4_NAME} callisto )

install (TARGETS ${APP1_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install (TARGETS ${APP2_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install (TARGETS ${APP3_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install (TARGETS ${APP4_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

#/ =======================================================================================
#/ **                            NerveNet - C M A K E L I S T                           **
#/ =========================================================================== END FILE ==
