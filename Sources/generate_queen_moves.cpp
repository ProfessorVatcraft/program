#include <vector>

#include "generate_queen_moves.h"

std::vector<Move> generate_queen_moves(Board& b, int start_row, int start_col, int turn){
    std::vector<Move> queen_diag_moves = generate_bishop_moves(b, start_row, start_col, turn);
    std::vector<Move> queen_hor_moves = generate_rook_moves(b, start_row, start_col, turn);
    std::vector<Move> queen_moves;
    queen_moves.insert(queen_moves.end(), queen_diag_moves.begin(), queen_diag_moves.end());
    queen_moves.insert(queen_moves.end(), queen_hor_moves.begin(), queen_hor_moves.end());
    return queen_moves;
}
