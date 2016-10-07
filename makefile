CC=g++
INCL=./include
SRC=./src
LIB=./lib
BIN=./bin
EXE=main

all: gen-libs compile run

gen-libs: main.o sembol.o kart.o

compile:
	$(CC) $(LIB)/main.o $(LIB)/sembol.o $(LIB)/kart.o -o $(BIN)/$(EXE)
	
run: 
	$(BIN)/$(EXE).exe

main.o: $(SRC)/main.cpp
	$(CC) -I $(INCL) -c $(SRC)/main.cpp -o $(LIB)/main.o

sembol.o: $(SRC)/sembol.cpp
	$(CC) -I $(INCL) -c $(SRC)/sembol.cpp -o $(LIB)/sembol.o

kart.o: $(SRC)/kart.cpp
	$(CC) -I $(INCL) -c $(SRC)/kart.cpp -o $(LIB)/kart.o
	
clean:
	del "$(BIN)\$(EXE).exe"
	del "$(LIB)\*.o"