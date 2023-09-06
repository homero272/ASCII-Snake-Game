# ASCII-Snake-Game
Homero Arellano

Traditional snake game in form of ASCII characters
uses the curses package
to run simply compile using 'make' or 'g++ *.cpp -lncurses' if make fails
when executing, it requires two numbers at the command line, indicating the grid space!
ex. ./a.out 9 9
9x9 is smallest
25x80 is biggest
uses a queue data structure as the 'snake' seen in the game
-gets updated via push/pop
keeps track of the head of the snake via '@'
curses library enables a sperate window for the game and is updated each move
