/*-----------------------------------------<astar.cpp>-----------------------------------------*/
#include<cmath>
#include<iostream>
#include<cstddef>
#include"matrix.h"
#include"manhattan.h"
#include<cstdlib>
using namespace std;

Matrix * frontier = new Matrix[1000000];
long int top = -1;

int explored[1000000][9];
long int top_exp = -1;

void insertFront(Matrix *a_node)
{

    if(top==-1)
    {
        frontier[0] = *a_node;
    }
    else
    {
        long int i=0,j=0;

        while(i<=top && frontier[i].path_cost + heuristic(&frontier[i]) <= a_node->path_cost + heuristic(a_node))
            i++;
        for(j=top;j>=i; --j)
            frontier[j+1] = frontier[j];
        frontier[i] = *a_node;
    }
    top++;
}

Matrix * removeLast()
{
    Matrix * popped = new Matrix;
    if(top==-1)
        return NULL;
    else
    {
        for(int i=0; i<9; ++i)
            popped->state[i] = frontier[0].state[i];
        popped->parent = frontier[0].parent;
        popped->path_cost = frontier[0].path_cost;
        for(long int i=0; i<top; ++i)
            frontier[i] = frontier[i+1];
        top--;
        return popped;
    }
}

void insertExplored(int * state){
    top_exp++;
    for(int i=0; i<9; ++i)
        explored[top_exp][i] = state[i];
}

int isExplored(int * state)
{
    int cnt = 0;
    for(long int i=0; i<=top_exp; ++i)
    {
        cnt = 0;
        for(int j=0; j<9; ++j)
        {
            if(explored[i][j] == state[j])
            {
                cnt++;
            }
        }
        if(cnt==9)
            return 1;
    }
    return 0;
}

void astar(Matrix initial_node)
{

    Matrix * initial = new Matrix;
    initial = &initial_node;

    Matrix * temp, * gen_node;
    int actions;
    int possible_actions[4];

    insertFront(initial);

    while(true)
    {
        if(top==-1)
        {
            cout<<"Fail"<<endl;
            cout<<"No solution found!"<<endl;
            return;
        }
        temp = removeLast();
        insertExplored(temp->state);
        if(evaluate_Result(temp))
        {
            while(temp)
            {
                for(int i=0; i<9; ++i)
                    cout <<temp->state[i]<<" ";
                cout<<endl;
                temp = temp->parent;
            }
            return;
        }

        actions = temp->actions();
        switch(actions)
        {
            case 3:possible_actions[0]=1;possible_actions[1]=1;possible_actions[2]=0;possible_actions[3]=0;break;
            case 9:possible_actions[0]=1;possible_actions[3]=1;possible_actions[2]=0;possible_actions[1]=0;break;
            case 6:possible_actions[1]=1;possible_actions[2]=1;possible_actions[0]=0;possible_actions[3]=0;break;
            case 12:possible_actions[2]=1;possible_actions[3]=1;possible_actions[1]=0;possible_actions[0]=0;break;
            case 7:possible_actions[0]=1;possible_actions[1]=1;possible_actions[2]=0;possible_actions[3]=0;break;
            case 11:possible_actions[0]=1;possible_actions[1]=1;possible_actions[3]=1;possible_actions[2]=0;break;
            case 13:possible_actions[0]=1;possible_actions[3]=1;possible_actions[2]=1;possible_actions[1]=0;break;
            case 14:possible_actions[3]=1;possible_actions[1]=1;possible_actions[2]=1;possible_actions[0]=0;break;
            case 15:possible_actions[0]=1;possible_actions[1]=1;possible_actions[2]=1;possible_actions[3]=1;break;
        }

        for(int i=0; i<4; ++i)
        {
            if(possible_actions[i]==1)
            {
                gen_node = state_transition(temp,pow(2,i));
                if(isExplored(gen_node->state) == 0)
                    insertFront(gen_node);
            }
        }

    }

}
/*-----------------------------------------</astar.cpp>-----------------------------------------*/
