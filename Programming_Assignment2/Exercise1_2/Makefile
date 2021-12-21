CXX 		= g++
CFLAGS 		= --std=c++17
DEBUG 		= -g
OPTIM 		= 
TARGET 		= main
OBJS_DIR	= obj
SOURCES_DIR = src
CXX_SOURCES = $(notdir $(wildcard ./src/*.cpp))
CXX_OBJS	= $(patsubst %.cpp, %.o, $(CXX_SOURCES))

all: src/*.cpp include/*.h
	$(CXX) $(CFLAGS) $(DEBUG) $(OPTIM) $(SOURCES_DIR)/main.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)