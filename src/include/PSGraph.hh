// ====================================================================== BEGIN FILE =====
// **                                   P S G R A P H                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2012-2019, Stephen W. Soliday                                      **
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
/** @brief  Multi-page Postscript Graphics.
 *  @file   PSGraph.hh
 *  @author Stephen W. Soliday
 *  @date 2012-06-17 Original release.
 *  @date 2019-Jun-23 CMake refactorization.
 *
 *  Provides the interface for multi-page postscript graphics.
 */
// =======================================================================================


#ifndef __HH_PSGRAPH_TRNCMP
#define __HH_PSGRAPH_TRNCMP


#include <TLogger.hh>
#include <list>


// =======================================================================================
// ---------------------------------------------------------------------------------------
class PSGraph {                                                                 // PSGraph
  // -------------------------------------------------------------------------------------

public:

 typedef enum { NORMAL=0, BOLD=1, ITALIC=2 } font_enum;
 

  // =====================================================================================
  // -------------------------------------------------------------------------------------
  class Color {                                                          // PSGraph::Color
    // -----------------------------------------------------------------------------------
  public:
    real8_t r;   ///< Red   component
    real8_t g;   ///< Green component
    real8_t b;   ///< Blue  component

    Color  ( void );
    Color  ( real8_t _r, real8_t _g, real8_t _b );
    Color  ( Color& C );
    ~Color ( void );

    void set  ( real8_t _r, real8_t _g, real8_t _b );
    void copy ( Color& C );

    static Color white;     ///< The color White    #FFFFFF
    static Color black;     ///< The color Black    #000000
    static Color red;       ///< The color Red      #FF0000
    static Color green;     ///< The color Green    #00FF00
    static Color blue;      ///< The color Blue     #0000FF
    static Color cyan;      ///< The color Cyan     #00FFFF
    static Color magenta;   ///< The color Magenta  #FF00FF
    static Color yellow;    ///< The color Yellow   #FFFF00

  protected:
    void correct( void );
    
  }; // end class PSGraph::Color


  // =====================================================================================
  /** @brief Graphics Window.
   *  This class defines a graphics window that will be physically placed on a page.
   */
  // -------------------------------------------------------------------------------------
  class Window {                                                        // PSGraph::Window
    // -----------------------------------------------------------------------------------
  protected:
    real8_t device_width;                           ///< physical window width    (inches)
    real8_t device_height;                          ///< physical window height   (inches)
    real8_t device_x;                               ///< physical window position (inches)
    real8_t device_y;                               ///< physical window position (inches)

    void write_ps_window_header  ( FILE* psout );
    void write_ps_window_trailer ( FILE* psout );

  public:
    Window                 ( void );
    Window                 ( real8_t dev_width, real8_t dev_height );
    virtual ~Window        ( void );
    
    virtual void pswrite   ( FILE* fp ) = 0;
    void         setDevice ( real8_t dev_x, real8_t dev_y );
    
  }; // end class PSGraph::Window


  // =====================================================================================
  // -------------------------------------------------------------------------------------
  class Draw : public PSGraph::Window {                                   // PSGraph::Draw
    // -----------------------------------------------------------------------------------
  private:
    EMPTY_PROTOTYPE( Draw );

    int        id;
    char*      temp_filename;
    FILE*      file_handle;

    static int window_count;

  protected:
    real8_t world_x1;                         ///< windows lower left  device x coordinate
    real8_t world_x2;                         ///< windows lower left  device y coordinate
    real8_t world_y1;                         ///< windows upper right device x coordinate
    real8_t world_y2;                         ///< windows upper right device x coordinate

    real8_t slope_x, slope_y;
    real8_t inter_x, inter_y;

    PSGraph::Color last;
    PSGraph::Color saved;

    bool init              ( real8_t dev_width, real8_t dev_height,
			     real8_t x1, real8_t y1, real8_t x2, real8_t y2 );

    void drawFillPolygon   ( real8_t* x, real8_t* y, size_t n, bool fill );

    void drawFillRectangle ( real8_t x1, real8_t y1, real8_t x2, real8_t y2, bool fill );

  public:
    Draw                   ( real8_t dev_width, real8_t dev_height,
			     real8_t x1, real8_t y1, real8_t x2, real8_t y2 );

    Draw                   ( real8_t dev_width, real8_t dev_height );

    virtual ~Draw          ( void );

    void    saveColor      ( void );
    void    restoreColor   ( void );
    void    setRGB         ( PSGraph::Color& C );
    void    setRGB         ( real8_t r, real8_t g, real8_t b );

    void    setFont        ( PSGraph::font_enum ftype );
    
    void    drawLine       ( real8_t x1, real8_t y1, real8_t x2,  real8_t y2 );
    void    drawRay        ( real8_t xc, real8_t yc, real8_t m, real8_t theta );

    
    void    drawBorder     ( void );
    void    drawPolygon    ( real8_t* x, real8_t* y, size_t n );

    void    fillPolygon    ( real8_t* x, real8_t* y, size_t n );

    void    drawRectangle  ( real8_t x1, real8_t y1, real8_t x2, real8_t y2 );

    void    fillRectangle  ( real8_t x1, real8_t y1, real8_t x2, real8_t y2 );

    void    drawEllipse    ( real8_t xc, real8_t yc,
			     real8_t a, real8_t b, real8_t theta,
			     size_t parts=64 );

    void    fillEllipse    ( real8_t xc, real8_t yc,
			     real8_t a, real8_t b, real8_t theta,
			     size_t parts=64 );

    void    drawCircle     ( real8_t xc, real8_t yc,
			     real8_t r,
			     size_t parts=64 );

    void    fillCircle     ( real8_t xc, real8_t yc,
			     real8_t r,
			     size_t parts=64 );

    void    write          ( std::string text,
			     real8_t x1, real8_t y1,
			     real8_t x2, real8_t y2, real8_t theta = 0.0);
    
    void    write_inch     ( std::string,
			     real8_t x,     real8_t y,
			     real8_t width, real8_t height, real8_t theta = 0.0);

    virtual void pswrite   ( FILE* fp );

    real8_t      scaleX    ( real8_t x );
    real8_t      scaleY    ( real8_t y );

  }; // end class PSGraph::Draw

  
  // =====================================================================================
  // -------------------------------------------------------------------------------------
  class Page {                                                            // PSGraph::Page
    // -----------------------------------------------------------------------------------
  private:
    EMPTY_PROTOTYPE( Page );

  protected:
    std::list<PSGraph::Window*> wlist;

    std::string  name;
    size_t       page_number;

    void write_ps_page_header  ( FILE* psout );
    void write_ps_page_trailer ( FILE* psout );

  public:
    Page         ( size_t pn );
    ~Page        ( void );

    void setName ( std::string nm );

    bool add     ( PSGraph::Window* w, real8_t x, real8_t y );
    void pswrite ( FILE* fp );
  
  }; // end class PSGraph::Page


  // =====================================================================================
protected:
  EMPTY_PROTOTYPE( PSGraph );
  TLOGGER_HEADER( logger );
  
  PSGraph::Page** page;       ///< Array of pages
  size_t          num_page;   ///< Number of pages

  void write_ps_header  ( std::string fspc, FILE* psout );
  void write_ps_trailer ( FILE* psout );

public:
  PSGraph      ( size_t n = 1 );
  ~PSGraph     ( void );

  void setName ( size_t pn, std::string nm );
  void add     ( PSGraph::Window* w, size_t pn, real8_t x, real8_t y );
  void pswrite ( std::string fspc );

}; // end class PSGraph


// =======================================================================================
/** @brief 
 *
 */
// ---------------------------------------------------------------------------------------
inline  void PSGraph::Color::set( real8_t _r, real8_t _g, real8_t _b ) {
  // -------------------------------------------------------------------------------------
  r=_r;
  g=_g;
  b=_b;
  correct();
}


// =======================================================================================
/**
 *
 */
// ---------------------------------------------------------------------------------------
inline  void PSGraph::Color::copy( Color& C ) {
  // -------------------------------------------------------------------------------------
  r=C.r;
  g=C.g;
  b=C.b;
}


// =======================================================================================
/** @brief Set Name.
 *  @param[in] nm page name
 */
// ---------------------------------------------------------------------------------------
inline  void PSGraph::Page::setName ( std::string nm ) {
  // -------------------------------------------------------------------------------------
  name = nm;
}


// =======================================================================================
/** @brief Scale.
 *  @param[in] x coordinate in world coordinates.
 *  @return coordinate in device coordinates.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t PSGraph::Draw::scaleX( real8_t x ) {
  // -------------------------------------------------------------------------------------
  return ((slope_x * x) + inter_x);
}


// =======================================================================================
/** @brief Scale.
 *  @param[in] y coordinate in world coordinates.
 *  @return coordinate in device coordinates.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t PSGraph::Draw::scaleY( real8_t y ) {
  // -------------------------------------------------------------------------------------
  return ((slope_y * y) + inter_y);
}


// =======================================================================================
/** @brief Draw a circle.
 *  @param[in] xc x coordinate of the center of the ellipse.
 *  @param[in] yc y coordinate of the center of the ellipse.
 *  @param[in] r  value of the semi-minor axis.
 *  @param[in] parts number of segments.
 *
 *  Draw an ellipse centered at (x,y) and rotated theta radians.
 */
// ---------------------------------------------------------------------------------------
inline  void PSGraph::Draw::drawCircle( real8_t xc, real8_t yc, real8_t r, size_t parts ) {
  // -------------------------------------------------------------------------------------
  drawEllipse( xc, yc, r, r, 0.0, parts );
}

    
// =======================================================================================
/** @brief Draw a circle.
 *  @param[in] xc x coordinate of the center of the ellipse.
 *  @param[in] yc y coordinate of the center of the ellipse.
 *  @param[in] r  value of the semi-minor axis.
 *  @param[in] parts number of segments.
 *
 *  Draw an ellipse centered at (x,y) and rotated theta radians.
 */
// ---------------------------------------------------------------------------------------
inline  void PSGraph::Draw::fillCircle( real8_t xc, real8_t yc, real8_t r, size_t parts ) {
  // -------------------------------------------------------------------------------------
  fillEllipse( xc, yc, r, r, 0.0, parts );
}


// ==========================================================================================
/** @brief Draw Polygon.
 *  @param[in] x array of x world coordinates.
 *  @param[in] y array of y world coordinates.
 *  @param[in] n number of coordinates to use ( n <= x.length )
 *
 *  Draw a polygon defined by a set of vertices.
 */
// ------------------------------------------------------------------------------------------
inline  void PSGraph::Draw::drawPolygon( real8_t* x, real8_t* y, size_t n ) {
  // ----------------------------------------------------------------------------------------
  PSGraph::Draw::drawFillPolygon( x, y, n, false );
}


// ==========================================================================================
/** @brief Fill Polygon.
 *  @param[in] x array of x world coordinates.
 *  @param[in] y array of y world coordinates.
 *  @param[in] n number of coordinates to use ( n <= x.length )
 *
 *  Fill a polygon defined by a set of vertices and fill.
 */
// ------------------------------------------------------------------------------------------
inline  void PSGraph::Draw::fillPolygon( real8_t* x, real8_t* y, size_t n ) {
  // ----------------------------------------------------------------------------------------
  PSGraph::Draw::drawFillPolygon( x, y, n, true );
}


// ==========================================================================================
    /** @brief Draw Rectangle.
     *  @param[in] x1 lower left  in device x coordinate
     *  @param[in] y1 lower left  in device y coordinate
     *  @param[in] x2 upper right in device x coordinate
     *  @param[in] y2 upper right in device x coordinate
     *
     *  Draw a rectangle in this window.
     */
// ------------------------------------------------------------------------------------------
inline  void PSGraph::Draw::drawRectangle( real8_t x1, real8_t y1, real8_t x2, real8_t y2 ) {
  // ----------------------------------------------------------------------------------------
  PSGraph::Draw::drawFillRectangle( x1, y1, x2, y2, false );
}


// ==========================================================================================
    /** @brief Draw Rectangle.
     *  @param[in] x1 lower left  in device x coordinate
     *  @param[in] y1 lower left  in device y coordinate
     *  @param[in] x2 upper right in device x coordinate
     *  @param[in] y2 upper right in device x coordinate
     *
     *  Fill a rectangle in this window.
     */
// ------------------------------------------------------------------------------------------
inline  void PSGraph::Draw::fillRectangle( real8_t x1, real8_t y1, real8_t x2, real8_t y2 ) {
  // ----------------------------------------------------------------------------------------
  PSGraph::Draw::drawFillRectangle( x1, y1, x2, y2, true );
}


#endif


// =======================================================================================
// **                                   P S G R A P H                                   **
// ======================================================================== END FILE =====
