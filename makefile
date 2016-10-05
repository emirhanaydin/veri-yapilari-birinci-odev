CC=g++
INCL=./include
SRC=./src
LIB=./lib

all: compile

compile: main.o sembol.o kart.o compile
	g++ $(LIB)/main.o $(LIB)/sembol.o $(LIB)/kart.o -o ./bin/main

main.o: $(SRC)/main.cpp
	$(CC) -I $(INCL) -c $(SRC)/main.cpp -o $(LIB)/main.o

sembol.o: $(SRC)/sembol.cpp
	$(CC) -I $(INCL) -c $(SRC)/sembol.cpp -o $(LIB)/sembol.o

kart.o: $(SRC)/kart.cpp
	$(CC) -I $(INCL) -c $(SRC)/kart.cpp -o $(LIB)/kart.o