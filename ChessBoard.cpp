#include "ChessBoard.h"
#include <iostream>
#include <cstring>

//////Create, initialise, destroy and reset board
ChessBoard::ChessBoard() {

  initialise_variables();
  initialise_board();
  display_board();
}

ChessBoard::~ChessBoard() {
  delete_dynamic_memory();
}

void ChessBoard::resetBoard() {
  
  delete_dynamic_memory();
  initialise_variables();
  initialise_board();
  display_board();
}

void ChessBoard::delete_dynamic_memory() {

  for (int rank = 0 ; rank < 8 ; rank++)
    for (int file = 0 ; file < 8 ; file++)
      if (board[rank][file] != nullptr) {	
	delete board[rank][file];
	board[rank][file] = nullptr;
      }

  delete [] white_king_loc;
  delete [] black_king_loc;
}

void ChessBoard::initialise_variables() {

  std::cout << "A new chess game is started!" << std::endl;  
  std::cout << std::endl;
  
  std::cout << "Lower case letters are White." << std::endl;
  std::cout << "Upper case letters are Black." << std::endl;
  std::cout << std::endl;

  white_king_loc = new char[3];
  black_king_loc = new char[3];
  
  white_turn = true;
  turn_count = 0;
  game_over = false;
}

void ChessBoard::initialise_board() {

  bool black_or_white = true; //black_or_white = true means white
  for (int i = 0 ; i <8 ; i++)
    for (int j = 0 ; j < 8 ; j++) {
      board[j][i] = nullptr;
      board_vis[j][i] = '.';
    }

  for (int rank = 1; rank < 8; rank += 5) {
    for (int file = 0 ; file < 8 ; file ++) {
      board[rank][file] = new Pawn(black_or_white, "Pawn");
      *board[rank][file] = Pawn(black_or_white, "Pawn");
      board_vis[rank][file] = ((black_or_white == true) ? 'p' : 'P');
    }
    black_or_white = !black_or_white;
  }
  
  for (int rank = 0; rank < 8; rank += 7) {
    for (int file = 0 ; file < 8 ; file += 7) {
      board[rank][file] = new Rook(black_or_white, "Rook");
      *board[rank][file] = Rook(black_or_white, "Rook");
      board_vis[rank][file] = ((black_or_white == true) ? 'r' : 'R');      
    }
    black_or_white = !black_or_white;
  }
  
  for (int rank = 0; rank < 8; rank += 7) {
    for (int file = 1 ; file < 8 ; file += 5) {
      board[rank][file] = new Knight(black_or_white, "Knight");
      *board[rank][file] = Knight(black_or_white, "Knight"); 
      board_vis[rank][file] = ((black_or_white == true) ? 'n' : 'N');
    }
    black_or_white = !black_or_white;
  }

  for (int rank = 0; rank < 8; rank += 7) {
    for (int file = 2 ; file < 8 ; file += 3) {
      board[rank][file] = new Bishop(black_or_white, "Bishop");
      *board[rank][file] = Bishop(black_or_white, "Bishop");
      board_vis[rank][file] = ((black_or_white == true) ? 'b' : 'B');
    }
    black_or_white = !black_or_white;
  }

  //black_or_white = true here
  
  board[0][4] = new King(black_or_white, "King");
  *board[0][4] = King(black_or_white, "King");
  strcpy(white_king_loc, "E1");
  board_vis[0][4] = 'k';
  
  board[0][3] = new Queen(black_or_white, "Queen");
  *board[0][3] = Queen(black_or_white, "Queen");
  board_vis[0][3] = 'q';

  board[7][4] = new King(!black_or_white, "King");
  *board[7][4] = King(!black_or_white, "King");
  strcpy(black_king_loc, "E8");
  board_vis[7][4] = 'K';

  board[7][3] = new Queen(!black_or_white, "Queen");
  *board[7][3] = Queen(!black_or_white, "Queen");
  board_vis[7][3] = 'Q';    
  
}

////////////Helper functions

const char* ChessBoard::colour(bool white_turn) {

  if (white_turn == true)
    return "White";

  else
    return "Black";
}

void ChessBoard::display_board() {
  if (turn_count != 0)
    std::cout << "Turn count: " << turn_count << std::endl;
  
  std::cout << "    ";
  for (int r=0; r<8; r++)
    std::cout << (char) ('A'+r) << "   ";
  std::cout << '\n';
  for (int r=7; r>-1; r--) {
    print_frame();
    print_row(board_vis[r],r);
  }
  print_frame();
}

void ChessBoard::print_frame() {
  std::cout << "  +---+---+---+---+---+---+---+---+" << '\n';    
}

void ChessBoard::print_row(const char* data, int row) {
  std::cout << (char) ('1' + row) << " ";
  for (int i=0; i<8; i++) {
    std::cout << '|' << " ";
    std::cout << ((data[i] == '.') ? ' ' : data[i]) << " ";
  }
  std::cout << "|" << '\n';
}

void ChessBoard::tempMove(const char* start, const char* end, Piece* board[8][8]) {

  if (strncmp(start, white_king_loc, 2) == 0)
    strcpy(white_king_loc, end);
  
  if (strncmp(start, black_king_loc, 2) == 0)
    strcpy(black_king_loc, end);
  
  board[end[1] - '1'][end[0] - 'A'] = board[start[1] - '1'][start[0] - 'A'];
  board[start[1] - '1'][start[0] - 'A'] = nullptr;

}

bool ChessBoard::temp_validMove(const char* start, const char* end, Piece* board[8][8]) {

  Piece* start_piece = board[start[1] - '1'][start[0] - 'A'];

  if (!(start_piece->checkPath(start, end, board)))
    return false;
      
  if (!(start_piece->checkObsticles(start, end, board)))
    return false;
  
  if (end_own_piece(end, white_turn, board))
    return false;

  return true;
}

void ChessBoard::undo_tempMove(const char* start, const char* end, Piece* start_piece, Piece* end_piece, Piece* board[8][8]) {

  if (strncmp(end, white_king_loc, 2) == 0)
    strcpy(white_king_loc, start);
  
  if (strncmp(end, black_king_loc, 2) == 0)
    strcpy(black_king_loc, start);
  
  board[start[1] - '1'][start[0] - 'A'] = start_piece;
  board[end[1] - '1'][end[0] - 'A'] = end_piece;  
}

////////////Functions for play

void ChessBoard::submitMove(const char* start, const char* end) {

  std::cout << std::endl;
  
  //Check whether game is over
  if(game_over) {
    std::cout << "Invalid move: " << start << " to " << end << std::endl;        
    std::cout << "Game is over. Must reset board to start new game." << std::endl;
    return;
  }
  
  //Check if move is valid
  if (!validMove(start, end, white_turn, board, 1))
    return;

  //Move piece
  makeMove(start, end, white_turn, board);
  
  //Check if check/checkmate
  check_game(white_turn, board);

  //Display board
  turn_count++;
  display_board();
  
  //Move to other player's turn
  white_turn = !white_turn;
  
}

bool ChessBoard::validMove(const char* start, const char* end, bool white_turn, Piece* board[8][8], bool comments) {

  Piece* start_piece = board[start[1] - '1'][start[0] - 'A'];

  if (!check_input(start, end, comments))
    return false;
  
  if (!start_is_piece(start, board)) {
    if (comments) {
      std::cout << "Invalid move: " << start << " to " << end << std::endl;        
      std::cout << "There is no piece at position " << start << "!" << std::endl;
    }
    return false;
  }
  
  if (!check_colour(start, white_turn, board))  {
    if (comments) {
      std::cout << "Invalid move: " << start << " to " << end << std::endl;
      std::cout << "It is not " << colour(!white_turn) << "'s turn to move!" << std::endl;
    }
    return false;
  }
    
  if (!(start_piece->checkPath(start, end, board))) {
    if (comments) {
      std::cout << "Invalid move: " << start << " to " << end << std::endl;            
      std::cout << colour(white_turn) << "'s " << start_piece->getName();
      std::cout << " cannot move to " << end << "!" << std::endl;
    }
    return false;
  }
    
  if (!(start_piece->checkObsticles(start, end, board))) {
    if (comments) {
      std::cout << "Invalid move: " << start << " to " << end << std::endl;            
      std::cout << colour(white_turn) << "'s " << start_piece->getName();
      std::cout << " cannot move to " << end << "!" << std::endl;
    }
    return false;
  }
  
  if (end_own_piece(end, white_turn, board)) {
    if (comments) {
      std::cout << "Invalid move: " << start << " to " << end << std::endl;    
      std::cout << "End position is own piece" << std::endl;
    }
    return false;
  }

  if (move_puts_king_in_check(start, end, white_turn, board)) {
    if (comments) {
      std::cout << "Invalid move: " << start << " to " << end << std::endl;    
      std::cout << "Move places " << colour(white_turn) << "'s king in check!" << std::endl;
    }
    return false;
  }

  return true;
}

bool ChessBoard::check_input(const char* start, const char* end, bool comments) {

  bool incorrect_start_length = false;
  bool incorrect_end_length = false;
  bool start_out_of_bounds = false;
  bool end_out_of_bounds = false;

  if (strlen(start) != 2)
    incorrect_start_length = true;

  if (strlen(end) != 2)
    incorrect_end_length = true;

  if ((start[0] < 'A') || (start[0] > 'H'))
    start_out_of_bounds = true;

  if ((start[1] < '1') || (start[1] > '8'))
    start_out_of_bounds = true;

  if ((end[0] < 'A') || (end[0] > 'H'))
    end_out_of_bounds = true;

  if ((end[1] < '1') || (end[1] > '8'))
    end_out_of_bounds = true;

  if (incorrect_start_length) {
    if (comments) {
      std::cout << "Invalid move: " << start << " to " << end << std::endl;        
      std::cout << start << " is not two characters!" << std::endl;
      std::cout << "Example cell reference: \"A1\"." << std::endl;
    }
    return false;
  }

  if (incorrect_end_length) {
    if (comments) {
      std::cout << "Invalid move: " << start << " to " << end << std::endl;        
      std::cout << end << " is not two characters!" << std::endl;
      std::cout << "Example cell reference: \"A1\"." << std::endl;
    }
    return false;
  }

  if (start_out_of_bounds) {
    if (comments) {
      std::cout << "Invalid move: " << start << " to " << end << std::endl;        
      std::cout << start << " is out of bounds!" << std::endl;
      std::cout << "Example cell reference: \"A1\"." << std::endl;
    }
    return false;
  }

  if (end_out_of_bounds) {
    if (comments) {
      std::cout << "Invalid move: " << start << " to " << end << std::endl;        
      std::cout << end << " is out of bounds!" << std::endl;
      std::cout << "Example cell reference: \"A1\"." << std::endl;
    }
    return false;
  }

  return true;
}

bool ChessBoard::start_is_piece(const char* start, Piece* board[8][8]) {

  bool start_is_piece = true;
  
  if (board[start[1] - '1'][start[0] - 'A'] == nullptr)
    start_is_piece = false;

  if (start_is_piece == false)
    return false;

  return true;
}

bool ChessBoard::end_own_piece(const char* end, bool white_turn, Piece* board[8][8]) {

  bool end_is_own_piece = false;

  if (board[end[1] - '1'][end[0] - 'A'] != nullptr)
    if (board[end[1] - '1'][end[0] - 'A']->getColour() == white_turn)
      end_is_own_piece = true;

  if (end_is_own_piece) 
    return true;

  return false;
}

bool ChessBoard::check_colour(const char* start, bool white_turn, Piece* board[8][8]) {
  
  if (board[start[1] - '1'][start[0] - 'A']->getColour() != white_turn) 
    return false;

  return true;
}

bool ChessBoard::move_puts_king_in_check(const char* start, const char* end, bool white_turn, Piece* board[8][8]) {

  Piece* start_piece = board[start[1] - '1'][start[0] - 'A'];
  Piece* end_piece = board[end[1] - '1'][end[0] - 'A'];

  bool check = false;

  tempMove(start, end, board);
  
  if (king_in_check(white_turn, board))
    check = true;
  
  undo_tempMove(start, end, start_piece, end_piece, board);

  if (check)
    return true;

  return false;
}
		
void ChessBoard::makeMove(const char* start, const char* end, bool white_turn, Piece* board[8][8]) {

  Piece* start_piece = board[start[1] - '1'][start[0] - 'A'];
  Piece* end_piece = board[end[1] - '1'][end[0] - 'A'];

  if (strncmp(start, white_king_loc, 2) == 0) 
    strcpy(white_king_loc, end);

  if (strncmp(start, black_king_loc, 2) == 0) 
    strcpy(black_king_loc, end);
    
  std::cout << colour(white_turn) << "'s " << start_piece->getName() << " moves from ";
  std::cout << start << " to " << end;
    
  if (board[end[1] - '1'][end[0] - 'A'] != nullptr) {
    std::cout << " taking " << colour(!white_turn) << "'s " << end_piece->getName();
    delete board[end[1] - '1'][end[0] - 'A'];
    board[end[1] - '1'][end[0] - 'A'] = nullptr;
  }

  std::cout << std::endl;

  board[end[1] - '1'][end[0] - 'A'] = board[start[1] - '1'][start[0] - 'A'];  
  board[start[1] - '1'][start[0] - 'A'] = nullptr;

  board_vis[end[1] - '1'][end[0] - 'A'] = board_vis[start[1] - '1'][start[0] - 'A'];
  board_vis[start[1] - '1'][start[0] - 'A'] = '.';
}

void ChessBoard::check_game(bool white_turn, Piece* board[8][8]) {

  if (!can_move(!white_turn, board)) {
    if (king_in_check(!white_turn, board)) {
      game_over = true;
      std::cout << colour(!white_turn) << " is in checkmate" << std::endl;
    }
    else {
      game_over = true;
      std::cout << "Stalemate" << std::endl;
    }
  }
  
  else {
    if (king_in_check(!white_turn, board)) 
      std::cout << colour(!white_turn) << " is in check" << std::endl;
  }
}

bool ChessBoard::can_move(bool white_turn, Piece* board[8][8]) {

  bool can_move = false;
  
  for (int start_rank = 0 ; start_rank < 8 ; start_rank++)
    for (int start_file = 0 ; start_file < 8 ; start_file++)
      for (int end_rank = 0 ; end_rank < 8 ; end_rank++) 
	for (int end_file = 0 ; end_file < 8 ; end_file++) {

	  std::string start;
	  std::string end;
	  
	  start += start_rank + 'A';     
	  start += start_file + '1';    
	  end += end_rank + 'A';
	  end += end_file + '1';

	  if (validMove(start.c_str(), end.c_str(), white_turn, board, 0)) 
	    can_move = true;

	  if (can_move)
	    return true;

	}

  return false;
}

bool ChessBoard::king_in_check(bool white_turn, Piece* board[8][8]) {
  bool check = false;
  char* correct_king_loc = new char[3];
  Piece* start_piece;
  char* start = new char[2];
  
  if (white_turn) 
    strcpy(correct_king_loc, white_king_loc);

  if (!white_turn) 
    strcpy(correct_king_loc, black_king_loc);

  white_turn = !white_turn;
  
  for (int rank = 0 ; rank < 8 ; rank++)
    for (int file = 0 ; file < 8 ; file++) {
      start[0] = file + 'A';
      start[1] = rank + '1';
      start_piece = board[start[1] - '1'][start[0] - 'A'];

      if ((start_piece != nullptr) && (start_piece->getColour() == white_turn))
	  if (temp_validMove(start, correct_king_loc, board)) 
	    check = true;
    }

  white_turn = !white_turn;
  delete [] start;
  delete [] correct_king_loc;

  if (check)
    return true;

  return false;
}







