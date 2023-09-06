/*
    Homero Arellano - Screen header file; Initializes the playing field and contains/keeps track of the
    `                 all the cells plus all the FREE cells on the playing field
*/
#include "Cell.hpp"
#include <vector>
#include <curses.h>
using namespace std;
#ifndef PROJECT2_SCREEN_HPP
#define PROJECT2_SCREEN_HPP
class Screen {
public:
    Screen();    //A constructor that initializes the vectors
    void setWidthAndHeight(int row,int column); // sets rows and columns of playing field
    void setScreen(); // only initilaizes the screen, does NOT draw it
    void update(); //updates the screen by redrawing based off any changes made
    int size(){return freeCells.size();} // returns the size of the free cell pool
    void makeFree(Cell c); // make c a free (empty) cell
    void wormOccupy(Cell c,int part); // make c occupied by the worm
    bool isFree(Cell c);// return true if c is free, false if it’s occupied
    int state(Cell c){return allCells.at(c.row).at(c.column).state;} // returns the state of the given cell 
    void setState(Cell c,int state){allCells.at(c.row).at(c.column).state = state;} // sets state of Cell accordingly
    Cell getRandomFreeCell(); // randomly select and return a free cell to place the snack in
    int id(Cell c){return allCells.at(c.row).at(c.column).id;} // returns the id of the cell wanted
    void startup( void ); // startups and initializes the main playing screen with worm
    void terminate( void ); // closes the playing screen nicely and ends with a message 

private:
    vector<Cell> freeCells;
    vector<vector<Cell> > allCells;
    int row, column;

};

#endif //PROJECT2_SCREEN_HPP
