#ifndef GENERATE_PAWN_MOVES_H_INCLUDED
#define GENERATE_PAWN_MOVES_H_INCLUDED

#include <vector>

#include "Board.h"
#include "Piece.h"
#include "En_passant_check.h"
#include "Move.h"

std::vector<Move> generate_pawn_moves(Board& b, int start_row, int start_col, int turn);

#endif // GENERATE_PAWN_MOVES_H_INCLUDED
