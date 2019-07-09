// ====================================================================== BEGIN FILE =====
// **                                  L I N A L G 3 D                                  **
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
 *  @file   LinAlg3D.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-06
 *
 *  Provides the interface for linear algebra functions, with three element vectors and
 *  nine element matrices.
 */
// =======================================================================================

#ifndef __HH_LINALG3D_TRNCMP
#define __HH_LINALG3D_TRNCMP

#include <Vector3D.hh>
#include <Matrix3D.hh>

const Vector3D getRow      ( const Matrix3D& M, size_t index );
const Vector3D getColumn   ( const Matrix3D& M, size_t index );
const Vector3D getDiagonal ( const Matrix3D& M );

void           setRow      ( Matrix3D& M, const Vector3D& v, size_t index );
void           setColumn   ( Matrix3D& M, const Vector3D& v, size_t index );
void           setDiagonal ( Matrix3D& M, const Vector3D& v );

const Matrix3D diagonal    ( const Vector3D& V );
const Vector3D diagonal    ( const Matrix3D& M );

const Vector3D dot         ( const Vector3D& V, const Matrix3D& M );
const Vector3D dot         ( const Matrix3D& M, const Vector3D& V );

void           dot         ( Vector3D& C, const Vector3D& V, const Matrix3D& M );
void           dot         ( Vector3D& C, const Matrix3D& M, const Vector3D& V );

void           covariance  ( Matrix3D& M, real8_t data[][3], size_t n );
const Matrix3D covariance  (              real8_t data[][3], size_t n );

void           covariance  ( Matrix3D& M, Vector3D *data,    size_t n );
const Matrix3D covariance  (              Vector3D *data,    size_t n );

const Matrix3D ROT1        ( const real8_t ang );
const Matrix3D ROT2        ( const real8_t ang );
const Matrix3D ROT3        ( const real8_t ang );

bool eigen( Vector3D& eval, Vector3D& ev1, Vector3D& ev2, Vector3D& ev3, const Matrix3D& M );

// =======================================================================================
/** @brief Get Row.
 *  @param[in] M     reference to a Matrix3D.
 *  @param[in] index row index.
 *  @return row index as a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D getRow( const Matrix3D& M, size_t index ) {
  // -------------------------------------------------------------------------------------
  switch(index%3) {
    case 0: return Vector3D( M.a00, M.a01, M.a02 );
    case 1: return Vector3D( M.a10, M.a11, M.a12 );
    case 2: return Vector3D( M.a20, M.a21, M.a22 );
      
    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}


// =======================================================================================
/** @brief Get Column.
 *  @param[in] M     reference to a Matrix3D.
 *  @param[in] index column index.
 *  @return column index as a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D getColumn( const Matrix3D& M, size_t index ) {
  // -------------------------------------------------------------------------------------
  switch(index%3) {
    case 0: return Vector3D( M.a00, M.a10, M.a20 );
    case 1: return Vector3D( M.a01, M.a11, M.a21 );
    case 2: return Vector3D( M.a02, M.a12, M.a22 );
      
    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}


// =======================================================================================
/** @brief Get Diagonal.
 *  @param[in] M reference to a Matrix3D.
 *  @return diagonal as a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D getDiagonal( const Matrix3D& M ) {
  // -------------------------------------------------------------------------------------
return Vector3D( M.a00, M.a11, M.a22 );
}






// =======================================================================================
/** @brief Set Row.
 *  @param[inout] M     reference to a Matrix3D.
 *  @param[in]    V     reference to a Vector3D.
 *  @param[in]    index row index.
 *
 *  Set the index row of a Matrix3D with the elements from a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  void setRow( Matrix3D& M, const Vector3D& V, size_t index ) {
  // -------------------------------------------------------------------------------------
  switch(index%3) {
    case 0: M.a00 = V.x[0];    M.a01 = V.x[1];    M.a02 = V.x[2];    break;
    case 1: M.a10 = V.x[0];    M.a11 = V.x[1];    M.a12 = V.x[2];    break;
    case 2: M.a20 = V.x[0];    M.a21 = V.x[1];    M.a22 = V.x[2];    break;
      
    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}


// =======================================================================================
/** @brief Set Column.
 *  @param[inout] M     reference to a Matrix3D.
 *  @param[in]    V     reference to a Vector3D.
 *  @param[in]    index column index.
 *
 *  Set the index column of a Matrix3D with the elements from a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  void setColumn( Matrix3D& M, const Vector3D& V, size_t index ) {
  // -------------------------------------------------------------------------------------
  switch(index%3) {
    case 0: M.a00 = V.x[0];    M.a10 = V.x[1];    M.a20 = V.x[2];    break;
    case 1: M.a01 = V.x[0];    M.a11 = V.x[1];    M.a21 = V.x[2];    break;
    case 2: M.a02 = V.x[0];    M.a12 = V.x[1];    M.a22 = V.x[2];    break;
      
    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
}


// =======================================================================================
/** @brief Set Diagonal.
 *  @param[inout] M reference to a Matrix3D.
 *  @param[in]    V reference to a Vector3D.
 *
 *  Set the diagonal of a Matrix3D with the elements from a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  void setDiagonal( Matrix3D& M, const Vector3D& V ) {
  // -------------------------------------------------------------------------------------
  M.a00 = V.x[0];    M.a11 = V.x[1];    M.a22 = V.x[2];
}






// =======================================================================================
/** @brief Diagonal.
 *  @param[in] V reference to a Vector3D.
 *  @return Matrix3D.
 *
 *  Create a Matrix3D that is the diagonal of the Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Matrix3D diagonal( const Vector3D& V ) {
  // -------------------------------------------------------------------------------------
  return Matrix3D( V.x[0],    D_ZERO, D_ZERO,
                   D_ZERO, V.x[1],    D_ZERO,
                   D_ZERO, D_ZERO, V.x[2] );
}


// =======================================================================================
/** @brief Diagonal.
 *  @param[in] M reference to a Matrix3D.
 *  @return Vector3D.
 *
 *  Create a Vector3D from the diagonal of a Matrix3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D diagonal( const Matrix3D& M ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( M.a00, M.a11, M.a22 );
}






// =======================================================================================
/** @brief Dot.
 *  @param[in] V reference to a Vector3D.
 *  @param[in] M reference to a Matrix3D.
 *  @return Vector3D.
 *
 *  Perform a dot product of a row vector with a matrix    <v| = <v|M>
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D dot( const Vector3D& V, const Matrix3D& M ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( (V.x[0] * M.a00) + (V.x[1] * M.a10) + (V.x[2] * M.a20),
                   (V.x[0] * M.a01) + (V.x[1] * M.a11) + (V.x[2] * M.a21),
                   (V.x[0] * M.a02) + (V.x[1] * M.a12) + (V.x[2] * M.a22) );
}

// =======================================================================================
/** @brief Dot.
 *  @param[in] M reference to a Matrix3D.
 *  @param[in] V reference to a Vector3D.
 *  @return Vector3D.
 *
 *  Perform a dot product of a matrix and a column vector    |v> = <M|v>
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D dot( const Matrix3D& M, const Vector3D& V ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( (V.x[0] * M.a00) + (V.x[1] * M.a01) + (V.x[2] * M.a02),
                   (V.x[0] * M.a10) + (V.x[1] * M.a11) + (V.x[2] * M.a12),
                   (V.x[0] * M.a20) + (V.x[1] * M.a21) + (V.x[2] * M.a22) );
}

// =======================================================================================
/** @brief Dot.
 *  @param[out] C reference to a Vector3D.
 *  @param[in]  V reference to a Vector3D.
 *  @param[in]  M reference to a Matrix3D.
 *
 *  Perform a dot product of a row vector with a matrix  C=V.M    <v| = <v|M>
 */
// ---------------------------------------------------------------------------------------
inline  void dot( Vector3D& C, const Vector3D& V, const Matrix3D& M ) {
  // -------------------------------------------------------------------------------------
  C.x[0] = (V.x[0] * M.a00) + (V.x[1] * M.a10) + (V.x[2] * M.a20);
  C.x[1] = (V.x[0] * M.a01) + (V.x[1] * M.a11) + (V.x[2] * M.a21);
  C.x[2] = (V.x[0] * M.a02) + (V.x[1] * M.a12) + (V.x[2] * M.a22);
}

// =======================================================================================
/** @brief Dot.
 *  @param[out] C reference to a Vector3D.
 *  @param[in]  M reference to a Matrix3D.
 *  @param[in]  V reference to a Vector3D.
 *
 *  Perform a dot product of a matrix and a column vector  C=M.V    |v> = <M|v>
 */
// ---------------------------------------------------------------------------------------
inline  void dot( Vector3D& C, const Matrix3D& M, const Vector3D& V ) {
  // -------------------------------------------------------------------------------------
  C.x[0] = (V.x[0] * M.a00) + (V.x[1] * M.a01) + (V.x[2] * M.a02);
  C.x[1] = (V.x[0] * M.a10) + (V.x[1] * M.a11) + (V.x[2] * M.a12);
  C.x[2] = (V.x[0] * M.a20) + (V.x[1] * M.a21) + (V.x[2] * M.a22);
}


#endif


// =======================================================================================
// **                                  L I N A L G 3 D                                  **
// ======================================================================== END FILE =====
