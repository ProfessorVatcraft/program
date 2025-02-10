#ifndef GENERATE_MOVES_H_INCLUDED
#define GENERATE_MOVES_H_INCLUDED

#include "Board.h"
#include "Piece.h"
#include "En_passant_check.h"
#include "Move.h"
std::vector<Move> generate_moves(Board& b, int turn);

#endif // GENERATE_MOVES_H_INCLUDED
