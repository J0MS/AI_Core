#define CATCH_CONFIG_MAIN
#include <bits/stdc++.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <fstream>
#include <unistd.h>
#include <chrono>
#include <unordered_set>
#include "catch.hpp"
#include "aco.hpp"
#include "matrix.hpp"


//class ACO;
//using namespace std;
int seed = 100;
int n, m, u, v, w;

int loadInput() {
  std::cin >> n >> m;
  if (n > 0 || m > 0) {
    return 1;
  } else {
    return 0;
  }

}


int testMWVC(int numVertex, int numEdges){

  std::cin >> n >> m;
  ACO aco(n, m);
  for(int i = 0; i < n; i++) {
    std::cin >> w;
    aco.setWeight(i, w);
  }
  for(; m > 0; m--) {
    std::cin >> u >> v;
    aco.setEdge(u, v);
  }
  aco.randomEngineGenerator(seed);
  printf("\nSeed: %d\n", seed);
  pair<unordered_set<int>, int> currentSolution = aco.getSolution();
  for (int x : currentSolution.first){
    printf("%d, ", x);
  }
  return currentSolution.second;

}




int Factorial( int number ) {
 return number <= 1 ? 1      : Factorial( number - 1 ) * number;  // pass
}

TEST_CASE( "Testing input", "[single-file]" ) {
    REQUIRE( loadInput() == 1 );
}


TEST_CASE( "Testing ACO for optimum with vertex = 200, edges = 4555" ) {
    REQUIRE( testMWVC(200, 4555) == 68 );

}


/*
if (n==200 && m==4555 ) {
  TEST_CASE( "Testing ACO for optimum on trampa200.txt" ) {
      REQUIRE( test_MWVC(200, 4555) == 68 );
  }
}
*/

TEST_CASE( "Factorial of 0 is 1 (fail)", "[single-file]" ) {
    REQUIRE( Factorial(0) == 1 );
}

TEST_CASE( "Factorials of 1 and higher are computed (pass)", "[single-file]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}


TEST_CASE( "vectors can be sized and resized", "[vector]" ) {
    int x = 2;
    std::vector<int> v( 5 );
    if (x==2) {
      std::vector<int> v( 5 );
    } else {
      std::vector<int> v( 0 );
    }

    REQUIRE( v.size() == 5 );
    REQUIRE( v.capacity() >= 5 );

    SECTION( "resizing bigger changes size and capacity" ) {
        v.resize( 10 );

        REQUIRE( v.size() == 10 );
        REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "resizing smaller changes size but not capacity" ) {
        v.resize( 0 );

        REQUIRE( v.size() == 0 );
        REQUIRE( v.capacity() >= 5 );
    }
    SECTION( "reserving bigger changes capacity but not size" ) {
        v.reserve( 10 );

        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "reserving smaller does not change size or capacity" ) {
        v.reserve( 0 );

        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );
    }
}
