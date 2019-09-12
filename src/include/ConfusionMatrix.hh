// ====================================================================== BEGIN FILE =====
// **                           C O N F U S I O N M A T R I X                           **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019, Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
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
/** @brief Confusion Matrix.
 *  @file   ConfusionMatrix.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-10
 *
 *  Provides the interface for a confusion matrix.
 */
// =======================================================================================


#ifndef __HH_CONFUSIONMATRIX_TRNCMP
#define __HH_CONFUSIONMATRIX_TRNCMP


#include <Array.hh>


// =======================================================================================
class ConfusionMatrix {
  // -------------------------------------------------------------------------------------
 protected:

  Array<int32_t> CM;      ///< confusion matrix
  int32_t*       A;       ///< actual sums
  int32_t*       P;       ///< predicted sums
  int32_t        N;       ///< number of samples
  int32_t        n_class; ///< number of classes

  EMPTY_PROTOTYPE( ConfusionMatrix );

  void _display    ( std::string fmt, std::ostream& os );
  
 public:
  ConfusionMatrix  ( const int32_t n );
  ~ConfusionMatrix ( void );
  
  void reset       ( void );
  void add         ( const int32_t true_index, const int32_t cls_index );

  real8_t   accuracy  ( void ) const;
  real8_t   precision ( const int32_t i ) const;
  real8_t   recall    ( const int32_t i ) const;
  real8_t   F1        ( const int32_t i ) const;

  void      display   ( std::string fmt, std::ostream& os );
  void      display   ( std::ostream& os, std::string fmt );
  void      display   ( std::string fmt );
  void      display   ( std::ostream& os );
  void      display   ( void );

}; // end class ConfusionMatrix


// =======================================================================================
/** @brief Display.
 *  @param[in] fmt edit descriptor for reporting ratios.
 *  @param[in] os  reference to an output stream.
 */
// ---------------------------------------------------------------------------------------
inline  void ConfusionMatrix::display( std::string fmt, std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  _display( fmt, os );
}


// =======================================================================================
/** @brief Display.
 *  @param[in] fmt edit descriptor for reporting ratios.
 *  @param[in] os  reference to an output stream.
 */
// ---------------------------------------------------------------------------------------
  inline  void ConfusionMatrix::display( std::ostream& os, std::string fmt ) {
  // -------------------------------------------------------------------------------------
  _display( fmt, os );
}


// =======================================================================================
/** @brief Display.
 *  @param[in] fmt edit descriptor for reporting ratios.
 *  @param[in] os  reference to an output stream.
 */
// ---------------------------------------------------------------------------------------
  inline  void ConfusionMatrix::display( std::string fmt ) {
  // -------------------------------------------------------------------------------------
    _display( fmt, std::cout );
}


// =======================================================================================
/** @brief Display.
 *  @param[in] fmt edit descriptor for reporting ratios.
 *  @param[in] os  reference to an output stream.
 */
// ---------------------------------------------------------------------------------------
  inline  void ConfusionMatrix::display( std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  _display( "%8.6f", os );
}


// =======================================================================================
/** @brief Display.
 *  @param[in] fmt edit descriptor for reporting ratios.
 *  @param[in] os  reference to an output stream.
 */
// ---------------------------------------------------------------------------------------
  inline  void ConfusionMatrix::display( void ) {
  // -------------------------------------------------------------------------------------
    _display( "%8.6f", std::cout );
}

#endif

  
// =======================================================================================
// **                           C O N F U S I O N M A T R I X                           **
// ======================================================================== END FILE =====
