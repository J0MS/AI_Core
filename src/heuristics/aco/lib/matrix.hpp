/*-----------------------------------------<matrix.cpp>-----------------------------------------*/
#ifndef matrix_H
#define matrix_H

class matrix{
public:
  int sequence;
  double **G;

public:
  matrix();
  matrix(int);
  void updateWeight(int, int, double);
  double getWeight(int, int);
};

#endif

/*-----------------------------------------</matrix.cpp>-----------------------------------------*/
