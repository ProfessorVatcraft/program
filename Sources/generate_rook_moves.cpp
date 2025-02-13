#include <vector>

#include "generate_rook_moves.h"

std::vector<Move> generate_rook_moves(Board& b, int start_row, int start_col, int turn){
    std::vector<Move> rook_moves;

    int rook_row_offsets[4] = {0, -1, 1, 0};
    int rook_col_offsets[4] = {-1,0, 0, 1};

    for(int i = 0; i < 4; i++){
        int end_row = start_row + rook_row_offsets[i];
        int end_col = start_col + rook_col_offsets[i];
        while((end_row >= 0 && end_row < 8) && (end_col >= 0 && end_col < 8)){
            if(b.board[end_row][end_col].color == turn){
                break;
            }
            rook_moves.push_back({start_row, start_col, end_row, end_col});
            if(b.board[end_row][end_col].color == -turn){
                break;
            }
            end_row += rook_row_offsets[i];
            end_col += rook_col_offsets[i];
        }
    }
    return rook_moves;
}
