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
void Table::resize( const int32_t ns, const int32_t nv ) {
  // -------------------------------------------------------------------------------------
  int32_t new_alloc = ns * nv;
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
Table::Table( const int32_t ns, const int32_t nv ) : INIT_VAR(0) {
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
  const int32_t n = nsamp * nvar;
  for ( int32_t i=0; i<n; i++ ) {
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
  const int32_t n = nsamp * nvar;
  for ( int32_t i=0; i<n; i++ ) {
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
void Table::row( real8_t* row, const int32_t sidx ) {
  // -------------------------------------------------------------------------------------
  real8_t* src = (data + sidx);
  real8_t* dst = row;
  for ( int32_t i=0; i<nvar; i++ ) {
    *dst++ = *src; src += nsamp;
  }
}




// =======================================================================================
/** @brief Read ASCII File.
 *  @param[in] inf reference to an input stream.
 *  @return true if an error ocurred.
 */
// ---------------------------------------------------------------------------------------
bool Table::read_ascii( std::istream& inf ) {
  // -------------------------------------------------------------------------------------
  int32_t  ns, nv;
  real8_t x;
  inf >> ns;
  inf >> nv;
  resize( ns, nv );
  for ( int32_t s=0; s<ns; s++ ) {
    for ( int32_t v=0; v<nv; v++ ) {
      inf >> x; at(s,v) = x;
    }
  }

  return false;
}


// =======================================================================================
/** @brief Write ASCII.
 *  @param[in] outf reference to an output stream.
 *  @param[in] sfmt print format.
 *  @return true if an error ocurred.
 *
 *  Write the contents of this Table to an output stream. This will begin with two
 *  integers: number of samples and number of variables. Each subsequent line will
 *  contain one sample of nvar variables. The format specified by the argument sfmt
 *  is a string in the form of a printf edit descriptor.
 */
// ---------------------------------------------------------------------------------------
bool Table::write_ascii( std::ostream& outf, const int32_t start, const int32_t finis,
                         const std::string sfmt ) {
  // -------------------------------------------------------------------------------------
  outf << (finis - start + 1) << " " << nvar << "\n";
  for ( int32_t s=start; s<=finis; s++ ) {
    outf << c_fmt( sfmt.c_str(), at(s,0) );
    for ( int32_t v=1; v<nvar; v++ ) {
      outf << " " << c_fmt( sfmt.c_str(), at(s,v) );
    }
    outf << "\n";
  }

  return false;
}


// =======================================================================================
/** @brief Write ASCII.
 *  @param[in] outf reference to an output stream.
 *  @param[in] sfmt print format.
 *  @return true if an error ocurred.
 *
 *  Write the contents of this Table to an output stream. This will begin with two
 *  integers: number of samples and number of variables. Each subsequent line will
 *  contain one sample of nvar variables. The format specified by the argument sfmt
 *  is a string in the form of a printf edit descriptor.
 */
// ---------------------------------------------------------------------------------------
bool Table::write_ascii( std::ostream& outf, const std::string sfmt ) {
  // -------------------------------------------------------------------------------------
  return write_ascii( outf, 0, nsamp-1, sfmt );
}




// =======================================================================================
/** @brief Read ASCII.
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
    logger->error( "Cannot open %s for reading.", fspc );
    return true;
  }

  bool rv = read_ascii( inf );
  
  inf.close();
  return rv;
}


// =======================================================================================
/** @brief Write ASCII FIle;
 *  @param[in] fspc file specification for the destination of this Table.
 *  @param[in] sfmt print format.
 *  @return true if an error ocurred.
 *
 *  Write the contents of this Table to a file fspc. The file will begin with two
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
    logger->error( "Cannot open %s for writing.", fspc );
    return true;
  }

  
  bool rv = write_ascii( outf, sfmt );
  
  outf.close();
  return rv;
}




// =======================================================================================
/** @brief Sum.
 *  @param[out] s    pointer to an array containing the sums.
 *  @param[in]  n    number of items to sum
 *  @param[in]  axis the axis along which to sum. (default: 0)
 *  @return 0==success
 *
 *  Depending on the value of axis, this procedure will sum samples of vairables.
 *  For example: is axis==0 then the samples will be summed and there will be nvar sums.
 *               otherwise the variables will be summed and there will be nsamp sums.
 */
// ---------------------------------------------------------------------------------------
int Table::sum( real8_t* s, const int32_t n, const int axis ) const {
  // -------------------------------------------------------------------------------------
  int rv = 0;
  if ( 0==axis ) {
    if ( n > nvar ) {
      logger->error( LOCATION, "n(%d) must be less than or equal to nvar(%d)", n, nvar );
      rv = 1;
    } else {
      const int32_t nv = Min( n, nvar );
      for ( int32_t iv=0; iv<nv; iv++ ) {
	s[iv] = D_ZERO;
	for ( int32_t is=0; is<nsamp; is++ ) {
	  s[iv] += get(is,iv);
	}
      }
    }
  } else {
    if ( n > nsamp ) {
      logger->error( LOCATION, "n(%d) must be less than or equal to nsamp(%d)", n, nsamp );
      rv = 2;
    } else {
      const int32_t ns = Min( n, nsamp );
      for ( int32_t is=0; is<ns; is++ ) {
	s[is] = D_ZERO;
	for ( int32_t iv=0; iv<nvar; iv++ ) {
	  s[is] += get(is,iv);
	}
      }
    }
  }
  return rv;
}


// =======================================================================================
/** @brief Mean
 *  @param[out] s    pointer to an array containing the means.
 *  @param[in]  n    number of means
 *  @param[in]  axis the axis along which to find means. (default: 0)
 *  @return 0==success
 *
 *  Depending on the value of axis, this procedure will average samples of vairables.
 *  For example: is axis==0 then the samples will be aveaged and there will be nvar means.
 *               otherwise the variables will be averages and there will be nsamp means.
 */
// ---------------------------------------------------------------------------------------
int Table::mean( real8_t* mu, const int32_t n, const int axis ) const {
  // -------------------------------------------------------------------------------------
  int rv = sum(mu, n, axis);
  if ( 0 == rv ) {
    const real8_t count = static_cast<real8_t>((0==axis) ? (nsamp) : (nvar));

    for ( int32_t i=0; i<n; i++ ) {
      mu[i] /= count;
    }
  }
  return rv;
}


// =======================================================================================
// **                                     T A B L E                                     **
// ======================================================================== END FILE =====
