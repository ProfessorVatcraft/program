#ifndef GENERATE_PAWN_MOVES_H_INCLUDED
#define GENERATE_PAWN_MOVES_H_INCLUDED

#include <vector>

#include "board.h"
#include "move.h"
#include "en_passant.h"

std::vector<Move> generate_pawn_moves(Board& b, int start_row, int start_col, int turn);

#endif // GENERATE_PAWN_MOVES_H_INCLUDED
