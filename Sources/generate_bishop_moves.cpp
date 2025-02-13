#include <vector>

#include "generate_bishop_moves.h"

std::vector<Move> generate_bishop_moves(Board& b, int start_row, int start_col, int turn){
    std::vector<Move> bishop_moves;

    int bishop_right_diag_offsets[4] = {-1, -1, 1, 1};
    int bishop_left_diag_offsets[4] = {-1, 1, -1, 1};

    for(int i = 0; i < 4; i++){
        int end_row = start_row + bishop_left_diag_offsets[i];
        int end_col = start_col + bishop_right_diag_offsets[i];
        while((end_row >= 0 && end_row < 8) && (end_col >= 0 && end_col < 8)){
            if(b.board[end_row][end_col].color == turn){
                break;
            }
            bishop_moves.push_back({start_row, start_col, end_row, end_col});
            if(b.board[end_row][end_col].color == -turn){
                break;
            }
            end_row += bishop_left_diag_offsets[i];
            end_col += bishop_right_diag_offsets[i];
        }
    }
    return bishop_moves;
}
