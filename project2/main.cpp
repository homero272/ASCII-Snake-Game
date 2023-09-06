/*
    Homero Arellano - Serves as the main controller for the game, calls functions from 
                      the Screen and Worm class to initialize the Snake and Screen, while
                      moving the snake accordingly (W,A,S,D)
*/

#include <iostream>
#include "Worm.hpp"
#include <string>
#include <stdlib.h>
#include "Screen.hpp"
#include <sstream>
#include "Cell.hpp"
#include <curses.h>
#include <signal.h>
#include <sgtty.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;


const int SEC_DELAY = 0;
const int USEC_DELAY = 800000;
static char lastc = ' ';

void die( void ); // occurs when the snake does and terminates the screen/ends game
char get_char( void ); // grabs nput recieved from the user during game
bool isValid(char cc); // validates if the input from user is valid (W,A,S,D)
void setWorm(Screen& screen, Worm& snake,Cell &curr); // sets the worm on screen
void setSnack(Screen& screen, Cell& snack); //sets the snack on screen
void setScore(int rows, int columns,int score); // sets the score (makes it visible during game)




int main(int argc,char*argv[]) {
    int rows = stoi(argv[1]);
    int columns = stoi(argv[2]);
    if(rows < 9 || rows > 25 || columns < 9 || columns > 80)
    {
        std::cerr << "Rows or Columns are not within bounds" << endl;
        exit(1);
    }

    Screen screen;
    screen.setWidthAndHeight(rows,columns);
    screen.setScreen();





    bool dead = false;
    int snake_row = (rows/2) + 1;
    int snake_col = (columns/2) - 3;
    
    Worm snake;
    Cell curr;

    curr.row = snake_row;
    curr.column = snake_col;
    curr.id = screen.id(curr);
    curr.state = -2;

    
    setWorm(screen,snake,curr);

  
    Cell snack;
    int score = 0;
    
    screen.startup();
    
    setSnack(screen,snack);
    mvaddstr(0,1,"Worm");
    mvaddstr(0,columns-3,"Score");

    refresh();
    int growth = 0;
    while(!dead)
    {
        setScore(rows,columns,score);
        refresh();

        char cc;
        do {cc = get_char();}
        while (cc == ' ' || isValid(cc) == false);


        if(cc == 'q')
        {
            dead = true;
            terminate();
            cout << "YOU QUIT!!! NO SAVED SCORE" << endl;
        }
        if(cc == 'w')
        {
            curr.row --;
        }
        else if(cc == 'a')
        {
            curr.column --;
        }
        else if(cc == 's')
        {
            curr.row ++;
        }
        else if(cc == 'd')
        {
            curr.column ++;
        }
        
       
        Cell free;
        if(screen.isFree(curr) == false)
        {
            dead = true;
            break;
        }
        refresh();
        if(screen.state(curr) == -3)
        {
            growth+=snack.size;
            score += snack.size;
            
            refresh();
                    
            if(!(screen.isFree(snack)))
            {
                terminate();
                cout << "SNACK IS NOT ACTUALLY FREE" << endl;
                exit(1);
                
            }
            setSnack(screen,snack);
            refresh();
            screen.update();
        }
        screen.update();
        
        Cell head;
        head = snake.head();
        screen.setState(head,-2);
        snake.addHead(curr);
        screen.wormOccupy(curr,-5);
        screen.update();
        if(growth < 1 )
        {
            free = snake.removeTail();
            screen.makeFree(free);
        }
        else if(growth > 0)
        {
            Cell tail;
            tail = snake.tail();
            screen.wormOccupy(tail,-2);
            growth --;
        }
        
        refresh();
        screen.update();

    }
    refresh();
    screen.terminate();
    cout << endl << "        GAME OVER!!!" << endl << endl << endl;
    cout << "       a$$$$$$$$$$a" << endl;
    cout << "     a$$$$$$$$$$$$$$a" << endl;
    cout << "   a$$$$$$$$$$$$$$$$$$a" << endl;
    cout << "  a$$$$$$$$$$$$$$$$$$$$a" << endl;
    cout << " a$$$$$   $$$$$$   $$$$$a" << endl;
    cout << "a$$$$$     $$$$     $$$$$a" << endl;
    cout << "a$$$$$$$ $$$$$$$$$$$$$$$$a" << endl;
    cout << "a$$$$$$$ $$$$$$$$$$$$$$$$a" << endl;
    cout << "a$$$$$$$$$$$$$$$$$$$$$$$$a" << endl;
    cout << " a$$$$$$          $$$$$$a" << endl;
    cout << "  a$$$$  $$$$$$$$  $$$$a" << endl;
    cout << "   a$$ $$$$$$$$$$$$ $$a" << endl;
    cout << "     a$$$$$$$$$$$$$$a" << endl;
    cout << "       a$$$$$$$$$$a" << endl << endl;
    cout << "YOU HIT SOMETHING!!!!" << endl << "FINAL SCORE: " << score << endl;
    


    return 0;
}






//closes the window
void die( void )
{
    signal( SIGINT, SIG_IGN );
    mvcur( 0, COLS - 1, LINES - 1, 0 );
    endwin();
    exit( 1 );
}


//recieves input from the user and returns the character recieved
char get_char( )
{
    char       c;
    struct timeval tvec;
    fd_set rfds;

    tvec.tv_sec = SEC_DELAY;
    tvec.tv_usec = USEC_DELAY;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    int retval = select(1, &rfds, NULL, NULL, &tvec);

    if ( retval < 0 )
        die();

    if ( retval ) {
        if ( read(0, &c, 1) < 0)
            die();
         if( c == 'a' || c == 'd' || c == 'w' || c == 's' ) {
             lastc = c;
         }
    }
    return( lastc );
}



//validates that the character given is valid in the 'a,w,s,d' format
bool isValid(char cc)
{
    if(cc != 'a' && cc != 'w' && cc != 's' && cc != 'd')
    {
        return false;
    }
    return true;
}


// initializes the snack cell and places it randomly on the screen as a random int
void setSnack(Screen& screen,Cell& snack){
    
    srand(time(nullptr));
    int num = rand() % 9 + 1;
    snack.size = num;
    string s = to_string(num);
    char c = s[0];
    snack = screen.getRandomFreeCell();
    while(!(screen.isFree(snack)))
    {
        snack = screen.getRandomFreeCell();
    }
    snack.state = -3;
    screen.wormOccupy(snack,-3);
    mvaddch(snack.row+1,snack.column+1,c);

}


//initializes the worm on the screen
void setWorm(Screen& screen, Worm& snake,Cell& curr){
    for(int i = 0; i < 8; ++i)
    {
        curr.column ++;
        snake.addHead(curr);
        
        curr.id = screen.id(curr);
        if(i == 7)
        {
            screen.wormOccupy(curr,-5);

        }
        else{
            screen.wormOccupy(curr,-2);
        }
    }
}

//sets the score on the top of the playing screen
void setScore(int rows,int columns, int score){
        string convert = to_string(score);
        if(convert.size() == 1)
        {
            char points = convert[0];
            mvaddch(0,columns+3,points);
        
        }
        else if(convert.size() == 2)
        {
            char points = convert[0];
            char points2 = convert[1];
            mvaddch(0,columns+3,points);
            mvaddch(0,columns+4,points2);
        }
        else if(convert.size() == 3)
        {
            char points = convert[0];
            char points2 = convert[1];
            char points3 = convert[2];
            mvaddch(0,columns+3,points);
            mvaddch(0,columns+4,points2);
            mvaddch(0,columns+5,points3);
        }
}
