// ====================================================================== BEGIN FILE =====
// **                              A B S O L U T E D A T E                              **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2013-2019, Stephen W. Soliday                                      **
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
/** @brief  Absolute Date
 *  @file   AbsoluteDate.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-15.
 *
 *  Provides the interface for a class to maintain date and time functions.
 */
// =======================================================================================


#ifndef __HH_ABSOLUTEDATE_TRNCMP
#define __HH_ABSOLUTEDATE_TRNCMP

#include <trncmp.hh>


// =======================================================================================
class AbsoluteDate {
  // -------------------------------------------------------------------------------------
 public:

  // =====================================================================================
  class Span {                                                           // AbsoluteDate::Span
    // -----------------------------------------------------------------------------------
   public:
    double span; ///< Seconds.

    Span   ( void );
    Span   ( real8_t sec );
    Span   ( const Span& S );
    ~Span  ( void );

    int    compare    ( const Span& S ) const;
    Span&  operator=  ( const Span& ) = default;
    Span&  operator+= ( const Span& S );
    Span&  operator-= ( const Span& S );
    Span&  operator+= ( const real8_t s );
    Span&  operator-= ( const real8_t s );
    Span&  operator*= ( const real8_t s );
    Span&  operator/= ( const real8_t s );

  }; // end class AbsoluteDate::Span

 public:
  // -----------------------------------------------------------------------------------

  Span  epoch;  ///< Number of seconds since 1970-Jan-01 00:00:00.0 UTC
 
  AbsoluteDate ( void );
  AbsoluteDate ( const real8_t jday );
  AbsoluteDate ( const AbsoluteDate& dt, double offset = D_ZERO );
  AbsoluteDate ( const int32_t yr,   const int32_t mo=0, const int32_t da=0,
             const int32_t hr=0, const int32_t mn=0, const int32_t sc=D_ZERO );

  AbsoluteDate& operator=  ( const AbsoluteDate& ) = default;

  int         compare      ( const AbsoluteDate& dt ) const;

  void        set          ( const int32_t yr,   const int32_t mo=0, const int32_t da=0,
                             const int32_t hr=0, const int32_t mn=0, const real8_t sc=D_ZERO,
                             const int32_t ut=0 );

  real8_t     getJD        ( void ) const;
  int32_t     getYear      ( void ) const;
  int32_t     getMonth     ( void ) const;
  int32_t     getDay       ( void ) const;
  int32_t     getDayOfYear ( void ) const;
  int32_t     getHour      ( void ) const;
  int32_t     getMinute    ( void ) const;
  real8_t     getSecond    ( void ) const;

  void        addDay       ( real8_t da );
  void        addHour      ( real8_t hr );
  void        addMinute    ( real8_t mn );
  void        addSecond    ( real8_t sc );
  
  void        fromString   ( std::string str );
  std::string toString     ( void ) const;
  
}; // end class AbsoluteDate


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::Span::Span( void ) : span( D_ZERO ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] sec seconds.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::Span::Span( real8_t sec ) : span( sec ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] S reference to another Span.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::Span::Span( const Span& S ) : span( S.span ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::Span::~Span( void ) {
  // -------------------------------------------------------------------------------------
  span = D_ZERO;
}


// =======================================================================================
/** @brief Compare.
 *  @param[in] S reference to another Span.
 *  @return -1 if S is less than this,
 *           0 if S and this are equal,
 *          +1 if S is greater than this.
 *
 *  Compare another Span to this one.
 */
// ---------------------------------------------------------------------------------------
inline  int AbsoluteDate::Span::compare( const Span& S ) const {
  // -------------------------------------------------------------------------------------
  return ( S.span < this->span ) ? (-1) : ( ( S.span > this->span ) ? (+1) : (0) );
}


// =======================================================================================
/** @brief Add.
 *  @param[in] S reference to another Span.
 *  @return a reference to this Span.
 *
 *  Add another's Span to this Span.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::Span& AbsoluteDate::Span::operator+=( const Span& S ) {
  // -------------------------------------------------------------------------------------
  this->span += S.span;
  return *this;
}


// =======================================================================================
/** @brief Subtract.
 *  @param[in] S reference to another Span.
 *  @return a reference to this Span.
 *
 *  Subtract another's Span from this Span.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::Span& AbsoluteDate::Span::operator-=( const Span& S ) {
  // -------------------------------------------------------------------------------------
  this->span -= S.span;
  return *this;
}


// =======================================================================================
/** @brief Add.
 *  @param[in] s seconds.
 *  @return a reference to this Span.
 *
 *  Add seconds to this Span.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::Span& AbsoluteDate::Span::operator+=( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->span += s;
  return *this;
}


// =======================================================================================
/** @brief Subtract.
 *  @param[in] s seconds.
 *  @return a reference to this Span.
 *
 *  Subtract seconds from this Span.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::Span& AbsoluteDate::Span::operator-=( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->span -= s;
  return *this;
}


// =======================================================================================
/** @brief Multiply.
 *  @param[in] x value.
 *  @return a reference to this Span.
 *
 *  Multiply this Span by the value x.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::Span& AbsoluteDate::Span::operator*=( const real8_t x ) {
  // -------------------------------------------------------------------------------------
  this->span *= x;
  return *this;
}


// =======================================================================================
/** @brief Divide.
 *  @param[in] x value.
 *  @return a reference to this Span.
 *
 *  Divide this Span by the value x.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::Span& AbsoluteDate::Span::operator/=( const real8_t x ) {
  // -------------------------------------------------------------------------------------
  this->span /= x;
  return *this;
}








// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::AbsoluteDate( void ) : epoch() {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] jday the Julian Day number.
 *
 *  Construct a new AbsoluteDate instance from the Julian Date.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::AbsoluteDate ( const real8_t jday ) : epoch() {
  // -------------------------------------------------------------------------------------
  epoch.span = (jday - 2.4405875e6) * 8.64e4;
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] dt reference to another AbsoluteDate.
 *  @param[in] offset seconds from dt. (*default: 0)
 *
 *  Construct a new AbsoluteDate instance that is dt plus offset seconds.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::AbsoluteDate ( const AbsoluteDate& dt, double offset ) : epoch(dt.epoch) {
  // -------------------------------------------------------------------------------------
  this->epoch += offset;
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] yr year.         (required)
 *  @param[in] mo month.        (defualt: 0)
 *  @param[in] da day of month. (defualt: 0)
 *  @param[in] hr hour.         (defualt: 0)
 *  @param[in] mn minute.       (defualt: 0)
 *  @param[in] sc second.       (defualt: 0.000)
 *
 *  Construct a new AbsoluteDate instance from a calendar date.
 */
// ---------------------------------------------------------------------------------------
inline  AbsoluteDate::AbsoluteDate ( const int32_t yr, const int32_t mo, const int32_t da,
                             const int32_t hr, const int32_t mn, const int32_t sc ) : epoch() {
  // -------------------------------------------------------------------------------------
  this->set( yr, mo, da, hr, mn, sc );
}


// =======================================================================================
/** @brief Compare.
 *  @param[in] dt reference to another AbsoluteDate.
 *  @return -1 if dt is less than this,
 *           0 if dt and this are equal,
 *          +1 if dt is greater than this.
 *
 *  Compare another AbsoluteDate to this one.
 */
// ---------------------------------------------------------------------------------------
inline  int AbsoluteDate::compare( const AbsoluteDate& dt ) const {
  // -------------------------------------------------------------------------------------
  return (this->epoch).compare( dt.epoch );
}


// =======================================================================================
/** @brief Add Days.
 *  @param[in] days days.
 *
 *  Add days * 86400.0 seconds to this AbsoluteDate.
 */
// ---------------------------------------------------------------------------------------
inline  void AbsoluteDate::addDay( real8_t days ) {
  // -------------------------------------------------------------------------------------
  this->epoch += (8.64e4 * days);
}


// =======================================================================================
/** @brief Add Hours.
 *  @param[in] hrs hours.
 *
 *  Add hrs * 3600.0 seconds to this AbsoluteDate.
 */
// ---------------------------------------------------------------------------------------
inline  void AbsoluteDate::addHour( real8_t hrs ) {
  // -------------------------------------------------------------------------------------
  this->epoch += (3.6e3 * hrs);
}


// =======================================================================================
/** @brief Add Minutes.
 *  @param[in] mns minutes.
 *
 *  Add mns * 60.0 seconds to this AbsoluteDate.
 */
// ---------------------------------------------------------------------------------------
inline  void AbsoluteDate::addMinute( real8_t mns ) {
  // -------------------------------------------------------------------------------------
  this->epoch += (mns * 6.0e10);
}


// =======================================================================================
/** @brief Add Seconds.
 *  @param[in] secs seconds.
 *
 *  Add secs seconds to this AbsoluteDate.
 */
// ---------------------------------------------------------------------------------------
inline  void AbsoluteDate::addSecond( real8_t secs ) {
  // -------------------------------------------------------------------------------------
  this->epoch += secs;
}

#endif


// =======================================================================================
// **                              A B S O L U T E D A T E                              **
// ======================================================================== END FILE =====
