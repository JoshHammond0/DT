all: clean main

dt: dt.cpp
	g++ -g -Wall -Wextra -c -o dt.o dt.cpp

main:
	g++ -std=c++11 -g -Wall -Wextra -o main main.cpp dt.cpp

clean:
	rm -f main dt.o
