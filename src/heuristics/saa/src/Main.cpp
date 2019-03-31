#include <iostream>
#include <sstream>
#include <chrono>
#include <fstream>
#include <sqlite3.h>
#include "matrix.hpp"
#include "saa.hpp"
#include <unistd.h>


using namespace std;
static const char VERSION[] = "0.1";
istream *instance;
ifstream inFile;
Matrix graph(1092);
SAA saa(1092);

//static int callback(void *, int, char **, char **);


unsigned long long getTotalSystemMemory(){
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return pages * page_size;
}

bool is_file_exist(const char *fileName){
    std::ifstream infile(fileName);
    return infile.good();
}


std::vector <int> read_citiesList(char instancias[]) {
	std::vector <int> temp_arr;
  std::ifstream inFile(instancias);
    if (inFile.is_open()){
        std::string line;
        while( std::getline(inFile,line) ){
            std::stringstream ss(line);
            stringstream lineStream(line);
            std::vector<std::string> enrolled;
            std::string course;
            int registros = 0;
            while( std::getline(ss,course,',') ){
                 temp_arr.push_back(std::stoi( course ));
                 registros++;
                 //std::cout<<", \""<<course<<"\"";
            }
        }
    }

  	return temp_arr;
}


void updateCitiesCost(vector<int> cities_id,vector<double> list_Cities) {
  for (size_t i = 0; i < cities_id.size()-1; i++) {
    for (size_t j = i; j < cities_id.size()-1; j++) {
      double distance = cities_id[i]+cities_id[j + 1];
      list_Cities.push_back(distance );
    }
  }

}


// Fixed
static int callback(void *, int, char **, char **);

int main(int argc, char** argv){
  printf("\n");
  printf("%-25s%-25s", " " ,"Simulated annealing algorithm.\n");
  printf("Version: %s | @J0MS \n",VERSION);
  printf("\n");
  printf("Current problem: TSP\n");

  if(argc != 2) {
    cout << "Fatal error: You need to supply input file!." <<endl;
    printf("\n");
    return -1;
  }

  if (is_file_exist(argv[1])) {
    inFile.open(argv[1]);
    instance = &inFile;
    cout << "Succesfully loaded: "<< argv[1] <<endl;
  }else{
    cout << "Fatal error: File does not exist!." <<endl;
    return -1;
  }

  printf("Instance size:%d\n",(int)read_citiesList(argv[1]).size() );
  printf("\n");
  cout << "Memory: " << sizeof(instance) << " of " << getTotalSystemMemory() << " bytes" <<endl;
  int fisrt_seed=0, last_seed=500; //How many seeds?
  bool verbose=false;

  //Loading db   -> Now this block is impossible refactoring.
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

  rc = sqlite3_exec(db, sql, callback, &saa, &zErrMsg);

  if (rc != SQLITE_OK){
    cout << "SQL error: " << zErrMsg << endl;
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);


  string cityID;
  vector<int> currentSolution;

  // Reading instance
  while (getline(*instance, cityID)){
    // --PARSE INPUT--
    stringstream ss;
    ss << cityID;
    while (getline(ss, cityID, ','))
    {
      currentSolution.push_back(stoi(cityID) - 1);
    }

    // --./saa Testing seeds--
    for (int seed = fisrt_seed; seed < last_seed; seed++){
      auto start = chrono::steady_clock::now();
      saa.setRandomEngineGenerator(seed, currentSolution.size());
      pair<vector<int>, double> candidate_solution = saa.getSolution(currentSolution, verbose);

      printf("\nSeed number: %d\n", seed);
      for (auto i : candidate_solution.first){
        printf("%d,", i+1);
      }
      printf("\nEvaluation: %2.9f\n", candidate_solution.second);
      auto end = chrono::steady_clock::now();
      printf("Time: %d\n", (int)chrono::duration_cast<chrono::seconds>(end - start).count());
    }
    currentSolution.clear();
  }
  return 0;

}


static int callback(void *saa, int argc, char **argv, char **azColName){
  SAA *temp_saa = static_cast<SAA *>(saa);
  //terminate called after throwing an instance of 'std::logic_error'
  //what():  basic_string::_M_construct null not valid
  if (argv[7] != NULL)
    temp_saa->real_connection(stoi(argv[0]) - 1, stoi(argv[7]) - 1, stod(argv[8]));
  temp_saa->add_cityID(stoi(argv[0]) - 1, {stod(argv[4]), stod(argv[5])});
  return 0;
}


void printVector(std::vector<double> const &input){
	for (auto it = input.cbegin(); it != input.cend(); it++){
		std::cout << *it << ' ';
    //std::cout << *it + 1 << ' ';
    if (*it +1< input.back() ) {
      std::cout << *it + 1 << ' ';
    }
	}
}
