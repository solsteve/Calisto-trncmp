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
 *  @file   ConfusionMatrix.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-10
 *
 *  Provides the methods for a confusion matrix.
 */
// =======================================================================================


#include <ConfusionMatrix.hh>


// =======================================================================================
/** @brief Constructor.
 *  @param[in] n number of classes.
 */
// ---------------------------------------------------------------------------------------
ConfusionMatrix::ConfusionMatrix( const int32_t n )
    : CM(n,n), A(0), P(0), N(0), n_class(n) {
  // -------------------------------------------------------------------------------------
  A = new int32_t[ n_class ];
  P = new int32_t[ n_class ];
  reset();
}

// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
ConfusionMatrix::~ConfusionMatrix( void ) {
  // -------------------------------------------------------------------------------------
  delete[] A;
  delete[] P;
}


// =======================================================================================
/** @brief Reset.
 */
// ---------------------------------------------------------------------------------------
void ConfusionMatrix::reset( void ) {
  // -------------------------------------------------------------------------------------
  CM.set();
  zero(A,n_class);
  zero(P,n_class);
  N = 0;
}


// =======================================================================================
/** @brief Add.
 *  @param[in] true_index true  index.
 *  @param[in] cls_index  class index.
 */
// ---------------------------------------------------------------------------------------
void ConfusionMatrix::add( const int32_t true_index, const int32_t cls_index ) {
  // -------------------------------------------------------------------------------------
  CM(true_index,cls_index) += 1;
  A[true_index] += 1;
  P[cls_index]  += 1;
  N             += 1;
}


// =======================================================================================
/** @brief Display.
 *  @param[in] fmt edit descriptor for reporting ratios.
 *  @param[in] os  reference to an output stream.
 */
// ---------------------------------------------------------------------------------------
void ConfusionMatrix::_display( std::string fmt, std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  const char* GL[] = { "t ", "r ", "u ", "e " };

  os << "     predict\n  ";
  for ( int32_t i=0; i<n_class; i++ ) {
    os << c_fmt( "       %02d", (i+1) );
  }
  os << "\n     +";
  for ( int32_t i=0; i<n_class; i++ ) {
    os << "--------+";
  }
  os << "\n";

  for ( int32_t row=0; row<n_class; row++ ) {

    os << ((row<2) ? (GL[row*2]) : ("  "))
       << c_fmt( "%02d |", (row+1) );
    for ( int32_t i=0; i<n_class; i++ ) {
      os << c_fmt( " %6d |", CM.get(row,i) );
    }
    os << "\n"
       <<((row<2) ? (GL[row*2+1]) : ("  "))
       << "   +";
    for ( int32_t i=0; i<n_class; i++ ) {
      os << "--------+";
    }
    os << "\n";
  }

  os << "\nAccuracy  = " << c_fmt( fmt, accuracy() ) << "\n"
     << "Precision =";
  for ( int32_t i=0; i<n_class; i++ ) {
    os << " " << c_fmt( fmt, precision(i) );
  }
  os << "\nRecall    =";
  for ( int32_t i=0; i<n_class; i++ ) {
    os << " " << c_fmt( fmt, recall(i) );
  }
  os << "\nF1-score  =";
  for ( int32_t i=0; i<n_class; i++ ) {
    os << " " << c_fmt( fmt, F1(i) );
  }
  os << "\n";
}


// =======================================================================================
/** @brief Accuracy.
 *  @param[in] i class index.
 *  @return accuracy
 *
 *  Accuracy.
 */
// ---------------------------------------------------------------------------------------
real8_t ConfusionMatrix::accuracy( void ) const {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;
  for ( int32_t i=0; i<n_class; i++ ) {
    sum += (real8_t)CM.get(i,i);
  }
  return (real8_t)sum / (real8_t)N;
}


// =======================================================================================
/** @brief Precision.
 *  @param[in] i class index.
 *  @return precision
 *
 *  PPV = Precision | Positive Predictive Value.
 */
// ---------------------------------------------------------------------------------------
real8_t ConfusionMatrix::precision( const int32_t i ) const {
  // -------------------------------------------------------------------------------------
  return (real8_t)CM.get(i,i) / (real8_t)P[i];
}


// =======================================================================================
/** @brief Recall.
 *  @param[in] i class index.
 *  @return recall
 *
 *  TPR = Recall | True Positive Rate | Hit Rate | Sensitivity.
 */
// ---------------------------------------------------------------------------------------
real8_t ConfusionMatrix::recall( const int32_t i ) const {
  // -------------------------------------------------------------------------------------
  return (real8_t)CM.get(i,i) / (real8_t)A[i];
}


// =======================================================================================
/** @brief F1 Score.
 *  @param[in] i class index.
 *  @return F1 Score.
 *
 *  F1 Score.
 */
// ---------------------------------------------------------------------------------------
real8_t ConfusionMatrix::F1( const int32_t i ) const {
  // -------------------------------------------------------------------------------------
  real8_t tpr = recall(i);
  real8_t ppv = precision(i);
  return D_TWO * (tpr*ppv) / (tpr+ppv);
}


// =======================================================================================
// **                           C O N F U S I O N M A T R I X                           **
// ======================================================================== END FILE =====
