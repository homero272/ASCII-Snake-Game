/*
// Homero Arellano - Cell struct file, defines what a Cell type is and give it attributes
                     appropiate to the worm game, and overloads the '=' and '==' operator
*/

#ifndef PROJECT2_CELL_HPP
#define PROJECT2_CELL_HPP
struct Cell {
    /*
         0 = free Cell
         -1 = border
         -2 = occupied by worm
         -3 = occupied by snack
         -5= worm head

     */
    int id, state = 0, row = 0 , column = 0,size=0;
    
    //overloads the '=' assigning same attributes of 1 Cell to another
    Cell& operator= (const Cell s){
        this->id = s.id;
        this->row = s.row;
        this->column = s.column;
        this->state = s.state;
        
        return *this;
    };

    // overloads the '==' operator, comparing the row and column of the 2 snacks
    bool operator== (const Cell s){
        if(this->row == s.row)
        {
            if(this->column == s.column)
            {
                return true;
            }
        }
        return false;

    };


};
#endif //PROJECT2_CELL_HPP
