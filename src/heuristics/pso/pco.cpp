/*---------------------------------------------------------------<PSO>----------------------------------------------------------------------*/
#include<bits/stdc++.h>
#define ll long long int
#define pii pair<ll,ll>
#define mp make_pair
#define pb push_back
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define M 100005
#define mod 1000000007
#define inf LLONG_MAX


using namespace std;
int n;
vector<double> varsize;
double varmin;
double varmax;
double max_velocity;
double min_velocity;

double rand_double()
{
     return ((rand()%1000)/(1000.00));
}


/*
Cost function is the function on which the decision variable will be optimized
*/
double cost_function(vector<double> &a)
{
     double cost=0;
     for(int i=0;i<n;i++)
     cost+=abs(pow(a[i]-(i+1),2));
     return cost;
}


/*
Structure to implement the personal best of particle
have 2 parameters
1. position
2. cost
*/
struct node2
{
     vector<double> position;
     double cost;
     node2()
     {
          position.assign(n,0.0);
          cost=inf;
     }
};


/*
Structure of each particle having 5 parameters
1. position
2. velocity
3. cost
4. personal best position -> implemented with another structure node2
5. personal best cost     -> implemented with another structure node2
*/
struct node1
{
     vector<double> position,velocity;
     double cost;
     node2 best;
     node1()
     {
          position.assign(n,0.0);
          for(int i=0;i<n;i++)
          {
               position[i]=(rand_double()*(varmax-varmin))+varmin;     //  initializing random position
               best.position[i]=position[i];                           // initializing personal best position
          }
          velocity.assign(n,0);                                        // initializing velocity to zero
          cost=cost_function(position);                                // initializing cost
          best.cost=cost;                                              // initializing personal best cost
     }
     
     void update_velocity(double w,double c1,double c2,vector<double> &gbest)
     {
          for(int i=0;i<n;i++)
          {
               /*Updating velocity where v[i]=inertial_velocity+velocity_personal_best+velociy_soicial_best*/
               velocity[i]=w*velocity[i] ;                                  //Inertial velocity
               velocity[i]+=c1*rand_double()*(best.position[i]-position[i]);//Personal best velocity
               velocity[i]+=c2*rand_double()*(gbest[i]-position[i]);        //Global best velocity
               velocity[i]=min(velocity[i],max_velocity);
               velocity[i]=max(velocity[i],min_velocity);
          }
     }
     
     void update_position()
     {
          for(int i=0;i<n;i++)
          {
               /*Updating position where position=position+velocity*1*/
               position[i]=position[i]+velocity[i];
               position[i]=min(position[i],varmax);
               position[i]=max(position[i],varmin);
          }
     }
     
     void update_cost()
     {
          /*Updating cost function cosidering the current position*/
          cost=cost_function(position);
          if(best.cost>cost)
          {
               best.cost=cost;
               for(int i=0;i<n;i++)
               best.position[i]=position[i];
          }
     }
};


int main()
{
 	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int i,j;
	/* Problem  Defination*/
	n=5;
	varmin=-10.0;                         // Lower Bound of Decision Variables
	varmax=10.0;                          // Upper Bound of Decision Variables
	max_velocity=0.2*(varmax-varmin);     // Upper bound of velocity
	min_velocity=-max_velocity;           // Lower bound of velocity


	/* Parameters of PSO */
	int maxit=100;                       // Maximum iteration
	int npop=50;                         // population size
     double w=1;                          // Inertia coefficient
     double c1=2;                         // Personal Acceleration coefficient
     double c2=2;                         // Social Acceleration coefficient
     double wdamp=0.99;                   // Damping ratio of inertia coefficient


     /* Initialization */
     node2 globalbest ;                   // Initializing global best
     node1 particle[npop];                // Initializing each particle
     for(i=0;i<n;i++)
     {
          if(particle[i].best.cost<globalbest.cost)
          globalbest=particle[i].best;
     }


     /*Main loop of PSO*/
     ofstream file_;
     file_.open("result.txt");
     for(i=0;i<maxit;i++)
     {
          for(j=0;j<npop;j++)
          {
               particle[j].update_velocity(w,c1,c2,globalbest.position);   //Updating velocity
               particle[j].update_position();                              //Updating position
               particle[j].update_cost();                                  //Updating cost
               if(particle[j].best.cost<globalbest.cost)    //Updating the Global best decision veriables
               globalbest=particle[j].best;
          }
          w*=wdamp;
          cout<<"Iteration :"<<i+1<<"   "<<" Global best cost :"<<globalbest.cost<<endl;
          file_<<globalbest.cost<<endl;
     }


     /*Results*/
     cout<<endl<<"Global best cost :"<<globalbest.cost<<endl;
     cout<<"Global best position :"<<endl;
     for(i=0;i<n;i++)
     {
          cout<<fixed<<globalbest.position[i]<<" ";
     }
     cout<<endl;
     cin.get();
     file_.close();
     return 0;
}
/*---------------------------------------------------------------</PSO>----------------------------------------------------------------------*/
