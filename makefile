CC=g++
CFLAGS=-std=c++11 -Wall -g #-DDEBUG

EXE=echecs

SRC=lemain.cpp square.cpp chessboard.cpp piece.cpp game.cpp
OBJ=lemain.o  square.o  chessboard.o  piece.o  game.o
INC=main.h square.h chessboard.h piece.h game.h piece_annexe.h

all: $(EXE) docs

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -o $@

.PHONY: docs

docs: $(SRC) $(INC) ./Doxyfile
	@doxygen ./Doxyfile

SUFFIXES:.cpp .o

lemain.o : lemain.cpp chessboard.cpp game.cpp
	$(CC) $(CFLAGS) -c $<

game.o: game.cpp chessboard.h piece.h square.h piece_annexe.h
	$(CC) $(CFLAGS) -c $<

chessboard.o : chessboard.cpp piece.h square.h piece_annexe.h
	$(CC) $(CFLAGS) -c $<

piece.o: piece.cpp piece.h square.h chessboard.h piece_annexe.h
	$(CC) $(CFLAGS) -c $<

square.o : square.cpp square.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXE) *.o *.dSYM *~ 
