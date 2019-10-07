#/ ====================================================================== BEGIN FILE =====
#/ **                           Top Level - C M A K E L I S T                           **
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
#/ @date    2019-Apr-22
#/
#/ =======================================================================================

cmake_minimum_required( VERSION 3.10 )

project ( Callisto CXX )

set ( PROJECT_DESCRIPTION "Callisto CPP Libraries" )
set ( PROJECT_URL "https://github.com/solsteve" )

include ( GNUInstallDirs )

set ( Callisto_LIBNAME callisto )
set ( Callisto_MAJOR_VERSION 3 )
set ( Callisto_MINOR_VERSION 0 )
set ( Callisto_PATCH_VERSION 0.dev )
set ( Callisto_VERSION "${\
Callisto_MAJOR_VERSION}.\
${Callisto_MINOR_VERSION}.\
${Callisto_PATCH_VERSION}" )

set ( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" )
message ( STATUS "Path = ${CMAKE_MODULE_PATH}" )

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

find_package(BLAS)
find_package(LAPACK)
if(LAPACK_FOUND AND BLAS_FOUND)
  set(lapackblas_libraries ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})
endif()


  
#/ =======================================================================================

if ( "${CMAKE_BUILD_TYPE}" STREQUAL "" )

  message ( STATUS "Build type not explicitly set. Trying to guess..." )
  get_filename_component ( BINDIR ${PROJECT_BINARY_DIR} NAME )
  
  if ( ${BINDIR} MATCHES "RELEASE" )
    set ( CMAKE_BUILD_TYPE "RELEASE" )
    message ( STATUS "Set to ${CMAKE_BUILD_TYPE}" )
  elseif ( ${BINDIR} MATCHES "DEBUG" )
    set ( CMAKE_BUILD_TYPE "DEBUG" )
    message ( STATUS "Set to ${CMAKE_BUILD_TYPE}" )
  else ( )
    message ( WARNING "Unable to deduce build type. Use -DCMAKE_BUILD_TYPE=<RELEASE/DEBUG>" )
  endif ( ${BINDIR} MATCHES "RELEASE" )
  
else ( )
  message ( STATUS "Build Type is ${CMAKE_BUILD_TYPE}" )
endif ( "${CMAKE_BUILD_TYPE}" STREQUAL "" )

#/ =======================================================================================

set ( GARCH "\
-fverbose-asm -ansi -fsigned-char -funsigned-bitfields -fshort-enums \
-funroll-loops -march=corei7 -mtune=corei7 -fipa-sra -fopenmp" )

set ( GWARN "\
-W -Wall -Wextra -Wfloat-equal -Wshadow -Wcast-align -Wredundant-decls \
-Wundef -Wpointer-arith -Wsign-compare -Wconversion -Wpacked -Wno-multichar \
-Wmissing-noreturn -Wunused-macros -Wendif-labels -Wformat -Wformat-security \
-Wswitch-default -Wswitch-enum -Wsynth -Wreorder -Winline -Weffc++ \
-fcheck-new -Wsign-promo -Woverloaded-virtual -Wno-unused-result" )

set ( GFORM "-std=gnu++11" )
set ( GFIX  "--param max-inline-insns-single=2000" )

set ( CMAKE_CXX_FLAGS_RELEASE "-O3    ${GWARN} ${GARCH} ${GFORM} ${GFIX}" )
set ( CMAKE_CXX_FLAGS_DEBUG   "-O1 -g ${GWARN} ${GARCH} ${GFORM}" )

#/ =======================================================================================

#set( CMAKE_BUILD_TYPE Release )

set ( CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/callisto )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

#/ =======================================================================================

if ( ${CMAKE_BUILD_TYPE} MATCHES "DEBUG" )
  message ( STATUS "DEBUG Compile Options: ${CMAKE_CXX_FLAGS_DEBUG}" )
else ( )
  if ( ${CMAKE_BUILD_TYPE} MATCHES "RELEASE" )
    message ( STATUS "RELEASE Compile Options: ${CMAKE_CXX_FLAGS_RELEASE}" )
  else ( )
    message ( STATUS "Compiler option could not be set" )
  endif ( )
endif ( )

#/ =======================================================================================
#/ Add the sub-builds
#/ ---------------------------------------------------------------------------------------

add_subdirectory ( src )
add_subdirectory ( apps )

#/ =======================================================================================

#include(CTest)
enable_testing()


#/ =======================================================================================

#option(BUILD_DOCS "Build documentation" ON)

if (BUILD_DOCS)
find_package(Doxygen)
if (DOXYGEN_FOUND)
  
  set(DOXYGEN_IN  ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

  message("Doxygen build started source=${CMAKE_CURRENT_SOURCE_DIR}/src")

  add_custom_target( doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
else  (BUILD_DOCS)
  message("No DOC will be built")
endif (BUILD_DOCS)

#/ =======================================================================================
#/ **                           Top Level - C M A K E L I S T                           **
#/ =========================================================================== END FILE ==
