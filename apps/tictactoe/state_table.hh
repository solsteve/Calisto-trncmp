// ====================================================================== BEGIN FILE =====

#ifndef __STATE_TABLE_HH
#define __STATE_TABLE_HH

#include <state.hh>

// =======================================================================================
class StateTable {
  // -------------------------------------------------------------------------------------
 public:

  State* table;
  size_t table_size;

  StateTable( std::string fspc );
  StateTable( size_t n );
  ~StateTable( void );

  void destroy ( void );
  void init    ( size_t n );

  void write ( std::string fspc );
  void read  ( std::string fspc );

 private:
  EMPTY_PROTOTYPE( StateTable );
};

#endif

// ======================================================================== END FILE =====
