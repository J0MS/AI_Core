#include "matrix.hpp"
#include "saa.hpp"
#include <vector>
#include <sqlite3.h>
#include<iostream>
#include<vector>
#include<string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <fstream>
#include <sqlite3.h>
#include "matrix.hpp"
#include "saa.hpp"
#include <unistd.h>

using namespace std;

std::vector<int> cities;
std::vector<int> currentSolution;
std::vector<int> finalSolution;


Matrix::Matrix() {}

Matrix::Matrix(int size){
  this->solution = size;
  this->Graphic = new double *[size];
  for (int i = 0; i < size; i++)
  {
    this->Graphic[i] = new double[size];
    for (int j = 0; j < size; j++)
      if (i == j)
        this->Graphic[i][j] = 0;
      else
        this->Graphic[i][j] = -1;
  }
}

void swap(vector<int> cities_vector,int i,int j){
    int temp=cities_vector[i];
    cities_vector[i]=cities_vector[j];
    cities_vector[j]=temp;
}

double getRadians(double value) {
  return (value*PI)/180;
}

void Matrix::addConnection(int u, int v, double weight) {
  this->Graphic[u][v] = weight;
}

int distance(int city1,int city2){
    return  cities[city1];
}

double Matrix::getDistance(int u, int v) {
  return this->Graphic[u][v];
}
