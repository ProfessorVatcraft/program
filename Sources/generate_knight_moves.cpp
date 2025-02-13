#include <vector>

#include "generate_knight_moves.h"

std::vector<Move> generate_knight_moves(Board& b, int start_row, int start_col, int turn){
    std::vector<Move> knight_moves;

    int knight_row_offsets[8] = {-2, -2, -1, 1, 2, 2, -1, 1};
    int knight_col_offsets[8] = {-1, 1, 2, 2, -1, 1, -2, -2};

    for(int i = 0; i < 8; i++){
        int end_row = start_row + knight_row_offsets[i];
        int end_col = start_col + knight_col_offsets[i];
        if((end_row >= 0 && end_row < 8) && (end_col >= 0 && end_col < 8)){
            if(b.board[end_row][end_col].color != turn){
                knight_moves.push_back({start_row, start_col, end_row, end_col});
            }
        }
    }
    return knight_moves;
}
