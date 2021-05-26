// ====================================================================== BEGIN FILE =====
// **                               P O I N T _ C L O U D                               **
// =======================================================================================
// **                                                                                   **
// **  Copyright (c) 2020, Stephen W. Soliday                                           **
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
/** @brief  Open3D Point Cloud data (output from PointNet)
 *  @file   point_cloud.hh
 *  @author Stephen W. Soliday
 *  @date   2020-Oct-22
 *
 *  
 */
// =======================================================================================


#ifndef __HH_POINTCLOUD_TRNCMP
#define __HH_POINTCLOUD_TRNCMP

#include <trncmp.hh>
#include <TLogger.hh>

// =======================================================================================
class PointCloud {
  // -------------------------------------------------------------------------------------
 protected:

  TLOGGER_HEADER(logger); ///< reference to logger instance

 public:
  // =====================================================================================
  class Point {                                                       // PointCloud::Point 
    // -----------------------------------------------------------------------------------
   public:
    real8_t x;
    real8_t y;
    real8_t z;
    int16_t r;
    int16_t g;
    int16_t b;

    Point  ( void );
    ~Point ( void );
    void destroy( void );
  };

  // =====================================================================================
 private:
  size_t num_points;
  Point* points;

  void destroy( void );
    
 public:

  PointCloud   ( std::string fspc );
  PointCloud   ( std::string fspc, real8_t ratio );
  ~PointCloud  ( void );
    
  size_t N     ( void );
  Point& point ( const size_t idx );

  void write( std::ofstream& outf );
};

// =======================================================================================
inline size_t PointCloud::N( void ) {
  // -------------------------------------------------------------------------------------
  return num_points;
}
  
// =======================================================================================
inline PointCloud::Point& PointCloud::point ( const size_t idx ) { 
  // -------------------------------------------------------------------------------------
  return points[idx];
}


#endif


// =======================================================================================
// **                               P O I N T _ C L O U D                               **
// ======================================================================== END FILE =====
