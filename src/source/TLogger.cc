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
 *  @file   TLogger.cc
 *  @author Stephen W. Soliday
 *  @date   2013-07-12  Original release.
 *  @date   2019-Apr-26 CMake refactorization.
 *
 *  Provides the interface for a console/file logging system.
 */
// =======================================================================================


#include <TLogger.hh>
#include <time.h>


TLogger* TLogger::theInstance = static_cast<TLogger*>(0);

const int TLogger::UNSET    = 0;
const int TLogger::CRITICAL = 1;
const int TLogger::ERROR    = 2;
const int TLogger::WARN     = 3;
const int TLogger::INFO     = 4;
const int TLogger::DEBUG    = 5;


// =======================================================================================
/** @brief Default Abort Handler.
 */
// ---------------------------------------------------------------------------------------
class __DefaultAbortHandler : public TLogger::AbortHandler {
  // -------------------------------------------------------------------------------------
  /** @brief Default abort handler.
   *  @param n exit code.
   *
   *  Provide a default message for application abort.
   */
  // -------------------------------------------------------------------------------------
  virtual void handle( int n ) {
    // -----------------------------------------------------------------------------------
    std::cout << " Performing a default TLogger abort with exit code: " + n << std::endl;
    exit(n);
  };
};


static __DefaultAbortHandler __TDAH;

TLogger::AbortHandler* TLogger::DEFAULT_ABORT_HANDLER = &__TDAH;


// =======================================================================================
/** @brief Timestamp.
 *  @param buffer pointer to a buffer to store the time stamp. ( Defaul: null ).
 *  @return pointer to a character array containing the formated time stamp..
 *
 *  Generate a formated time stamp. YYYYMM.DD hh:mm:ss Use the buffer provided.
 *  If the pointer to the buffer is null reuse the static allocation.
 */
// ---------------------------------------------------------------------------------------
char* TLogger::TimeStamp( char* buffer ) {
  // -------------------------------------------------------------------------------------
  static char default_buffer[96];
  char* P = buffer;
  if (static_cast<char*>(0) == P) {
    P = default_buffer;
  }

  time_t             raw;
  struct tm          temp;

  time( &raw );
  gmtime_r( &raw, &temp );

  sprintf( P,
	   "%04d%02d.%02d %02d:%02d:%02d",
	   temp.tm_year+1900, temp.tm_mon+1, temp.tm_mday,
	   temp.tm_hour, temp.tm_min, temp.tm_sec );

  return P;
}


// =======================================================================================
/** @brief Constructor.
 *
 *  Instantiate logger.
 */
// ---------------------------------------------------------------------------------------
TLogger::TLogger( void ) : console_level(0), write_level(0), logfile_name(0),
			   abort_level(0), abort_handler(0), flag(false) {
  // -------------------------------------------------------------------------------------
  console_level  = TLogger::INFO;
  write_level    = TLogger::WARN;
  logfile_name   = static_cast<char*>(0);
  abort_level    = TLogger::CRITICAL;
  abort_handler  = TLogger::DEFAULT_ABORT_HANDLER;
  flag           = true;
}

// =======================================================================================
/** @brief Destructor.
 *
 *  Deallocate memory for this logger.
 */
// ---------------------------------------------------------------------------------------
TLogger::~TLogger( void ) {
  // -------------------------------------------------------------------------------------
  console_level  = TLogger::UNSET;
  write_level    = TLogger::UNSET;
  abort_level    = TLogger::UNSET;
  abort_handler  = TLogger::DEFAULT_ABORT_HANDLER;
  flag           = false;

  if ( static_cast<char*>(0) != logfile_name ) {
    delete logfile_name;
  }
  logfile_name = static_cast<char*>(0);
}


// =======================================================================================
/** @brief Request Instance.
 *  @return the singleton instance.
 *
 *  Return the singleton instance of this logger.
 */
// ---------------------------------------------------------------------------------------
TLogger* TLogger::getInstance( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<TLogger*>(0) == TLogger::theInstance ) {
    TLogger::theInstance = new TLogger();
  }

  return TLogger::theInstance;
}


// =======================================================================================
/** @brief Delete the single instance.
 *
 *  Delete the singleton instance.
 */
// ---------------------------------------------------------------------------------------
void TLogger::delInstance( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<TLogger*>(0) != TLogger::theInstance ) {
    delete TLogger::theInstance;
  }

  TLogger::theInstance = static_cast<TLogger*>(0);
}


// =======================================================================================
/** @brief On.
 *
 *  Turn the logging on.
 */
// ---------------------------------------------------------------------------------------
void TLogger::on( void ) {
  // -------------------------------------------------------------------------------------
  flag = true;
}


// =======================================================================================
/** @brief Off.
 *
 *  Turn the logging off with out altering the logger's current properties.
 */
// ---------------------------------------------------------------------------------------
void TLogger::off( void ) {
  // -------------------------------------------------------------------------------------
  flag = false;
}


// =======================================================================================
/** @brief Generate message.
 *  @param level message severity level.
 *  @param extra extra text.
 *
 *  Generate a log message. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::message( int level, char* extra ) {
  // -------------------------------------------------------------------------------------
  if ( flag ) {
    static const char* stamp = "UCEWID";
    static char        header[512];

    if ( static_cast<char*>(0) == extra ) {
      sprintf( header, "[%s] **%c**", TLogger::TimeStamp(), stamp[level%6] );
    } else {
      sprintf( header, "[%s] **%c** ( %s )", TLogger::TimeStamp(), stamp[level%6], extra );
    }

    // ----- console display (stderr) ----------------------------------------------------

    if (level <= console_level) {
      fprintf( stderr, "%s\n", header );
      fflush(stderr);
    }

    // ----- log to a file ---------------------------------------------------------------

    if ( static_cast<char*>(0) != logfile_name ) {
      if (level <= write_level) {
	FILE* fp = fopen( logfile_name, "a" );
	if (static_cast<FILE*>(0) == fp) {
	  fprintf( stderr, "[%s]: **W** Failed to open log file: %s\n",
		   header, logfile_name );
	} else {
	  fprintf( fp, "%s\n", header );
	  fflush(fp);
	  fclose(fp);
	}
      }
    }

    // ----- abort the program if this level is reached ----------------------------------

    if (level <= abort_level) {
      abort_handler->handle( level );
    }
  }
}


// =======================================================================================
/** @brief Generate message.
 *  @param level message severity level.
 *  @param fmt printf style format string.
 *  @param list variable parameters.
 *  @param extra extra text.
 *
 *  Generate a log message. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::message( int level, const char* fmt, va_list list, char* extra ) {
  // -------------------------------------------------------------------------------------
  if ( flag ) {
    static const char* stamp = "UCEWID";
    static char        header[512];

    sprintf( header, "[%s] **%c**", TLogger::TimeStamp(), stamp[level%6] );

    // ----- console display (stderr) ----------------------------------------------------

    if (level <= console_level) {
      fprintf( stderr, "%s ", header );
      vfprintf( stderr, fmt, list );
      if ( static_cast<char*>(0) != extra ) {
        fprintf( stderr, " ( %s )", extra );
      }
      fprintf( stderr, "\n" );
      fflush(stderr);
    }

    // ----- log to a file ---------------------------------------------------------------

    if ( static_cast<char*>(0) != logfile_name ) {
      if (level <= write_level) {
	FILE* fp = fopen( logfile_name, "a" );
	if (static_cast<FILE*>(0) == fp) {
	  fprintf( stderr, "[%s]: **W** Failed to open log file: %s\n",
		   header, logfile_name );
	} else {
	  fprintf( fp, "%s ", header );
	  vfprintf( fp, fmt, list );
          if ( static_cast<char*>(0) != extra ) {
            fprintf( fp, " ( %s )", extra );
          }        
	  fprintf( fp, "\n" );
	  fflush(fp);
	  fclose(fp);
	}
      }
    }

    // ----- abort the program if this level is reached ----------------------------------

    if (level <= abort_level) {
      abort_handler->handle( level );
    }
  }
}


// =======================================================================================
/** @brief Critical message.
 *  @param fmt printf style format string.
 *  @param ... variable parameters.
 *
 *  Generate a critical log message. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::critical( const char* fmt, ... ) {
  // -------------------------------------------------------------------------------------
  va_list  ap;
  va_start(ap, fmt);
  message(TLogger::CRITICAL, fmt, ap);
  va_end(ap);
}


// =======================================================================================
/** @brief Error message.
 *  @param fmt printf style format string.
 *  @param ... variable parameters.
 *
 *  Generate a error log message. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::error( const char* fmt, ... ) {
  // -------------------------------------------------------------------------------------
  va_list  ap;
  va_start(ap, fmt);
  message(TLogger::ERROR, fmt, ap);
  va_end(ap);
}


// =======================================================================================
/** @brief Warn message.
 *  @param fmt printf style format string.
 *  @param ... variable parameters.
 *
 *  Generate a warn log message. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::warn( const char* fmt, ... ) {
  // -------------------------------------------------------------------------------------
  va_list  ap;
  va_start(ap, fmt);
  message(TLogger::WARN, fmt, ap);
  va_end(ap);
}


// =======================================================================================
/** @brief Info message.
 *  @param fmt printf style format string.
 *  @param ... variable parameters.
 *
 *  Generate a info log message. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::info( const char* fmt, ... ) {
  // -------------------------------------------------------------------------------------
  va_list  ap;
  va_start(ap, fmt);
  message(TLogger::INFO, fmt, ap);
  va_end(ap);
}


// =======================================================================================
/** @brief Debug message.
 *  @param fmt printf style format string.
 *  @param ... variable parameters.
 *
 *  Generate a debug log message. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::debug( const char* fmt, ... ) {
  // -------------------------------------------------------------------------------------
  va_list  ap;
  va_start(ap, fmt);
  message(TLogger::DEBUG, fmt, ap);
  va_end(ap);
}


// =======================================================================================
/** @brief Format Location
 *  @param line line in the source code.
 *  @param file fullpath to the source code.
 *  @param name of the function.
 *  @return char pointer to a formated representation of the stack location.
 *
 *  Format the location information.
 */
// ---------------------------------------------------------------------------------------
char* TLogger::format_location( int line, const char* file, const char* func ) {
  // -------------------------------------------------------------------------------------
  static char buffer[1024];
  sprintf( buffer, "%s %s:%d", func, file, line);
  return buffer;
}


// =======================================================================================
/** @brief Critical message.
 *  @param file name of the source code file (__FILE__).
 *  @param func name of the calling function (__PRETTY_FUNCTION__)
 *  @param line source code line number      (__LINE__)
 *  @param fmt printf style format string.
 *  @param ... variable parameters.
 *
 *  Generate a critical log message, including the filename, function, and line number of the 
 *  calling function. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::critical( int line, const char* file, const char* func,
			const char* fmt, ... ) {
  // -------------------------------------------------------------------------------------
  va_list  ap;
  va_start(ap, fmt);
  message(TLogger::CRITICAL, fmt, ap, format_location(line, file, func) );
  va_end(ap);
}


// =======================================================================================
/** @brief Error message.
 *  @param file name of the source code file (__FILE__).
 *  @param func name of the calling function (__PRETTY_FUNCTION__)
 *  @param line source code line number      (__LINE__)
 *  @param fmt printf style format string.
 *  @param ... variable parameters.
 *
 *  Generate a error log message, including the filename, function, and line number of the 
 *  calling function. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::error( int line, const char* file, const char* func,
		     const char* fmt, ... ) {
  // -------------------------------------------------------------------------------------
  va_list  ap;
  va_start(ap, fmt);
  message(TLogger::ERROR, fmt, ap, format_location(line, file, func) );
  va_end(ap);
}


// =======================================================================================
/** @brief Warn message.
 *  @param file name of the source code file (__FILE__).
 *  @param func name of the calling function (__PRETTY_FUNCTION__)
 *  @param line source code line number      (__LINE__)
 *  @param fmt printf style format string.
 *  @param ... variable parameters.
 *
 *  Generate a warn log message, including the filename, function, and line number of the 
 *  calling function. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::warn( int line, const char* file, const char* func,
                    const char* fmt, ... ) {
  // -------------------------------------------------------------------------------------
  va_list  ap;
  va_start(ap, fmt);
  message(TLogger::WARN, fmt, ap, format_location(line, file, func) );
  va_end(ap);
}


// =======================================================================================
/** @brief Info message.
 *  @param file name of the source code file (__FILE__).
 *  @param func name of the calling function (__PRETTY_FUNCTION__)
 *  @param line source code line number      (__LINE__)
 *  @param fmt printf style format string.
 *  @param ... variable parameters.
 *
 *  Generate a info log message, including the filename, function, and line number of the 
 *  calling function. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::info( int line, const char* file, const char* func,
		    const char* fmt, ... ) {
  // -------------------------------------------------------------------------------------
  va_list  ap;
  va_start(ap, fmt);
  message(TLogger::INFO, fmt, ap, format_location(line, file, func) );
  va_end(ap);
}


// =======================================================================================
/** @brief Debug message.
 *  @param file name of the source code file (__FILE__).
 *  @param func name of the calling function (__PRETTY_FUNCTION__)
 *  @param line source code line number      (__LINE__)
 *  @param fmt printf style format string.
 *  @param ... variable parameters.
 *
 *  Generate a debug log message, including the filename, function, and line number of the 
 *  calling function. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::debug( int line, const char* file, const char* func,
		     const char* fmt, ... ) {
  // -------------------------------------------------------------------------------------
  va_list  ap;
  va_start(ap, fmt);
  message(TLogger::DEBUG, fmt, ap, format_location(line, file, func) );
  va_end(ap);
}


// =======================================================================================
/** @brief Critical message.
 *  @param file name of the source code file (__FILE__).
 *  @param func name of the calling function (__PRETTY_FUNCTION__)
 *  @param line source code line number      (__LINE__)
 *
 *  Generate a critical log message, including the filename, function, and line number of the 
 *  calling function. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::critical( int line, const char* file, const char* func ) {
  // -------------------------------------------------------------------------------------
  message(TLogger::CRITICAL, format_location(line, file, func) );
}


// =======================================================================================
/** @brief Error message.
 *  @param file name of the source code file (__FILE__).
 *  @param func name of the calling function (__PRETTY_FUNCTION__)
 *  @param line source code line number      (__LINE__)
 *
 *  Generate a error log message, including the filename, function, and line number of the 
 *  calling function. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::error( int line, const char* file, const char* func ) {
  // -------------------------------------------------------------------------------------
  message(TLogger::ERROR, format_location(line, file, func) );
}


// =======================================================================================
/** @brief Warn message.
 *  @param file name of the source code file (__FILE__).
 *  @param func name of the calling function (__PRETTY_FUNCTION__)
 *  @param line source code line number      (__LINE__)
 *
 *  Generate a warn log message, including the filename, function, and line number of the 
 *  calling function. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::warn( int line, const char* file, const char* func ) {
  // -------------------------------------------------------------------------------------
  message(TLogger::WARN, format_location(line, file, func) );
}


// =======================================================================================
/** @brief Info message.
 *  @param file name of the source code file (__FILE__).
 *  @param func name of the calling function (__PRETTY_FUNCTION__)
 *  @param line source code line number      (__LINE__)
 *
 *  Generate a info log message, including the filename, function, and line number of the 
 *  calling function. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::info( int line, const char* file, const char* func ) {
  // -------------------------------------------------------------------------------------
  message(TLogger::INFO, format_location(line, file, func) );
}


// =======================================================================================
/** @brief Debug message.
 *  @param line source code line number      (__LINE__)
 *  @param file name of the source code file (__FILE__).
 *  @param func name of the calling function (__PRETTY_FUNCTION__)
 *
 *  Generate a debug log message, including the filename, function, and line number of the 
 *  calling function. Format the message using printf formating.
 */
// ---------------------------------------------------------------------------------------
void TLogger::debug( int line, const char* file, const char* func ) {
  // -------------------------------------------------------------------------------------
  message(TLogger::DEBUG, format_location(line, file, func) );
}


// =======================================================================================
/** @brief Set abort level.
 *  @param level minimum level to generate an abort.
 *
 *  Set the minimum level for generating an abort.
 */
// ---------------------------------------------------------------------------------------
void TLogger::setAbortLevel( int level ) {
  // -------------------------------------------------------------------------------------
  abort_level = level;
}


// =======================================================================================
/** @brief Register abort handler.
 *  @param ah pointer to the abort handler class.
 *  @param new_level new minimum level to generate an abort. (default: no change)
 *
 *  Register a new abort handler with the logging system. Set the new level for
 *  generating an abort.
 */
// ---------------------------------------------------------------------------------------
void TLogger::registerAbortHandler( TLogger::AbortHandler* ah, int new_level ) {
  // -------------------------------------------------------------------------------------
  abort_handler = ah;

  if ( 0 < new_level ) { setAbortLevel( new_level ); }
}


// =======================================================================================
/** @brief Set the console level.
 *  @param level minimum level to write to the console.
 *
 *  Set the minimum level to write messages on the console.
 */
// ---------------------------------------------------------------------------------------
void TLogger::setConsoleLevel( int level ) {
  // -------------------------------------------------------------------------------------
  console_level = level;
}


// =======================================================================================
/** @brief Set the write level.
 *  @param level minimum level to write to the log file.
 *
 *  Set the minimum level to append messages to the log file.
 */
// ---------------------------------------------------------------------------------------
void TLogger::setWriteLevel( int level ) {
  // -------------------------------------------------------------------------------------
  write_level = level;
}


// =======================================================================================
/** @brief Set the log file.
 *  @param fspc full path to the file to append with new log entries.
 *  @param new_level new level at which to log to a file (default: no change).
 *
 *  Set the name of the logfile.
 */
// ---------------------------------------------------------------------------------------
void TLogger::setLogfile( const char* fspc, int new_level ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<char*>(0) == logfile_name ) {
    logfile_name = new char[ MAXPATHLEN ];
  }

  copy( logfile_name, fspc );

  if ( 0 < new_level ) { setWriteLevel( new_level ); }
}


// =======================================================================================
// **                                   T L O G G E R                                   **
// ======================================================================== END FILE =====
