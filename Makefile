name = o
libs = -lSDL2 -lSDL2_image
args = -std=c++20 $(libs)
srcs = $(wildcard ./src/*.cpp)

all:
	g++ $(srcs) $(args) -o $(name)
