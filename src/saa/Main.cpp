#include <iostream>
#include <sstream>
#include <chrono>
#include <fstream>
#include <sqlite3.h>
#include "jarro2783/cxxopts.hpp"
#include "matrix.hpp"
#include "saa.hpp"

using namespace std;




//Full graph
#define NUMBER_OF_CITIES 1092
#define DBREPOSITORY "../data/tsp.db"

// Callback function for open DB.
static int callback(void *, int, char **, char **);

int main(int argc, char** argv){
  cout << "epic ref 17 num num_cities solved!" << endl;
  auto currentseed = chrono::steady_clock::now();
  int fisrt_seed=0, last_seed=10; //How many seeds?
  istream *is = &cin;
  ifstream inFile;
  bool hybrid=false, sweep=true, verbose=false;

  cxxopts::Options options(argv[0], "TSP problem solution using simmulated saa heuristic.");
  try
  {
    options
      .add_options()
      ("h, help", "Show help")
      ("f, file", "Input file to read instance (ignore to read from stdin)", cxxopts::value<string>(), "file")
      ("s, start", "Start seed to use. Default is 0", cxxopts::value<int>(), "N")
      ("e, end", "End seed to use. Default is 10", cxxopts::value<int>(), "M")
      ("v, verbose", "Verbose accepted solutions")
      ("use-hybrid", "Use hybrid sweep calculation")
      ("skip-sweep", "Skip final sweep calculation");

    auto result = options.parse(argc, argv);
    if (result.count("h"))
    {
      cout << options.help() << endl;
      return 0;
    }
    if (result.count("f"))
    {
      inFile.open(result["f"].as<string>());
      is = &inFile;
    }
    if (result.count("s"))
    {
      fisrt_seed = result["s"].as<int>();
    }
    if (result.count("e"))
    {
      last_seed = result["e"].as<int>();
    }
    if (result.count("use-hybrid"))
    {
      hybrid = true;
    }
    if (result.count("final-sweep"))
    {
      sweep = false;
    }
    if (result.count("v"))
    {
      verbose = true;
    }
  } catch (const cxxopts::OptionException& e)
  {
    cout << "Error parsing options: " << e.what() << endl;
    return 1;
  }

  // NUMBER_OF_CITIES
  const int num_cities = NUMBER_OF_CITIES;
  SAA saa(num_cities);

  //Loading db
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  rc = sqlite3_open(DBREPOSITORY, &db);
  char sql[200];

  if (rc)
  {
    cout << " Can't open database: " << sqlite3_errmsg(db) << endl;
    return 0;
  }

  sprintf(sql, "SELECT * \
        FROM (SELECT * FROM cities LIMIT %d) A \
        LEFT JOIN (SELECT * FROM connections) B \
        ON A.id=B.id_city_1 AND B.id_city_2<=%d;",
          num_cities, num_cities);

  rc = sqlite3_exec(db, sql, callback, &saa, &zErrMsg);

  if (rc != SQLITE_OK)
  {
    cout << "SQL error: " << zErrMsg << endl;
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
  // --END DATABASE READ SECTION--

  string s;
  vector<int> currentSolution;

  // READ TEST CASES FROM INPUT FILE (COMMA SEPARATED).
  while (getline(*is, s))
  {
    // --PARSE INPUT--
    stringstream ss;
    ss << s;
    while (getline(ss, s, ','))
    {
      currentSolution.push_back(stoi(s) - 1);
    }
    // --END PARSE INPUT--
    // --SIMULATED ANNEALING--
    for (int seed = fisrt_seed; seed < last_seed; seed++)
    {
      auto start = chrono::steady_clock::now();
      // params: (seed, uniform_int_generator_max)
      saa.setRandomEngineGenerator(seed, currentSolution.size());
      // params: (initial_instance, hybrid_sweep?, final_sweep?)
      pair<vector<int>, double> res = saa.getSolution(currentSolution, hybrid, sweep, verbose);

      printf("\nSeed: %d\n", seed);
      for (auto i : res.first)
      {
        printf("%d, ", i+1);
      }
      printf("\nEvaluation: %2.9f\n", res.second);
      auto end = chrono::steady_clock::now();
      printf("Elapsed time: %d\n", (int)chrono::duration_cast<chrono::seconds>(end - start).count());
    }
    currentSolution.clear();
    // --END SIMULATED ANNEALING--
  }
  auto gend = chrono::steady_clock::now();
  printf("Total elapsed time: %d\num_cities", (int)chrono::duration_cast<chrono::seconds>(gend - currentseed).count());
  return 0;
}

static int callback(void *saa, int argc, char **argv, char **azColName)
{
  SAA *a = static_cast<SAA *>(saa);
  if (argv[7] != NULL)
    a->validEdge(stoi(argv[0]) - 1, stoi(argv[7]) - 1, stod(argv[8]));
  a->addCity(stoi(argv[0]) - 1, {stod(argv[4]), stod(argv[5])});
  return 0;
}
