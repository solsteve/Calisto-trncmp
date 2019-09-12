#include <DateTime.hh>
#include <ISO8601.hh>
#include <StringTool.hh>





void testJD( const int32_t year, const int32_t month, const int32_t day ) {
  DateComponents DC( year, month, day );
  fprintf( stdout,
           "%04d-%02d-%02d = %.2f\n",
           year, month, day,
           2451544.5 + (double)DC.getJ2000Day() );
}

// =======================================================================================
void TEST01( void ) {
  // -------------------------------------------------------------------------------------

  testJD( 1970, 1, 1 );
  testJD( 1990, 5, 26 );
  testJD( 2000, 1, 1 );
  testJD( 2019, 8, 15 );
  testJD( 2473, 6, 18 );
  testJD( 1776, 7, 4 );
}


// =======================================================================================
void check( std::string test ) {
  // -------------------------------------------------------------------------------------
  std::cout << "\nChecking ["<< test << "]\n";

  ISO8601 T(test);

  std::cout << T.toString() << std::endl;
 }


// =======================================================================================
void check2( std::string test ) {
  // -------------------------------------------------------------------------------------
  std::cout << "\nChecking ["<< test << "]\n";

  std::regex e ("^(\\d\\d):?(\\d\\d):?(\\d\\d(?:[.,]\\d+)?)?(?:Z|([-+]\\d+))?$");

  std::cmatch cm;
  
  //std::regex_match ( test.c_str(), cm, e, std::regex_constants::match_default );
  std::regex_match ( test.c_str(), cm, e );

  for (unsigned i=1; i<cm.size(); ++i) {
    if ( "" != cm[i] ) {
      std::cout << i << ": [" << cm[i] << "]\n";
    }
  }
 }


// =======================================================================================
void TEST02( void ) {
  // -------------------------------------------------------------------------------------
  const char test1[] = "2019-06-18T12:34";
  const char test2[] = "2019T12:34:56";
  const char test3[] = "2019-06T12:34:56.789";
  const char test4[] = "12:34:56Z";
  const char test5[] = "12:34:56.789Z";
  const char test6[] = "12:34:56+8762";
  const char test7[] = "12:34:56.789+987";
  const char test8[] = "12:34:56-17";
  const char test9[] = "12:34:56.789-1234";

  check( test1 );
  check( test2 );
  check( test3 );
  check( test4 );
  check( test5 );
  check( test6 );
  check( test7 );
  check( test8 );
  check( test9 );
}


// =======================================================================================
void TEST03( int argc, char *argv[] ) {
  // -------------------------------------------------------------------------------------
  if ( 3 == argc ) {
    std::string str( argv[2] );

    std::regex  re( argv[1] );
    const char* cstr = str.c_str();
    std::cmatch cm;

    std::regex_match ( cstr, cm, re, std::regex_constants::match_default );

    std::cout << "[" << argv[1] << "] -";

    if ( 0 == cm.size() ) {
      std::cout << " NO MATCH:[" << str << "]\n";
    } else {
    for (unsigned i=0; i<cm.size(); ++i) {
      std::cout << " " << i << "[" << cm[i] << "]";
    }
    std::cout << "\n";
    }
    
  } else {
    std::cerr << "\nUSAGE: " << argv[0] << " \"regex\" \"test string\"\n\n";
  }
}


// =======================================================================================
int main( /* int argc, char *argv[] */ ) {
  // -------------------------------------------------------------------------------------
  //std::cout << "\n----- TEST01 ----------------------------\n\n";
  TEST01();
  //std::cout << "\n----- TEST02 ----------------------------\n\n";
  //TEST02();
  //TEST03(argc,argv);
  return 0;
}
