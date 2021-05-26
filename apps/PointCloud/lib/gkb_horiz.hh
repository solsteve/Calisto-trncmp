// ====================================================================== BEGIN FILE =====
// **                                 G K B _ H O R I Z                                 **
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
/** @brief GKB Horizon Data
 *  @file   gkb_horiz.hh
 *  @author Stephen W. Soliday
 *  @date   2020-Oct-21
 *
 *  
 */
// =======================================================================================


#ifndef __HH_GKB_HORIZ_TRNCMP
#define __HH_GKB_HORIZ_TRNCMP

#include <trncmp.hh>
#include <TLogger.hh>


// =======================================================================================
class GKBH {
  // -------------------------------------------------------------------------------------
 protected:
  
  TLOGGER_HEADER(logger); ///< reference to logger instance


 public:
  // =====================================================================================
  class Wedge {                                                             // GKBH::Wedge
    // -----------------------------------------------------------------------------------
   public:
    real8_t angle;            // wedge center angle in radians
    real8_t width;            // half width of wedge in radians  (center +/- width)
    real8_t distance;         // base leg distance in meters
    real8_t elevation;        // height of horizon object
    int16_t flag;             // flag 0=no-bldg, 1=bldg

    Wedge        ( void );
    ~Wedge       ( void );
    void destroy ( void );
  };


  // =====================================================================================
  class Point {                                                             // GKBH::Point
    // -----------------------------------------------------------------------------------
   private:
    size_t  n_wedges;
    Wedge  *wedges;

    
   public:
    int16_t zone;  // UTM Zone number
    real8_t xutm;  // UTM Easting
    real8_t yutm;  // UTM Northing
    real8_t alt;   // Altitude in meters
    real8_t lon;   // Longitude
    real8_t lat;   // Latitude

    Point             ( size_t nw, std::ifstream& inf, bool ASCII=false );
    ~Point            ( void );
    void   destroy    ( void );
    
    Wedge& wedge      ( const size_t idx );
    size_t N          ( void );

    void   read       ( size_t nw, std::ifstream& inf );
    void   readASCII  ( size_t nw, std::ifstream& inf );

    void   write      ( std::ofstream& outf );
    void   writeASCII ( std::ofstream& outf );
  };


  // =====================================================================================
 private:
  size_t   n_grid_points;
  size_t   n_grid_wedges;
  Point  **grid_points;
  
 public:
  
  GKBH              ( std::string fspc, bool ASCII = false );
  ~GKBH             ( void );
  void   destroy    ( void );
  
  Point* point      ( const size_t idx );
  size_t NG         ( void );
  size_t NW         ( void );

  void   read       ( std::string fspc );
  void   readASCII  ( std::string fspc );
  
  void   write      ( std::string fspc );
  void   writeASCII ( std::string fspc );
};


// =======================================================================================
inline GKBH::Wedge& GKBH::Point::wedge( const size_t idx ) {
  // -------------------------------------------------------------------------------------
  return wedges[ idx ];
}


// =======================================================================================
inline size_t GKBH::Point::N( void ) {
  // -------------------------------------------------------------------------------------
  return n_wedges;
}


// =======================================================================================
inline GKBH::Point* GKBH::point( const size_t idx ) {
  // -------------------------------------------------------------------------------------
  return grid_points[ idx ];
}


// =======================================================================================
inline size_t GKBH::NG( void ) {
  // -------------------------------------------------------------------------------------
  return n_grid_points;
}


// =======================================================================================
inline size_t GKBH::NW( void ) {
  // -------------------------------------------------------------------------------------
  return n_grid_wedges;
}


#endif


// =======================================================================================
// **                                 G K B _ H O R I Z                                 **
// ======================================================================== END FILE =====
