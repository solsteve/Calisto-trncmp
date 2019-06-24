// ====================================================================== BEGIN FILE =====
// **                             C T E S T _ T L O G G E R                             **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019, Stephen W. Soliday                                           **
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
/** @brief Test the T-Logger class.
 *  @file   ctest_tlogger.cc
 *  @author Stephen W. Soliday
 *  @date   2013-06-24
 *  @date   2019-Apr-26 CMake refactorization.
 *
 *  This is a test of the TLogger utility.
 */
// =======================================================================================


#include <trncmp.hh>


#include <TLogger.hh>
#include <unistd.h>

// =======================================================================================
// ---------------------------------------------------------------------------------------
class LoggerDemo {
  // -------------------------------------------------------------------------------------
 protected:
  TLogger* logger;

  class MyAbortHandler : public TLogger::AbortHandler {
    virtual void handle( int n ) {
      std::cout << "This is my C++ logger abort function." << std::endl;
      exit(n);
    };
  };

  LoggerDemo(const LoggerDemo&);
  LoggerDemo& operator=(const LoggerDemo&);

 public:
  LoggerDemo( void );
  ~LoggerDemo( void );
  void GO( void );
};

// =======================================================================================
// ---------------------------------------------------------------------------------------
LoggerDemo::LoggerDemo( void ) : logger(0) {
  // -------------------------------------------------------------------------------------
  logger = TLogger::getInstance();

  logger->setLogfile("./test_c.log");
  logger->registerAbortHandler( new MyAbortHandler() );
  logger->setConsoleLevel(TLogger::DEBUG);
  logger->setWriteLevel(TLogger::DEBUG);
  logger->setAbortLevel(TLogger::CRITICAL);
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
LoggerDemo::~LoggerDemo( void ) {
  // -------------------------------------------------------------------------------------
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
void LoggerDemo::GO( void ) {
  // -------------------------------------------------------------------------------------
  std::cerr << "C++: Logger test: start" << std::endl << std::endl;

  logger->debug( "This is a debug message %f", 3.14 );
  logger->info( "This is an info message" );
  sleep(2);
  logger->warn( LOCATION, "This is a warning message number %d", 3 );
  sleep(2);
  logger->error( "This is an error message" );
  logger->critical( "This is a  critical message" );

  std::cerr << std::endl << "C++: Logger test: stop" << std::endl << std::endl;
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
int main( void ) {
  // -------------------------------------------------------------------------------------

  LoggerDemo* x = new LoggerDemo( );

  x->GO();

  delete x;

  return 0;
}



// =======================================================================================
// **                             C T E S T _ T L O G G E R                             **
// ======================================================================== END FILE =====
