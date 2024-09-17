engine: src/main.cpp
	g++ -std=c++20 -Wall -o engine src/main.cpp -lSDL2
clean:
	rm -f engine *.o