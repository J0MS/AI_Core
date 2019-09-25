/*-----------------------------------------<Matrix.cpp>-----------------------------------------*/
#include<cstddef>
#include"matrix.h"

Matrix::Matrix(){
    //Put initial states in matrix
    for(int i=0; i<9; ++i){
        state[i] = -1;
    }
    //First cost of path
    path_cost = 0;
    //initialise the parent
    parent = NULL;
}

int Matrix::actions(){
    //up = 1; left = 2; down = 4; right = 8;
    //e.g: up,left,right = 11;
    //assumes valid state
    int blank_pos = state[0];
    int actions;

    switch(blank_pos){
        case 0: return 12;
        case 1: return 14;
        case 2: return 6;
        case 3: return 13;
        case 4: return 15;
        case 5: return 7;
        case 6: return 9;
        case 7: return 11;
        case 8: return 3;
    }
    return actions;

}
/*-----------------------------------------</Matrix.cpp>-----------------------------------------*/
