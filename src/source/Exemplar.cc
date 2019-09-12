// ====================================================================== BEGIN FILE =====
// **                                   E X E M P L A R                                 **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2006-2019, Stephen W. Soliday                                      **
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
/** @brief  Exemplar Data Sets.
 *  @file   Exemplar.cc
 *  @author Stephen W. Soliday
 *  @date   2017-Jun-04 Original release.
 *  @date   2019-Sep-02 CMake refactorization.
 *
 *  Provides the methods for an exemplar data set pair.
 */
// =======================================================================================

#include <Exemplar.hh>
#include <FileTool.hh>

#define INIT_VAR2(_a) data(_a), n_buf(_a), n_samp(_a), n_vars(_a)

#define INIT_VAR3(_a) input(), output(), input_edit(DEFAULT_EDIT_DES), output_edit(DEFAULT_EDIT_DES)


TLOGGER_REFERENCE( Exemplar, logger );


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
Exemplar::Meta::Meta( void ) : n_sample(0), n_input(0), n_output(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] mf full path to a meta file.
 */
// ---------------------------------------------------------------------------------------
Exemplar::Meta::Meta( std::string mf ) : n_sample(0), n_input(0), n_output(0) {
  // -------------------------------------------------------------------------------------
  read( mf );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] ns number of samples.
 *  @param[in] ni number of input  variables.
 *  @param[in] no number of output variables.
 */
// ---------------------------------------------------------------------------------------
Exemplar::Meta::Meta( const int32_t ns, const int32_t ni, const int32_t no ) :
    n_sample(ns), n_input(ni), n_output(no) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Exemplar::Meta::~Meta( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}


// =======================================================================================
/** @brief Destroy.
 */
// ---------------------------------------------------------------------------------------
void Exemplar::Meta::destroy( void ) {
  // -------------------------------------------------------------------------------------
  n_sample = 0;
  n_input  = 0;
  n_output = 0;
}


// =======================================================================================
/** @brief To String
 *  @return string of meta data line.
 */
// ---------------------------------------------------------------------------------------
std::string Exemplar::Meta::toString( void ) {
  // -------------------------------------------------------------------------------------
  std::string buffer( c_fmt( "%d", n_sample ) );
  buffer.append( c_fmt( " %d", n_input ) );
  if ( 0 < n_output ) {
    buffer.append( c_fmt( " %d", n_output ) );
  }
  return buffer;
}


// =======================================================================================
/** @brief FromString
 *  @param[in] parsable string of meta data line.
 */
// ---------------------------------------------------------------------------------------
void Exemplar::Meta::fromString( std::string str ) {
  // -------------------------------------------------------------------------------------
  destroy();
  int32_t ns, ni, no;
  const char* buffer = str.c_str();
  int32_t n = sscanf( buffer, "%d %d %d", &ns, &ni, &no );
  if ( 2 == n ) { no = 0; n++; }
  if ( 3 == n ) {
    n_sample = ns;
    n_input  = ni;
    n_output = no;
  } else {
    logger->error( "Meta data was not parsed [%s]", buffer );
  }
}


// =======================================================================================
/** @brief Read
 *  @param[in] inf reference to an input stream.
 *  @return true is error occurs.
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::Meta::read( std::ifstream& inf  ) {
  // -------------------------------------------------------------------------------------
  char buffer[64];
  inf.getline( buffer, 62 );
  fromString( buffer );
  return false;
}


// =======================================================================================
/** @brief Write
 *  @param[in] outf reference to an output stream.
 *  @return true is error occurs.
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::Meta::write( std::ofstream& outf ) {
  // -------------------------------------------------------------------------------------
  outf << toString() << "\n";
  return false;
}


// =======================================================================================
/** @brief Read.
 *  @param[in] fspc path to a Meta file.
 *  @return true is error occurs.
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::Meta::read( std::string fspc ) {
  // -------------------------------------------------------------------------------------
  int istat;
  std::ifstream inf = FileTool::openRead( fspc, &istat );

  if ( 0 != istat ) {
    logger->error( "Exemplar::Meta::read: Cannot open %s for reading.", fspc );
    return true;
  }

  bool rv = read( inf );
  
  inf.close();
  return rv;
}


// =======================================================================================
/** @brief Write.
 *  @param[in] fspc path to a Meta file.
 *  @return true is error occurs.
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::Meta::write( std::string fspc ) {
  // -------------------------------------------------------------------------------------
  int istat;
  std::ofstream outf = FileTool::openWrite( fspc, &istat );

  if ( 0 != istat ) {
    logger->error( "Exemplar::Meta::read: Cannot open %s for writing.", fspc );
    return true;
  }

  bool rv = write( outf );
  
  outf.close();
  return rv;
}








// =======================================================================================
/** @brief Destroy.
 *
 *  Remove internal allocation.
 */
// ---------------------------------------------------------------------------------------
void Exemplar::Data::destroy( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<real8_t*>(0) != data ) {
    delete[] data;
  }
  data   = static_cast<real8_t*>(0);
  n_buf  = 0;
  n_samp = 0;
  n_vars = 0;  
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
Exemplar::Data::Data( void ) : INIT_VAR2(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief
 *  @param[in] ns number of samples.
 *  @param[in] nv number of variables in each sample.
 */
// ---------------------------------------------------------------------------------------
Exemplar::Data::Data( const int32_t ns, const int32_t nv ) : INIT_VAR2(0) {
  // -------------------------------------------------------------------------------------
  resize( ns, nv );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Exemplar::Data::~Data( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}


// =======================================================================================
/** @brief Resize.
 *  @param[in] ns number of samples.
 *  @param[in] nv number of variables in each sample.
 *
 *  Create internal allocation.
 */
// ---------------------------------------------------------------------------------------
void Exemplar::Data::resize( const int32_t ns, const int32_t nv ) {
  // -------------------------------------------------------------------------------------
  destroy();
  n_buf  = ns * nv;
  n_samp = ns;
  n_vars = nv;
  data   = new real8_t[ n_buf ];
}








// =======================================================================================
/** @brief Destroy.
 *
 *  Free internal allocation.
 */
// ---------------------------------------------------------------------------------------
void Exemplar::destroy( void ) {
  // -------------------------------------------------------------------------------------
  input.destroy();
  output.destroy();
  setFormat();
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
Exemplar::Exemplar( void ) : INIT_VAR3(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] M reference to Meta data.
 */
// ---------------------------------------------------------------------------------------
Exemplar::Exemplar( Meta& M ) : INIT_VAR3(0) {
  // -------------------------------------------------------------------------------------
  resize( M );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] ns number of samples.
 *  @param[in] ni number of input variables.
 *  @param[in] no number of output variables (default: 0).
 */
// ---------------------------------------------------------------------------------------
Exemplar::Exemplar( const int32_t ns, const int32_t ni, const int32_t no ) : INIT_VAR3(0) {
  // -------------------------------------------------------------------------------------
  resize( ns, ni, no );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] mfdf full path to an Exemplar file.
 */
// ---------------------------------------------------------------------------------------
Exemplar::Exemplar( std::string mfdf ) : INIT_VAR3(0) {
  // -------------------------------------------------------------------------------------
  read( mfdf );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] mf   full path to an Metadata file.
 *  @param[in] df   full path to an Data file.
 */
// ---------------------------------------------------------------------------------------
Exemplar::Exemplar( std::string mf, std::string df ) : INIT_VAR3(0) {
  // -------------------------------------------------------------------------------------
  read( mf, df ); 
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Exemplar::~Exemplar( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}


// =======================================================================================
/** @brief Resize.
 *  @param[in] M reference to Meta data.
 *
 *  Resize this Exemplar based of the contents of a Meta class.
 */
// ---------------------------------------------------------------------------------------
void Exemplar::resize( const Meta& M ) {
  // -------------------------------------------------------------------------------------
  resize( M.n_sample, M.n_input, M.n_output );
}


// =======================================================================================
/** @brief
 *  @param[in] ns number of samples.
 *  @param[in] ni number of input variables.
 *  @param[in] no number of output variables (default: 0).
 *  @return
 */
// ---------------------------------------------------------------------------------------
void Exemplar::resize( const int32_t ns, const int32_t ni, const int32_t no ) {
  // -------------------------------------------------------------------------------------
  destroy();
  resize_input( ns, ni );
  resize_output( ns, no );
}


// =======================================================================================
/** @brief Resize Input.
 *  @param[in] ns number of samples.
 *  @param[in] ni number of input variables.
 */
// ---------------------------------------------------------------------------------------
void Exemplar::resize_input( const int32_t ns, const int32_t ni ) {
  // -------------------------------------------------------------------------------------
  input.resize( ns, ni );
}


// =======================================================================================
/** @brief Resize Output.
 *  @param[in] ns number of samples.
 *  @param[in] no number of output variables (default: 0).
 */
// ---------------------------------------------------------------------------------------
void Exemplar::resize_output( const int32_t ns,  const int32_t no ) {
  // -------------------------------------------------------------------------------------
  if ( 0==no) {
    output.destroy();
  } else {
    output.resize( ns, no );
  }
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] src reference to a source dataset.
 */
// ---------------------------------------------------------------------------------------
void Exemplar::Data::copy( Exemplar::Data& src ) {
  // -------------------------------------------------------------------------------------
  this->resize( src.n_samp, src.n_vars );
  for ( int32_t i=0; i<this->n_buf; i++ ) {
    this->data[i] = src.data[i];
  }
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] src reference to a source Exemplar.
 *  @param[im] wd  flag to copy which dataset(s). (BOTH, INPUT, OUTPUT)
 *  @note if only INPUT or OUTPUT is copied. The copy goes into this Exemplar::input.
 */
// ---------------------------------------------------------------------------------------
void Exemplar::copy( Exemplar& src, exemplar_data_e wd ) {
  // -------------------------------------------------------------------------------------
  this->input.destroy();
  this->output.destroy();

  switch(wd) {
    case INPUT:  this->input.copy( src.input );  break;
    case OUTPUT: this->input.copy( src.output ); break;
    case BOTH:
    default:
      this->input.copy(  src.input );
      this->output.copy( src.output );
      break;
  }
}








// =======================================================================================
// ---------------------------------------------------------------------------------------
bool Exemplar::read_pair( std::ifstream& inf,
                          Data& idat, const int32_t ns, const int32_t ni,
                          Data& odat, const int32_t no ) {
  // -------------------------------------------------------------------------------------
  real8_t x;
  idat.resize( ns, ni );
  odat.resize( ns, no );
  for ( int32_t i=0; i<ns; i++ ) {
    for ( int32_t j=0; j<ni; j++ ) {
      inf >> x; idat.set( i,j, x );
    }
    for ( int32_t j=0; j<no; j++ ) {
      inf >> x; odat.set( i,j, x );
    }
  }
  return false;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
bool Exemplar::read_single( std::ifstream& inf,
                            Data& idat, const int32_t ns, const int32_t ni ) {
  // -------------------------------------------------------------------------------------
  real8_t x;
  idat.resize( ns, ni );
  for ( int32_t i=0; i<ns; i++ ) {
    for ( int32_t j=0; j<ni; j++ ) {
      inf >> x; idat.set( i,j, x );
    }
  }
  return false;
}


// =======================================================================================
/** @brief Write Pair.
 *  @param[in] outf reference to an output filer stream.
 *  @param[in] idat reference to an input  data object.
 *  @param[in] odat reference to an output data object.
 *  @param[in] ifmt edit descriptor for the input  data.
 *  @param[in] ofmt edit descriptor for the output data.
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::write_pair( std::ofstream& outf, Data& idat, Data& odat,
                           std::string ifmt, std::string ofmt ) {
  // -------------------------------------------------------------------------------------
  const char* fmt1 = ifmt.c_str();
  const char* fmt2 = (0 == ofmt.size()) ? ifmt.c_str() : ofmt.c_str();

  const int32_t ns = idat.size(0);
  const int32_t ni = idat.size(1);
  const int32_t no = odat.size(1);

  for ( int32_t i=0; i<ns; i++ ) {
    for ( int32_t j=0; j<ni; j++ ) {
      outf << c_fmt( fmt1, idat.get( i, j ) ) << " ";
    }
    for ( int32_t j=0; j<no; j++ ) {
      outf << " " << c_fmt( fmt2, odat.get( i, j ) );
    }
    outf << "\n";
  }
  return false;
}


// =======================================================================================
/** @brief Write Single.
 *  @param[in] outf reference to an output filer stream.
 *  @param[in] idat reference to an input  data object.
 *  @param[in] ifmt edit descriptor for the input  data.
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::write_single( std::ofstream& outf, Data& idat,
                             std::string ifmt ) {
  // -------------------------------------------------------------------------------------
  const char* fmt1 = ifmt.c_str();

  const int32_t ns = idat.size(0);
  const int32_t ni = idat.size(1);

  for ( int32_t i=0; i<ns; i++ ) {
    outf << c_fmt( fmt1, idat.get( i, 0 ) );
    for ( int32_t j=1; j<ni; j++ ) {
      outf << " " << c_fmt( fmt1, idat.get( i, j ) );
    }
    outf << "\n";
  }
  return false;
}








// =======================================================================================
/** @brief Read.
 *  @param[in] mfdf full path to an Exemplar file.
 *  @return true if error occurs.
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::read( std::string mfdf ) {
  // -------------------------------------------------------------------------------------
  destroy();
  
  int istat;
  std::ifstream inf = FileTool::openRead( mfdf, &istat );

  if ( 0 != istat ) {
    logger->error( "Exemplar::read:  Cannot open %s for reading.", mfdf );
    return true;
  }

  bool rv = true;
  Meta meta;
  if ( ! meta.read( inf ) ) {
    rv = ( 0 < meta.n_output ) ?
        Exemplar::read_pair(   inf,
                               input,  meta.n_sample, meta.n_input,
                               output, meta.n_output ) :
        Exemplar::read_single( inf,
                               input,  meta.n_sample, meta.n_input );
  }

  inf.close();
  return rv;
}


// =======================================================================================
/** @brief Read.
 *  @param[in] mf   full path to an Metadata file.
 *  @param[in] df   full path to an Data file.
 *  @return true if error occurs.
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::read( std::string mf, std::string df ) {
  // -------------------------------------------------------------------------------------
  destroy();

  Meta meta;
  if ( meta.read( mf ) ) {
    return true;
  }
 
  int istat;
  std::ifstream inf = FileTool::openRead( df, &istat );

  if ( 0 != istat ) {
    logger->error( "Exemplar::read:  Cannot open %s for reading.", df );
    return true;
  }

  bool rv = ( 0 < meta.n_output ) ?
      Exemplar::read_pair(   inf,
                             input,  meta.n_sample, meta.n_input,
                             output, meta.n_output ) :
      Exemplar::read_single( inf,
                             input,  meta.n_sample, meta.n_input );
  
  inf.close();
  return rv;
}



















// =======================================================================================
/** @brief Write.
 *  @param[in] mfdf full path to the combined meta and dataset file.
 *  @param[im] wd   flag to write which dataset(s). (BOTH, INPUT, OUTPUT)
 *  @param[im] um   flag to write Meta record. (META, NOMETA)
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::write( std::string mfdf, exemplar_data_e wd, exemplar_meta_e um ) {
  // -------------------------------------------------------------------------------------
  int istat;
  std::ofstream outf = FileTool::openWrite( mfdf, &istat );

  if ( 0 != istat ) {
    logger->error( "Exemplar::write:  Cannot open %s for writing.", mfdf );
    return true;
  }

  bool rv = false;
  
  if ( META == um ) {
    switch( wd ) {
      case INPUT: {  // ----- Write just the input dataset -------------------------------
        Meta tm( nSample(), nInput() );
        rv = tm.write( outf );
      } break;
      case OUTPUT: { // ----- Write just the ouput dataset -------------------------------
        if ( META == um ) {
          Meta tm( nSample(), nOutput() );
          rv = tm.write( outf );
        } else {
          logger->error( "There is no output dataset to be written" );
          rv = true;
        }
      } break;
      case BOTH:
      default: {     // ----- Write both the input and output datasets -------------------
        Meta tm( nSample(), nInput(), nOutput() );
        rv = tm.write( outf );
      } break;
    }
  }

  // -------------------------------------------------------------------------------------
  if ( ! rv ) {
  
    switch( wd ) {
      case INPUT: {  // ----- Write just the input dataset -------------------------------
        rv = Exemplar::write_single( outf, input, input_edit );
      } break;
      case OUTPUT: { // ----- Write just the ouput dataset -------------------------------
        rv = Exemplar::write_single( outf, output, output_edit );
      } break;
      case BOTH:
      default: {     // ----- Write both the input and output datasets -------------------
        rv =  Exemplar::write_pair( outf, input, output, input_edit, output_edit );
      } break;
    }
  }
  
  outf.close();
  return rv;
}


// =======================================================================================
/** @brief Write Meta Data.
 *  @param[in] mf   full path to an Metadata file.
 *  @param[im] wd   flag to write which dataset(s). (BOTH, INPUT, OUTPUT)
 *  @return true if error occurs.
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::write_meta( std::string mf, exemplar_data_e wd ) {
  // -------------------------------------------------------------------------------------
  bool rv = false;
  
  switch( wd ) {
    case INPUT: {  // ----- Write just the input dataset ---------------------------------
      Meta tm( nSample(), nInput() );
      rv = tm.write( mf );
    } break;
    case OUTPUT: { // ----- Write just the ouput dataset ---------------------------------
      if ( hasOutput() ) {
        Meta tm( nSample(), nOutput() );
        rv = tm.write( mf );
      } else {
        logger->error( "There is no output dataset to be written" );
        rv = true;
      }
    } break;
    case BOTH:
    default: {     // ----- Write both the input and output datasets ---------------------
      Meta tm( nSample(), nInput(), nOutput() );
      rv = tm.write( mf );
    } break;
  }

  return rv;
}
  
// =======================================================================================
/** @brief Write.
 *  @param[in] mf   full path to an Metadata file.
 *  @param[in] df   full path to an Data file.
 *  @param[im] wd   flag to write which dataset(s). (BOTH, INPUT, OUTPUT)
 *  @return true if error occurs.
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::write( std::string mf, std::string df, exemplar_data_e wd ) {
  // -------------------------------------------------------------------------------------
  bool rv = write_meta( mf, wd );
      
  if ( ! rv ) {
    
    int istat;
    std::ofstream outf = FileTool::openWrite( df, &istat );

    if ( 0 != istat ) {
      logger->error( "Exemplar::write:  Cannot open %s for writing.", df );
      return true;
    }

    switch( wd ) {
      case INPUT: {  // ----- Write just the input dataset -------------------------------
        rv = Exemplar::write_single( outf, input, input_edit );
      } break;
      case OUTPUT: { // ----- Write just the ouput dataset -------------------------------
        rv = Exemplar::write_single( outf, output, output_edit );
      } break;
      case BOTH:
      default: {     // ----- Write both the input and output datasets -------------------
        rv = Exemplar::write_pair( outf, input, output, input_edit, output_edit );
      } break;
    }
  
    outf.close();
  }
  
  return rv;
}







// =======================================================================================
/** @brief Write.
 *  @param[in] mfdf full path to the combined meta and dataset file.
 *  @param[im] um   flag to write Meta record. (META, NOMETA)
 *  @param[im] wd   flag to write which dataset(s). (BOTH, INPUT, OUTPUT)
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::write( std::string mfdf, exemplar_meta_e um, exemplar_data_e wd ) {
  // -------------------------------------------------------------------------------------
  return write( mfdf, wd, um );
}


// =======================================================================================
/** @brief Write.
 *  @param[in] mfdf full path to the combined meta and dataset file.
 *  @param[im] um   flag to write Meta record. (META, NOMETA)
 *  @note the default is to write both data sets.
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::write( std::string mfdf, exemplar_meta_e um ) {
  // -------------------------------------------------------------------------------------
  return write( mfdf, BOTH, um );
}


// =======================================================================================
/** @brief Write.
 *  @param[in] mfdf full path to the combined meta and dataset file.
 *  @param[im] wd   flag to write which dataset(s). (BOTH, INPUT, OUTPUT)
 *  @note the default is to write the Meta record.
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::write( std::string mfdf, exemplar_data_e wd ) {
  // -------------------------------------------------------------------------------------
  return write( mfdf, wd, META );
}


// =======================================================================================
/** @brief Write.
 *  @param[in] mfdf full path to the combined meta and dataset file.
 *  @note the default is to write the Meta record and both data sets.
 */
// ---------------------------------------------------------------------------------------
bool Exemplar::write( std::string mfdf ) {
  // -------------------------------------------------------------------------------------
  return write( mfdf, BOTH, META );
}


// =======================================================================================
// **                                   E X E M P L A R                                 **
// ======================================================================== END FILE =====
