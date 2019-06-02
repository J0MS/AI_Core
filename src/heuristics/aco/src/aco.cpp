/*-----------------------------------------<aco.cpp>-----------------------------------------*/

#include <random>
#include <algorithm>
#include "aco.hpp"
#include "matrix.hpp"

using namespace std;

//Constructor
ACO::ACO(int n, int m){
  this->n = n;
  this->m = m;
  this->G = matrix(n);
  this->coverGraph = matrix(n);
  this->improveAttempts = 0;
  this->minimumCost = 0;
  for (int k = 0; k < ANTS; k++){
    Ant *a = new Ant(k, this->n);
    this->ants.push_back(a);
  }
}



pair<unordered_set<int>, int> ACO::getSolution(){
  this->getFullGraph();
  this->getFirstSolution();
  int C = this->minimumCost;
  int a = this->bestSolution.size();
  this->initialPheromone = (double)this->n * (this->n - a) / C;

  uniform_int_distribution<int> randomNode(0, this->n - 1);
  for (int j = 0; j < this->n; j++){
    this->globalPheromone.push_back(this->initialPheromone);
  }
  while (this->improveAttempts < MAX_IMPROVE_ATTEMPTS){
    for (Ant *k : this->ants){
      this->restart(k);
      this->stateTransition(k, randomNode(this->defaultRengine));
    }
    this->execIteration();
  }
  return {this->bestSolution, this->minimumCost};
}

void ACO::getFirstSolution(){
  matrix g(this->n);
  for (int i = 0; i < this->n; i++)
    for (int j = 0; j < this->n; j++){
      g.updateWeight(i, j, this->coverGraph.getWeight(i, j));}
  for (int i = 0; i < this->n; i++){
    int bestV;
    double maxRatio = 0;
    for (int j = 0; j < this->n; j++){
      double ratio = g.getWeight(j, j) / this->G.getWeight(j, j);
      if (ratio > maxRatio){
        bestV = j;
        maxRatio = ratio;
      }
    }
    if (maxRatio == 0)
      break;
    if (g.getWeight(bestV, bestV) > 0){
      this->bestSolution.insert(bestV);
      this->minimumCost += this->G.getWeight(bestV, bestV);
      for (int j = 0; j < this->n; j++){
        if (bestV == j)
          continue;
        if (g.getWeight(bestV, j) == 1){
          g.updateWeight(bestV, j, 0);
          g.updateWeight(j, bestV, 0);
          g.updateWeight(bestV, bestV, g.getWeight(bestV, bestV) - 1);
          g.updateWeight(j, j, g.getWeight(j, j) - 1);
        }
      }
    }
  }
}

void ACO::execIteration(){
  bool fullIteration = false;
  while (!fullIteration){
    fullIteration = true;
    for (Ant *k : this->ants){
      if (k->edgesMissing > 0){
        fullIteration = false;
        this->nextMove(k);
      }
    }
  }
  this->improveAttempts++;
  for (int j = 0; j < this->n; j++){
    if (this->bestSolution.find(j) != this->bestSolution.end()){
      this->globalPheromone[j] = (1 - EVAPORATION_RATE) * this->globalPheromone[j] + (EVAPORATION_RATE * (1.0 / this->minimumCost));
      //printf("Node %d %2.6f in cover graph\n", j, globalPheromone[j]);
    }
    else{
      this->globalPheromone[j] = (1 - EVAPORATION_RATE) * this->globalPheromone[j];
      //printf("%d %2.6f\n", j, globalPheromone[j]);
    }
  }
  //printf("--Iteration complete--\n");
  printf("Iteration %d %s\n",this->improveAttempts, "complete" );
}

void ACO::nextMove(Ant *k){
  double argMax = 0;
  int preferedVertex;
  double argSum = 0.0;
  for (int j = 0; j < this->n; j++){
    double arg = this->globalPheromone[j] * (k->CV.getWeight(j, j) / this->G.getWeight(j, j)) * RELATIVE_SIGNIFICANCE * 10;
    if (arg > argMax){
      argMax = arg;
      preferedVertex = j;
    }
    argSum += arg;
  }
  double q = this->urd(this->defaultRengine);
  if (q < THRESHOLD){
    this->stateTransition(k, preferedVertex);
  }
  else{
    vector<double> vertexProb(ceil(argSum));
    int i = 0;
    for (int j = 0; j < this->n; j++){
      double vertexChances = this->globalPheromone[j] * (k->CV.getWeight(j, j) / this->G.getWeight(j, j)) * RELATIVE_SIGNIFICANCE * 10;
      for (; i < vertexChances; i++){
        vertexProb[i] = j;
      }
    }
    uniform_real_distribution<double> dice(0, vertexProb.size() - 1);
    int result = vertexProb[dice(this->defaultRengine)];
    this->stateTransition(k, result);
  }
}

void ACO::stateTransition(Ant *k, int j){
  this->updateTotalWeight(k, j);
  k->actualVertex = j;
  //double prev = this->globalPheromone[j];
  this->globalPheromone[j] = (1 - PHI) * this->globalPheromone[j] + PHI * this->initialPheromone;
  if (k->edgesMissing == 0){
    this->evaluateSolution(k->solution, k->solutionCost);
  }
}

void ACO::updateTotalWeight(Ant *k, int v){
  if (k->solution.find(v) == k->solution.end()){
    k->solution.insert(v);
    k->solutionCost += this->G.getWeight(v, v);
  }
  for (int j = 0; j < this->n; j++){
    if (j == v)
      continue;
    if (k->CV.getWeight(v, j) == 1)
    {
      k->CV.updateWeight(v, j, 0);
      k->CV.updateWeight(j, v, 0);
      k->CV.updateWeight(v, v, k->CV.getWeight(v, v) - 1);
      k->CV.updateWeight(j, j, k->CV.getWeight(j, j) - 1);
      k->edgesMissing -= 1;
    }
  }
}

void ACO::evaluateSolution(unordered_set<int> &solution, int solutionCost){
  if (solutionCost < this->minimumCost){
    this->bestSolution = solution;
    this->minimumCost = solutionCost;
    this->improveAttempts = 0;
  }
}

void ACO::restart(Ant *k){
  for (int i = 0; i < this->n; i++)
    for (int j = 0; j < this->n; j++)
      k->CV.updateWeight(i, j, this->coverGraph.getWeight(i, j));
  k->edgesMissing = this->m;
  k->solution.clear();
  k->solutionCost = 0;
}

void ACO::getFullGraph(){
  for (int i = 0; i < this->n; i++){
    for (int j = i; j < this->n; j++){
      if (i == j){
        continue;
      }
      if (this->G.getWeight(i, j) == -1){
        this->coverGraph.updateWeight(i, j, 0);
      }
      else{
        this->coverGraph.updateWeight(i, j, 1);
        this->coverGraph.updateWeight(j, i, 1);
        this->coverGraph.updateWeight(i, i, this->coverGraph.getWeight(i, i) + 1);
        this->coverGraph.updateWeight(j, j, this->coverGraph.getWeight(j, j) + 1);
      }
    }
  }
}

void ACO::randomEngineGenerator(int seed){
  default_random_engine defaultRengine(seed);
  this->defaultRengine = defaultRengine;
  uniform_real_distribution<double> urd(0.0, 1.0);
  this->urd = urd;
}

void ACO::setWeight(int u, int w){
  this->G.updateWeight(u, u, w);
}

void ACO::setEdge(int u, int v){
  this->G.updateWeight(u, v, 1);
  this->G.updateWeight(v, u, 1);
}

ACO::~ACO(){
  for (auto x : this->ants){
    delete x;
  }

}

/*-----------------------------------------</aco.cpp>-----------------------------------------*/
