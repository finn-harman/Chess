#include "Pawn.h"

#include <iostream>
#include <cmath>

Pawn::Pawn(bool white, const char* name) : Piece(white, name) {}

bool Pawn::checkPath(const char* start, const char* end, Piece* const board[8][8]) {

  int file_change = (end[0] - 'A') - (start[0] - 'A');
  int rank_change = (end[1] - '1') - (start[1] - '1');

  if (getColour()) {
    if ((rank_change == 1) && (file_change == 0))
      return true;
    
    if (start[1]== '2') 
      if ((rank_change == 2) && (file_change == 0))
	return true;
    
    if (board[end[1] - '1'][end[0] - 'A'] != nullptr) {
      if ((rank_change == 1) && (file_change == 1))
	return true;
      if ((rank_change == 1) && (file_change == -1))
	return true;
    }
  }

  if (!getColour()) {
    if ((rank_change == -1) && (file_change == 0))
      return true;
    
    if (start[1]== '7') 
      if ((rank_change == -2) && (file_change == 0))
	return true;
    
    if (board[end[1] - '1'][end[0] - 'A'] != nullptr) {
      if ((rank_change == -1) && (file_change == 1))
	return true;
      if ((rank_change == -1) && (file_change == -1))
	return true;
    }
  }

  return false;
}

bool Pawn::checkObsticles(const char* start, const char* end, Piece* const board[8][8]) {

  int file_change = (end[0] - 'A') - (start[0] - 'A');
  int rank_change = (end[1] - '1') - (start[1] - '1');

  bool obsticles_in_path = false;

  if (getColour()) {
    if ((rank_change == 1) && (file_change == 0))
      if (board[(start[1] - '1') + 1][start[0] - 'A'] != nullptr)
	obsticles_in_path = true;
    
    if ((rank_change == 2) && (file_change == 0)) {
      if (board[(start[1] - '1') + 1][start[0] - 'A'] != nullptr)
	obsticles_in_path = true;
      if (board[(start[1] - '1') + 2][start[0] - 'A'] != nullptr)
	obsticles_in_path = true;
    }
  }

  if (!getColour()) {
    if ((rank_change == -1) && (file_change == 0))
      if (board[(start[1] - '1') - 1][start[0] - 'A'] != nullptr)
	obsticles_in_path = true;
    
    if ((rank_change == -2) && (file_change == 0)) {
      if (board[(start[1] - '1') - 1][start[0] - 'A'] != nullptr)
	obsticles_in_path = true;
      if (board[(start[1] - '1') - 2][start[0] - 'A'] != nullptr)
	obsticles_in_path = true;
    }
  }
  
  if (obsticles_in_path == true) 
    return false;
  
  return true;
}


