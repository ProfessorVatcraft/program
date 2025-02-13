#ifndef GENERATE_MOVES_H_INCLUDED
#define GENERATE_MOVES_H_INCLUDED

#include <vector>

#include "generate_pawn_moves.h"
#include "generate_knight_moves.h"
#include "generate_bishop_moves.h"
#include "generate_rook_moves.h"
#include "generate_queen_moves.h"
#include "generate_king_moves.h"

std::vector<Move> generate_moves(Board& b, int turn);

#endif // GENERATE_MOVES_H_INCLUDED
