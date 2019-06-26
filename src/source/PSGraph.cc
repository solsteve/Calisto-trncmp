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

#define NULL_DRAW_NODE  static_cast<PSGraph::Draw::Node*>(0)
#define NULL_WINDOW     static_cast<PSGraph::Window*>(0)

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
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
PSGraph::Window::~Window( void ) {
  // -------------------------------------------------------------------------------------
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
    logger->error( "Failed to open temp file [%s]", temp_filename );
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
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
PSGraph::Draw::~Draw( void ) {
  // -------------------------------------------------------------------------------------
  fclose(file_handle);
  unlink(temp_filename);
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
PSGraph::Page::Page( size_t pn ) : firstWindow(0), name(0), page_number(0) {
  // -------------------------------------------------------------------------------------
  page_number = pn;
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
PSGraph::Page::~Page( void ) {
  // -------------------------------------------------------------------------------------
  logger->info("Do we need to clean up?");
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
  PSGraph::Draw::Node* temp = new PSGraph::Draw::Node( w, firstWindow );
  w->setDevice( x, y );
  firstWindow = temp;
  return false;
}


// =======================================================================================
/** @brief Pop Window.
 *  @return pointer to a window.
 *
 *  Remove the top window from the window stack.
 */
// ---------------------------------------------------------------------------------------
PSGraph::Window* PSGraph::Page::pop( void ) {
  // -------------------------------------------------------------------------------------
  if ( NULL_DRAW_NODE == firstWindow ) {
    return NULL_WINDOW;
  }

  PSGraph::Draw::Node* temp = firstWindow;
  PSGraph::Window*     w    = temp->window;
  firstWindow  = temp->next;
  temp->window = NULL_WINDOW;
  temp->next   = NULL_DRAW_NODE;
  delete temp;
  return w;
}


// =======================================================================================
/** @brief Write.
 *  @param[in] fp pointer to a file handle.
 */
// ---------------------------------------------------------------------------------------
void PSGraph::Page::pswrite( FILE* fp ) {
  // -------------------------------------------------------------------------------------
  PSGraph::Page::write_ps_page_header( fp );

  for (PSGraph::Draw::Node* node = firstWindow; node; node = node->next) {
    node->window->pswrite( fp );
  }

  PSGraph::Page::write_ps_page_trailer( fp );
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
  if (static_cast<char*>(0) == name) {
    fprintf( psout, "%%%%Page: %u %u\n", page_number, page_number);
  } else {
    fprintf( psout, "%%%%Page: %s %u\n", name, page_number);
  }
  fprintf( psout, "%%%%--------------------------------------------------------------\n");
  fprintf( psout, "%%%%BeginPageSetup\n");
  fprintf( psout, "startpage\n");
  fprintf( psout, "TIMES\n");
  fprintf( psout, "%%%%EndPageSetup\n");
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
// **                                   P S G R A P H                                   **
// ======================================================================== END FILE =====
