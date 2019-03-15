#include "bits/stdc++.h"
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <numeric>

#define R 6373000 //Planet radius
#define PI 3.14159265


static int originalGraph[1092][1092];
using namespace std;

//g++ saa.cpp -l sqlite3 -o saa

vector<int> cities;
vector<int> currentSolution;
vector<int> finalSolution;
vector<int> finalOrder;
int arr[40];// arr is the array that stores the City order
int numofCities;
//double planetRadius = 6373000;
vector<double>distances;
vector<double>latitude;
vector<double>longitude;
vector<double>instance;

class SAA{
    /*This Class defines the Basic functions for the SAA Problem, like taking the Input and calculating the distance matrix for the cities*/
    public:
      //static double tempDistance;
      char node[3];
      int points[40][2],numCities;
     //SAA(int i,int j) : x(i),y(j){}

     void inputData(){
        scanf("%d Num of cities?",&numCities);
        int i=0;
        int x,y;
        getc_unlocked(stdin);
        //double distance;
        while(i<numCities)
        {
            scanf("%s%d%d ",node,&points[i][0],&points[i][1]);
            //cities.push_back()
            i++;
        }

     }

    // double A = sin( pow(((latitude[129] - latitude[0])/2),2 ) ) + cos(latitude[0]) * cos(latitude[129]) * sin(pow(((longitude[129] - longitude[0])/2),2 ));
    // double C = 2 * atan2(sqrt(A),sqrt((1-A)));  //2 × arctan( A, 1 − A). sqrt(x)
    // double natural_distance = R * C;



     //double SAA::tempDistance = 0;

};




int distance(int city1,int city2){
    return originalGraph[city1][city2];
}

double getRandomNumber(double i,double j){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_real_distribution<double> distribution (i,j);
    //cout<<"returning random number:"<<(double(distribution(generator)))<<"\n";
    return double(distribution(generator));
}

//Returns the tour length of the current order of cities
int getTourLength() {
    //cout<<"the cuurentcities are \n";

    vector<int>:: iterator it=cities.begin();
    /*for(it=cities.begin();it!=cities.end();it++)
    {
        cout<<*it<<" ";
    }
    cout<<"\n";*/
    it=cities.begin();
    int pcity1=*it,ncity;
    //cout<<"City pointer is "<<pcity1<<"\n";
    int tourLength=distance(0,pcity1);
    for(it=cities.begin()+1;it!=cities.end();it++){
        ncity=*it;
        tourLength+=distance(pcity1,ncity);

        pcity1=ncity;
    }

    tourLength+=distance(pcity1,0); //adding the distance back to the source path
    return tourLength;
}

void swap(vector<int> cities_vector,int i,int j){
    int temp=cities_vector[i];
    cities_vector[i]=cities_vector[j];
    cities_vector[j]=temp;
}

int rdtsc(){
__asm__ __volatile__("rdtsc");
}

vector<int> generatenewPath(vector<int> cities_id) {
  double normal;
  int counter;
  int rand1 = (int) round(getRandomNumber(0,cities_id.size() -1));
  int rand2 = (int) round(getRandomNumber(0,cities_id.size() -1));

  printf("Aleatorios generados %d-%d\n", rand1, rand2);

  int temp=cities_id[rand1];
  cities_id[rand1]=cities_id[rand2];
  cities_id[rand2]=temp;

  //int nearestNeighbourTourLength=getTourLength();
  return cities_id;
}

void swap2(int i,int j)
{
    vector<int>::iterator it=cities.begin();
    int temp=*(it+i);
    *(it+i)=*(it+j);
    *(it+j)=temp;

}

double getProbability(int difference,double temperature) {
    return exp(-1*difference/temperature);
}

int minimum=INT_MAX;

//std::vector<string> tempDistances;

double tempDistance;
static int callbackDistance(void *data, int argc, char **argv, char **azColName ) {
   int i;
   int tmp;
   for(i = 0; i<argc; i++) {
     //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
     //printf("%s\n", argv[i] );
      stringstream strTemp(argv[i]);
      double x = 0;
      strTemp >> x;
      strTemp.clear();
      tempDistance = x ? x : 0;
      distances.push_back(x);
      strTemp.clear();
      //tempDistances.push_back( argv[i] );
   }
   //printf("\n");
   return 0;
}

double getDistance(int id1, int id2) {
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  char *sql,*sql2;
  int x,y;
  const char* data = "Callback function called";
  /* Open database */
  rc = sqlite3_open("data.sqlite", &db);

  if( rc ) {
     fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
  } else {
    std::string statement =  "SELECT distance  FROM connections WHERE id_city_1='" + std::to_string(id1) +"'" + " AND" + " id_city_2='"  + std::to_string(id2) +"';";
    sql = (char *) statement.c_str();
    rc = sqlite3_exec(db, sql, callbackDistance, (void*)data, &zErrMsg);
    //printf("INdides: %s \n", statement.c_str() );
    statement.clear();
  }
   sqlite3_close(db);
  return tempDistance;
}




//tempDistances.push_back(statement3);
static int callback(void *data, int argc, char **argv, char **azColName ) {
   int i;
   //fprintf(stderr, "%s: ", (const char*)data);

   for(i = 0; i<argc; i++) {
    //  printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      //printf("%s\n", argv[i] );
      stringstream strTemp(argv[i]);
      double x = 0;
      strTemp >> x;
      distances.push_back(x);
      //tempDistances.push_back( argv[i] );
   }
   //printf("\n");
   return 0;
}


double getRadians(double value) {
  return (value*PI)/180;
}

static int callbackLat(void *data, int argc, char **argv, char **azColName ) {
   for(int i = 0; i<argc; i++) {
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      //printf("%s\n", argv[i] );
      stringstream strTemp(argv[i]);
      double x = 0;
      double lat = 0;
      strTemp >> x;
      lat = getRadians(x);
      latitude.push_back(lat);
   }
   return 0;
}



static int callbackLong(void *data, int argc, char **argv, char **azColName ) {
   for(int i = 0; i<argc; i++) {
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      //printf("%s\n", argv[i] );
      stringstream strTemp(argv[i]);
      double x = 0;
      double lon = 0;
      strTemp >> x;
      lon = getRadians(x);
      longitude.push_back(lon);
   }
   return 0;
}


void print(std::vector<double> const &input){
	for (auto it = input.cbegin(); it != input.cend(); it++){
		std::cout << *it << ' ';
    //std::cout << *it + 1 << ' ';
    if (*it +1< input.back() ) {
      std::cout << *it + 1 << ' ';
    }
	}

}


void generate_Vectors(std::string field, std::string table) {
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  char *sql,*sql2;
  int x;
  int y;
  const char* data = "Callback function called";
  /* Open database */
  rc = sqlite3_open("data.sqlite", &db);

  if( rc ) {
     fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
  } //else {
     //fprintf(stderr, "Opened database successfully\n");
  //}
  for(std::size_t i=0; i<1093; i++){

    std::string statement = "SELECT "+field+" FROM "+table+" WHERE id" + " ='"  + std::to_string(i) +"';";
  //  auto result = "SELECT " + field +" FROM "+ table + " WHERE "+ cond1 + "='" + std::to_string(i) +"'" + " AND " +  cond2 + " ='"  + std::to_string(y) +"';";

    sql = (char *) statement.c_str();
    //char temp[] = "latitude";
    if (field == "latitude") {
      rc = sqlite3_exec(db, sql, callbackLat, (void*)data, &zErrMsg);
    } else if (field == "longitude") {
      rc = sqlite3_exec(db, sql, callbackLong, (void*)data, &zErrMsg);
    }

  //printf("%s\n", statement.c_str() );
  }
  sqlite3_close(db);
}

//


std::vector <int> read_citiesList(char instancias[]) {
	std::vector <int> temp_arr;
  std::ifstream inFile(instancias);
    if (inFile.is_open()){
        std::string line;
        while( std::getline(inFile,line) ){
            std::stringstream ss(line);
            stringstream lineStream(line);
            int num;
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
//d(u, v) = R × C.
double calculateDistance(int u,int v){
   //double A = sin( pow(((latitude[v-1] - latitude[u-1])/2),2 ) ) + cos(latitude[u-1]) * cos(latitude[v-1]) * sin(pow(((longitude[v-1] - longitude[u-1])/2),2 ));
   double A =  pow(sin(((latitude[v-1] - latitude[u-1])/2)),2 ) + cos(latitude[u-1]) * cos(latitude[v-1]) *  pow( (sin((longitude[v-1] - longitude[u-1])/2)),2 );
   double C = 2 * atan2(sqrt(A),sqrt(1-A));  //2 × arctan( A, 1 − A). sqrt(x)
   return R * C;
}

void createOriginalDistanceGraph(){
   int i,j;
   for(i=0;i<latitude.size();i++){
       originalGraph[i][i]=0;

       for(j=i+1;j<latitude.size();j++){
         originalGraph[i][j]=calculateDistance(i,j );
         originalGraph[j][i]=originalGraph[i][j];
       }
   }
}

void updateCitiesCost(vector<int> cities_id,vector<double> list_Cities) {
  for (size_t i = 0; i < cities_id.size()-1; i++) {
    for (size_t j = i; j < cities_id.size()-1; j++) {
      double distance = getDistance(cities_id[i],cities_id[j + 1]);
      list_Cities.push_back(distance );

      tempDistance = 0;
    }
  }

}

vector<double> Lprima;
double normal(vector<int> cities_id,vector<double> list_Cities) {
  double normal;
  int counter;
  for (size_t i = 0; i < cities_id.size()-1; i++) {
    for (size_t j = i; j < cities_id.size()-1; j++) {
      double distance = getDistance(cities_id[i],cities_id[j + 1]);
      if (distance != 0) {
        counter++;
        list_Cities.push_back(distance );
        //cout << counter << " " << i << ":"<< cities_id[i] << "-" <<cities_id[j + 1] << " = " <<list_Cities[counter] <<"\n";
      }

      tempDistance = 0;
    }
  }
  sort(list_Cities.begin(), list_Cities.end(), greater<int>());
  list_Cities.resize(cities_id.size() - 1);
  Lprima = list_Cities;
  return std::accumulate(list_Cities.begin(), list_Cities.end(), 0.);
}


double weightFunction(vector<double> dist, double norm) {
  double weight;
  weight = std::accumulate(dist.begin(), dist.end(), 0.) ;
  return weight/norm;
}


int main ( int argc, char *argv[] ){
  generate_Vectors("latitude","cities");
  generate_Vectors("longitude","cities");
  createOriginalDistanceGraph();
  vector<int> points = read_citiesList((char *) argv[1]);

  vector<double> L;
  int rows =  sizeof originalGraph / sizeof originalGraph[0];
  int cols = sizeof originalGraph[0] / sizeof(int);

  for (size_t i = 0; i < points.size()-1; i++) {
    L.push_back(getDistance(points[i],points[i + 1 ]) );
    //cout << " " << i << ":"<< points[i] << "-" <<points[i + 1] << " = " <<getDistance(points[i],points[i + 1 ]) <<"\n";
    tempDistance = 0;
  }

currentSolution=generatenewPath(points);

/*
  for (size_t i = 0; i < L.size(); i++) {
    printf("Imprimiendo L %d-%d -> %2.9f\n",points[i] , points[i + 1], L[i] );
  }
*/

  double normalizer = normal(currentSolution,Lprima);
  double max = *max_element(Lprima.begin(), Lprima.end());
  instance = L;
  for (size_t i = 0; i < instance.size(); i++) {
    if (instance[i] == 0) {
      instance[i] = calculateDistance(currentSolution[i],currentSolution[i + 1])* max;
    }
    //printf("Distancia calculada - L |id: %d|%d-%d->   %2.9f             :  ,%2.9f\n",i,points[i],points[i+1] ,instance[i],L[i]);
  }



  double cost = weightFunction(instance,normalizer);
  printf("Evaluation: %2.9f \n",cost );
  printf("MAX: %2.9f \n",max );
  printf("NORM: %2.9f \n",normalizer );
return 0;
/*
  for (size_t i = 0; i < instance.size(); i++) {
    printf("Imprimiendo instance %d-%d|    L:%d   ->   %2.9f\n",points[i] , points[i + 1],(int)i,instance[i] );
  }
*/
  std::cout << '\n' << ' ';
  int i;

  vector<int>::iterator it,it2;
  SAA prob1;
  //prob1.inputData();
  //createOriginalDistanceGraph();

  //print(Lprima);

  numofCities=instance.size();

std::cout << "1. random: " << (int) round(getRandomNumber(0,numofCities-1)) << '\n';
std::cout << "2. random: " << (int) round(getRandomNumber(0,numofCities-1)) << '\n';
std::cout << "3. random: " << (int) round(getRandomNumber(0,numofCities-1)) << '\n';

  //Generate the initial city tour and get the  nearestNeighbourTourLength
//int bestTourLength=generatenewPath(points, Lprima); //start with a random(better) point

return 0;
int bestTourLength;
  if(minimum > bestTourLength ) minimum=bestTourLength;
  double temperature,coolingRate=0.9,absoluteTemperature=0.00001,probability;
  int position1=0,position2=0;
  int newTourLength,difference;
  std::fstream fs;
  fs.open ("Results.txt", std::fstream::in | std::fstream::out );
  for(int rs=0;rs<1000;rs++){
      temperature=99999999999999999999999999999999999999999.0; //Initial Temperature
      //temperature=DBL_MAX;
      //cout<<"doing rs "<<rs<<"\n";
      fs<<"[";

      while(temperature > absoluteTemperature){
          //cout<<"LOL";


          position1=int(getRandomNumber(0,numofCities-1));
          position2=int(getRandomNumber(0,numofCities-1));
          while(position1==position2 or( (position1>numofCities-2) or (position2>numofCities-2)))
          {
              position1=int(getRandomNumber(0,numofCities-2));
              position2=int(getRandomNumber(0,numofCities-2));

          }
          cout<<"position1 is "<<position1<<" position2 is "<<position2<<"\n";


      }
      fs<<"]\n";
      random_shuffle(cities.begin(),cities.end());
      //cout<<"the best solution is "<<bestTourLength<<"\n";
    }
    fs.close();
  printf("Solution: %2.9f \n",bestTourLength );
  printf("Minumum: %2.9f \n",minimum );

  //for (size_t i = 0; i < finalOrder.size(); i++) {
  //  printf("Imprimiendo final order %d-%d|    L:%d   ->   %2.9f\n",(int)i,finalOrder[i] );
  //}

  //double cost2 = weightFunction(finalOrder,normalizer);
  //printf("Evaluation: %2.9f \n",cost2 );


  int feasible = ((bestTourLength > 1) ? 0 : 1);
  if (feasible==0) {
    cout<<" FEASIBLE: "<<"YES"<<"\n";
  } else {
    cout<<" FEASIBLE: "<<"NO"<<"\n";
  }
  return 0;



}
