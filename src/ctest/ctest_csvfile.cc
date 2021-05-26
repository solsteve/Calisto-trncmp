// ====================================================================== BEGIN FILE =====
// **                             C T E S T _ C S V F I L E                             **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2021, Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
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
/** @brief Test the CSVFile class.
 *  @file   ctest_CSVFile.cc
 *  @author Stephen W. Soliday
 *  @date   2021-Mar-10
 *
 *  This is a test of the CSVFile class.
 */
// =======================================================================================

#include <CSVFile.hh>

#define TEMP_FILE "/tmp/test.csv"

static int32_t LonLat[5][2] = { { 711965, 3974982 },
                                { 712081, 3974892 },
                                { 711992, 3975104 },
                                { 711882, 3975087 },
                                { 711872, 3975181 } };
static real8_t ColRow[5][2] = { {   28.596786, -13.451078 },
                                { -100.068459,  60.243793 },
                                {  132.863449,  57.528339 },
                                {  160.856461, -52.798977 },
                                {  110.856362,  52.778911 } };

static const size_t NUM_SAMPLE = 5;

// =======================================================================================
void build_test( void ) {
  // -------------------------------------------------------------------------------------
  FILE* fp = fopen( TEMP_FILE, "w" );

  fprintf( fp, "LON,LAT,COL,ROW\n" );
  for ( size_t i=0; i<NUM_SAMPLE; i++ ) {
    fprintf( fp, "%d,%d,%11.6f,%11.6f\n",
             LonLat[i][0], LonLat[i][1], ColRow[i][0], ColRow[i][1] );
  }

  fclose( fp );
}
 
// =======================================================================================
int main( void ) {
  // -------------------------------------------------------------------------------------
  build_test();

  
  CSVFile* csv = new CSVFile( TEMP_FILE );

  size_t n = csv->size(1);

  std::cout << "Number of fields = " << n << std::endl;

  for ( size_t i=0; i<n; i++ ) {
    std::cout << "[" << csv->header(i) << "]\n";
  }

  size_t m = csv->size();

  std::cout << "Number of records = " << m << std::endl;

  real8_t mse = 0.0e0;
  for ( size_t i=0; i<m; i++ ) {
    int32_t lon = csv->getInt32( i, "LON" );
    int32_t lat = StringTool::asInt32( csv->get( i, "LAT" ) );
    real8_t col = csv->getReal8( i, "COL" );
    real8_t row = StringTool::asReal8( csv->get( i, "ROW" ) );

    real8_t d1 = (real8_t)LonLat[i][0] - (real8_t)lon;  mse += (d1*d1);
    real8_t d2 = (real8_t)LonLat[i][1] - (real8_t)lat;  mse += (d2*d2);
    real8_t d3 =          ColRow[i][0] -          col;  mse += (d3*d3);
    real8_t d4 =          ColRow[i][1] -          row;  mse += (d4*d4);
     
    std::cout << lon << "\t" << lat << "\t"
              << col << "\t" << row << "\n";
  }

  std::cout << "MSE = " << mse << std::endl;


        
  delete csv;
  
  return 0;
}


// =======================================================================================
// **                             C T E S T _ C S V F I L E                             **
// ======================================================================== END FILE =====
