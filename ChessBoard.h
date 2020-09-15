#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

class ChessBoard {

  //////Create, initialise, destroy and reset board
  void delete_dynamic_memory();
  void initialise_variables();
  void initialise_board();

  Piece* board[8][8];
  char board_vis[8][8];
  bool white_turn;
  int turn_count;
  
  char* white_king_loc;
  char* black_king_loc;

  bool game_over;  

  ////////////Helper functions
  
  //Returns string of which player's turn it is
  const char* colour(bool white_turn);

  //Display chess board as 2D array of ASCII characters
  void display_board();
  void print_frame();
  void print_row(const char*, int row);

  //Performs termporary move
  void tempMove(const char* start, const char* end, Piece* board[8][8]);

  //Checks validity of temporary move
  bool temp_validMove(const char* start, const char* end, Piece* board[8][8]);

  //Undoes temporary move
  void undo_tempMove(const char* start, const char* end, Piece* start_piece, Piece* end_piece, Piece* board[8][8]);

  ////////////Functions for play
  
  //Check if player's move is valid
  bool validMove(const char* start, const char* end, bool white_turn, Piece* board[8][8], bool comments);

  //Checks called to verify move validity

  //Check start and end position are on the board
  bool check_input(const char* start, const char* end, bool comments);
  //Check if start position is a piece
  bool start_is_piece(const char* start, Piece* board[8][8]);
  //Check if end position is not player's own piece
  bool end_own_piece(const char* end, bool white_turn, Piece* board[8][8]);
  //Check move is for the player whose turn it is
  bool check_colour(const char* start, bool white_piece, Piece* board[8][8]);
  //Check player's move does not put themselves in check
  //To do this, we call king_in_check, tempMove, temp_validMove, undo_tempMove
  bool move_puts_king_in_check(const char* start, const char* end, bool white_turn, Piece* board[8][8]);
  //checkObsticles and checkPath are also called as checked - defined for each piece type in their respective class

  //Make move 		      
  void makeMove(const char* start, const char* end, bool white_turn, Piece* board[8][8]);

  //Check if move puts other player in check / checkmate / stalemate
  void check_game(bool white_turn, Piece* board[8][8]);
  
  //Check if other player has any valid moves
  bool can_move(bool white_turn, Piece* board[8][8]);
  
  //Check if other player's king is in check
  bool king_in_check(bool white_turn, Piece* board[8][8]);

 public:

  //////Create, initialise, destroy and reset board
  ChessBoard();
  ~ChessBoard();
  void resetBoard();

  ////////////Functions for play

  //Submit move - before a player's move is made, put it through checks to ensure it is valid
  void submitMove(const char* start, const char* end);
  
};

#endif
