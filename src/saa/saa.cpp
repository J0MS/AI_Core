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
#include <numeric>

#define R 6373000 //Planet radius
#define PI 3.14159265


int originalGraph[1092][1092];
using namespace std;

//g++ saa.cpp -l sqlite3 -o saa

vector<int> cities;
vector<int> finalOrder;
int arr[40];// arr is the array that stores the City order
int numOfCities;
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
    //cout<<"returning "<<(double(distribution(generator)))<<"\n";
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
    //cout<<"\n the pcity is "<<pcity1<<"\n";
    int tourLength=distance(0,pcity1);
    for(it=cities.begin()+1;it!=cities.end();it++)
    {
        ncity=*it;
        tourLength+=distance(pcity1,ncity);

        pcity1=ncity;
    }

    tourLength+=distance(pcity1,0); //adding the distance back to the source path
    return tourLength;
}

void swap(int i,int j){
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}


int getNearestNeighbourTour() {
    vector<int>::iterator it;
    int numCities=numOfCities,i,j;

    for(i=0;i<numCities;i++)
    {
        arr[i]=i;
        //cout<<"arr is "<<i<<"\n";
    }
    int best,bestIndex;
    for(i=1;i<numCities;i++)
    {
        best=INT_MAX;
        for(j=i;j<numCities;j++)
        {
            if(distance(i-1,j)<best)
            {
                best=distance(i,j);
                bestIndex=j;
            }
        }
        swap(i,bestIndex);
    }
    cities.clear();
    for(i=1;i<numCities;i++)
    {
        cities.push_back(arr[i]);
        finalOrder.push_back(arr[i]);
    }

    int nearestNeighbourTourLength=getTourLength();
    return nearestNeighbourTourLength;
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
void open_DB(vector<int> points,std::string field , std::string table, std::string cond1, std::string cond2  ) {
   sqlite3 *db;//
   char *zErrMs;//g = 0;
   //int rc;
   char *sql,*sql2;
   int x,y,rc;
   const char* data = "Callback function called";
   /* Open database */
   rc = sqlite3_open("data.sqlite", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   } //else {
    //  fprintf(stderr, "Opened database successfully\n");
  // }

std::string statement = "SELECT latitude,longitude FROM cities WHERE id ='1092';";
//std::string statement2 = "SELECT longitude FROM cities WHERE id ='1092';";

      for(std::size_t i=0; i<points.size(); i++){
        x  = points[i];
   		  y = points[i+1];
        if (x == points.back() ) {
          break;
        }
      //std::string field = "distance";
      auto result = "SELECT " + field +" FROM "+ table + " WHERE "+ cond1 + "='" + std::to_string(x) +"'" + " AND " +  cond2 + " ='"  + std::to_string(y) +"';";

  //    sql = (char *) statement.c_str();
      //sql = (char *) result.c_str();
       /* Execute SQL statement */
    //  rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);


  //    sql2 = (char *) statement2.c_str();
      //sql = (char *) result.c_str();
       /* Execute SQL statement */
//      rc = sqlite3_exec(db, sql2, callback2, (void*)data, &zErrMsg);

 	}

      fprintf(stdout, "Operation done successfully\n");
   sqlite3_close(db);
}

std::vector <int> generate_Vector(char instancias[]) {
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

double CalculateDistance(int lat_U,int lat_V,int long_U,int long_V){
   //d(u, v) = R × C.
   double A = sin( pow(((latitude[lat_V] - latitude[lat_U])/2),2 ) ) + cos(latitude[lat_U]) * cos(latitude[lat_V]) * sin(pow(((longitude[long_V] - longitude[long_U])/2),2 ));
   double C = 2 * atan2(sqrt(A),sqrt((1-A)));  //2 × arctan( A, 1 − A). sqrt(x)
   double natural_distance = R * C;
   return natural_distance;
}

void createOriginalDistanceGraph(){
   int i,j;
   for(i=0;i<latitude.size();i++){
       originalGraph[i][i]=0;

       for(j=i+1;j<latitude.size();j++){
         originalGraph[i][j]=CalculateDistance(i,j,i,j );
         originalGraph[j][i]=originalGraph[i][j];
       }
   }
}


double normal(vector<double> dist) {
  return std::accumulate(dist.begin(), dist.end(), 0.);
  //return 0;
}

double weightFunction(vector<double> dist, double norm) {
  double weight;
  for (size_t i = 2; i < dist.size()-1; i++) {
    weight = std::accumulate(dist.begin(), dist.end(), 0.) ;
  }
  return weight/norm;
}


int main ( int argc, char *argv[] ){
  generate_Vectors("latitude","cities");
  generate_Vectors("longitude","cities");
  createOriginalDistanceGraph();
  vector<int> points = generate_Vector((char *) argv[1]);
  vector<double> L;
  vector<double> L_prima;
  //open_DB(points,"distance","connections","id_city_1","id_city_2");

  int rows =  sizeof originalGraph / sizeof originalGraph[0];
  int cols = sizeof originalGraph[0] / sizeof(int);

  for (size_t i = 0; i < points.size()-1; i++) {
    L.push_back(getDistance(points[i],points[i + 1 ]) );
    //cout << " " << i << ":"<< points[i] << "-" <<points[i + 1] << " : " <<getDistance(points[i],points[i + 1 ]) <<"\n";
    tempDistance = 0;
  }

  instance = L;
  double max = *max_element(L.begin(), L.end());

  for (size_t i = 0; i < points.size()-1; i++) {
    if (instance[i] == 0) {
      instance[i] = originalGraph[i][i + 1] * max;
    }
    //cout << " " << i << ":"<< points[i] << "-" <<points[i + 1] << " : " <<instance[i]<<"\n";
  }


  cout<<"Max distance: "<<max<<endl;

  double normalizer = normal(L);
  cout<<"Normalizer: "<<normalizer<<endl;

  double cost = weightFunction(instance,normalizer);
  cout<<"Evaluation: "<<cost<<endl;
  std::cout << '\n' << ' ';

  //for (vector<double>::iterator it = instance.begin() ; it != instance.end(); ++it){
  //  cout << "\t" << *it ;
  //}

  std::cout << '\n' << ' ';
  int i;

  vector<int>::iterator it,it2;
  SAA prob1;
  //prob1.inputData();
  //createOriginalDistanceGraph();

  //print(L);

  numOfCities=instance.size();


//return 0;
  //Generate the initial city tour and get the  nearestNeighbourTourLength
  int bestTourLength=getNearestNeighbourTour(); //start with a random(better) point

  if(minimum > bestTourLength ) minimum=bestTourLength;
  double temperature,coolingRate=0.9,absoluteTemperature=0.00001,probability;
  int position1=0,position2=0;
  int newTourLength,difference;
  std::fstream fs;
  fs.open ("tspResults.txt", std::fstream::in | std::fstream::out );
  for(int rs=0;rs<100;rs++){
      temperature=99999999999999999999999999999999999999999.0; //Initial Temperature
      //temperature=DBL_MAX;
      //cout<<"doing rs "<<rs<<"\n";
      fs<<"[";
      while(temperature > absoluteTemperature){
          //cout<<"LOL";


          position1=int(getRandomNumber(0,numOfCities-1));
          position2=int(getRandomNumber(0,numOfCities-1));
          while(position1==position2 or( (position1>numOfCities-2) or (position2>numOfCities-2)))
          {
              position1=int(getRandomNumber(0,numOfCities-2));
              position2=int(getRandomNumber(0,numOfCities-2));

          }
          //cout<<"position1 is "<<position1<<" position2 is "<<position2<<"\n";
          swap2(position1,position2);
          it2=cities.begin();
          if(position2 > position1)
          random_shuffle(it2+position1,it2+position2);
          newTourLength=getTourLength();
          if(minimum > newTourLength ) minimum=newTourLength;
          fs<<newTourLength<<",";
          //cout<<"current tour length is "<<newTourLength<<" n bestTourLength is "<<bestTourLength<<"\n\n";
          difference=newTourLength-bestTourLength;

          if(difference <0 or (difference >0 and  getProbability(difference,temperature) > getRandomNumber(0,1))){
              finalOrder.clear();

              for(it=cities.begin();it!=cities.end();it++)
              {
                  finalOrder.push_back(*it);
              }
              bestTourLength=difference+bestTourLength;
          }
          temperature=temperature*coolingRate;

      }
      fs<<"]\n";
      random_shuffle(cities.begin(),cities.end());
      //cout<<"the best solution is "<<bestTourLength<<"\n";
    }
    fs.close();
  cout<<"Solution: "<<bestTourLength<<"\n";
  cout<<" Minimum: "<<minimum<<"\n";
  return 0;



}
