// ====================================================================== BEGIN FILE =====
// **                                S T R I N G T O O L                                **
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
/** @brief  String Tool.
 *  @file   StringTool.hh
 *  @author Stephen W. Soliday
 *  @date   2013-Aug-18 Original release.
 *  @date   2019-May-06 CMake refactorization.
 *
 *  Provides the implementation for a set of string manipulation tools.
 */
// =======================================================================================


#ifndef __HH_STRINGTOOL_TRNCMP
#define __HH_STRINGTOOL_TRNCMP


#include <trncmp.hh>

#include <sstream>
#include <vector>
#include <iterator>





// =======================================================================================
class StringTool {
  // -------------------------------------------------------------------------------------
 public:

  // =====================================================================================
  class Splitter {                                                 // StringTool::Splitter
    // -----------------------------------------------------------------------------------
  protected:
    std::vector<std::string> vector;

  public:
    Splitter  ( const std::string& str, const char del = ',' );

    
    ~Splitter ( void );

    size_t       size       ( void );
    std::string& operator[] ( size_t idx );
    std::string& at         ( size_t idx ) noexcept(false);
  }; // end class StringTool::Splitter


 public:

  static const size_t NOT_FOUND;

  static std::string  toString     ( const bool      val );
  static std::string  toString     ( const real8_t   val, const std::string fmt = "%f"   );
  static std::string  toString     ( const real4_t   val, const std::string fmt = "%f"   );
  static std::string  toString     ( const int64_t   val, const std::string fmt = "%ld"  );
  static std::string  toString     ( const int32_t   val, const std::string fmt = "%d"   );
  static std::string  toString     ( const int16_t   val, const std::string fmt = "%hd"  );
  static std::string  toString     ( const int8_t    val, const std::string fmt = "%hhd" );
  static std::string  toString     ( const u_int64_t val, const std::string fmt = "%lu"  );
  static std::string  toString     ( const u_int32_t val, const std::string fmt = "%u"   );
  static std::string  toString     ( const u_int16_t val, const std::string fmt = "%hu"  );
  static std::string  toString     ( const u_int8_t  val, const std::string fmt = "%hhu" );

  static std::string  toString     ( const std::string* lst, const size_t n );
  static std::string  toString     ( const real8_t*   lst, const size_t n, const std::string fmt = "%f"   );
  static std::string  toString     ( const real4_t*   lst, const size_t n, const std::string fmt = "%f"   );
  static std::string  toString     ( const int64_t*   lst, const size_t n, const std::string fmt = "%ld"  );
  static std::string  toString     ( const int32_t*   lst, const size_t n, const std::string fmt = "%d"   );
  static std::string  toString     ( const int16_t*   lst, const size_t n, const std::string fmt = "%hd"  );
  static std::string  toString     ( const int8_t*    lst, const size_t n, const std::string fmt = "%hhd" );
  static std::string  toString     ( const u_int64_t* lst, const size_t n, const std::string fmt = "%lu"  );
  static std::string  toString     ( const u_int32_t* lst, const size_t n, const std::string fmt = "%u"   );
  static std::string  toString     ( const u_int16_t* lst, const size_t n, const std::string fmt = "%hu"  );
  static std::string  toString     ( const u_int8_t*  lst, const size_t n, const std::string fmt = "%hhu" );

  static std::string  toHex        ( const u_int64_t val );
  static std::string  toHex        ( const u_int32_t val );
  static std::string  toHex        ( const u_int16_t val );
  static std::string  toHex        ( const u_int8_t  val );

  static std::string  toHex        ( const u_int64_t* lst, const size_t n );
  static std::string  toHex        ( const u_int32_t* lst, const size_t n );
  static std::string  toHex        ( const u_int16_t* lst, const size_t n );
  static std::string  toHex        ( const u_int8_t*  lst, const size_t n );

  static bool         asBool       ( const std::string S );
  static real8_t      asReal8      ( const std::string S );
  static real4_t      asReal4      ( const std::string S );
  static int64_t      asInt64      ( const std::string S, int base = 10 );
  static int32_t      asInt32      ( const std::string S, int base = 10 );
  static int16_t      asInt16      ( const std::string S, int base = 10 );
  static int8_t       asInt8       ( const std::string S, int base = 10 );
  static u_int64_t    asUInt64     ( const std::string S, int base = 10 );
  static u_int32_t    asUInt32     ( const std::string S, int base = 10 );
  static u_int16_t    asUInt16     ( const std::string S, int base = 10 );
  static u_int8_t     asUInt8      ( const std::string S, int base = 10 );

  static std::string* asStringList ( size_t& n, const std::string S );
  static bool*        asBoolList   ( size_t& n, const std::string S );
  static real8_t*     asReal8List  ( size_t& n, const std::string S );
  static real4_t*     asReal4List  ( size_t& n, const std::string S );
  static int64_t*     asInt64List  ( size_t& n, const std::string S, int base = 10 );
  static int32_t*     asInt32List  ( size_t& n, const std::string S, int base = 10 );
  static int16_t*     asInt16List  ( size_t& n, const std::string S, int base = 10 );
  static int8_t*      asInt8List   ( size_t& n, const std::string S, int base = 10 );
  static u_int64_t*   asUInt64List ( size_t& n, const std::string S, int base = 10 );
  static u_int32_t*   asUInt32List ( size_t& n, const std::string S, int base = 10 );
  static u_int16_t*   asUInt16List ( size_t& n, const std::string S, int base = 10 );
  static u_int8_t*    asUInt8List  ( size_t& n, const std::string S, int base = 10 );

  static std::string  trim         ( const std::string str );
  
  static std::string  containedBy  ( const std::string test,
                                     const std::string lhs, const std::string rhs );

  static size_t       find_in      ( const std::string str, const char test );

}; // end class StringTool


// =======================================================================================
/** @brief Find character in string.
 *  @param str  input string.
 *  @param test test character.
 *  @return position in the string of the test character.
 *
 *  Find the test character in the input string. If the test character is not found
 *  return StringTool::NOT_FOUND.
 */
// ---------------------------------------------------------------------------------------
inline size_t StringTool::find_in( const std::string str, const char test ) {
  // -------------------------------------------------------------------------------------
  return str.find_first_of( test );
}








// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
inline  StringTool::Splitter::~Splitter( void ) {
  // -------------------------------------------------------------------------------------
  vector.clear();
}


// =======================================================================================
/** @brief Size.
 *  @return number of tokens.
 *
 *  Return the number of tokens parsed by this splitter.
 */
// ---------------------------------------------------------------------------------------
inline  size_t StringTool::Splitter::size( void ) {
  // -------------------------------------------------------------------------------------
  return vector.size();
}


// =======================================================================================
/** @brief Get.
 *  @param idx token index.
 *  @return token at index.
 *
 *  Return a token at index idx.
 */
// ---------------------------------------------------------------------------------------
inline  std::string& StringTool::Splitter::operator[] ( size_t idx ) {
  // -------------------------------------------------------------------------------------
  return this->vector.at(idx);
}


// =======================================================================================
/** @brief Get.
 *  @param idx token index.
 *  @return token at index.
 *
 *  Return a token at index idx.
 */
// ---------------------------------------------------------------------------------------
inline  std::string& StringTool::Splitter::at( size_t idx ) noexcept(false) {
  // -------------------------------------------------------------------------------------
  return this->vector.at( idx );
}


#endif


// =======================================================================================
// **                                S T R I N G T O O L                                **
// ======================================================================== END FILE =====
