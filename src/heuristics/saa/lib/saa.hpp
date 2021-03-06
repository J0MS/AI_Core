#ifndef SAA_H
#define SAA_H

#include "bits/stdc++.h"
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <numeric>
#include <vector>
#include <random>
#include "matrix.hpp"

using namespace std;

#define R 6373000 //Planet radius
#define PI 3.14159265
#define BATCH_SIZE 5000
#define MAX_BATCH_ATTEMPTS BATCH_SIZE * 10
#define EPSILON 0.001
#define EPSILONP 0.0001
#define PHI 0.95
#define INITIAL_TEMP 8
#define MINIMUM_ACCEPTED_P .95

class SAA{
public:
  int num_cities;
  Matrix Graphic;
  Matrix full_Graphic;
  pair<double, double> *cities;
  double normalizer;
  double max;
  vector<int> s;
  vector<int> minimum_solution;
  double minimum_cost;
  default_random_engine dre;
  uniform_int_distribution<int> uid;

  static double calculateDistance(double, double, double, double);
  void createOriginalDistanceGraph();
  void normal(vector<int> &);
  double weightFunction(vector<int> &);
  void generatenewPath(vector<int> &);
  pair<vector<int>, double> get_neighbour(double);
  double calculateBatch(double, bool);
  void acceptancebyThresholds(double, bool);
  double initialTemperature(double, double);
  double percentageofAccepted(double);
  double binarySearch(double, double, double);



public:
  SAA(int);
  void setRandomEngineGenerator(int, int);
  void real_connection(int, int, double);
  void add_cityID(int, pair<double, double>);
  pair<vector<int>, double> getSolution(vector<int> &, bool);
};

#endif
