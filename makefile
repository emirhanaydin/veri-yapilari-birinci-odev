CC=g++
INCL=./include
SRC=./src
LIB=./lib
BIN=./bin
EXE=main

all: gen-libs compile run

gen-libs: main.o sembol.o kart.o konsol.o

compile:
	$(CC) $(LIB)/main.o $(LIB)/sembol.o $(LIB)/kart.o $(LIB)/konsol.o -o $(BIN)/$(EXE)
	
run: 
	$(BIN)/$(EXE).exe

main.o:
	$(CC) -I $(INCL) -c $(SRC)/main.cpp -o $(LIB)/main.o

sembol.o:
	$(CC) -I $(INCL) -c $(SRC)/sembol.cpp -o $(LIB)/sembol.o

kart.o:
	$(CC) -I $(INCL) -c $(SRC)/kart.cpp -o $(LIB)/kart.o
	
konsol.o:
	$(CC) -I $(INCL) -c $(SRC)/konsol.cpp -o $(LIB)/konsol.o
	
clean:
	del "$(BIN)\$(EXE).exe"
	del "$(LIB)\*.o"