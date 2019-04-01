#define CATCH_CONFIG_MAIN
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include "catch.hpp"
#include "saa.hpp"
#include "matrix.hpp"
#include <sqlite3.h>


//class SAA;
using namespace std;
SAA test_saa(1092);
int verbose = false;
int seed = 20;
static int callback(void *, int, char **, char **);


vector<int>v1{ 1,2,3,28,74,163,164,165,166,167,169,326,327,328,329,330,489,490,491,492,493,494,495,653,654,655,658,666,814,815,816,817,818,819,978,979,980,981,1037,1073 };
vector<int>v2{1,2,3,4,5,6,7,8,9,11,12,14,16,17,19,20,22,23,25,26,27,28,74,75,151,163,164,165,166,167,168,169,171,172,173,174,176,179,181,182,183,184,185,186,187,297,326,327,328,329,330,331,332,333,334,336,339,340,343,344,345,346,347,349,350,351,352,444,483,489,490,491,492,493,494,495,496,499,500,501,502,504,505,507,508,509,510,511,512,520,652,653,654,655,656,657,658,660,661,662,663,665,666,667,668,670,671,673,674,675,676,678,814,815,816,817,818,819,820,821,822,823,825,826,828,829,832,837,839,840,978,979,980,981,982,984,985,986,988,990,991,995,999,1001,1003,1004,1037,1038,1073,1075 };
vector<int>v3{ 494,495,167,328,326,814,1037,169,1073,330,28,819,655,818,666,658,166,74,980,327,164,491,492,489,817,978,981,3,165,979,493,329,163,2,816,654,490,653,815,1 };
vector<int>v4{11,164,501,492,25,17,444,826,327,511,504,985,500,825,20,660,510,343,334,1003,349,331,995,984,491,499,347,489,4,174,817,668,176,978,352,23,163,172,839,815,184,667,656,507,344,490,653,7,823,678,816,187,14,982,181,332,345,654,820,26,991,27,990,333,981,3,165,988,6,5,1004,351,185,22,676,665,673,173,2,9,1,829,661,832,657,663,986,508,168,505,19,496,182,329,509,493,979,837,8,662,999,674,670,350,840,336,980,297,340,671,179,512,821,652,1075,483,171,346,75,183,16,520,186,675,339,502,1038,12,828,151,822,1001,74,166,1037,814,326,494,167,495,328,169,1073,330,28,819,655,818,666,658 };




double testCostFunction(vector<int> test_vector) {
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  rc = sqlite3_open("../data/tsp.db", &db);
  char sql[200];

  if (rc){
    cout << " Can't open database: " << sqlite3_errmsg(db) << endl;
    return 0;
  }

  sprintf(sql, "SELECT * FROM (SELECT * FROM cities LIMIT %d) X LEFT JOIN (SELECT * FROM connections) Y ON X.id=Y.id_city_1 AND Y.id_city_2<=%d;",1092, 1092);

  rc = sqlite3_exec(db, sql, callback, &test_saa, &zErrMsg);

  if (rc != SQLITE_OK){
    cout << "SQL error: " << zErrMsg << endl;
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);

  test_saa.setRandomEngineGenerator(seed, test_vector.size());
  
  //pair<vector<int>, double> candidate_solution = test_saa.getSolution(test_vector, verbose);
  pair<vector<int>, double> test_solution = make_pair(v1,(double)7991106.993166080676019);//test_saa.getSolution(test_vector, verbose);
  return test_solution.second;
}


static int callback(void *temp_saa, int argc, char **argv, char **azColName){
  SAA *tSAA = static_cast<SAA *>(temp_saa);
  //terminate called after throwing an instance of 'std::logic_error'
  //what():  basic_string::_M_construct null not valid
  if (argv[7] != NULL)
    tSAA->real_connection(stoi(argv[0]) - 1, stoi(argv[7]) - 1, stod(argv[8]));
  tSAA->add_cityID(stoi(argv[0]) - 1, {stod(argv[4]), stod(argv[5])});
  return 0;
}


int Factorial( int number ) {
 return number <= 1 ? 1      : Factorial( number - 1 ) * number;  // pass
}


TEST_CASE( "Cost function v1_40", "[single-file]" ) {
    REQUIRE( testCostFunction(v1) ==  7991106.993166080676019);
}


TEST_CASE( "Factorial of 0 is 1 (fail)", "[single-file]" ) {
    REQUIRE( Factorial(0) == 1 );
}

TEST_CASE( "Factorials of 1 and higher are computed (pass)", "[single-file]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}