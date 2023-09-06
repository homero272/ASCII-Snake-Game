/*
    Homero Arellano - Implementation of the actual Worm represented as a circular queue
*/


#include <array>
#include "Cell.hpp"
#include <iostream>
using namespace std;
#ifndef PROJECT2_WORM_HPP
#define PROJECT2_WORM_HPP


class Worm {
public:
    Worm(); //constructor for the worm
    void setMax(int num); // sets the allocation for the array based off rows and columns
    bool addHead(Cell c); // Given a cell, make it the new head of the worm
    Cell removeTail(); // Remove the worm’s tail from the queue
    Cell head() {return array[backIndex];} // Return the cell representing the position of the worm’s head without modifying the worm
    Cell tail() {return array[frontIndex];} // same for the tail
    int Size() {return size;} // returns the size of the array
private:
    Cell* array;
    int frontIndex, backIndex;
    int size,MAX;
};
#endif //PROJECT2_WORM_HPP
