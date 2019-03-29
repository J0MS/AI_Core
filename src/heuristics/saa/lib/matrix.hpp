#ifndef MATRIX_H // error: redefinition of ‘class Matrix’
#define MATRIX_H

class Matrix{
private:
  int solution;
  double **Graphic;

public:
  Matrix();
  Matrix(int);
  void addConnection(int, int, double);
  double getDistance(int, int);
  void load_Database();
  
};

#endif
