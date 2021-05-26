// ====================================================================== BEGIN FILE =====
// **                              C T E S T _ T H R E A D                              **
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
/** @brief  Test harness for the SThread class.
 *  @file   ctest_thread.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Mar-18.
 *  @date   2010-04-02
 *  @date   2004-08-28 original code (from SolLib4)
*
 *  Provides a basic test of the SThread class.
 */
// =======================================================================================

#include <SThread.hh>
#include <unistd.h>

// =======================================================================================
// ---------------------------------------------------------------------------------------
class MyThread : public SThread {
  // -------------------------------------------------------------------------------------
public:
  MyThread  ( void ) {};
  virtual ~MyThread ( void ) {};

  virtual void run(void);
};

// =======================================================================================
// ---------------------------------------------------------------------------------------
void MyThread::run(void) {
  // -------------------------------------------------------------------------------------
  MSG("My Thread RUN Start");

  for (int i=0; i<10; i++) {
    fprintf( stdout, "%s: %d\n", getName(), i );
    usleep(2000L + (rand() % 1000000L) );
  }

  MSG("My Thread RUN Stop");
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
int main(void) {
  // -------------------------------------------------------------------------------------
  MSG("Parent Start");
  MSG("Parent Create Thread 1");
  SThread *t1 = (SThread*) new MyThread();
  MSG("Parent Create Thread 2");
  SThread *t2 = (SThread*) new MyThread();

  MSG("Parent Start Thread 1 & 2");
  t1->start();
  t2->start();

  MSG("Parent Join Thread 1");
  t1->join();

  MSG("Parent Join Thread 2");
  t2->join();

  MSG("Parent Done");
  return 0;
}



// =======================================================================================
// **                              C T E S T _ T H R E A D                              **
// ======================================================================== END FILE =====
