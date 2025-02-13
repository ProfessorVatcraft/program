#include <vector>

#include "generate_king_moves.h"

std::vector<Move> generate_king_moves(Board& b, int start_row, int start_col, int turn){
    std::vector<Move> king_moves;

    int king_first_offsets[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int king_second_offsets[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for(int i = 0 ; i < 8 ; i++){
        int end_row = start_row + king_first_offsets[i];
        int end_col = start_col + king_second_offsets[i];

        if((end_row >= 0 && end_row < 8) && (end_col >= 0 && end_col < 8)){
            if(b.board[end_row][end_col].color != turn){
                king_moves.push_back({start_row, start_col, end_row, end_col});
            }
        }
    }

    if(turn == White){
        if(castling_kingside_white == true && b.board[7][5].piece == Empty && b.board[7][6].piece == Empty){
            king_moves.push_back({7, 4, 7, 6});
        }
        if(castling_queenside_white == true && b.board[7][3].piece == Empty && b.board[7][2].piece == Empty && b.board[7][1].piece == Empty){
            king_moves.push_back({7, 4, 7, 2});
        }
    }
    else if(turn == Black){
        if(castling_kingside_black == true && b.board[0][5].piece == Empty && b.board[0][6].piece == Empty){
            king_moves.push_back({0, 4, 0, 6});
        }
        if(castling_queenside_black == true && b.board[0][3].piece == Empty && b.board[0][2].piece == Empty && b.board[0][1].piece == Empty){
            king_moves.push_back({0, 4, 0, 2});
        }
    }
    return king_moves;
}
