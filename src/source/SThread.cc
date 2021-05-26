// ====================================================================== BEGIN FILE =====
// **                                   S T H R E A D                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2010, 04, 20, Stephen W. Soliday                                   **
// **                              stephen.soliday@trncmp.org                           **
// **                              http://research.trncmp.org                           **
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
/** @brief  Wrap System native threads.
 *  @file   SThread.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Mar-18.
 *  @date   2010-04-02
 *  @date   2004-08-28 original code (from SolLib4)
*
 *  Provides the methods for wrapping system native threads.
 */
// =======================================================================================
#include <SThread.hh>
#include <sys/time.h>

u_int32_t SThread::numberOfThreads       = 0L;
u_int32_t SThread::numberOfActiveThreads = 0L;

// =======================================================================================
/** @brief Constructor.
 *  @param detach specifies whether we want to create a detached thread
 *  @param size   specifies the stack size of the thread.
 */
// ---------------------------------------------------------------------------------------
SThread::SThread( bool detach ) : theThread(0), myNumber(0), detach_after_start(detach) {
  // -------------------------------------------------------------------------------------
  SThread::numberOfThreads++;
  myNumber = SThread::numberOfThreads;
  sprintf( threadName, "Thread-%d", SThread::numberOfThreads );
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
SThread::~SThread( void ) {
  // -------------------------------------------------------------------------------------
  SThread::numberOfThreads--;
  myNumber = 0L;
}

// =======================================================================================
/** @brief Start Thread.
 *   Sends a cancellation request to the underlying thread.  The target thread will either
 *   ignore the request, honor it immediately or defer it until it reaches a 
 *   cancellation point.
 */
// ---------------------------------------------------------------------------------------
int SThread::start( void ) {
  // -------------------------------------------------------------------------------------
  if ( 0 != theThread ) {
    SThread::numberOfActiveThreads++;
    theThread = new std::thread( [&] { this->run(); } );
    if ( detach_after_start ) {
      theThread->detach();
    }
    return 0;
  } else {
    fprintf( stderr, "Thread is already active" );
  }
  return 1;
}

// =======================================================================================
/** Join Thread.
 * Suspends the exection of the calling thread until this thread
 * terminates.
 */
// ---------------------------------------------------------------------------------------
void SThread::join( void ) {
  // -------------------------------------------------------------------------------------
  theThread->join();
  SThread::numberOfActiveThreads--;
}

// =======================================================================================
/**
 * Wait for this condition variable to be signaled for at most
 * 'ms' milliseconds.
 *
 * @param mutex reference to a locked mutex.
 * @param ms    milliseconds to wait for a signal.
 *
 * @return true if thread finishes, false if timeout is reached.
 */
// ---------------------------------------------------------------------------------------
bool SThreadCond::wait( SMutex& mutex, u_int32_t ms ){
  // -------------------------------------------------------------------------------------
  std::unique_lock<std::mutex> lk(mutex.mtx);

  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  now += std::chrono::milliseconds(ms);

  if(cond.wait_until(lk, now ) ==  std::cv_status::timeout) {
      return true;
  }

  return false;
}


// =======================================================================================
// **                                   S T H R E A D                                   **
// ======================================================================== END FILE =====
