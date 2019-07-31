// ====================================================================== BEGIN FILE =====
// **                                     T A B L E                                     **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 1993-2019, Stephen W. Soliday                                      **
// **                           stephen.soliday@trncmp.org                              **
// **                           http://research.trncmp.org                              **
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
/** @brief  Table (2D Array)
 *  @file   Table.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-26 CMake refactorization.
 *
 *  Provides the methods for a 2D Table
 *  @see Statistics, Covariance, and PCA
 */
// =======================================================================================

#include <Table.hh>
#include <FileTool.hh>

#define INIT_VAR(a) data(a), nsamp(a), nvar(a), nalloc(a)

TLOGGER_REFERENCE( Table, logger );


// =======================================================================================
/** @brief Resize.
 *  @param[in] ns number of samples   (row).
 *  @param[in] nv number of variables (col).
 *
 *  Reallocate space if required.
 */
// ---------------------------------------------------------------------------------------
void Table::resize( const size_t ns, const size_t nv ) {
  // -------------------------------------------------------------------------------------
  size_t new_alloc = ns * nv;
  if ( new_alloc > nalloc ) {
    destroy();
    data = new real8_t[ new_alloc ];
    nalloc = new_alloc;
  }
  nsamp = ns;
  nvar  = nv;      
}


// =======================================================================================
/** @brief Destroy.
 *
 *  Deallocatedata buffer.
 */
// ---------------------------------------------------------------------------------------
void Table::destroy( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<real8_t*>(0) != data ) {
    delete[] data;
  }
  nsamp  = 0;
  nvar   = 0;
  nalloc = 0;
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
Table::Table( void ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] ns number of samples   (row).
 *  @param[in] nv number of variables (col).
 */
// ---------------------------------------------------------------------------------------
Table::Table( const size_t ns, const size_t nv ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  resize( ns, nv );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] tab reference to a source Table.
 */
// ---------------------------------------------------------------------------------------
Table::Table( const Table& tab ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  copy( tab );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] fspc file specification for the source of this Table.
 */
// ---------------------------------------------------------------------------------------
Table::Table( const std::string fspc ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  read_ascii( fspc );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Table::~Table( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}


// =======================================================================================
/** @brief Set.
 *  @param[in] value value to with. (default: 0)
 *
 *  Set every element of this table to the same value.
 */
// ---------------------------------------------------------------------------------------
void Table::set( const real8_t value ) {
  // -------------------------------------------------------------------------------------
  const size_t n = nsamp * nvar;
  for ( size_t i=0; i<n; i++ ) {
    data[i] = value;
  }
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] tab reference to a source Table.
 *
 *  Copy the contents of the source Table tab into this Table.
 */
// ---------------------------------------------------------------------------------------
void Table::copy( const Table& tab ) {
  // -------------------------------------------------------------------------------------
  resize( tab.nsamp, tab.nvar );
  const size_t n = nsamp * nvar;
  for ( size_t i=0; i<n; i++ ) {
    data[i] = tab.data[i];
  }
}


// =======================================================================================
/** @brief Row Pointer.
 *  @param[out] row  pointer to a buffer to copy the row.
 *  @param[in]  sidx index to the sample.
 *
 *  Copy the contents of the row at sample sidx into the supplied buffer row.
 *  @note it is up to the programmer to make sure that row points to an allocation large
 *        enough to copy the entire row.
 */
// ---------------------------------------------------------------------------------------
void Table::row( real8_t* row, const size_t sidx ) {
  // -------------------------------------------------------------------------------------
  real8_t* src = (data + sidx);
  real8_t* dst = row;
  for ( size_t i=0; i<nvar; i++ ) {
    *dst++ = *src; src += nsamp;
  }
}


// =======================================================================================
/** @brief Read ASCII File.
 *  @param[in] fspc file specification for the source of this Table.
 *  @param[in] 
 *  @return 
 */
// ---------------------------------------------------------------------------------------
bool Table::read_ascii( const std::string fspc ) {
  // -------------------------------------------------------------------------------------
  int istat;
  std::ifstream inf = FileTool::openRead( fspc, &istat );

  if ( 0 != istat ) {
    logger->error( "Cannot open %s for reading." );
    return true;
  }

  size_t  ns, nv;
  real8_t x;
  inf >> ns;
  inf >> nv;
  resize( ns, nv );
  for ( size_t s=0; s<ns; s++ ) {
    for ( size_t v=0; v<nv; v++ ) {
      inf >> x; at(s,v) = x;
    }
  }
  
  inf.close();
  return false;
}


// =======================================================================================
/** @brief Write ASCII FIle;
 *  @param[in] fspc file specification for the destination of this Table.
 *  @param[in] sfmt print format.
 *  @return true if an error ocurred.
 *
 *  Write the contents of this Table to a file fspc. The file will be gin with two
 *  integers: number of samples and number of variables. Each subsequent line will
 *  contain one sample of nvar variables. The format specified by the argument sfmt
 *  is a string in the form of a printf edit descriptor.
 */
// ---------------------------------------------------------------------------------------
bool Table::write_ascii( const std::string fspc, const std::string sfmt ) {
  // -------------------------------------------------------------------------------------
  int istat;
  std::ofstream outf = FileTool::openWrite( fspc, &istat );

  if ( 0 != istat ) {
    logger->error( "Cannot open %s for writting." );
    return true;
  }

  outf << nsamp << " " << nvar << "\n";
  for ( size_t s=0; s<nsamp; s++ ) {
    outf << c_fmt( sfmt.c_str(), at(s,0) );
    for ( size_t v=1; v<nvar; v++ ) {
      outf << " " << c_fmt( sfmt.c_str(), at(s,v) );
    }
    outf << "\n";
  }
  
  outf.close();
  return false;
}


// =======================================================================================
// **                                     T A B L E                                     **
// ======================================================================== END FILE =====
