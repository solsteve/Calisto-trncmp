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
 *  @file   Exemplar.hh
 *  @author Stephen W. Soliday
 *  @date   2017-Jun-04 Original release.
 *  @date   2019-Sep-02 CMake refactorization.
 *
 *  Provides the interface for an exemplar data set pair.
 */
// =======================================================================================

#ifndef __HH_EXEMPLAR_TRNCMP
#define __HH_EXEMPLAR_TRNCMP

#include <trncmp.hh>
#include <TLogger.hh>

typedef enum { NOMETA=0, META=1 } exemplar_meta_e;

typedef enum { BOTH=0, INPUT=1, OUTPUT=2 } exemplar_data_e;

#define DEFAULT_EDIT_DES "%23.16e"


// =======================================================================================
class Exemplar {                                                               // Exemplar
  // -------------------------------------------------------------------------------------
 public:

  TLOGGER_HEADER( logger );
  
  // =====================================================================================
  class Meta {                                                           // Exemplar::Meta
    // -----------------------------------------------------------------------------------
   public:
    int32_t n_sample;   ///< Number of samples.
    int32_t n_input;    ///< Number of input  variables.
    int32_t n_output;   ///< Number of output variables.

    Meta  ( void );
    Meta  ( const int32_t ns, const int32_t ni, const int32_t no = 0 );
    Meta  ( std::string mf );
    ~Meta ( void );

    Meta& operator=( const Meta& ) = default;

    void        destroy    ( void );

    std::string toString   ( void );
    void        fromString ( std::string str );

    bool        read       ( std::ifstream& inf  );
    bool        write      ( std::ofstream& outf );

    bool        read       ( std::string fspc );
    bool        write      ( std::string fspc );

  }; // end class Exemplar::Meta

  
  // =====================================================================================
  class Data {                                                           // Exemplar::Data
    // -----------------------------------------------------------------------------------
   protected:
    real8_t* data;
    int32_t  n_buf;
    int32_t  n_samp;
    int32_t  n_vars;

    EMPTY_PROTOTYPE( Data );

   public:
    Data  ( void );
    Data  ( const int32_t ns, const int32_t nv );
    ~Data ( void );

    void     copy( Data& src );

    void     destroy ( void );
    void     resize  ( const int32_t ns, const int32_t nv );
    int32_t  size    ( const int dim=0 ) const;

    void     set     ( const int32_t is, const int32_t iv, const real8_t val );
    real8_t  get     ( const int32_t is, const int32_t iv ) const ;
    real8_t* get     ( const int32_t is );
    real8_t* get     ( void );
    
  }; // end class Exemplar::Data

  // =====================================================================================
 protected:
  
  Data        input;
  Data        output;
  std::string input_edit;
  std::string output_edit;
  
  void destroy( void );

  static bool read_pair    ( std::ifstream& inf,
                             Data& idat, const int32_t ns, const int32_t ni,
                             Data& odat, const int32_t no );
  
  static bool read_single  ( std::ifstream& inf,
                             Data& idat, const int32_t ns, const int32_t ni );
  
  static bool write_pair   ( std::ofstream& outf, Data& idat, Data& odat,
                             std::string ifmt = DEFAULT_EDIT_DES,
                             std::string ofmt = DEFAULT_EDIT_DES );
  
  static bool write_single ( std::ofstream& outf, Data& idat,
                             std::string ifmt = DEFAULT_EDIT_DES );

 public:
  Exemplar  ( void );
  Exemplar  ( std::string mfdf );
  Exemplar  ( std::string mf, std::string df );

  Exemplar  ( Meta& M );
  Exemplar  ( const int32_t ns, const int32_t ni, const int32_t no = 0 );

  ~Exemplar ( void );

  void     resize          ( const Meta& M );
  void     resize          ( const int32_t ns, const int32_t ni, const int32_t no = 0 );
  void     resize_input    ( const int32_t ns, const int32_t ni );
  void     resize_output   ( const int32_t ns, const int32_t no );
  void     deleteOutput    ( void );

  int32_t  nSample         ( void ) const;
  int32_t  nInput          ( void ) const;
  int32_t  nOutput         ( void ) const;
  bool     hasOutput       ( void ) const;

  Meta     getMeta         ( exemplar_data_e wd = BOTH ) const;

  void     copy            ( Exemplar& src, exemplar_data_e wd = BOTH );

  void     setIn           ( const int32_t is, const int32_t iv, const real8_t val );
  real8_t  getIn           ( const int32_t is, const int32_t iv ) const ;
  real8_t* getIn           ( const int32_t is );
  Data*    getIn           ( void );

  void     setOut          ( const int32_t is, const int32_t iv, const real8_t val );
  real8_t  getOut          ( const int32_t is, const int32_t iv ) const ;
  real8_t* getOut          ( const int32_t is );
  Data*    getOut          ( void );

  bool     read            ( std::string mfdf );
  bool     read            ( std::string df, const Meta& M );
  bool     read            ( std::string df, const int32_t ns, const int32_t ni, const int32_t no );
  bool     read            ( std::string mf, std::string df );

  void     setInputFormat  ( std::string fmt_i );
  void     setOutputFormat ( std::string fmt_o );
  void     setFormat       ( std::string fmt_i, std::string ifmt_o );
  void     setFormat       ( std::string fmt );
  void     setFormat       ( void );

  bool     write           ( std::string mfdf,
                             exemplar_data_e wd, exemplar_meta_e um );

  bool     write           ( std::string mf, std::string df,
                             exemplar_data_e wd = BOTH );

  bool     write_meta      ( std::string mf, exemplar_data_e wd = BOTH );

  // ----- alias ------------------------------------------------------
  bool     write           ( std::string mfdf,
                             exemplar_meta_e um, exemplar_data_e wd );

  bool     write           ( std::string mfdf,
                             exemplar_meta_e um );

  bool     write           ( std::string mfdf,
                             exemplar_data_e wd );

  bool     write           ( std::string mfdf );

  
}; // end class Exemplar


// =======================================================================================
/** @brief Size.
 *  @param[in] dim dimension.
 *  @return number of samples if dim==0, otherwise the number of variables.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t Exemplar::Data::size( const int dim ) const {
  // -------------------------------------------------------------------------------------
  return ( 0==dim ) ? (n_samp) : (n_vars);
}


// =======================================================================================
/** @brief Set.
 *  @param[in] is  sample index.
 *  @param[in] iv  variable index.
 *  @param[in] val value to set.
 *
 */
// ---------------------------------------------------------------------------------------
inline  void Exemplar::Data::set( const int32_t is, const int32_t iv, const real8_t val ) {
  // -------------------------------------------------------------------------------------
  data[is*n_vars + iv] = val;
}


// =======================================================================================
/** @brief Get.
 *  @param[in] is sample index.
 *  @param[in] iv variable index.
 *  @return value at (is,iv)
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Exemplar::Data::get( const int32_t is, const int32_t iv ) const  {
  // -------------------------------------------------------------------------------------
  return data[is*n_vars + iv];
}


// =======================================================================================
/** @brief Get.
 *  @param[in] is sample index.
 *  @return pointer to an output vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t* Exemplar::Data::get( const int32_t is ) {
  // -------------------------------------------------------------------------------------
  return (data + is*n_vars);
}


// =======================================================================================
/** @brief Get.
 *  @param[in] is sample index.
 *  @return pointer to an output vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t* Exemplar::Data::get( void ) {
  // -------------------------------------------------------------------------------------
  return data;
}


// =======================================================================================
/** @brief Size.
 *  @return number of samples.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t Exemplar::nSample( void ) const {
  // -------------------------------------------------------------------------------------
  return input.size(0);
}


// =======================================================================================
/** @brief Size.
 *  @return number of input variables.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t Exemplar::nInput( void ) const {
  // -------------------------------------------------------------------------------------
  return input.size(1);
}


// =======================================================================================
/** @brief Size.
 *  @return number of output variables.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t Exemplar::nOutput( void ) const {
  // -------------------------------------------------------------------------------------
  return output.size(1);
}


// =======================================================================================
/** @brief Has Output.
 *  @return true is the is an output data set.
 */
// ---------------------------------------------------------------------------------------
inline  bool Exemplar::hasOutput( void ) const {
  // -------------------------------------------------------------------------------------
  return (0 < output.size(1));
}


// =======================================================================================
/** @brief Set Input
 *  @param[in] is  sample index.
 *  @param[in] iv  variable index.
 *  @param[in] val value to set.
 *
 */
// ---------------------------------------------------------------------------------------
inline  void Exemplar::setIn( const int32_t is, const int32_t iv, const real8_t val ) {
  // -------------------------------------------------------------------------------------
  input.set( is, iv, val );
}


// =======================================================================================
/** @brief Get Input.
 *  @param[in] is sample index.
 *  @param[in] iv variable index.
 *  @return value at (is,iv)
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Exemplar::getIn( const int32_t is, const int32_t iv ) const  {
  // -------------------------------------------------------------------------------------
  return input.get( is, iv );
}


// =======================================================================================
/** @brief Get Input.
 *  @param[in] is sample index.
 *  @return pointer to an output vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t* Exemplar::getIn( const int32_t is ) {
  // -------------------------------------------------------------------------------------
  return input.get( is );
}


// =======================================================================================
/** @brief Get Input.
 *  @return pointer to the input dataset.
 */
// ---------------------------------------------------------------------------------------
inline  Exemplar::Data* Exemplar::getIn( void ) {
  // -------------------------------------------------------------------------------------
  return &input;
}


// =======================================================================================
/** @brief Set Output
 *  @param[in] is  sample index.
 *  @param[in] iv  variable index.
 *  @param[in] val value to set.
 *
 */
// ---------------------------------------------------------------------------------------
inline  void Exemplar::setOut( const int32_t is, const int32_t iv, const real8_t val ) {
  // -------------------------------------------------------------------------------------
  output.set( is, iv, val );
}


// =======================================================================================
/** @brief Get Output.
 *  @param[in] is sample index.
 *  @param[in] iv variable index.
 *  @return value at (is,iv)
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Exemplar::getOut( const int32_t is, const int32_t iv ) const  {
  // -------------------------------------------------------------------------------------
  return output.get( is, iv );
}


// =======================================================================================
/** @brief Get Output.
 *  @param[in] is sample index.
 *  @return pointer to an output vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t* Exemplar::getOut( const int32_t is ) {
  // -------------------------------------------------------------------------------------
  return output.get( is );
}


// =======================================================================================
/** @brief Get Output.
 *  @return pointer to the output dataset.
 */
// ---------------------------------------------------------------------------------------
inline  Exemplar::Data* Exemplar::getOut( void ) {
  // -------------------------------------------------------------------------------------
  return &output;
}

// =======================================================================================
/** @brief Get Meta.
 *  @return the Meta object for this Exemplar.
 */
// ---------------------------------------------------------------------------------------
inline Exemplar::Meta Exemplar::getMeta( exemplar_data_e wd ) const {
  // -------------------------------------------------------------------------------------
  if ( INPUT == wd ) {
    return Exemplar::Meta( nSample(), nInput(), 0 );
  }
  if ( OUTPUT == wd ) {
    return Exemplar::Meta( nSample(), nOutput(), 0 );
  }
  return Exemplar::Meta( nSample(), nInput(), nOutput() );
}


// =======================================================================================
/** @brief Delete Output.
 *
 *  Remove the output data set.
 */
// ---------------------------------------------------------------------------------------
inline void Exemplar::deleteOutput( void ) {
  // -------------------------------------------------------------------------------------  
  output.destroy();
}


// =======================================================================================
/** @brief Read.
 */
// ---------------------------------------------------------------------------------------
inline  bool Exemplar::read( std::string df, const Meta& M ) {
  // -------------------------------------------------------------------------------------
  return read( df, M.n_sample, M.n_input, M.n_output );
}



// =======================================================================================
/** @brief Set Edit Descriptor.
 *  @param[in] fmt_i input  dataset edit descriptor.
 *
 *  Set the input dataset edit descriptor for writing the datset in ascii format.
 *  These edit descriptor is identical to the ones used by printf.
 */
// ---------------------------------------------------------------------------------------
inline  void Exemplar::setInputFormat( std::string fmt_i ) {
  // ---------------------------------------------------------------------------------------
  input_edit  = fmt_i;
}


// =======================================================================================
/** @brief Set Edit Descriptor.
 *  @param[in] fmt_o output dataset edit descriptor.
 *
 *  Set the output dataset edit descriptor for writing the datset in ascii format.
 *  These edit descriptor is identical to the ones used by printf.
 */
// ---------------------------------------------------------------------------------------
inline  void Exemplar::setOutputFormat( std::string fmt_o ) {
  // ---------------------------------------------------------------------------------------
  output_edit = fmt_o;
}


// =======================================================================================
/** @brief Set Edit Descriptor.
 *  @param[in] fmt_i input  dataset edit descriptor.
 *  @param[in] fmt_o output dataset edit descriptor.
 *
 *  Set both of the edit descriptors for writing the datsets in ascii format.
 *  These edit descriptors are identical to the ones used by printf.
 */
// ---------------------------------------------------------------------------------------
inline  void Exemplar::setFormat( std::string fmt_i, std::string fmt_o ) {
  // ---------------------------------------------------------------------------------------
  input_edit  = fmt_i;
  output_edit = fmt_o;
}


// =======================================================================================
/** @brief Set Edit Descriptor.
 *  @param[in] fmt dataset edit descriptor.
 *
 *  Set both of the edit descriptors for writing the datsets in ascii format.
 *  These edit descriptors are identical to the ones used by printf.
 *  Both input and output will use the same edit descriptor.
 */
// ---------------------------------------------------------------------------------------
inline  void Exemplar::setFormat( std::string fmt ) {
  // ---------------------------------------------------------------------------------------
  input_edit  = fmt;
  output_edit = fmt;
}


// =======================================================================================
/** @brief Set Edit Descriptor.
 *
 *  Set both of the edit descriptors for writing the datsets in ascii format.
 *  These edit descriptors are identical to the ones used by printf.
 *  Both input and output will use the same defualt edit descriptor: "%23.16e".
 */
// ---------------------------------------------------------------------------------------
inline  void Exemplar::setFormat( void ) {
  // -------------------------------------------------------------------------------------
  input_edit  = DEFAULT_EDIT_DES;
  output_edit = DEFAULT_EDIT_DES;
}


#endif


// =======================================================================================
// **                                   E X E M P L A R                                 **
// ======================================================================== END FILE =====
