name = o
libs = -lSDL2
args = -std=c++20 $(libs)
srcs = $(wildcard ./src/*.cpp)

all:
	g++ $(srcs) $(args) -o $(name)
