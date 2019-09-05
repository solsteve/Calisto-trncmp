// ====================================================================== BEGIN FILE =====
// **                            D A T E C O M P O N E N T S                            **
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
/** @brief  Date Components
 *  @file   DateComponents.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-15.
 *
 *  Provides the interface for a class to maintain date functions.
 *
 *  @note Parts of this are borrowed heavily from OreKit 9.3.1
 *        Copyright 2002-2019 CS Systèmes d'Information
 *        Licensed to CS Systèmes d'Information (CS) under one or more
 *        contributor license agreements.
 */
// =======================================================================================


#include <DateComponents.hh>
#include <ISO8601.hh>


/** J2000.0 Reference epoch: 2000-01-01. */
DateComponents DateComponents::J2000_EPOCH(2000, 1, 1);
  
/** Java Reference epoch: 1970-01-01. */
DateComponents DateComponents::UNIX_EPOCH(1970, 1, 1);

/** Reference epoch for modified julian dates: 1858-11-17. */
DateComponents DateComponents::MODIFIED_JULIAN_EPOCH(1858, 11, 17);

/** Offset between J2000 epoch and modified julian day epoch. */
int32_t DateComponents::MJD_TO_J2000 = 51544L;

/** Offset between J2000 epoch and UNIX epoch. */
int32_t DateComponents::UNIX_TO_J2000 = 10957L;

  // ----- Year factories --------------------------------------
ProlepticJulianFactory DateComponents::PROLEPTIC_JULIAN_FACTORY;
JulianFactory          DateComponents::JULIAN_FACTORY;
GregorianFactory       DateComponents::GREGORIAN_FACTORY;

  // ----- MonthDay factories ----------------------------------
LeapYearFactory        DateComponents::LEAP_YEAR_FACTORY;
CommonYearFactory      DateComponents::COMMON_YEAR_FACTORY;

int32_t LeapYearFactory::PrevMon[]   = { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };
int32_t CommonYearFactory::PrevMon[] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };


// =======================================================================================
void DateComponents::validate( void ) {
  // -------------------------------------------------------------------------------------
  if ( 9999 < year  ) { throw std::invalid_argument( "Year is to large" );  }
  if (    1 > year  ) { throw std::invalid_argument( "Year is to small" );  }
  
  if (   12 < month ) { throw std::invalid_argument( "Month is to large" ); }
  if (    1 > month ) { throw std::invalid_argument( "Month is to small" ); }
  
  if (   31 < day   ) { throw std::invalid_argument( "Day is to large" );   }
  if (    1 > day   ) { throw std::invalid_argument( "Day is to small" );   }
}


// =======================================================================================
/** @brief Constructor
 */
// ---------------------------------------------------------------------------------------
DateComponents::DateComponents( void ) : year(1), month(1), day(1) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor
 *  @todo thow errors for invalid dates
 */
// ---------------------------------------------------------------------------------------
DateComponents::DateComponents( const int32_t _year,
                                const int32_t _month,
                                const int32_t _day ) :
    year(_year), month(_month), day(_day) {
  // -------------------------------------------------------------------------------------
  validate();
}


// =======================================================================================
/** @brief Constructor
 *  @todo thow errors for invalid dates
 */
// ---------------------------------------------------------------------------------------
DateComponents::DateComponents( const int32_t _year,
                                const int32_t _day_of_year ) : year(0), month(0), day(0) {
  // -------------------------------------------------------------------------------------
  set( _year, _day_of_year );
}


// =======================================================================================
/** @brief Constructor
 *  @todo thow errors for invalid dates
 */
// ---------------------------------------------------------------------------------------
DateComponents::DateComponents( const int32_t _offset ) : year(0), month(0), day(0) {
  // -------------------------------------------------------------------------------------
  set( _offset );
}


// =======================================================================================
/** @brief Constructor
 *  @todo thow errors for invalid dates
 */
// ---------------------------------------------------------------------------------------
DateComponents::DateComponents( const DateComponents& DC ) : year(0), month(0), day(0) {
  // -------------------------------------------------------------------------------------
  copy( DC );
}

  
// =======================================================================================
/** @brief Copy.
 *  @param[in] DC reference to a TimeComponents used as a source.
 */
// ---------------------------------------------------------------------------------------
void DateComponents::copy( const DateComponents& DC ) {
  // -------------------------------------------------------------------------------------
  this->year  = DC.year;
  this->month = DC.month;
  this->day   = DC.day;
}


// =======================================================================================
/** @brief Equals.
 *  @param[in] that Reference to aanother DateCompomnents class.
 *  @return true if the two DateComponents have matching elements.
 */
// ---------------------------------------------------------------------------------------
bool DateComponents::equals( DateComponents& that ) {
  // -------------------------------------------------------------------------------------
  if ( this->year  != that.year )  { return false; }
  if ( this->month != that.month ) { return false; }
  if ( this->day   != that.day )   { return false; }

  return true;
}


// =======================================================================================
/** @brief Compare to.
 *  @param[in] that Reference to another DateCompomnents class.
 *  @return -1 if this DateComponents is less than that.
 *           0 if this DateComponents is equal to  that.
 *          +1 if this DateComponents is greater than that.
 */
// ---------------------------------------------------------------------------------------
int DateComponents::compare( DateComponents& that ) {
  // -------------------------------------------------------------------------------------
  if ( this->year < that.year )   { return -1; }
  if ( this->year > that.year )   { return +1; }

  if ( this->month < that.month ) { return -1; }
  if ( this->month > that.month ) { return +1; }

  if ( this->day < that.day )     { return -1; }
  if ( this->day > that.day )     { return +1; }

  return 0;
}

  
// =======================================================================================
/** @brief 
 */
// ---------------------------------------------------------------------------------------
void DateComponents::set( const int32_t _year, const int32_t _month, const int32_t _day ) {
  // -------------------------------------------------------------------------------------
  year  = _year;
  month = _month;
  day   = _day;
  validate();
}


// =======================================================================================
/** @brief Set.
 *  @param _year        year number (may be 0 or negative for BC years)
 *  @param _day_of_year day number in the year from 1 to 366
 *
 *  Set a date from a year and day number.
 */
// ---------------------------------------------------------------------------------------
void DateComponents::set( const int32_t _year, const int32_t _day_of_year ) {
  // -------------------------------------------------------------------------------------
  DateComponents temp(_year - 1, 12, 31);
  int32_t off = temp.getJ2000Day() + _day_of_year;

  set( J2000_EPOCH.getJ2000Day() + off );
  
  if (_day_of_year != getDayOfYear()) {
    fprintf( stdout, "%d-%d-%d %d %d\n", year, month, day, _day_of_year, getDayOfYear() );
    throw std::invalid_argument( "Non existant day in year" ); 
  }
}




// =======================================================================================
/** @brief Set.
 *  @param _offset offset with respect to a J2000_EPOCH.
 *
 *  This follows the astronomical convention for calendars:
 *  it considers a year zero and 10 days are missing in 1582
 *  from 1582-10-15:               gregorian calendar
 *  from 0001-01-01 to 1582-10-04: julian calendar
 *  up to 0000-12-31:              proleptic julian calendar
 */
// ---------------------------------------------------------------------------------------
void DateComponents::set( const int32_t _offset ) {
  // -------------------------------------------------------------------------------------
  YearFactory* yFactory = dynamic_cast<YearFactory*>(&DateComponents::GREGORIAN_FACTORY);
  
  if (_offset < -152384) {
    if (_offset > -730122) {
      yFactory = dynamic_cast<YearFactory*>(&DateComponents::JULIAN_FACTORY);
    } else {
      yFactory = dynamic_cast<YearFactory*>(&DateComponents::PROLEPTIC_JULIAN_FACTORY);
    }
  }
  year = yFactory->getYear(_offset);
  const int32_t dayInYear = _offset - yFactory->getLastJ2000DayOfYear(year - 1);

  // handle month/day according to the year being a common or leap year
  MonthDayFactory* mdFactory = (yFactory->isLeap(year))                  ?
      dynamic_cast<MonthDayFactory*>(&DateComponents::LEAP_YEAR_FACTORY) :
      dynamic_cast<MonthDayFactory*>(&DateComponents::COMMON_YEAR_FACTORY);

  month = mdFactory->getMonth(dayInYear);
  day   = mdFactory->getDay(dayInYear, month);

  validate();
}


// =======================================================================================
/** @brief Get the day number in year.
 *  @return day number in year.
 *
 *  Day number in year is between 1 (January 1st) and either 365 or
 *  366 inclusive depending on year.
 */
// ---------------------------------------------------------------------------------------
int32_t DateComponents::getDayOfYear( void ) const {
  // -------------------------------------------------------------------------------------
  DateComponents temp(year - 1, 12, 31);
  return getJ2000Day() - temp.getJ2000Day();
}


// =======================================================================================
/** @brief Get the day number with respect to J2000 epoch.
 *  @return day number with respect to J2000 epoch.
 */
// ---------------------------------------------------------------------------------------
int32_t DateComponents::getJ2000Day( void ) const {
  // -------------------------------------------------------------------------------------
  YearFactory* yFactory = dynamic_cast<YearFactory*>(&DateComponents::GREGORIAN_FACTORY);

  if (year < 1583) {
    if (year < 1) {
      yFactory = dynamic_cast<YearFactory*>(&DateComponents::PROLEPTIC_JULIAN_FACTORY);
    } else {
      if ((year < 1582) || (month < 10) || ((month < 11) && (day < 5))) {
        yFactory = dynamic_cast<YearFactory*>(&DateComponents::JULIAN_FACTORY);
      }
    }
  }

  MonthDayFactory* mdFactory = (yFactory->isLeap(year))                  ?
      dynamic_cast<MonthDayFactory*>(&DateComponents::LEAP_YEAR_FACTORY) :
      dynamic_cast<MonthDayFactory*>(&DateComponents::COMMON_YEAR_FACTORY);

  return yFactory->getLastJ2000DayOfYear(year - 1) +
      mdFactory->getDayInYear(month, day);
}




// =======================================================================================
int32_t DateComponents::toJulianDate( void ) {
  // -------------------------------------------------------------------------------------
  return 2451544 + getJ2000Day();
}

// ---------------------------------------------------------------------------------------
DateComponents DateComponents::fromJulianDate( int32_t jday ) {
  // -------------------------------------------------------------------------------------
  return DateComponents( jday - 2451544 );
}





// =======================================================================================
/** @brief To String
 *  @return ISO 8601 formated string containing the date.
 */
// ---------------------------------------------------------------------------------------
std::string DateComponents::toString( void ) {
  // -------------------------------------------------------------------------------------
  ISO8601 P;
  P.setDate( year, month, day );
  return P.toString();
}


// =======================================================================================
/** @brief Parse a String
 *  @param[in] str ISO 8601 formated string containing the date.
 *  @return static instance of a TimeComponents class.
 */
// ---------------------------------------------------------------------------------------
DateComponents DateComponents::fromString ( std::string str ) {
  // -------------------------------------------------------------------------------------
  ISO8601 P( str );
  int32_t y = P.getYear();
  int32_t m = P.getMonth();
  int32_t d = P.getDay();

  return DateComponents(y,m,d);
}










// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
JulianFactory::JulianFactory( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
JulianFactory::~JulianFactory( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Year.
 *  @param[in] j2000Day day number with respect to J2000 epoch
 *  @return year number
 *
 *  Get the year number for a given day number with respect to J2000 epoch.
 */
// ---------------------------------------------------------------------------------------
int32_t JulianFactory::getYear(const int32_t j2000Day) {
  // -------------------------------------------------------------------------------------
  return  (int32_t) ((4l *  j2000Day + 2921948l) / 1461l);
}


// =======================================================================================
/** @brief J2000 Day Of Year.
 *  @param[in] year year number.
 *  @return day number with respect to J2000 epoch for new year's Eve.
 *
 *  Get the day number with respect to J2000 epoch for new year's Eve.
 */
// ---------------------------------------------------------------------------------------
int32_t JulianFactory::getLastJ2000DayOfYear(const int32_t year) {
  // -------------------------------------------------------------------------------------
  return 365 *  year + year / 4 - 730122;
}


// =======================================================================================
/** @brief Leap.
 *  @param[in] year year number.
 *  @return true if year is a leap year.
 *
 *  Check if a year is a leap or common year.
 */
// ---------------------------------------------------------------------------------------
bool JulianFactory::isLeap(const int32_t year) {
  // -------------------------------------------------------------------------------------
  return (year % 4) == 0;
}













// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
ProlepticJulianFactory::ProlepticJulianFactory( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
ProlepticJulianFactory::~ProlepticJulianFactory( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Year.
 *  @param[in] j2000Day day number with respect to J2000 epoch
 *  @return year number
 *
 *  Get the year number for a given day number with respect to J2000 epoch.
 */
// ---------------------------------------------------------------------------------------
int32_t ProlepticJulianFactory::getYear(const int32_t j2000Day) {
  // -------------------------------------------------------------------------------------
  return  (int) -((-4l * j2000Day - 2920488l) / 1461l);
}


// =======================================================================================
/** @brief J2000 Day Of Year.
 *  @param[in] year year number.
 *  @return day number with respect to J2000 epoch for new year's Eve.
 *
 *  Get the day number with respect to J2000 epoch for new year's Eve.
 */
// ---------------------------------------------------------------------------------------
int32_t ProlepticJulianFactory::getLastJ2000DayOfYear(const int32_t year) {
  // -------------------------------------------------------------------------------------
  return 365 * year + (year + 1) / 4 - 730123;
}


// =======================================================================================
/** @brief Leap.
 *  @param[in] year year number.
 *  @return true if year is a leap year.
 *
 *  Check if a year is a leap or common year.
 */
// ---------------------------------------------------------------------------------------
bool ProlepticJulianFactory::isLeap(const int32_t year) {
  // -------------------------------------------------------------------------------------
  return (year % 4) == 0;
}








// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
GregorianFactory::GregorianFactory( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
GregorianFactory::~GregorianFactory( void ) {
  // -------------------------------------------------------------------------------------
}

// =======================================================================================
/** @brief Year.
 *  @param[in] j2000Day day number with respect to J2000 epoch.
 *  @return year number.
 *
 *  Get the year number for a given day number with respect to J2000 epoch.
 */
// ---------------------------------------------------------------------------------------
int32_t GregorianFactory::getYear(const int32_t j2000Day) {
  // -------------------------------------------------------------------------------------
  // year estimate
  int year = (int) ((400l *  j2000Day + 292194288l) / 146097l);

  // the previous estimate is one unit too high in some rare cases
  // (240 days in the 400 years gregorian cycle, about 0.16%)
  if (j2000Day <= getLastJ2000DayOfYear(year - 1)) {
    --year;
  }

  // exact year
  return year;
}


// =======================================================================================
/** @brief J2000 Day Of Year.
 *  @param[in] year year number.
 *  @return day number with respect to J2000 epoch for new year's Eve.
 *
 *  Get the day number with respect to J2000 epoch for new year's Eve.
 */
// ---------------------------------------------------------------------------------------
int32_t GregorianFactory::getLastJ2000DayOfYear(const int32_t year) {
  // -------------------------------------------------------------------------------------
  return 365 *  year + year / 4 - year / 100 + year / 400 - 730120;
}


// =======================================================================================
/** @brief Leap.
 *  @param[in] year year number.
 *  @return true if year is a leap year.
 *
 *  Check if a year is a leap or common year.
 */
// ---------------------------------------------------------------------------------------
bool GregorianFactory::isLeap(const int32_t year) {
  // -------------------------------------------------------------------------------------
  return ((year % 4) == 0) && (((year % 400) == 0) || ((year % 100) != 0));
}








// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
LeapYearFactory::LeapYearFactory( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
LeapYearFactory::~LeapYearFactory( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Month.
 *  @param[in] dayInYear day number within year.
 *  @return month number.
 *
 *  Get the month number for a given day number within year.
 */
// ---------------------------------------------------------------------------------------
int32_t LeapYearFactory::getMonth( const int32_t dayInYear ) {
  // -------------------------------------------------------------------------------------
  return (dayInYear < 32) ? 1 : (10 *  dayInYear + 313) / 306;
}


// =======================================================================================
/** @brief Day.
 *  @param[in] dayInYear day number within year.
 *  @param[in] month month number.
 *  @return day number.
 *
 *  Get the day number for given month and day number within year.
 */
// ---------------------------------------------------------------------------------------
int32_t LeapYearFactory::getDay( const int32_t dayInYear, const int32_t month ) {
  // -------------------------------------------------------------------------------------
  return dayInYear - PrevMon[month];
}


// =======================================================================================
/** @brief Day In Year.
 *  @param[in] month month number.
 *  @param[in] day day number.
 *  @return day number within year.
 *
 *  Get the day number within year for given month and day numbers.
 */
// ---------------------------------------------------------------------------------------
int32_t LeapYearFactory::getDayInYear( const int32_t month, const int32_t day ) {
  // -------------------------------------------------------------------------------------
  return day + PrevMon[month];
}








// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
CommonYearFactory::CommonYearFactory( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
CommonYearFactory::~CommonYearFactory( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Month.
 *  @param[in] dayInYear day number within year.
 *  @return month number.
 *
 *  Get the month number for a given day number within year.
 */
// ---------------------------------------------------------------------------------------
int32_t CommonYearFactory::getMonth( const int32_t dayInYear ) {
  // -------------------------------------------------------------------------------------
  return (dayInYear < 32) ? 1 : (10 *  dayInYear + 323) / 306;
}


// =======================================================================================
/** @brief Day.
 *  @param[in] dayInYear day number within year.
 *  @param[in] month month number.
 *  @return day number.
 *
 *  Get the day number for given month and day number within year.
 */
// ---------------------------------------------------------------------------------------
int32_t CommonYearFactory::getDay( const int32_t dayInYear, const int32_t month ) {
  // -------------------------------------------------------------------------------------
  return dayInYear - PrevMon[month];
}


// =======================================================================================
/** @brief Day In Year.
 *  @param[in] month month number.
 *  @param[in] day day number.
 *  @return day number within year.
 *
 *  Get the day number within year for given month and day numbers.
 */
// ---------------------------------------------------------------------------------------
int32_t CommonYearFactory::getDayInYear( const int32_t month, const int32_t day ) {
  // -------------------------------------------------------------------------------------
  return day + PrevMon[month];
}


// =======================================================================================
// **                            D A T E C O M P O N E N T S                            **
// ======================================================================== END FILE =====
