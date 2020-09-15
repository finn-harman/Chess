#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {

 public:
  //Check if path is valid for piece
  bool checkPath(const char* start, const char* end, Piece* const board[8][8]);
  
  //Check if obsticles in path make move invalid
  bool checkObsticles(const char* start, const char* end, Piece* const board[8][8]);

  Knight(bool white, const char* name);
  virtual ~Knight() {};

};

#endif
