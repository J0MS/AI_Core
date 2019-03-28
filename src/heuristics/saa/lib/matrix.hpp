#ifndef GRAPH_H
#define GRAPH_H

class Matrix
{
private:
  int solution;
  double **Graphic;

public:
  Matrix();
  Matrix(int);
  void addConnection(int, int, double);
  double getDistance(int, int);
};

#endif
