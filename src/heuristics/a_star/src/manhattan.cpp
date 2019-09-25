/*-----------------------------------------<Main.cpp>-----------------------------------------*/
#include<iostream>
#include"matrix.h"
#include"manhattan.h"
using namespace std;

int evaluate_Result(Matrix * curr_node){
    int goal_state[9] = {8,0,1,2,3,4,5,6,7};
    for(int i=0; i<9; ++i){
        if(curr_node->state[i] != goal_state[i])
            return 0;
    }
    return 1;
}

int heuristic(Matrix * curr_node){
    //heuristic is the number of the misplaced current_moves in the state.
    int goal_state[9] = {8,0,1,2,3,4,5,6,7};
    int heuristic = 0;
    for(int i=0; i<9; ++i)
    {
        if(curr_node->state[i] != goal_state[i])
        {
            heuristic++;
        }
    }
    return heuristic;
}

Matrix* state_transition(Matrix *curr_node, int action){
    Matrix *next_node = new Matrix;
    int blank_position = curr_node->state[0];
    int current_move;

    if(action==1){
        current_move = blank_position - 3;
        for(int i=1;i<9;++i){
            if(curr_node->state[i]==current_move)

            {
                next_node->state[0] = current_move;
                next_node->state[i] = blank_position;
            }
            else
            {
                next_node->state[i] = curr_node->state[i];

            }
        }

    }

    else if(action==2)//left action
    {
        current_move = blank_position-1;

        for(int i=0;i<9;++i)
        {
            if(curr_node->state[i]==blank_position-1)

            {
                next_node->state[0] = current_move;
                next_node->state[i] = blank_position;
            }
            else
            {
                next_node->state[i] = curr_node->state[i];
            }
        }

    }

    else if(action==4)//down action
    {
        current_move = blank_position+3;

        for(int i=0;i<9;++i)
        {
            if(curr_node->state[i]==blank_position+3)

            {
                next_node->state[0] = current_move;
                next_node->state[i] = blank_position;
            }
            else
            {
                next_node->state[i] = curr_node->state[i];
            }
        }

    }

    else//right action
    {
        current_move = blank_position+1;

        for(int i=0;i<9;++i)
        {
            if(curr_node->state[i]==blank_position+1)

            {
                next_node->state[0] = current_move;
                next_node->state[i] = blank_position;
            }
            else
            {
                next_node->state[i] = curr_node->state[i];
            }
        }

    }

    next_node->parent = curr_node;
    next_node->path_cost = curr_node->path_cost + 1;

    return next_node;
}
