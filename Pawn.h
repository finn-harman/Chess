#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {

 public:
  //Check if path is valid for piece
  bool checkPath(const char* start, const char* end, Piece* const board[8][8]);
  
  //Check if obsticles in path make move invalid
  bool checkObsticles(const char* start, const char* end, Piece* const board[8][8]);

  Pawn(bool white, const char* name);
  virtual ~Pawn() {};

};

#endif
