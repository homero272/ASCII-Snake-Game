/*
    Homero Arellano - Actual implementation of the worm; includes basic operations
                      such as adding/removing
*/

#include "Worm.hpp"

const int MAXSIZE = 2000;

//initializes/constructs the worm data type
Worm::Worm() {
    MAX = MAXSIZE;



    array = new Cell[MAX]; // actually allocate the array
    if (array == nullptr) {
        std::cerr << "Couldn't allocate initial array\n";
        exit(1);
    }

    frontIndex = 0;
    size = 0;
    backIndex = 0;
}

//sets the max allocation for the worm
void Worm::setMax(int num) {
    MAX = num;
}

// adds to the head/back of the array and returns whether it was successful or not
bool Worm::addHead(Cell c) {
    //makes sure queue isnt full
    c.state = -2;
    if(size == MAX){
        return false;
    }
    else if (size == 0){
        array[frontIndex] = c;

    }
    else{
        backIndex = (backIndex+1) % MAX;
        array[backIndex] = c;
    }

    size++;
    return true;

}



//removes from tail/front of the array and returns the cell removed
Cell Worm::removeTail() {

    if (size == 1){
        Cell value;
        value.state = 0;
        value = array[frontIndex];


        backIndex = 0;
        frontIndex = 0;
        size --;
        return value;
    }
    if(size > 1){
        Cell value;
        value = array[frontIndex];

        frontIndex +=1;
        size --;
        return value;
    }
}


