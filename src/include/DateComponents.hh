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


#ifndef __HH_DATECOMP_TRNCMP
#define __HH_DATECOMP_TRNCMP

#include <trncmp.hh>

// =======================================================================================
class YearFactory {
  // -------------------------------------------------------------------------------------
 public:
  YearFactory          ( void ) {};
  virtual ~YearFactory ( void ) {};

  virtual  int32_t getYear               ( const int32_t jday ) = 0;
  virtual  int32_t getLastJ2000DayOfYear ( const int32_t year ) = 0;
  virtual  bool    isLeap                ( const int32_t year ) = 0;
}; // end class YearFactory;


// =======================================================================================
class ProlepticJulianFactory : public YearFactory {
  // -------------------------------------------------------------------------------------
 public:
  ProlepticJulianFactory          ( void );
  virtual ~ProlepticJulianFactory ( void );

  virtual int32_t getYear               ( const int32_t j2000Day );
  virtual int32_t getLastJ2000DayOfYear ( const int32_t year );
  virtual bool    isLeap                ( const int32_t year );

}; // end class LeapYearFactory


// =======================================================================================
class JulianFactory : public YearFactory {
  // -------------------------------------------------------------------------------------
 public:
  JulianFactory          ( void );
  virtual ~JulianFactory ( void );

  virtual int32_t getYear               ( const int32_t j2000Day );
  virtual int32_t getLastJ2000DayOfYear ( const int32_t year );
  virtual bool    isLeap                ( const int32_t year );

}; // end class LeapYearFactory


// =======================================================================================
class GregorianFactory : public YearFactory {
  // -------------------------------------------------------------------------------------
 public:
  GregorianFactory          ( void );
  virtual ~GregorianFactory ( void );

  virtual int32_t getYear               ( const int32_t j2000Day );
  virtual int32_t getLastJ2000DayOfYear ( const int32_t year );
  virtual bool    isLeap                ( const int32_t year );
  
}; // end class LeapYearFactory


// =======================================================================================
class MonthDayFactory {
  // -------------------------------------------------------------------------------------
 public:
  MonthDayFactory          ( void ) {};
  virtual ~MonthDayFactory ( void ) {};

  virtual  int32_t getMonth     ( const int32_t dayInYear ) = 0;
  virtual  int32_t getDay       ( const int32_t dayInYear, const int32_t month ) = 0;
  virtual  int32_t getDayInYear ( const int32_t month,     const int32_t day )   = 0;
}; // end class YearFactory;


// =======================================================================================
class LeapYearFactory : public MonthDayFactory {
  // -------------------------------------------------------------------------------------
 protected:
  static int32_t PrevMon[];
  
 public:
  LeapYearFactory          ( void );
  virtual ~LeapYearFactory ( void );

  virtual  int32_t getMonth     ( const int32_t dayInYear );
  virtual  int32_t getDay       ( const int32_t dayInYear, const int32_t month );
  virtual  int32_t getDayInYear ( const int32_t month,     const int32_t day );
  
}; // end class LeapYearFactory


// =======================================================================================
class CommonYearFactory : public MonthDayFactory {
  // -------------------------------------------------------------------------------------
 protected:
  static int32_t PrevMon[];
  
 public:
  CommonYearFactory          ( void );
  virtual ~CommonYearFactory ( void );

  virtual  int32_t getMonth     ( const int32_t dayInYear );
  virtual  int32_t getDay       ( const int32_t dayInYear, const int32_t month );
  virtual  int32_t getDayInYear ( const int32_t month,     const int32_t day );
  
}; // end class CommonYearFactory




// =======================================================================================
class DateComponents {
  // -------------------------------------------------------------------------------------
 public:
  /** J2000.0 Reference epoch: 2000-01-01. */
  static  DateComponents J2000_EPOCH;
  
  /** Java Reference epoch: 1970-01-01. */
  static  DateComponents UNIX_EPOCH;

  /** Reference epoch for modified julian dates: 1858-11-17. */
  static  DateComponents MODIFIED_JULIAN_EPOCH;

  /** Offset between J2000 epoch and modified julian day epoch. */
  static int32_t MJD_TO_J2000;

  /** Offset between J2000 epoch and UNIX epoch. */
  static int32_t UNIX_TO_J2000;

  // ----- Year factories -------------------------------
  static ProlepticJulianFactory PROLEPTIC_JULIAN_FACTORY;
  static JulianFactory          JULIAN_FACTORY;

  // ----- MonthDay factories ---------------------------
  static GregorianFactory       GREGORIAN_FACTORY;
  static LeapYearFactory        LEAP_YEAR_FACTORY;
  static CommonYearFactory      COMMON_YEAR_FACTORY;
  
 protected:
  int32_t year;       ///< Year number.
  int32_t month;      ///< Month number.
  int32_t day;        ///< Day number.

  void validate( void );


 public:
  DateComponents( void );

  DateComponents( const int32_t _year,
                  const int32_t _month,
                  const int32_t _day );

  DateComponents( const int32_t _year,
                  const int32_t _day_of_year );

  DateComponents( const int32_t _offset );

  DateComponents( const DateComponents& DC );

  DateComponents& operator=    ( const DateComponents& TC ) = default;
  void            copy         ( const DateComponents& TC );
  bool            equals       ( DateComponents& TC );
  int             compare      ( DateComponents& TC );
  
  void            set          ( const int32_t _year, const int32_t _month, const int32_t _day );
  void            set          ( const int32_t _year, const int32_t _day_of_year );
  void            set          ( const int32_t _offset );

  int32_t         getYear      ( void ) const;
  int32_t         getMonth     ( void ) const;
  int32_t         getDay       ( void ) const;
  int32_t         getDayOfYear ( void ) const;
  int32_t         getJ2000Day  ( void ) const;

  std::string           toString   ( void );
  static DateComponents fromString ( std::string str );

  int32_t               toJulianDate   ( void );
  static DateComponents fromJulianDate ( int32_t jday );

}; // end class DateComponents







// =======================================================================================
/** @brief Get Hours.
 *  @return hours.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t DateComponents::getYear( void ) const {
  // -------------------------------------------------------------------------------------
  return year;
}


// =======================================================================================
/** @brief Get Hours.
 *  @return hours.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t DateComponents::getMonth( void ) const {
  // -------------------------------------------------------------------------------------
  return month;
}


// =======================================================================================
/** @brief Get Hours.
 *  @return hours.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t DateComponents::getDay( void ) const {
  // -------------------------------------------------------------------------------------
  return day;
}


#endif


// =======================================================================================
// **                            D A T E C O M P O N E N T S                            **
// ======================================================================== END FILE =====
