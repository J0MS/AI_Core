/*-----------------------------------------<matrix.cpp>-----------------------------------------*/
#include "matrix.hpp"

matrix::matrix() {}

matrix::matrix(int n){
  this->sequence = n;
  this->G = new double *[n];
  for (int i = 0; i < n; i++){
    this->G[i] = new double[n];
    for (int j = 0; j < n; j++)
      if (i == j)
        this->G[i][j] = 0;
      else
        this->G[i][j] = -1;
  }
}

void matrix::updateWeight(int u, int v, double weight) {
  this->G[u][v] = weight;
}

double matrix::getWeight(int u, int v) {
  return this->G[u][v];
}

/*-----------------------------------------</matrix.cpp>-----------------------------------------*/
