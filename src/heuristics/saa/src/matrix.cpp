#include "matrix.hpp"
#include <vector>

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

void Matrix::addConnection(int u, int v, double weight) { this->Graphic[u][v] = weight; }
double Matrix::getDistance(int u, int v) { return this->Graphic[u][v]; }
