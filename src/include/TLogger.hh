// ====================================================================== BEGIN FILE =====
// **                                   T L O G G E R                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2013, 2019  Stephen W. Soliday                                     **
// **                            stephen.soliday@trncmp.org                             **
// **                            http://research.trncmp.org                             **
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
/** @brief  Extended math functions
 *  @file   mathdef.hh
 *  @author Stephen W. Soliday
 *  @date   2013-07-12  Original release.
 *  @date   2019-Apr-11 CMake refactorization.
 *
 *  Provides the interface for a console/file logging system.
 */
// =======================================================================================


#ifndef __HH_TLOGGER_TRNCMP
#define __HH_TLOGGER_TRNCMP

#include <trncmp.hh>
#include <stdarg.h>
#include <sys/types.h>

// =======================================================================================
/** @brief Console/file logger
 *
 *  Provides console and file logging system with custom abort.
 */
// ---------------------------------------------------------------------------------------
class TLogger {
  // -------------------------------------------------------------------------------------
 public:

  static const int UNSET;     ///< Level is not set
  static const int CRITICAL;  ///< Level is set to Critical
  static const int ERROR;     ///< Level is set to Error
  static const int WARN;      ///< Level is set to Warning
  static const int INFO;      ///< Level is set to Information
  static const int DEBUG;     ///< Level is set to Debugging

  // ===================================================
  /** @brief Abort handler
   */
  // ---------------------------------------------------
  class AbortHandler {          // TLogger::AbortHandler
    // -------------------------------------------------
   public:
    AbortHandler() {};          ///< defualt constructor
    virtual ~AbortHandler() {}; ///< defualt destructor
    virtual void handle( int n ) = 0;
  };

  ~TLogger( void );

  static TLogger* getInstance ( void );
  static void     delInstance ( void );
  static char*    TimeStamp   ( char* buffer = static_cast<char*>(0) );

  void on      ( void );
  void off     ( void );

  void message ( int level, const char* fmt, va_list list, char* extra = static_cast<char*>(0) );
  void message ( int level, char* extra = static_cast<char*>(0) );

  void critical ( const char* fmt, ... );
  void error    ( const char* fmt, ... );
  void warn     ( const char* fmt, ... );
  void info     ( const char* fmt, ... );
  void debug    ( const char* fmt, ... );

  void critical ( int line, const char* file, const char* func, const char* fmt, ... );
  void error    ( int line, const char* file, const char* func, const char* fmt, ... );
  void warn     ( int line, const char* file, const char* func, const char* fmt, ... );
  void info     ( int line, const char* file, const char* func, const char* fmt, ... );
  void debug    ( int line, const char* file, const char* func, const char* fmt, ... );

  void critical ( int line, const char* file, const char* func );
  void error    ( int line, const char* file, const char* func );
  void warn     ( int line, const char* file, const char* func );
  void info     ( int line, const char* file, const char* func );
  void debug    ( int line, const char* file, const char* func );

  void setAbortLevel         ( int level );
  void registerAbortHandler  ( AbortHandler* ah, int new_level = TLogger::UNSET );
  void setConsoleLevel       ( int level );
  void setWriteLevel         ( int level );
  void setLogfile            ( const char* fspc, int new_level = TLogger::UNSET );

 private:
  static TLogger*      theInstance;
  static AbortHandler* DEFAULT_ABORT_HANDLER;

  char* format_location( int line, const char* file, const char* func );

  TLogger( void );

 protected:
  TLogger(const TLogger&);            ///< dummy entry
  TLogger& operator=(const TLogger&); ///< dummy entry

  int           console_level;   ///< Minimum level to write to the console
  int           write_level;     ///< Minimum level to write to the log file
  char*         logfile_name;    ///< Name of the file to log to
  int           abort_level;     ///< Minimum level to abort the process
  AbortHandler* abort_handler;   ///< Handler for custom abort actions
  bool          flag;            ///< Toggle loging without altering properties
};

#define LOCATION  __LINE__, __FILE__, __PRETTY_FUNCTION__

#define TLOGGER_REFERENCE(_clnam, _vnam)  TLogger* _clnam::_vnam = TLogger::getInstance()
#define TLOGGER_INSTANCE(_vnam)           static TLogger*  _vnam = TLogger::getInstance()
#define TLOGGER_HEADER(_vnam)             static TLogger*  _vnam

#endif


// =======================================================================================
// **                                   T L O G G E R                                   **
// ======================================================================== END FILE =====
