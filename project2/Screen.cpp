/*
    Homero Arellano - Implemntaion for functions in the Screen.hpp; including setting the
                      playing field, starting up/ending the game
*/

#include "Screen.hpp"
#include "Cell.hpp"
#include "Worm.hpp"
#include <vector>
#include <iostream>

#include <stdlib.h>
#include <time.h>
#include<stdio.h>
using namespace std;

//constructor
Screen::Screen() {
    row = column = 0;
}

// sets the dimenseions (row x columns) for the playing field
void Screen::setWidthAndHeight(int row, int column) {
    this->row = row;
    this->column = column;
}

//sets the screen by creating a 2D vector of Cells and a 1D vector of free cells
void Screen::setScreen() {
     vector<Cell> cells;
     Cell cell;
     int id = 0;
     for(int i = 0; i < row + 2; ++i)
     {
         for(int j = 0; j < column + 2; ++j)
         {
             if(i == 0 || i == row +1 || j == 0 ||j == column + 1 )
             {
                 cell.id = -1;
                 cell.state = -1;
                 cell.row = i;
                 cell.column = j;
                 cells.push_back(cell);

             }
             else{
                 cell.id = id;
                 cell.column = j;
                 cell.row = i;
                 cell.state = 0;
                 freeCells.push_back(cell);
                 cells.push_back(cell);
                 id ++;

             }
         }
         allCells.push_back(cells);
         cells.clear();
     }
}




// given a cell, it updates it accordingly in the playing field (2D vector) as a free cell
// and adds it to the vector of free cells
void Screen::makeFree(Cell c) {
    c.state = 0;
    c.id = freeCells.size()-1;
    allCells.at(c.row).at(c.column).state = 0;
    allCells.at(c.row).at(c.column).id = c.id;
    Cell cell;
    cell = allCells.at(c.row).at(c.column);
    freeCells.push_back(c);
}

// given a cell and state of the cell, sets the cell as occupied in the 2D vector and
// removes it from the the vector of free cells
void Screen::wormOccupy(Cell c, int part) {
    c.state = part;
    allCells.at(c.row).at(c.column).state = part;
    if(freeCells.size()!=0)
    {
        int rowtemp = freeCells.at(freeCells.size() - 1).row;
        int coltemp = freeCells.at(freeCells.size() - 1).column;
        

        for(int i = 0; i < freeCells.size(); ++i)
        {
            if(c.row == freeCells.at(i).row)
            {
                if(c.column == freeCells.at(i).column)
                {
                    freeCells.at(i).row = rowtemp;
                    freeCells.at(i).column = coltemp;
                    break;
                }
            }
        }
        freeCells.pop_back();
    }
}

//returns a bool on whether or not a given cell is free or not (true = free)
bool Screen::isFree(Cell c) {
   if(allCells.at(c.row).at(c.column).state == 0 || allCells.at(c.row).at(c.column).state == -3) // snack is also "free"
   {
       return true;
   }
    return false;
}


//grabs a radom cell from the pool of free cells and returns it
Cell Screen::getRandomFreeCell() {
    Cell free;
    srand(time(nullptr));
    int random;
    random = rand() % (freeCells.size()-1);
    free = freeCells.at(random);
    

    return free;

}

//starts up the actual game, with both screen and worm drawn
void Screen::startup( void )
{
    initscr();     /* activate the curses */
    curs_set(0);   /* do not display the cursor */
    clear();       /* clear the screen that curses provides */
    noecho();      /* prevent the input chars to be echoed to the screen */
    cbreak();      /* change the stty so that characters are delivered to the
                       program as they are typed--no need to hit the return key!*/

    for(int i = 0; i < allCells.size(); ++i)
    {
        for(int j = 0; j < allCells.at(i).size(); ++j){
            if(allCells.at(i).at(j).state == -1)
            {
                mvaddch(i+1,j+1,'*');
            }
            if(allCells.at(i).at(j).state == -2)
            {
                mvaddch(i+1,j+1,'o');
            }
            if(allCells.at(i).at(j).state == -5)
            {
                mvaddch(i+1,j+1,'@');
            }  
        }
    }
    refresh();
}

//updates (redraws) the screen accoriding to the pool of all cells (2D vector)
void Screen::update() {
    for(int i = 0; i < allCells.size(); ++i)
    {
        for(int j = 0; j < allCells.at(i).size(); ++j){
            if(allCells.at(i).at(j).state == -1)
            {
                //cout << allCells.at(i).at(j).id << " ";
                mvaddch(i+1,j+1,'*');
            }
            if(allCells.at(i).at(j).state == 0)
            {
                mvaddch(i+1,j+1,' ');
            }
            if(allCells.at(i).at(j).state == -2)
            {
                mvaddch(i+1,j+1,'o');
            }
            if(allCells.at(i).at(j).state == -5)
            {
                mvaddch(i+1,j+1,'@');
            }


        }
    }

    refresh();
}


// occurs when the worm dies and closes the window nicely
void Screen::terminate( void )
{
    mvcur( 0, COLS - 1, LINES - 1, 0 );
    clear();
    refresh();
    endwin();
}
