

CXX = g++
CXXFLAGS = -Wall
LDFLAGS = -lSDL2

SRCS = src/main.cpp src/componentManager.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = engine

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f engine $(OBJS)




# engine: src/main.cpp
# 	g++ -std=c++20 -Wall -o engine src/main.cpp -lSDL2
# clean:
# 	rm -f engine *.o