#include "Piece.h"

Piece::Piece(bool black_or_white, const char* _name) : white(black_or_white), name(_name) {}

const char* Piece::getName() {
  return name;
}

bool Piece::getColour() {
  return white;
}

