#ifndef GENERATE_KNIGHT_MOVES_H_INCLUDED
#define GENERATE_KNIGHT_MOVES_H_INCLUDED

#include <vector>

#include "board.h"
#include "move.h"

std::vector<Move> generate_knight_moves(Board& b, int start_row, int start_col, int turn);

#endif // GENERATE_KNIGHT_MOVES_H_INCLUDED
