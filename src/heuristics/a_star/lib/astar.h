#ifndef ASTAR_H
#define ASTAR_H



void insertFrontier(Matrix * frontier, long int * top,Matrix a_node);
Matrix* popFrontier(Matrix * frontier, int * top);

int isExplored(int * state);
void insertExplored(int * state);
void astar(Matrix initial_node);



#endif
