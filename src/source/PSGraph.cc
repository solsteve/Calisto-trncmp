// ====================================================================== BEGIN FILE =====
// **                                   P S G R A P H                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2012, 19, Stephen W. Soliday                                       **
// **                          stephen.soliday@trncmp.org                               **
// **                          http://research.trncmp.org                               **
// **                                                                                   **
// **  -------------------------------------------------------------------------------  **
// **                                                                                   **
// **  This file, and associated source code, is not free software; you may not         **
// **  redistribute it and/or modify it. This library is currently in an on going       **
// **  development phase by its author and has, as yet, not been publicly distributed.  **
// **  Development of this library has been at the sole cost in both time and funding   **
// **  by its author. Until such a public release is made the author retains ALL RIGHTS **
// **  to this software. It is expected that if and when this library is deemed         **
// **  releasable it will be released under the GNU Public license for non-commercial   **
// **  use or with a restricted rights for government use. At that time each source     **
// **  file will contain either/both the standard GPL statement/disclaimer, and/or the  **
// **  DFARS Restricted Rights Legend.                                                  **
// **                                                                                   **
// **  This library exists at the present time WITHOUT ANY WARRANTY; without even the   **
// **  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.         **
// **  As you are not supposed to be in possession of this file if you use it,          **
// **  you use this code AT YOUR OWN RISK.                                              **
// **                                                                                   **
// ----- Modification History ------------------------------------------------------------
//
/** @brief  Multi-page Postscript Graphics.
 *  @file   PSGraph.cc
 *  @author Stephen W. Soliday
 *  @date 2012-06-17 Original release.
 *  @date 2019-Jun-23 CMake refactorization.
 *
 *  Provides the methods for multi-page postscript graphics.
 */
// =======================================================================================


#include <PSGraph.hh>
#include <sys/types.h>
#include <unistd.h>


PSGraph::Color PSGraph::Color::white   ( 1.0, 1.0, 1.0 );
PSGraph::Color PSGraph::Color::black   ( 0.0, 0.0, 0.0 );
PSGraph::Color PSGraph::Color::red     ( 1.0, 0.0, 0.0 );
PSGraph::Color PSGraph::Color::green   ( 0.0, 1.0, 0.0 );
PSGraph::Color PSGraph::Color::blue    ( 0.0, 0.0, 1.0 );
PSGraph::Color PSGraph::Color::cyan    ( 0.0, 1.0, 1.0 );
PSGraph::Color PSGraph::Color::magenta ( 1.0, 0.0, 1.0 );
PSGraph::Color PSGraph::Color::yellow  ( 1.0, 1.0, 0.0 );


int PSGraph::Draw::window_count = 0;


#define NULL_PAGE       static_cast<PSGraph::Page*>(0)


TLOGGER_REFERENCE( PSGraph, logger );


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
PSGraph::Color::Color( void ) : r(D_ZERO), g(D_ZERO), b(D_ZERO) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] _r value of red   component.
 *  @param[in] _g value of green component.
 *  @param[in] _b value of blue  component.
 */
// ---------------------------------------------------------------------------------------
PSGraph::Color::Color( real8_t _r, real8_t _g, real8_t _b ) : r(_r), g(_g), b(_b) {
  // -------------------------------------------------------------------------------------
  correct();
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] C reference to a souce Color.
 */
// ---------------------------------------------------------------------------------------
PSGraph::Color::Color( Color& C ) : r(C.r), g(C.g), b(C.b) {
  // -------------------------------------------------------------------------------------
  correct();
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
PSGraph::Color::~Color( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Correction.
 *
 *  Correct the color range
 */
// ---------------------------------------------------------------------------------------
void PSGraph::Color::correct( void ) {
  // -------------------------------------------------------------------------------------
  if (r < D_ZERO) { r = D_ZERO; }  if (r > D_ONE) { r = D_ONE; }
  if (g < D_ZERO) { g = D_ZERO; }  if (g > D_ONE) { g = D_ONE; }
  if (b < D_ZERO) { b = D_ZERO; }  if (b > D_ONE) { b = D_ONE; }
}








// =======================================================================================
/** @brief Constructor.
 *  Create an empty object.
 */
// ---------------------------------------------------------------------------------------
PSGraph::Window::Window( void ) :
    device_width(0), device_height(0), device_x(0), device_y(0) {
  // -------------------------------------------------------------------------------------
  std::cout << "Window()\n";
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] dev_width  window width  in device coordinates (inches).
 *  @param[in] dev_height window height in device coordinates (inches).
 */
// ---------------------------------------------------------------------------------------
PSGraph::Window::Window( real8_t dev_width, real8_t dev_height ) :
    device_width(0), device_height(0), device_x(0), device_y(0) {
  // -------------------------------------------------------------------------------------
  device_width  = dev_width;
  device_height = dev_height;
  std::cout << "Window()\n";
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
PSGraph::Window::~Window( void ) {
  // -------------------------------------------------------------------------------------
device_width  = 0.0;
device_height = 0.0;
device_x      = 0.0;
device_y      = 0.0;
  std::cout << "~Window()\n";
}


// =======================================================================================
/** @brief Set Position.
 *  @param[in] x window position in device coordinates (inches).
 *  @param[in] y window position in device coordinates (inches).
 */
// ---------------------------------------------------------------------------------------
void PSGraph::Window::setDevice( real8_t x, real8_t y ) {
  // -------------------------------------------------------------------------------------
  device_x = x;
  device_y = y;
}








// =======================================================================================
/** @brief Initialize.
 *  @param[in] dw window width  in device coordinates (inches).
 *  @param[in] dh window height in device coordinates (inches).
 *  @param[in] x1 windows lower left  device x coordinate
 *  @param[in] y1 windows lower left  device y coordinate
 *  @param[in] x2 windows upper right device x coordinate
 *  @param[in] y2 windows upper right device x coordinate
 *  @return the true on error.
 *
 *  Initialize the physical position of this object on a device.
 */
// ---------------------------------------------------------------------------------------
bool PSGraph::Draw::init( real8_t, real8_t,
                          real8_t x1, real8_t y1, real8_t x2, real8_t y2 ) {
  // -------------------------------------------------------------------------------------
  PSGraph::Draw::window_count += 1;
  id = PSGraph::Draw::window_count;
  temp_filename = new char[MAXPATHLEN];
  sprintf( temp_filename, "pswork_%d_%d.tmp", (int)getpid(), id );
  if ( static_cast<FILE*>(0) == ( file_handle = fopen( temp_filename, "a+" ) ) ) {
    logger->error( LOCATION, "Failed to open temp file [%s]", temp_filename );
    exit(1);
  }

  world_x1   = x1;
  world_x2   = x2;
  world_y1   = y1;
  world_y2   = y2;

  real8_t dx = world_x2 - world_x1;
  real8_t dy = world_y2 - world_y1;

  slope_x    = device_width  / dx;
  slope_y    = device_height / dy;

  inter_x    = -slope_x * world_x1;
  inter_y    = -slope_y * world_y1;

  return false;
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] dw window width  in device coordinates (inches).
 *  @param[in] dh window height in device coordinates (inches).
 *  @param[in] x1 windows lower left  device x coordinate
 *  @param[in] y1 windows lower left  device y coordinate
 *  @param[in] x2 windows upper right device x coordinate
 *  @param[in] y2 windows upper right device x coordinate
 */
// ---------------------------------------------------------------------------------------
PSGraph::Draw::Draw( real8_t dev_width, real8_t dev_height,
                     real8_t x1, real8_t y1, real8_t x2, real8_t y2 ) :
    PSGraph::Window(dev_width, dev_height), 
    id(0), temp_filename(0), file_handle(0), world_x1(0.0), world_x2(0.0), world_y1(0.0),
    world_y2(0.0), slope_x(0.0), slope_y(0.0), inter_x(0.0), inter_y(0.0), last(), saved() {
  // -------------------------------------------------------------------------------------
  this->init(dev_width, dev_height, x1, y1, x2, y2);
  std::cout << "  Draw (id=" << id << ")\n";
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] dw window width  in device coordinates (inches).
 *  @param[in] dh window height in device coordinates (inches).
 */
// ---------------------------------------------------------------------------------------
PSGraph::Draw::Draw( real8_t dev_width, real8_t dev_height ) :
    PSGraph::Window(dev_width, dev_height), 
    id(0), temp_filename(0), file_handle(0), world_x1(0.0), world_x2(0.0), world_y1(0.0),
    world_y2(0.0), slope_x(0.0), slope_y(0.0), inter_x(0.0), inter_y(0.0), last(), saved()
{
  // -------------------------------------------------------------------------------------
  this->init(dev_width, dev_height, D_ZERO, D_ZERO, dev_width, dev_height);
  std::cout << "  Draw (id=" << id << ")\n";
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
PSGraph::Draw::~Draw( void ) {
  // -------------------------------------------------------------------------------------
  fclose(file_handle);
  unlink(temp_filename);
  std::cout << " ~Draw (id=" << id << ")\n";
}


// =======================================================================================
/** @brief Draw Line.
 *  @param[in] x1 starting x world coordinate for the line.
 *  @param[in] y1 starting y world coordinate for the line.
 *  @param[in] x2 ending   x world coordinate for the line.
 *  @param[in] y2 ending   y world coordinate for the line.
 *
 *  Draw a line between two world coordinates.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::Draw::drawLine( real8_t x1, real8_t y1, real8_t x2, real8_t y2 ) {
  // -------------------------------------------------------------------------------------
  fprintf( file_handle,
	   "%.5f %.5f %.5f %.5f DL\n",
	   scaleX(x1), scaleY(y1), scaleX(x2), scaleY(y2) );
}


// ==========================================================================================
/** @brief Draw a ray.
 *  @param[in] xc    x coordinate of the origin of the ray.
 *  @param[in] yc    y coordinate of the origin of the ray.
 *  @param[in] m     magnitude.
 *  @param[in] theta angle in radians of the semi-marjor axis 
 *                   counter clockwise from the positive x axis.
 *
 *  Draw a ray length m from (x,y) and rotated theta radians.
 */
// ------------------------------------------------------------------------------------------
void PSGraph::Draw::drawRay( real8_t xc, real8_t yc, real8_t m, real8_t theta ) {
  // ----------------------------------------------------------------------------------------
  real8_t x = xc + m*cos(theta);
  real8_t y = yc + m*sin(theta);
  drawLine( xc, yc, x, y );
}



// ==========================================================================================
/** @brief Draw border.
 *
 *  Draw a rectangle around the border of this window.
 */
// ------------------------------------------------------------------------------------------
void PSGraph::Draw::drawBorder( void ) {
  // ----------------------------------------------------------------------------------------
  drawLine( world_x1, world_y1,  world_x1, world_y2 );
  drawLine( world_x1, world_y2,  world_x2, world_y2 );
  drawLine( world_x2, world_y2,  world_x2, world_y1 );
  drawLine( world_x2, world_y1,  world_x1, world_y1 );
}


// ==========================================================================================
/** @brief Draw Polygon.
 *  @param[in] x array of x world coordinates.
 *  @param[in] y array of y world coordinates.
 *  @param[in] n number of coordinates to use ( n <= x.length )
 *  @param[in] fill fill the polygon if true.
 *
 *  Draw a polygon defined by a set of vertices and optionally fill.
 */
// ------------------------------------------------------------------------------------------
void PSGraph::Draw::drawFillPolygon( real8_t* x, real8_t* y, size_t n, bool fill ) {
  // ----------------------------------------------------------------------------------------

  fprintf( file_handle, "newpath\n  %.5f %.5f moveto\n", scaleX(x[0]), scaleY(y[0]) );
  for (size_t i=1; i<n; i++) {
    fprintf( file_handle, "  %.5f %.5f lineto\n", scaleX(x[i]), scaleY(y[i]) );
  }
  fprintf( file_handle, "closepath " );

  if (fill) {
    fprintf( file_handle, "fill\n " );
  } else {
    fprintf( file_handle, "stroke\n " );
  }
}

// ==========================================================================================
    /** @brief Draw Rectangle.
     *  @param[in] x1 lower left  in device x coordinate
     *  @param[in] y1 lower left  in device y coordinate
     *  @param[in] x2 upper right in device x coordinate
     *  @param[in] y2 upper right in device x coordinate
     *  @param[in] fill fill the polygon if true.
     *
     *  Draw a rectangle in this window and optionally fill.
     */
// ------------------------------------------------------------------------------------------
void PSGraph::Draw::drawFillRectangle( real8_t x1, real8_t y1, real8_t x2, real8_t y2, bool fill ) {
  // ----------------------------------------------------------------------------------------
  real8_t x[4];
  real8_t y[4];

  x[0] = x1;     y[0] = y1;
  x[1] = x2;     y[1] = y1;
  x[2] = x2;     y[2] = y2;
  x[3] = x1;     y[3] = y2;

  if ( fill ) {
    fillPolygon( x, y, 4 );
  } else {
    drawPolygon( x, y, 4 );
  }
}


// ==========================================================================================
/** @brief Draw an ellipse.
 *  @param[in] xc    x coordinate of the center of the ellipse.
 *  @param[in] yc    y coordinate of the center of the ellipse.
 *  @param[in] a     value of the semi-major axis.
 *  @param[in] b     value of the semi-minor axis.
 *  @param[in] theta angle in radians of the semi-marjor axis 
 *               counter clockwise from the positive x axis.
 *  @param parts number of segments.
 *
 *  Draw an ellipse centered at (x,y) and rotated theta radians.
 */
// ------------------------------------------------------------------------------------------
void PSGraph::Draw::drawEllipse( real8_t xc, real8_t yc,
			  real8_t a, real8_t b, real8_t theta,
			  size_t parts ) {
  // ----------------------------------------------------------------------------------------
  real8_t T  = 0.0;
  real8_t dT = D_2PI / ((real8_t) parts);
  real8_t C  = cos(theta);
  real8_t S  = sin(theta);

  real8_t x0 = xc + C*a;
  real8_t y0 = yc + S*a;

  for (size_t i=0; i<parts; i++) {
    T += dT;
    real8_t X = a*cos(T);
    real8_t Y = b*sin(T);

    real8_t x1 = xc + C*X - S*Y;
    real8_t y1 = yc + S*X + C*Y;

    drawLine( x0, y0, x1, y1 );
    x0 = x1;
    y0 = y1;
  }
}


// ==========================================================================================
/** @brief Draw an ellipse.
 *  @param[in] xc    x coordinate of the center of the ellipse.
 *  @param[in] yc    y coordinate of the center of the ellipse.
 *  @param[in] a     value of the semi-major axis.
 *  @param[in] b     value of the semi-minor axis.
 *  @param[in] theta angle in radians of the semi-marjor axis 
 *                   counter clockwise from the positive x axis.
 *  @param[in] parts number of segments.
 *
 *  Draw an ellipse centered at (x,y) and rotated theta radians.
 */
// ------------------------------------------------------------------------------------------
void PSGraph::Draw::fillEllipse( real8_t xc, real8_t yc,
			  real8_t a, real8_t b, real8_t theta,
			  size_t parts ) {
  // ----------------------------------------------------------------------------------------
  real8_t T  = 0.0;
  real8_t dT = D_2PI / ((real8_t) parts);
  real8_t C  = cos(theta);
  real8_t S  = sin(theta);

  fprintf( file_handle, "newpath\n" );
  
  real8_t x0 = xc + C*a;
  real8_t y0 = yc + S*a;
  
  fprintf( file_handle, "%.5f %.5f moveto\n", scaleX(x0), scaleY(y0) );

  for (size_t i=0; i<parts; i++) {
    T += dT;
    real8_t X = a*cos(T);
    real8_t Y = b*sin(T);

    real8_t x1 = xc + C*X - S*Y;
    real8_t y1 = yc + S*X + C*Y;

    fprintf( file_handle, "%.5f %.5f lineto\n", scaleX(x1), scaleY(y1) );
  }

  fprintf( file_handle, "closepath fill\n" );
  
}



// =======================================================================================
/** @brief Write Text.
 *  @param[in] text string containing the text to write.
 *  @param[in] x1 starting x world coordinates.
 *  @param[in] y1 starting y world coordinates.
 *  @param[in] x2 width in world coordinates.
 *  @param[in] y2 height in world coordinates.
 *  @param[in] theta rotation about the starting coordinates in degrees counter clockwise.
 *
 *  Scale a string of text within a box of width and height. Place the text at the x and y
 *  coordinates and rotate it counter clockwise theta degrees.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::Draw::write( std::string text,
		    real8_t x1, real8_t y1, real8_t x2, real8_t y2, real8_t theta ) {
  // -------------------------------------------------------------------------------------
  real8_t x      = scaleX(x1);
  real8_t y      = scaleY(y1);
  real8_t width  = scaleX(x2) - x;
  real8_t height = scaleY(y2) - y;

  fprintf( file_handle, "%f %f %f %f %f (%s) BS\n", x, y, width, height, theta, text.c_str() );
}


// =======================================================================================
/** @brief Write Text.
 *  @param[in] text string containing the text to write.
 *  @param[in] x1 starting x device coordinates.
 *  @param[in] y1 starting y device coordinates.
 *  @param[in] x2 width in device coordinates.
 *  @param[in] y2 height in device coordinates.
 *  @param[in] theta rotation about the starting coordinates in degrees counter clockwise.
 *
 *  Scale a string of text within a box of width and height. Place the text at the x and y
 *  coordinates and rotate it counter clockwise theta degrees.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::Draw::write_inch( std::string text,
			 real8_t x, real8_t y, real8_t width, real8_t height, real8_t theta ) {
  // -------------------------------------------------------------------------------------
  fprintf( file_handle, "%f %f %f %f %f (%s) BS\n", x, y, width, height, theta, text.c_str() );
}










// ==========================================================================================
/** @brief Set Color.
 *  @param[in] C Color color.
 *
 *  Set the current Color value.
 */
// ------------------------------------------------------------------------------------------
void PSGraph::Draw::setRGB( Color& C ) {
  // ----------------------------------------------------------------------------------------
  last.copy( C );
  fprintf( file_handle, "%f %f %f setrgbcolor\n", last.r, last.g, last.b );
}


// ==========================================================================================
/** @brief Set Color.
 *  @param[in] r red.
 *  @param[in] g green.
 *  @param[in] b blue.
 *
 *  Set the current RGB value.
 */
// ------------------------------------------------------------------------------------------
void PSGraph::Draw::setRGB( real8_t r, real8_t g, real8_t b ) {
  // ----------------------------------------------------------------------------------------
  last.set( r, g, b );
  fprintf( file_handle, "%f %f %f setrgbcolor\n", last.r, last.g, last.b );
}



// ==========================================================================================
/** @brief Save Color.
 *
 *  Save the current drawing color.
 */
// ------------------------------------------------------------------------------------------
void PSGraph::Draw::saveColor( void ) {
  // ----------------------------------------------------------------------------------------
  saved.copy( last );
}


// ==========================================================================================
/** @brief Restore Color.
 *
 *  Restore the last saved drawing color.
 */
// ------------------------------------------------------------------------------------------
void PSGraph::Draw::restoreColor( void ) {
  // ----------------------------------------------------------------------------------------
  setRGB( saved.r, saved.g, saved.b );
}


// ==========================================================================================
/** @brief Set Font
 *  @param ftype font as defined by PSGraph constants
 */
// ------------------------------------------------------------------------------------------
void PSGraph::Draw::setFont( PSGraph::font_enum ftype ) {
  // ----------------------------------------------------------------------------------------
  switch(ftype) {
  case PSGraph::NORMAL: fprintf( file_handle, "TIMES\n"  ); break;
  case PSGraph::BOLD:   fprintf( file_handle, "TIMESB\n" ); break;
  case PSGraph::ITALIC: fprintf( file_handle, "TIMESI\n" ); break;
  default:
    MSG("What the frel");
    fprintf( file_handle, "TIMES\n"  ); break;
  }
}










// =======================================================================================
/** @brief Write.
 *  @param[in] fp file handle.
 *
 *  Write postscript file.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::Draw::pswrite( FILE* fp ) {
  // -------------------------------------------------------------------------------------
  char* line = new char[256];

  write_ps_window_header(fp);

  rewind( file_handle );

  while( (char*)0 != fgets( line, 256, file_handle ) ) {
    fputs( line, fp );
  }

  write_ps_window_trailer(fp);

  delete line;
}








// =======================================================================================
/** @brief Constructor.
 *  @param[in] pn page number.
 */
// ---------------------------------------------------------------------------------------
PSGraph::Page::Page( size_t pn ) : wlist(), name(), page_number(0) {
  // -------------------------------------------------------------------------------------
  page_number = pn;
  std::cout << "Page(pn=" << page_number << ")\n";
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
PSGraph::Page::~Page( void ) {
  // -------------------------------------------------------------------------------------
  wlist.clear();
  std::cout << "~Page(pn=" << page_number << ")\n";
}


// ======================================================================================
/** @brief Add Window.
 *  @param[in] w pointer to a window.
 *  @param[in] x horizontal position on page in inches.
 *  @param[in] y vertical   position on page in inches.
 *  @return true if an error occurs.
 *
 *  Add a window to this page.
 */
// ---------------------------------------------------------------------------------------
bool PSGraph::Page::add( PSGraph::Window* w, real8_t x, real8_t y ) {
  // -------------------------------------------------------------------------------------
  w->setDevice( x, y );
  wlist.push_back(w);
  return false;
}


// =======================================================================================
/** @brief Write.
 *  @param[in] fp pointer to a file handle.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::Page::pswrite( FILE* fp ) {
  // -------------------------------------------------------------------------------------
  write_ps_page_header( fp );

 for (std::list<PSGraph::Window*>::iterator it=wlist.begin();
       it != wlist.end();
       ++it) {
    (*it)->pswrite( fp );
  }

  write_ps_page_trailer( fp );
}








// =======================================================================================
/** @brief Constructor.
 *  @param[in] n number of pages.
 */
// ---------------------------------------------------------------------------------------
PSGraph::PSGraph( size_t n ) : page(0), num_page(0) {
  // -------------------------------------------------------------------------------------
  num_page = n;
  page     = new PSGraph::Page*[n];
  for (size_t i=0; i<n; i++) {
    page[i] = new PSGraph::Page(i);
  }
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
PSGraph::~PSGraph( void ) {
  // -------------------------------------------------------------------------------------
  for ( size_t i=0; i<num_page; i++ ) {
    if ( NULL_PAGE != page[i] ) {
      delete page[i];
    }
    page[i] = NULL_PAGE;
  }
  delete page;
  num_page = 0;
}


// =======================================================================================
/** @brief Set Page Name.
 *  @param[in] pn page number.
 *  @param[in] nm name.
 *
 *  Set the name of an individual page.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::setName( size_t pn, std::string nm ) {
  // -----------------------------------------------------------------------------------
  if ( pn < num_page ) {
    if ( NULL_PAGE != page[pn] ) {
      page[pn]->setName( nm );
    } else {
      logger->error( LOCATION, "Page %d has not yet been allocated.", pn );
    }
  } else {
    logger->error( LOCATION, "Page %d is out of range, expected < %d.", pn, num_page );
  }
}


// =======================================================================================
/** @brief Add.
 *  @param[in] w  pointer to the window.
 *  @param[in] pn page number.
 *  @param[in] x  position in device coordinates.
 *  @param[in] y  position in device coordinates.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::add( PSGraph::Window* w, size_t pn, real8_t x, real8_t y ) {
  // -----------------------------------------------------------------------------------
  if ( pn < num_page ) {
    if ( NULL_PAGE != page[pn] ) {
      page[pn]->add( w, x, y );
    } else {
      logger->error( LOCATION, "Page %d has not yet been allocated.", pn );
    }
  } else {
    logger->error( LOCATION, "Page %d is out of range, expected < %d.", pn, num_page );
  }
}


// =======================================================================================
/** @brief Name.
 *  @return the name
 *
 */
// ---------------------------------------------------------------------------------------
void PSGraph::pswrite( std::string fspc ) {
  // -------------------------------------------------------------------------------------
  FILE* fp = fopen( fspc.c_str(), "w" );
  
  write_ps_header( fspc, fp );

  for (size_t i=0; i<num_page; i++) {
    page[i]->pswrite(fp);
  }

  write_ps_trailer(fp);

  fclose(fp);
}








// =======================================================================================
/** @brief Write Header.
 *  @param[in] psout pointer to an output file handle.
 *
 *  Write the postscript header for this window on the output stream.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::Window::write_ps_window_header( FILE* psout ) {
  // -------------------------------------------------------------------------------------
  fprintf( psout, "%%%%----------------------------------\n");
  fprintf( psout, "gsave\n");
  fprintf( psout, "%f %f translate\n", device_x, device_y);
}


// =======================================================================================
/** @brief Write the postscript header.
 *  @param[in] psout pointer to a file handle.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::Page::write_ps_page_header( FILE* psout ) {
  // -------------------------------------------------------------------------------------
  fprintf( psout, "%%%%==============================================================\n");
  if ( 0 < name.size() ) {
    fprintf( psout, "%%%%Page: %s %lu\n", name.c_str(), page_number);
  } else {
    fprintf( psout, "%%%%Page: %lu %lu\n", page_number, page_number);
  }
  fprintf( psout, "%%%%--------------------------------------------------------------\n");
  fprintf( psout, "%%%%BeginPageSetup\n");
  fprintf( psout, "startpage\n");
  fprintf( psout, "TIMES\n");
  fprintf( psout, "%%%%EndPageSetup\n");
}


// =X=====================================================================================
/** @brief Write postscript header.
 *  @param psfile_name name of the postscript file for Title: xxxx
 *  @param psout pointer to a file.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::write_ps_header( std::string psfile_name, FILE* psout ) {
  // -------------------------------------------------------------------------------------
  time_t t = time((time_t*)0);
  fprintf( psout, "%%!PS-Adobe-3.0\n");
  fprintf( psout, "%%%%============================================= BEGIN FILE =====\n");
  fprintf( psout, "%%%%Title: %s\n", psfile_name.c_str() );
  fprintf( psout, "%%%%Creator: PSGraph (C++) TRNCMP15\n");
  fprintf( psout, "%%%%CreationDate: %s", ctime(&t) );
  fprintf( psout, "%%%%Orientation: Landscape\n");
  fprintf( psout, "%%%%Pages: %lu\n", num_page);
  fprintf( psout, "%%%%BoundingBox: 0 0 612 792\n");
  fprintf( psout, "%%%%DocumentPaperSizes: letter\n");
  fprintf( psout, "%%Magnification: 1.0000\n");
  fprintf( psout, "%%%%EndComments\n");
  fprintf( psout, "%%%%--------------------------------------------------------------\n");
  fprintf( psout, "%%%%BeginSetup\n");
  fprintf( psout, "[{\n");
  fprintf( psout, "%%%%BeginFeature: *PageRegion Letter\n");
  fprintf( psout, "<</PageSize [612 792]>> setpagedevice\n");
  fprintf( psout, "%%%%EndFeature\n");
  fprintf( psout, "} stopped cleartomark\n");
  fprintf( psout, "%%%%EndSetup\n");
  fprintf( psout, "%%%%--------------------------------------------------------------\n");
  fprintf( psout, "%%%%BeginProlog\n");
  fprintf( psout, "%%%%----------------------\n");
  fprintf( psout, "\n");
  fprintf( psout, "userdict /forms_ops 10 dict dup begin put\n");
  fprintf( psout, "\n");
  fprintf( psout, "/StartEPSF { %% prepare for EPSF inclusion\n");
  fprintf( psout, "userdict begin\n");
  fprintf( psout, "/PreEPS_state save def\n");
  fprintf( psout, "/dict_stack countdictstack def\n");
  fprintf( psout, "/ops_count count 1 sub def\n");
  fprintf( psout, "/showpage {} def\n");
  fprintf( psout, "} bind def\n");
  fprintf( psout, "\n");
  fprintf( psout, "/EPSFCleanUp { %% clean up after EPSF inclusion\n");
  fprintf( psout, "count ops_count sub {pop} repeat\n");
  fprintf( psout, "countdictstack dict_stack sub {end} repeat\n");
  fprintf( psout, "PreEPS_state restore\n");
  fprintf( psout, "end %% userdict\n");
  fprintf( psout, "} bind def\n");
  fprintf( psout, "\n");
  fprintf( psout, "%%%%----------------------\n");
  fprintf( psout, "\n");
  fprintf( psout, "/$PSGDict 200 dict def\n");
  fprintf( psout, "/$PSGBegin {$PSGDict begin /$PSGSaveState save def} def\n");
  fprintf( psout, "/$PSGEnd   {$PSGSaveState restore end} def\n");
  fprintf( psout, "%%%%----------------------\n");
  fprintf( psout, "/startpage {\n");
  fprintf( psout, "save\n");
  fprintf( psout, "newpath 0 792 moveto 0 0 lineto 612 0\n");
  fprintf( psout, "lineto 612 792 lineto closepath clip newpath\n");
  fprintf( psout, "$PSGBegin\n");
  fprintf( psout, "10 setmiterlimit 0 setlinejoin 0 setlinecap 0 setlinewidth\n");
  fprintf( psout, "612 0 translate 90 rotate 72 72 scale\n");
  fprintf( psout, "} bind def\n");
  fprintf( psout, "%%%%----------------------\n");
  fprintf( psout, "/stoppage { $PSGEnd restore } bind def\n");
  fprintf( psout, "/TIMESB { /Times-Bold findfont setfont } bind def\n");
  fprintf( psout, "/TIMESI { /Times-Italic findfont setfont } bind def\n");
  fprintf( psout, "/TIMES  { /Times findfont setfont } bind def\n");
  fprintf( psout, "/DL { newpath moveto lineto stroke } bind def\n");
  fprintf( psout, "/DR { newpath rectstroke } bind def\n");
  fprintf( psout, "/BS { %% x, y, width, height, string\n");
  fprintf( psout, "gsave\n");
  fprintf( psout, "  /str exch def /rot exch def /hgt exch def /wdt exch def\n");
  fprintf( psout, "  /yco exch def /xco exch def\n");
  fprintf( psout, "  xco yco translate 0 0 moveto rot rotate\n");
  fprintf( psout, "  wdt str stringwidth pop div hgt scale str show\n");
  fprintf( psout, "grestore\n");
  fprintf( psout, "} bind def\n");
  fprintf( psout, "%%%%EndProlog\n");
}







// =======================================================================================
/** @brief Write Trailer.
 *  @param[in] psout pointer to an output file handle.
 *
 *  Write the postscript trailer for this window on the output stream.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::Window::write_ps_window_trailer( FILE* psout ) {
  // -------------------------------------------------------------------------------------
  fprintf( psout, "grestore\n");
}


// =======================================================================================
/** @brief Write the postscript trailer.
 *  @param[in] psout pointer to a file handle.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::Page::write_ps_page_trailer( FILE* psout ) {
  // -------------------------------------------------------------------------------------
  fprintf( psout, "%%%%----------------------------------\n");
  fprintf( psout, "stoppage\n");
  fprintf( psout, "showpage\n");
}


// =======================================================================================
/** @brief Write postscript trailer.
 *  @param psout pointer to a file.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::write_ps_trailer( FILE* psout ) {
  // -------------------------------------------------------------------------------------
  fprintf( psout, "%%%%=============================================== END FILE =====\n");
  fprintf( psout, "%%%%Trailer\n");
  fprintf( psout, "%%EOF\n");
}


// =======================================================================================
// **                                   P S G R A P H                                   **
// ======================================================================== END FILE =====
