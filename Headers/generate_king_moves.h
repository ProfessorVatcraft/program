#ifndef GENERATE_KING_MOVES_H_INCLUDED
#define GENERATE_KING_MOVES_H_INCLUDED

#include <vector>

#include "board.h"
#include "move.h"
#include "castling_check.h"

std::vector<Move> generate_king_moves(Board& b, int start_row, int start_col, int turn);

#endif // GENERATE_KING_MOVES_H_INCLUDED
