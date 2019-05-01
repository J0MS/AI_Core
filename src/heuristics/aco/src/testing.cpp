#define CATCH_CONFIG_MAIN
#include <bits/stdc++.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include "catch.hpp"
#include "aco.hpp"
#include "matrix.hpp"


//class ACO;
//using namespace std;
int seed = 100;
int n, m, u, v, w;


void init(){
  std::cin >> n >> m;
  ACO aco(n, m);
}


/*
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

*/


int Factorial( int number ) {
 return number <= 1 ? 1      : Factorial( number - 1 ) * number;  // pass
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
