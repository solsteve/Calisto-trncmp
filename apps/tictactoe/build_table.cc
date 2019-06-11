// ====================================================================== BEGIN FILE =====

#include <state_table.hh>



// =======================================================================================
void renumber( State* table, size_t n  ) {
  // -------------------------------------------------------------------------------------

  size_t count = 0;
  for ( size_t i=0; i<n; i++ ) {
    if ( table[i].valid ) {
      table[i].id = count;
      count += 1;
    }
  }

  for ( size_t i=0; i<n; i++ ) {
    if ( table[i].valid ) {
      for ( size_t j=0; j<9; j++ ) {
        size_t nj = table[i].next[j];
        if ( nj > 0 ) {
          table[i].next[j] = table[nj].id;
          if ( 0 == table[nj].id ) {
            std::cerr << "Error in table ID\n";
            exit(1);
          }
        }
      }
    }
  }

}


// =======================================================================================
int build( State* table, size_t idx, size_t player  ) {
  // -------------------------------------------------------------------------------------
  size_t count = 0;
  size_t c     = State::check( table[idx] );
  size_t np    = State::toggle( player );
  size_t test[9];

  if ( 0 != c ) {
    table[idx].valid   = true;
    table[idx].result  = State::WIN;
    table[idx].current = State::EMPTY;
    table[idx].winner  = c;
    return 1;
  }
  
  for ( size_t i=0; i<9; i++ ) {
    if ( 0 == table[idx].board[i] ) {
      count += 1;
      table[idx].store( test );
      test[i] = player;
      size_t new_index = State::index( test );
      table[idx].next[i] = new_index;
      build( table, new_index, np );
    }
  }

  if ( 0 == count ) {
    table[idx].valid   = true;
    table[idx].result  = State::DRAW;
    table[idx].current = State::EMPTY;
    table[idx].winner  = State::EMPTY;
    return 1;    
  }

    table[idx].valid   = true;
    table[idx].result  = State::INPLAY;
    table[idx].current = player;
    table[idx].winner  = State::EMPTY;

  return 0;
}

size_t uid_counter = 1000;

// =======================================================================================
int makeUID_r( State* table, std::ofstream& fp, size_t idx ) {
  // -------------------------------------------------------------------------------------
  table[idx].uid = uid_counter++;
  //  fp << table[idx].uid << "\n";
  fp << idx << "\n";

  for ( size_t i=0; i<9; i++ ) {
    size_t nid = table[idx].next[i];
    if ( 0 < nid ) {
      makeUID_r( table, fp, nid );
    }
  }
  
  return 0;
}




// =======================================================================================
void makeUID( State* table, std::string fspc ) {
  // -------------------------------------------------------------------------------------
  uid_counter = 1000;
  std::ofstream fout( fspc );

  makeUID_r( table, fout, 0 );
  
  fout.close();
}


// =======================================================================================
int main( void ) {
  // -------------------------------------------------------------------------------------

  size_t max_states = State::maxIndex() + 1;
  
  StateTable* G = new StateTable( max_states );

  Counter C(3,9);
  C.reset();

  for ( size_t i=0; i<max_states; i++ ) {
    G->table[i].load( C );
    //G->table[i].display( std::cout );
    C.inc();
  }

  build( G->table, 0, State::PO );

  MARK;
  
  makeUID(G->table, "uid.1" );
  
  MARK;

  renumber( G->table, max_states );
  MARK;

  //makeUID(G->table, "uid.2" );
  
  MARK;
  
  size_t count = 0;
  for ( size_t i=0; i<max_states; i++ ) {
    if ( G->table[i].valid ) {
      G->table[i].display( std::cout );
      count += 1;
    }
  }

  std::cerr << "Found " << count << " valid boards out of " << max_states << "\n";
  MARK;

  std::ofstream fp( "state.data" );

  fp << count << "\n";
   MARK;
 
  count = 0;
  for ( size_t i=0; i<max_states; i++ ) {
    if ( G->table[i].valid ) {
      if ( count == G->table[i].id ) {
        fp << c_fmt( "%4lu", G->table[i].id );
        fp << c_fmt( " %lu", G->table[i].result );
        fp << c_fmt( " %lu", G->table[i].current );

        for ( size_t j=0; j<9; j++ ) {
          fp << c_fmt( " %lu", G->table[i].board[j] );
        }

        for ( size_t j=0; j<9; j++ ) {
          fp << c_fmt( " %4lu", G->table[i].next[j] );
        }

        fp << "\n";
      } else {
        std::cerr << "ID [" << G->table[i].id << "] is not equal to count[" << count << "]\n";
        exit(2);
      }
      count += 1;
    }
  }

  fp.close();
  
  MARK;

  StateTable T1( "state.data" );
  T1.write( "/tmp/st.x" );
  StateTable T2( "/tmp/st.x" );

  MARK;

  makeUID(T2.table, "uid.2" );

  MARK;
  
  delete G;
  
  return 0;
}

// ======================================================================== END FILE =====
