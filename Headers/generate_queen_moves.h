#ifndef GENERATE_QUEEN_MOVES_H_INCLUDED
#define GENERATE_QUEEN_MOVES_H_INCLUDED

#include <vector>

#include "board.h"
#include "move.h"
#include "generate_bishop_moves.h"
#include "generate_rook_moves.h"

std::vector<Move> generate_queen_moves(Board& b, int start_row, int start_col, int turn);

#endif // GENERATE_QUEEN_MOVES_H_INCLUDED
