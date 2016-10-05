CC=g++
INCL=./include
SRC=./src
LIB=./lib
BIN=./bin

all: compile

compile: main.o sembol.o kart.o
	$(CC) $(LIB)/main.o $(LIB)/sembol.o $(LIB)/kart.o -o $(BIN)/main
	$(BIN)/main.exe

main.o: $(SRC)/main.cpp
	$(CC) -I $(INCL) -c $(SRC)/main.cpp -o $(LIB)/main.o

sembol.o: $(SRC)/sembol.cpp
	$(CC) -I $(INCL) -c $(SRC)/sembol.cpp -o $(LIB)/sembol.o

kart.o: $(SRC)/kart.cpp
	$(CC) -I $(INCL) -c $(SRC)/kart.cpp -o $(LIB)/kart.o