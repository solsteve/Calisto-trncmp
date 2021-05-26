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
 *  @file   SThread.hh
 *  @author Stephen W. Soliday
 *  @date   2020-Mar-18.
 *  @date   2010-04-02
 *  @date   2004-08-28 original code (from SolLib4)
*
 *  Provides the interface for wrapping system native threads.
 */
// =======================================================================================

#ifndef __STHREAD_HH_TRNCMP
#define __STHREAD_HH_TRNCMP

#include <trncmp.hh>
#include <thread>
#include <asm/errno.h>
#include <mutex>
#include <condition_variable>
#include <chrono>

typedef std::thread::id sthread_id_t;

class SThread;
class SMutex;
class SThreadCond;

// =======================================================================================
// ---------------------------------------------------------------------------------------
class SThread {
  // -------------------------------------------------------------------------------------
private:
  std::thread*     theThread;     /** Handle for the thread */

  static u_int32_t numberOfActiveThreads;
  static u_int32_t numberOfThreads;
  
  int32_t          myNumber;
  char             threadName [64];
  bool             detach_after_start;

  SThread(const SThread& arg); 
  SThread& operator=(const SThread& rhs);

  // -------------------------------------------------------------------------------------
public:
  enum cancel_t {
    CANCEL_DISABLE   = 0,
    CANCEL_DEFERRED  = 1,
    CANCEL_IMMEDIATE = 2
  };

  SThread                      ( bool detach = false );
  
  virtual         ~SThread     ( void );

  int              start       ( void );
  void             join        ( void );
  
  virtual void     run         ( void ) = 0;

  sthread_id_t     id          ( void );
  u_int32_t        number      ( void );
  static u_int32_t count       ( void );
  static u_int32_t activeCount ( void );

  char*            getName     ( void );
  char*            setName     ( char* s );
};

// =======================================================================================
/** @brief Thread Id.
 *  @return pointer to this instance cast as a u_int32_t.
 *
 *   Return a unique identifer for each instance of the thread.
 */
// ---------------------------------------------------------------------------------------
inline sthread_id_t  SThread::id( void ) {
  // -------------------------------------------------------------------------------------
  if ( 0 == theThread ) {
    return static_cast<sthread_id_t>(0);
  }
  return theThread->get_id();
}

// =======================================================================================
// @brief Thread number.
// @return this threads number in instance order.
// ---------------------------------------------------------------------------------------
inline u_int32_t SThread::number( void ) {
  // -------------------------------------------------------------------------------------
  return myNumber;
}

// =======================================================================================
// Static function to return the number of instantiated threads.
// ---------------------------------------------------------------------------------------
inline u_int32_t SThread::count( void ) {
  // -------------------------------------------------------------------------------------
  return numberOfThreads;
}

// =======================================================================================
// Static function to return the number of active threads.
// ---------------------------------------------------------------------------------------
inline u_int32_t SThread::activeCount( void ) {
  // -------------------------------------------------------------------------------------
  return numberOfActiveThreads;
}

// =======================================================================================
// Get the name of the thread
// ---------------------------------------------------------------------------------------
inline char* SThread::getName( void ) {
  // -------------------------------------------------------------------------------------
  return threadName;
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
inline char* SThread::setName( char* s  ) {
  // -------------------------------------------------------------------------------------
  copy( threadName, s, 31 );
  return threadName;
}

// =======================================================================================
/** @brief Mutex Class.
 *  A mutex is used to protect a section of code such that at any time only a single thread
 *  can execute the code.
 */
// ---------------------------------------------------------------------------------------
class SMutex {
  // -------------------------------------------------------------------------------------
  friend class SThreadCond;

protected:
  std::mutex mtx;

public:
  SMutex       ( void );
  ~SMutex      ( void );
  void lock    ( void );
  bool trylock ( void );
  void unlock  ( void );
};
 
// =======================================================================================
/** @brief Constructor.
 *  Create a new mutex. Under Linux this is a 'fast' mutex.
 */
// ---------------------------------------------------------------------------------------
inline  SMutex::SMutex(void) : mtx() {
  // -------------------------------------------------------------------------------------
}

// =======================================================================================
/** @brief Destructor.
 *   Destroy a mutex object. Note: it is the responsibility of the caller to ensure the mutex
 *   is unlocked before destruction occurs.
 */
// ---------------------------------------------------------------------------------------
inline  SMutex::~SMutex(void) {
  // -------------------------------------------------------------------------------------
}

// =======================================================================================
/** @brief Lock this mutex.
 *   If the mutex is currently unlocked, it becomes locked and owned by the calling thread.
 *   If the mutex is already locked by another thread, the calling thread is suspended until
 *   the mutex is unlocked.  If the mutex is already locked and owned by the calling thread,
 *   the calling thread is suspended until the mutex is unlocked, effectively causing the
 *   calling thread to deadlock.
 *
 *  @see SGMutex::trylock
 */
// ---------------------------------------------------------------------------------------
inline  void SMutex::lock(void) {
  // -------------------------------------------------------------------------------------
  mtx.lock();
}

// =======================================================================================
/** @brief Unlock this mutex.
 *  It is assumed that the mutex is locked and owned by the calling thread.
 */
// ---------------------------------------------------------------------------------------
inline  void SMutex::unlock(void) {
  // -------------------------------------------------------------------------------------
  mtx.unlock();
}

// =======================================================================================
/** @brief Unlock this mutex.
 *  It is assumed that the mutex is locked and owned by the calling thread.
 */
// ---------------------------------------------------------------------------------------
inline  bool SMutex::trylock( void ) {
  // -------------------------------------------------------------------------------------
  return mtx.try_lock();
}

// =======================================================================================
/** @brief Thread Conditional Class.
 *   A condition variable is a synchronization device that allows threads to suspend 
 *   execution until some prediction on shared data is satisfied. A condition variable is 
 *   always associated with a mutex to avoid race conditions. 
 */
// ---------------------------------------------------------------------------------------
class SThreadCond {
  // -------------------------------------------------------------------------------------
public:
  SThreadCond  ( void );
  ~SThreadCond ( void );

  void wait      ( SMutex& );

  bool wait      ( SMutex& mutex, u_int32_t ms );
  void signal    ( void );
  void broadcast ( void );

private:
  std::condition_variable cond;
};

// =======================================================================================
/** @brief Constructor.
 *   Create a new condition variable.
 */
// ---------------------------------------------------------------------------------------
inline SThreadCond::SThreadCond(void) : cond() {
  // -------------------------------------------------------------------------------------
  //pthread_cond_init( &cond, 0 );
}

// =======================================================================================
/** @brief Destroy the condition object.
 */
// ---------------------------------------------------------------------------------------
inline SThreadCond::~SThreadCond(void) {
  // -------------------------------------------------------------------------------------
  //pthread_cond_destroy( &cond );
}

// =======================================================================================
/** @brief Signal.
 *
 *   Wake one thread waiting on this condition variable. Nothing happens if no threads are 
 *   waiting. If several threads are waiting exactly one thread is restarted.  It is not 
 *   specified which.
 */
// ---------------------------------------------------------------------------------------
inline void SThreadCond::signal(void) {
  // -------------------------------------------------------------------------------------
  //pthread_cond_signal( &cond );
  std::cerr << "*** SThreadCond::signal(void) * NOT IMPLEMENTED\n";
}

// =======================================================================================
/** @brief Broadcast.
 *
 *   Wake all threads waiting on this condition variable.
 *   Nothing happens if no threads are waiting.
 */
// ---------------------------------------------------------------------------------------
inline void SThreadCond::broadcast(void) {
  // -------------------------------------------------------------------------------------
  //pthread_cond_broadcast( &cond );
  std::cerr << "*** SThreadCond::broadcast(void) * NOT IMPLEMENTED\n";
}

// =======================================================================================
/** @brief Wait.
 *  @param mutex reference to a locked mutex.
 * 
 *   Wait for this condition variable to be signaled.
 */
// ---------------------------------------------------------------------------------------
inline void SThreadCond::wait( SMutex& mutex ) {
  // -------------------------------------------------------------------------------------
  std::unique_lock<std::mutex> lck(mutex.mtx);
  this->cond.wait( lck );
}

// =======================================================================================
/** @brief Synchronize Class.
 *   A scoped locking utility.
 *   An SGGuard object locks its synchronization object during creation and
 *   automatically unlocks it when it goes out of scope.
 */
// ---------------------------------------------------------------------------------------
class Synchronize {
  // -------------------------------------------------------------------------------------
private:
  SMutex& slock; /** A lockable object. */
  
public:
  // =====================================================================================
  /**@brief Constuctor.
   * @param l A lockable object.
   *
   *  Create an SGGuard object and lock the passed lockable object.
   */
  // -------------------------------------------------------------------------------------
  Synchronize( SMutex& l ) : slock(l) {
    // -----------------------------------------------------------------------------------
    slock.lock(); 
  }
  
  // =====================================================================================
  /** @brief Destructor.
   *   Destroy this object and unlock the locakable object.
   */
  // -------------------------------------------------------------------------------------
  ~Synchronize(void) {
    // -----------------------------------------------------------------------------------
    slock.unlock();
  }
};

#endif 


// =======================================================================================
// **                                   S T H R E A D                                   **
// ======================================================================== END FILE =====
