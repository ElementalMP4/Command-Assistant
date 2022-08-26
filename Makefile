all: build

build: main.cpp
	g++ -o command-not-found main.cpp