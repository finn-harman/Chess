chess: ChessMain.o ChessBoard.o Piece.o Bishop.o Rook.o Knight.o Queen.o King.o Pawn.o
	g++ -g ChessMain.o ChessBoard.o Piece.o Bishop.o Rook.o Knight.o Queen.o King.o Pawn.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h 
	g++ -Wall -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h Piece.h Bishop.h Rook.h Knight.h Queen.h King.h Pawn.h
	g++ -Wall -g -c ChessBoard.cpp

Piece.o: Piece.cpp Piece.h
	g++ -Wall -g -c Piece.cpp

Bishop.o: Bishop.cpp Bishop.h Piece.h
	g++ -Wall -g -c Bishop.cpp

Rook.o: Rook.cpp Rook.h Piece.h
	g++ -Wall -g -c Rook.cpp

Knight.o: Knight.cpp Knight.h Piece.h
	g++ -Wall -g -c Knight.cpp

Queen.o: Queen.cpp Queen.h Piece.h
	g++ -Wall -g -c Queen.cpp

King.o: King.cpp King.h Piece.h
	g++ -Wall -g -c King.cpp

Pawn.o: Pawn.cpp Pawn.h Piece.h
	g++ -Wall -g -c Pawn.cpp

clean:
	rm -f *.o execute
