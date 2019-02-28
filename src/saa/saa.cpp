#include "bits/stdc++.h"
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

int originalGraph[40][40];
using namespace std;

//g++ saa.cpp -l sqlite3 -o saa

vector<int> cities;
vector<int> finalOrder;
int arr[40];// arr is the array that stores the City order
int numOfCities;

class SAA{
    /*This Class defines the Basic functions for the SAA Problem, like taking the Input and calculating the distance matrix for the cities*/
    public:

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

     int CalculateDistance(int x1,int y1,int x2,int y2){
        return int(sqrt(pow(x1-x2,2)+pow(y1-y2,2)) + 0.5 );
     }


     void createOriginalDistanceGraph(){
        int i,j;
        for(i=0;i<numCities;i++){
            originalGraph[i][i]=0;

            for(j=i+1;j<numCities;j++){
                originalGraph[i][j]=CalculateDistance(points[i][0],points[i][1],points[j][0],points[j][1]);
                originalGraph[j][i]=originalGraph[i][j];
            }
        }
     }

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

int mini=INT_MAX;

std::vector<string> tempDistances;
vector<long double>distances;
//tempDistances.push_back(statement3);
static int callback(void *data, int argc, char **argv, char **azColName) {
   int i;
   //fprintf(stderr, "%s: ", (const char*)data);

   for(i = 0; i<argc; i++) {
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      //printf("%s\n", argv[i] );
      stringstream strTemp(argv[i]);
      long double x = 0;
      strTemp >> x;
      distances.push_back(x);
      //tempDistances.push_back( argv[i] );
   }
   printf("\n");
   return 0;
}


void print(std::vector<int> const &input){
	for (auto it = input.cbegin(); it != input.cend(); it++){
		std::cout << *it << ' ';
    //std::cout << *it + 1 << ' ';
    if (*it +1< input.back() ) {
      std::cout << *it + 1 << ' ';
    }
	}

}



void open_DB(vector<int> points) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   int x;
   int y;
   const char* data = "Callback function called";
   /* Open database */
   rc = sqlite3_open("data.sqlite", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

std::string statement = "SELECT distance  FROM connections WHERE id_city_1='1' AND id_city_2='7';";

      for(std::size_t i=0; i<points.size(); i++){
        x  = points[i];
   		  y = points[i+1];
        if (x == points.back() ) {
          break;
        }
      auto result = "SELECT distance  FROM connections WHERE id_city_1='" + std::to_string(x) +"'" + " AND" + " id_city_2='"  + std::to_string(y) +"';";
      //printf("%s\n", result.c_str() );
      string a = std::to_string(x);
      string b = std::to_string(y);
      //printf("%s aX\n", a.c_str());

      std::string statement3 = "SELECT distance  FROM connections WHERE id_city_1='";
      statement3.append(a.c_str());
      statement3.append("' AND id_city_2='");
      statement3.append(b.c_str());
      statement3.append("';");

      sql = (char *) statement3.c_str();
       /* Execute SQL statement */
      rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

 	}

  sql = (char *) statement.c_str();
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {

      fprintf(stdout, "Operation done successfully\n");
   }
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




int main ( int argc, char *argv[] ){
  vector<int> numbers = generate_Vector((char *) "instancias.txt");
  open_DB(numbers);

  double max = *max_element(distances.begin(), distances.end());
  cout<<"Max distance: "<<max<<endl;

  int i;

  vector<int>::iterator it,it2;
  SAA prob1;
  prob1.inputData();
  prob1.createOriginalDistanceGraph();
  numOfCities=prob1.numCities;

  //Generate the initial city tour and get the  nearestNeighbourTourLength
  int bestTourLength=getNearestNeighbourTour(); //start with a decent point

  if(mini > bestTourLength ) mini=bestTourLength;
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
          //cout<<"hi";


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
          if(mini > newTourLength ) mini=newTourLength;
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
  cout<<" Minimum: "<<mini<<"\n";
  return 0;



}
