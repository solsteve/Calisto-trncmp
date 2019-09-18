// ====================================================================== BEGIN FILE =====
// **                              F U Z Z Y : : G R O U P                              **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2015-2019, Stephen W. Soliday                                      **
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
/** @brief  Fuzzy Group.
 *  @file   fuzzy/Group.hh
 *  @author Stephen W. Soliday
 *
 * Provides the interface for a fuzzy group. A group is a collection of fuzzy Partitions.
 * R^m -> R^(mxSUM(n[i],i=1,n))
 *
 *
 */
// =======================================================================================


#ifndef __HH_FUZZY_GROUP_TRNCMP
#define __HH_FUZZY_GROUP_TRNCMP


#include <fuzzy/Partition.hh>
#include <VarReal.hh>
#include <TLogger.hh>


namespace fuzzy {


// =======================================================================================
class Group {
  // -------------------------------------------------------------------------------------
 protected:
  TLOGGER_HEADER( logger );
  EMPTY_PROTOTYPE( Group );

  int32_t     num_part;
  Partition** part;

  void destroy ( void );
  void resize  ( const int32_t n );

 public:
  Group   ( void );
  Group   ( const int32_t np );
  Group   ( const int32_t np, Partition** psrc );
  Group   ( VarReal& V );
  
  ~Group  ( void );

  int32_t    nIn           ( void ) const;
  int32_t    nOut          ( void ) const;
  int32_t    size          ( void ) const;
  real8_t*   create_buffer ( void );

  Partition& get           ( const int32_t i );
  void       set           ( const int32_t i, Partition& p );

  void       set           ( const int32_t np );
  void       set           ( const int32_t np, Partition** psrc );
  void       set           ( VarReal& V );
  
  // ----- execution --------------------------------------

  void       fuzzify       ( real8_t* mu, real8_t* x  );
  void       defuzzify     ( real8_t* x,  real8_t* mu );
  
  // ----- storage and transfer ---------------------------

  real8_t*   load          ( real8_t* src );
  real8_t*   store         ( real8_t* dst );

  bool       read          ( std::ifstream& ifs );
  bool       write         ( std::ofstream& ofs, std::string fmt = "%23.16e" );
}; // end class Group


}; // end namespace fuzzy


#endif 


// =======================================================================================
// **                              F U Z Z Y : : G R O U P                              **
// ======================================================================== END FILE =====
