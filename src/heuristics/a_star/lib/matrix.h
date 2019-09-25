#ifndef Matrix_H
#define Matrix_H

class Matrix
{
    public:
      
        int state[9];
        int path_cost;
        Matrix * parent;
        //member functions
        Matrix();//constructor
        int actions();

};


#endif
