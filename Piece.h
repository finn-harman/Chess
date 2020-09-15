#ifndef PIECE_H
#define PIECE_H

class Piece {

  bool white;
  const char* name;
  
 public:

  virtual bool checkPath(const char* start, const char* end, Piece* const board[8][8]) = 0;
  virtual bool checkObsticles(const char* start, const char* end, Piece* const board[8][8]) = 0;

  Piece(bool black_or_white, const char* _name);
  virtual ~Piece() {};
  const char* getName();
  bool getColour();
};

#endif
