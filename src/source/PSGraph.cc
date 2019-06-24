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
PSGraph::Color::Color( void ) : r(N_ZERO), g(N_ZERO), b(N_ZERO) {
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
  if (r < N_ZERO) { r = N_ZERO; }  if (r > N_ONE) { r = N_ONE; }
  if (g < N_ZERO) { g = N_ZERO; }  if (g > N_ONE) { g = N_ONE; }
  if (b < N_ZERO) { b = N_ZERO; }  if (b > N_ONE) { b = N_ONE; }
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
bool PSPage::add( PSWindow* w, real8_t x, real8_t y ) {
  // -------------------------------------------------------------------------------------
  PSDrawNode* temp = new PSDrawNode( w, firstWindow );
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
void PSGraph:Window::write_ps_window_header( FILE* psout ) {
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
void PSPage::write_ps_page_header( FILE* psout ) {
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
void PSGraph:Window::write_ps_window_trailer( FILE* psout ) {
  // -------------------------------------------------------------------------------------
  fprintf( psout, "grestore\n");
}


// =======================================================================================
/** @brief Write the postscript trailer.
 *  @param[in] psout pointer to a file handle.
 */
// ---------------------------------------------------------------------------------------
void PSPage::write_ps_page_trailer( FILE* psout ) {
  // -------------------------------------------------------------------------------------
  fprintf( psout, "%%%%----------------------------------\n");
  fprintf( psout, "stoppage\n");
  fprintf( psout, "showpage\n");
}











// =======================================================================================
// **                                   P S G R A P H                                   **
// ======================================================================== END FILE =====
