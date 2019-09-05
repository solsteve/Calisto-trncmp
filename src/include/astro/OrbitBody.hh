// ====================================================================== BEGIN FILE =====
// **                                 O R B I T B O D Y                                 **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019-, Stephen W. Soliday                                          **
// **                       stephen.soliday@trncmp.org                                  **
// **                       http://research.trncmp.org                                  **
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
/** @brief  OrbitalBody.
 *  @file   OrbitBody.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-14.
 *
 *  Provides a Model of an orbital body, with a mass, radius and
 *  orbiting a central potential.
 */
// =======================================================================================

#ifndef __HH_ORBITBODY_TRNCMP
#define __HH_ORBITBODY_TRNCMP

#include <trncmp.hh>

#define GRAV static_cast<real8_t>( 6.67428e-11 ) ///< kg*m^3/s^2  Gravitational Constant

// =======================================================================================
class OrbitBody {
  // -------------------------------------------------------------------------------------
 protected:
  OrbitBody*                          orbit_center; ///< Parent central body.
  std::map<std::string, OrbitBody*>*  satdb;        ///< Database of child satellites.

  std::string name;
  real8_t     body_mu;
  real8_t     body_mass;
  real8_t     surface_radius;

  OrbitBody( void );
  OrbitBody( OrbitBody* body );

  class Builder {
   public:
    std::string name;
    real8_t     radius;
    real8_t     mass;
    real8_t     mu;
    
    Builder( std::string nm );
    ~Builder( void );
    Builder* setCenter ( OrbitBody* body );
    Builder* setMass   ( const real8_t m );
    Builder* setRadius ( const real8_t r );
    Builder* setMu     ( const real8_t gm );

    OrbitBody* build( void );





    
  }; // end class Builder




  
  ~OrbitBody( void );

  int add( OrbitBody* body );
  
}; // end class OrbitBody


#endif


// =======================================================================================
// **                                 O R B I T B O D Y                                 **
// ======================================================================== END FILE =====
