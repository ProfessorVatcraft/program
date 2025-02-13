#ifndef GENERATE_BISHOP_MOVES_H_INCLUDED
#define GENERATE_BISHOP_MOVES_H_INCLUDED

#include <vector>

#include "board.h"
#include "move.h"

std::vector<Move> generate_bishop_moves(Board& b, int start_row, int start_col, int turn);

#endif // GENERATE_BISHOP_MOVES_H_INCLUDED
