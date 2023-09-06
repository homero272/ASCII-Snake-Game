OBJS	= Screen.o Worm.o main.o
SOURCE	= Screen.cpp Worm.cpp main.cpp
HEADER	= Cell.hpp Screen.hpp Worm.hpp
OUT	= p2
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -lncurses -o $(OUT) $(LFLAGS)

Screen.o: Screen.cpp
	$(CC) $(FLAGS) Screen.cpp 

Worm.o: Worm.cpp
	$(CC) $(FLAGS) Worm.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)
