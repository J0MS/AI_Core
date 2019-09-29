/*-----------------------------------------<Main.cpp>-----------------------------------------*/
#include<iostream>
#include"matrix.h"
#include"astar.h"
static const char VERSION[] = "0.1";
using namespace std;

int main(){
    printf("\n");
    printf("%-25s%-25s", " " ,"A* Algorithm.\n");
    printf("Version: %s | @J0MS \n",VERSION);
    printf("\n");
    printf("Current problem: 8x8 Matrix\n");

    Matrix initialPosition;
    int position;

    for(int i=0; i<9; ++i){
        cin>>position;
        initialPosition.state[i] = position;
    }

    astar(initialPosition);
    return 0;
}
/*-----------------------------------------</Main.cpp>-----------------------------------------*/
