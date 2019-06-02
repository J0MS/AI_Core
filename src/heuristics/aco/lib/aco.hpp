/*-----------------------------------------<aco.hpp>-----------------------------------------*/
#ifndef ANT_H
#define ANT_H

#include <unordered_set>
#include "matrix.hpp"

/* Class for represent Ants and atributes */
class Ant{
  public:
    int id;
    matrix CV;
    std::unordered_set<int> solution;
    int solutionCost;
    int edgesMissing;
    int actualVertex;

    //Constructor
    Ant(int k, int n){
      this->id = k;
      this->CV = matrix(n);
    };
};

#endif


#ifndef ACO_H
#define ACO_H

#include <vector>
#include <unordered_set>
#include <random>
#include "matrix.hpp"

using namespace std;

#define ANTS 15
#define RELATIVE_SIGNIFICANCE 1
#define THRESHOLD 0.5
#define EVAPORATION_RATE 0.2
#define PHI 0.12
#define MAX_IMPROVE_ATTEMPTS 150

/*Class for Ant Colony Optimization procedures and atributes*/
class ACO{
  private:
    int n;
    int m;
    matrix G;
    matrix coverGraph;
    vector<Ant *> ants;
    vector<double> globalPheromone;
    double initialPheromone;
    unordered_set<int> bestSolution;
    int minimumCost;
    int improveAttempts;
    default_random_engine defaultRengine;
    uniform_real_distribution<double> urd;

    void getFullGraph();
    void restart(Ant *);
    void updateTotalWeight(Ant *, int);
    void nextMove(Ant *);
    void execIteration();
    void stateTransition(Ant *, int);
    void evaluateSolution(unordered_set<int> &, int);
    void getFirstSolution();

  public:
    ACO(int, int);
    ~ACO();
    void setEdge(int, int);
    void setWeight(int, int);
    void randomEngineGenerator(int);
    pair<unordered_set<int>, int> getSolution();
};

#endif

/*-----------------------------------------</aco.hpp>-----------------------------------------*/
