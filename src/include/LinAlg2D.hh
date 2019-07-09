// ====================================================================== BEGIN FILE =====
// **                                  L I N A L G 2 D                                  **
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
/** @brief  Linear algebra functions.
 *  @file   LinAlg2D.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-06
 *
 *  Provides the interface for linear algebra functions, with two element vectors and
 *  four element matrices.
 */
// =======================================================================================

#ifndef __HH_LINALG2D_TRNCMP
#define __HH_LINALG2D_TRNCMP

#include <Vector2D.hh>
#include <Matrix2D.hh>

const Vector2D getRow      ( const Matrix2D& M, size_t index );
const Vector2D getColumn   ( const Matrix2D& M, size_t index );
const Vector2D getDiagonal ( const Matrix2D& M );

void           setRow      ( Matrix2D& M, const Vector2D& v, size_t index );
void           setColumn   ( Matrix2D& M, const Vector2D& v, size_t index );
void           setDiagonal ( Matrix2D& M, const Vector2D& v );

const Matrix2D diagonal    ( const Vector2D& V );
const Vector2D diagonal    ( const Matrix2D& M );

const Vector2D dot         ( const Vector2D& V, const Matrix2D& M );
const Vector2D dot         ( const Matrix2D& M, const Vector2D& V );

void           dot         ( Vector2D& C, const Vector2D& V, const Matrix2D& M );
void           dot         ( Vector2D& C, const Matrix2D& M, const Vector2D& V );

void           covariance  ( Matrix2D& M, real8_t data[][2], size_t n );
const Matrix2D covariance  (              real8_t data[][2], size_t n );

void           covariance  ( Matrix2D& M, Vector2D *data,    size_t n );
const Matrix2D covariance  (              Vector2D *data,    size_t n );

const Matrix2D ROT         ( const real8_t ang );

bool eigen( Vector2D& eval, Vector2D& ev1, Vector2D& ev2, const Matrix2D& M );

// =======================================================================================
/** @brief Get Row.
 *  @param[in] M     reference to a Matrix2D.
 *  @param[in] index row index.
 *  @return row index as a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D getRow( const Matrix2D& M, size_t index ) {
  // -------------------------------------------------------------------------------------
  switch(index%2) {
    case 0: return Vector2D( M.a00, M.a01 );
    case 1: return Vector2D( M.a10, M.a11 );
      
    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}


// =======================================================================================
/** @brief Get Column.
 *  @param[in] M     reference to a Matrix2D.
 *  @param[in] index column index.
 *  @return column index as a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D getColumn( const Matrix2D& M, size_t index ) {
  // -------------------------------------------------------------------------------------
  switch(index%2) {
    case 0: return Vector2D( M.a00, M.a10 );
    case 1: return Vector2D( M.a01, M.a11 );
      
    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}


// =======================================================================================
/** @brief Get Diagonal.
 *  @param[in] M reference to a Matrix2D.
 *  @return diagonal as a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D getDiagonal( const Matrix2D& M ) {
  // -------------------------------------------------------------------------------------
return Vector2D( M.a00, M.a11 );
}






// =======================================================================================
/** @brief Set Row.
 *  @param[inout] M     reference to a Matrix2D.
 *  @param[in]    V     reference to a Vector2D.
 *  @param[in]    index row index.
 *
 *  Set the index row of a Matrix2D with the elements from a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  void setRow( Matrix2D& M, const Vector2D& V, size_t index ) {
  // -------------------------------------------------------------------------------------
  switch(index%2) {
    case 0: M.a00 = V.x[0];    M.a01 = V.x[1];    break;
    case 1: M.a10 = V.x[0];    M.a11 = V.x[1];    break;
      
    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}


// =======================================================================================
/** @brief Set Column.
 *  @param[inout] M     reference to a Matrix2D.
 *  @param[in]    V     reference to a Vector2D.
 *  @param[in]    index column index.
 *
 *  Set the index column of a Matrix2D with the elements from a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  void setColumn( Matrix2D& M, const Vector2D& V, size_t index ) {
  // -------------------------------------------------------------------------------------
  switch(index%2) {
    case 0: M.a00 = V.x[0];    M.a10 = V.x[1];    break;
    case 1: M.a01 = V.x[0];    M.a11 = V.x[1];    break;
      
    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}


// =======================================================================================
/** @brief Set Diagonal.
 *  @param[inout] M reference to a Matrix2D.
 *  @param[in]    V reference to a Vector2D.
 *
 *  Set the diagonal of a Matrix2D with the elements from a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  void setDiagonal( Matrix2D& M, const Vector2D& V ) {
  // -------------------------------------------------------------------------------------
  M.a00 = V.x[0];    M.a11 = V.x[1];
}






// =======================================================================================
/** @brief Diagonal.
 *  @param[in] V reference to a Vector2D.
 *  @return Matrix2D.
 *
 *  Create a Matrix2D that is the diagonal of the Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix2D diagonal( const Vector2D& V ) {
  // -------------------------------------------------------------------------------------
  return Matrix2D( V.x[0],    D_ZERO,
                   D_ZERO, V.x[1] );
}


// =======================================================================================
/** @brief Diagonal.
 *  @param[in] M reference to a Matrix2D.
 *  @return Vector2D.
 *
 *  Create a Vector2D from the diagonal of a Matrix2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D diagonal( const Matrix2D& M ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( M.a00, M.a11 );
}






// =======================================================================================
/** @brief Dot.
 *  @param[in] V reference to a Vector2D.
 *  @param[in] M reference to a Matrix2D.
 *  @return Vector2D.
 *
 *  Perform a dot product of a row vector with a matrix    <v| = <v|M>
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D dot( const Vector2D& V, const Matrix2D& M ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( (V.x[0] * M.a00) + (V.x[1] * M.a10),
                   (V.x[0] * M.a01) + (V.x[1] * M.a11) );
}

// =======================================================================================
/** @brief Dot.
 *  @param[in] M reference to a Matrix2D.
 *  @param[in] V reference to a Vector2D.
 *  @return Vector2D.
 *
 *  Perform a dot product of a matrix and a column vector    |v> = <M|v>
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D dot( const Matrix2D& M, const Vector2D& V ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( (V.x[0] * M.a00) + (V.x[1] * M.a01),
                   (V.x[0] * M.a10) + (V.x[1] * M.a11) );
}

// =======================================================================================
/** @brief Dot.
 *  @param[out] C reference to a Vector2D.
 *  @param[in]  V reference to a Vector2D.
 *  @param[in]  M reference to a Matrix2D.
 *
 *  Perform a dot product of a row vector with a matrix  C=V.M    <v| = <v|M>
 */
// ---------------------------------------------------------------------------------------
inline  void dot( Vector2D& C, const Vector2D& V, const Matrix2D& M ) {
  // -------------------------------------------------------------------------------------
  C.x[0] = (V.x[0] * M.a00) + (V.x[1] * M.a10);
  C.x[1] = (V.x[0] * M.a01) + (V.x[1] * M.a11);
}

// =======================================================================================
/** @brief Dot.
 *  @param[out] C reference to a Vector2D.
 *  @param[in]  M reference to a Matrix2D.
 *  @param[in]  V reference to a Vector2D.
 *
 *  Perform a dot product of a matrix and a column vector  C=M.V    |v> = <M|v>
 */
// ---------------------------------------------------------------------------------------
inline  void dot( Vector2D& C, const Matrix2D& M, const Vector2D& V ) {
  // -------------------------------------------------------------------------------------
  C.x[0] = (V.x[0] * M.a00) + (V.x[1] * M.a01);
  C.x[1] = (V.x[0] * M.a10) + (V.x[1] * M.a11);
}


#endif


// =======================================================================================
// **                                  L I N A L G 2 D                                  **
// ======================================================================== END FILE =====
