#include "Bishop.h"

#include <iostream>
#include <cmath>

Bishop::Bishop(bool white, const char* name) : Piece(white, name) {}

bool Bishop::checkPath(const char* start, const char* end, Piece* const board[8][8]) {

  int abs_file_change = std::abs((end[0] - 'A') - (start[0] - 'A'));
  int abs_rank_change = std::abs((end[1] - '1') - (start[1] - '1'));

  if ((abs_rank_change == abs_file_change) && (abs_rank_change != 0))
    return true;

  return false;
}

bool Bishop::checkObsticles(const char* start, const char* end, Piece* const board[8][8]) {

  int file_change = (end[0] - 'A') - (start[0] - 'A');
  int rank_change = (end[1] - '1') - (start[1] - '1');

  bool obsticles_in_path = false;
  
  if (file_change > 0) 
    for (int i = 1 ; i < file_change ; i++) {
      if (rank_change > 0) 
	if (board[(start[1] - '1') + i][(start[0] - 'A') + i] != nullptr) {
	  obsticles_in_path = true;
	}
      if (rank_change < 0)
	if (board[(start[1] - '1') - i][(start[0] - 'A') + i] != nullptr) {
	  obsticles_in_path = true;
	}
    }

  if (file_change < 0) 
    for (int i = -1 ; i > file_change ; i--) {
      if (rank_change > 0) 
	if (board[(start[1] - '1') - i][(start[0] - 'A') + i] != nullptr) {
	  obsticles_in_path = true;
	}
      if (rank_change < 0)
	if (board[(start[1] - '1') + i][(start[0] - 'A') + i] != nullptr) {
	  obsticles_in_path = true;
	}
    }

  if (obsticles_in_path == true) 
    return false;
  
  return true;
}

