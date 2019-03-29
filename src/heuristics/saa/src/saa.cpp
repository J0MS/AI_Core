#include "bits/stdc++.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <random>
#include "saa.hpp"
#include "matrix.hpp"
#include <bits/stdc++.h>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <numeric>

using namespace std;

SAA::SAA(int size){
  this->num_cities = size;
  this->Graphic = Matrix(size);
  this->full_Graphic = Matrix(size);
  this->cities = new pair<double, double>[size];
}

void SAA::setRandomEngineGenerator(int seed, int size){
  default_random_engine dre(seed);
  this->dre = dre;
  uniform_int_distribution<int> uid(0, size - 1);
  this->uid = uid;
}

pair<vector<int>, double> SAA::getSolution(vector<int> &currentSolution, bool verbose){
  this->normalizer = 0;
  this->max = 0;
  this->minimum_cost = numeric_limits<double>::max(); // get Infinite!
  this->normal(currentSolution);
  this->createOriginalDistanceGraph();
  this->generatenewPath(currentSolution);
  double temperature = this->initialTemperature(INIT_T, MIN_INIT_ACC_P);
  this->acceptancebyThresholds(temperature, verbose);
  return {this->minimum_solution, this->minimum_cost};
}



double SAA::weightFunction(vector<int> &currentSolution){
  double sum = 0;
  for (int i = 0; i <(int)currentSolution.size() - 1; i++){
    sum += this->full_Graphic.getDistance(currentSolution[i], currentSolution[i + 1]);
  }
  return sum / this->normalizer;
}

void SAA::real_connection(int u, int v, double weight){
  this->Graphic.addConnection(u, v, weight);
  this->Graphic.addConnection(v, u, weight);
}

void SAA::normal(vector<int> &currentSolution){
  vector<double> L;
  int m = currentSolution.size();
  for (int i = 0; i < m; i++){
    for (int j = i + 1; j < m; j++){
      double w_ij = this->Graphic.getDistance(currentSolution[i], currentSolution[j]);
      if (w_ij > 0)
        L.push_back(w_ij);
    }
  }

  sort(L.rbegin(), L.rend());
  this->max = L.front(); // Mas rapido despues de ordenar.
  double normalizer = 0;
  for (int i = 0; i <(int)currentSolution.size() - 1; i++)
    normalizer += L[i];
  this->normalizer = normalizer;
}

double SAA::calculateDistance(double latU, double longU, double latV, double longV){
  latU = latU * PI / 180;
  latV = latV * PI / 180;
  longU = longU * PI / 180;
  longV = longV * PI / 180;

  double A = pow(sin((latV - latU) / 2), 2) + cos(latU) * cos(latV) * pow(sin((longV - longU) / 2), 2);
  double C = 2.0 * atan2(sqrt(A), sqrt(1 - A));
  return R * C;
}

void SAA::createOriginalDistanceGraph(){
  for (int i = 0; i < this->num_cities; i++)
    for (int j = 0; j < this->num_cities; j++){
      double actualW = this->Graphic.getDistance(i, j);
      if (actualW == -1){
        double latU = cities[i].first;
        double latV = cities[j].first;
        double longU = cities[i].second;
        double longV = cities[j].second;
        double ws = SAA::calculateDistance(latU, longU, latV, longV) * this->max;
        this->full_Graphic.addConnection(i, j, ws);
      }
      else{
        this->full_Graphic.addConnection(i, j, actualW);
      }
    }
}

void SAA::add_cityID(int i, pair<double, double> position){
  //TODO Update the vector in this function
  this->cities[i] = position;
}

//Procedimiento 1
double SAA::calculateBatch(double T,  bool verbose){
  int c = 0;
  int i = 0;
  double r = 0.0;
  double solution_cost = this->weightFunction(this->s);
  while (c < BATCH_SIZE){
    pair<vector<int>, double> get_neighbour = this->get_neighbour(solution_cost);
    vector<int> sp;
    sp.swap(get_neighbour.first);
    double neighbour_cost = get_neighbour.second;

    if (neighbour_cost < solution_cost + T){
      if(verbose){
        printf("%2.9f\n", neighbour_cost);
      }
      if(neighbour_cost < this->minimum_cost) {
        this->minimum_solution = sp;
        this->minimum_cost = neighbour_cost;
      }
      sp.swap(this->s);
      solution_cost = neighbour_cost;
      c += 1;
      r += neighbour_cost;
    }
    else
      i += 1;
    if (i >= MAX_BATCH_ATTEMPTS)
      break;
  }
  return (double)r / (double)BATCH_SIZE;
}


//Procedimiento 2
void SAA::acceptancebyThresholds(double T, bool verbose){
  double p = 0;
  while (T > EPSILON)
  {
    double q = numeric_limits<double>::max(); // get Infinite!
    while (p <= q)
    {
      q = p;
      p = this->calculateBatch(T, verbose);
    }
    T = PHI * T;
  }
}


//Procedimiento 3
double SAA::initialTemperature(double T, double P){
  double p = this->percentageofAccepted(T);
  double T1;
  double T2;
  if (abs(P - p) <= EPSILONP) //EpsilonP
    return T;
  if (p < P)
  {
    while (p < P)
    {
      T = 2 * T;
      p = this->percentageofAccepted(T);
    }
    T1 = T / 2;
    T2 = T;
  }
  else
  {
    while (p > P)
    {
      T = T / 2;
      p = this->percentageofAccepted(T);
    }
    T1 = T;
    T2 = 2 * T;
  }
  return this->binarySearch(T1, T2, P);
}

//Procedimiento 4
double SAA::percentageofAccepted(double T){
  int c = 0;
  int attempts = 0;
  for (int i = 0; i < BATCH_SIZE; i++){
    double solution_cost = this->weightFunction(this->s);
    pair<vector<int>, double> get_neighbour = this->get_neighbour(solution_cost);
    vector<int> sp;
    sp.swap(get_neighbour.first);
    double neighbour_cost = get_neighbour.second;
    if (neighbour_cost <= solution_cost + T){
      c += 1;
      sp.swap(this->s);
      attempts = 0;
    }
    else
      attempts += 1;
    if (attempts >= MAX_BATCH_ATTEMPTS)
      break;
  }
  double res = (double)c / (double)BATCH_SIZE;
  return res;
}


//Procedimiento 5
double SAA::binarySearch(double T1, double T2, double P){
  double Tm = (T1 + T2) / 2;
  if (T2 - T1 < EPSILONP)
    return Tm;
  double p = this->percentageofAccepted(Tm);
  if (abs(P - p) < EPSILONP)
    return Tm;
  if (p > P)
    return this->binarySearch(T1, Tm, P);
  else
    return this->binarySearch(Tm, T2, P);
}

void SAA::generatenewPath(vector<int> &currentSolution){
  this->s = currentSolution;
  shuffle(this->s.begin(), this->s.end(), dre);
}

pair<vector<int>, double> SAA::get_neighbour(double solution_cost){
  vector<int> sp = this->s;
  double neighbour_cost = solution_cost * this->normalizer;
  int i = this->uid(dre);
  int j;
  do{
    j = this->uid(dre);
  } while (i == j);

  if (j < i){
    i = i + j;
    j = i - j;
    i = i - j;
  }

  if (i != j - 1){
    neighbour_cost -= this->full_Graphic.getDistance(sp[i], sp[i + 1]);
    neighbour_cost -= this->full_Graphic.getDistance(sp[j - 1], sp[j]);
    neighbour_cost += this->full_Graphic.getDistance(sp[j], sp[i + 1]);
    neighbour_cost += this->full_Graphic.getDistance(sp[j - 1], sp[i]);
  }

  if (i != 0){
    neighbour_cost -= this->full_Graphic.getDistance(sp[i - 1], sp[i]);
    neighbour_cost += this->full_Graphic.getDistance(sp[i - 1], sp[j]);
  }
  if (j != (int)sp.size() - 1){
    neighbour_cost -= this->full_Graphic.getDistance(sp[j], sp[j + 1]);
    neighbour_cost += this->full_Graphic.getDistance(sp[i], sp[j + 1]);
  }

  sp[i] = sp[i] + sp[j];
  sp[j] = sp[i] - sp[j];
  sp[i] = sp[i] - sp[j];
  return {sp, neighbour_cost / this->normalizer};
}






void generate_Vectors(std::string field, std::string table) {
  char *zErrMsg = 0;
  const char* data = "Callback function called";
  std::cout << zErrMsg << '\n';
  std::cout << data << '\n';
}
