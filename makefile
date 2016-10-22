CC=g++
BIN=bin
INCL=include
LIB=lib
SRC=src
EXE=main

all: make_dirs gen_libs compile run

make_dirs:
	IF NOT EXIST $(BIN) (MD "$(BIN)")
	IF NOT EXIST $(INCL) (MD "$(INCL)")
	IF NOT EXIST $(LIB) (MD "$(LIB)")
	IF NOT EXIST $(SRC) (MD "$(SRC)")

gen_libs: main.o sembol.o kart.o konsol.o

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
	DEL "$(BIN)\$(EXE).exe"
	DEL "$(LIB)\*.o"