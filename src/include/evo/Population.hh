// ====================================================================== BEGIN FILE =====
// **                           E V O : : P O P U L A T I O N                           **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 1995-2019, Stephen W. Soliday                                      **
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
/** @brief Population.
 *  @file   evo/Population.hh
 *  @author Stephen W. Soliday
 *  @date   1995-Dec-29 Original C++ release (as FGA).
 *  @date   2016-Sep-01 Refactored for MPIch.
 *  @date   2018-Jul-11 Ported to HPSP Java.
 *  @date   2019-Sep-27 CMake refactorization.
 *
 *  Provides the abstract interface for an encoding.
 */
// =======================================================================================


#ifndef __HH_EVO_POPULATION_TRNCMP
#define __HH_EVO_POPULATION_TRNCMP

#include <evo/Metric.hh>
#include <evo/Encoding.hh>
#include <evo/Model.hh>


namespace evo {

// =======================================================================================
class Population {
  // -------------------------------------------------------------------------------------
 protected:

 public:
  enum search_type { RANDOM=0, BEST=1, WORST=2 };

 public:
  // =====================================================================================
  class Score {                                                       // Population::Score
    // -----------------------------------------------------------------------------------
   public:
    bool    new_best;     ///< Set to true if a new best is available.
    int32_t worst_index;  ///< Set to the index of the worst score.

    /** @brief Constructor */
    Score  ( void ) : new_best(false), worst_index(-1) {};

    /** @brief Destructor */
    ~Score ( void ) {};
  }; // end class Population::Score



  
 public:
  // =====================================================================================
  class Member {                                                     // Population::Member
    // -----------------------------------------------------------------------------------
   protected:

   public:
    Metric*   met;      ///< Pointer to a Metric
    Encoding* enc;      ///< Pointer to an Encoding
    int32_t   age;      ///< Age of the member

    Member  ( Model* mod );
    ~Member ( void );

    void copy( Member* src );
    
  }; // end class Population::Member



  
 public:
  // =====================================================================================
  class Group {                                                       // Population::Group
    // -----------------------------------------------------------------------------------
   protected:
    Member* member;        ///< Pointer to an array of members.
    int32_t n_member;      ///< Number of members.

    Member* best_member;   ///< Pointer to a copy of the best population member.
    Member* worst_member;  ///< Pointer to a copy of the worst population member.
     
    Model*  model;         ///< Pointer to a user defined model to be evaluated.
    
   public:
    Group  ( const int32_t n, Model* mod );
    ~Group ( void );

    Member* get   ( const int idx );
    void    set   ( const int idx, Member* m );
    
    Member* best  ( void );
    Member* worst ( void );
    int32_t size  ( void ) const;

    void    randomize     ( const real8_t pb = D_ZERO );
    void    bracket       ( void );
    void    noise         ( const real8_t scale );

    void    compute_scores ( void );
    Score   get_stats      ( bool rezero );

    int32_t find ( search_type st );
  
  }; // end class Population::Group

  

}; // end class Population


}; // end namespace evo


#endif


// =======================================================================================
// **                           E V O : : P O P U L A T I O N                           **
// =========================================================================== END FILE ==
