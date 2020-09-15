#include "King.h"

#include <iostream>
#include <cmath>

King::King(bool white, const char* name) : Piece(white, name) {}

bool King::checkPath(const char* start, const char* end, Piece* const board[8][8]) {

  int abs_file_change = std::abs((end[0] - 'A') - (start[0] - 'A'));
  int abs_rank_change = std::abs((end[1] - '1') - (start[1] - '1'));

  if ((abs_rank_change == abs_file_change) && (abs_rank_change == 1))
    return true;

  if ((abs_rank_change == 1) && (abs_file_change == 0))
    return true;

  if ((abs_file_change == 1) && (abs_rank_change == 0))
    return true;  

  return false;
}

bool King::checkObsticles(const char* start, const char* end, Piece* const board[8][8]) {

  return true;
}

