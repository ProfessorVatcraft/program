#include <iostream>
#include <vector>

#include "Generate_pawn_moves.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"

std::vector<Move> generate_pawn_moves(Board& b, int start_row, int start_col, int turn){
    std::vector<Move> pawn_moves;

    int direction = (turn == White) ? -1 : 1;
    int end_row = start_row + direction;
    int capture_left = start_col - 1;
    int capture_right = start_col + 1;

    if((end_row >= 0 && end_row < 8) && b.board[end_row][start_col].piece == Empty){
        pawn_moves.push_back({start_row, start_col, end_row, start_col});
        if((start_row == 1 && turn == Black) || (start_row == 6 && turn == White)){
            int two_square = end_row + direction;
            if(b.board[two_square][start_col].piece == Empty){
                pawn_moves.push_back({start_row, start_col, two_square, start_col});
            }
        }
    }

    if(end_row >=0 && end_row < 8){
        if(capture_left >= 0 && b.board[end_row][capture_left].color == -turn){
            pawn_moves.push_back({start_row, start_col, end_row, capture_left});
        }
        if(capture_right < 8 && b.board[end_row][capture_right].color == -turn){
            pawn_moves.push_back({start_row, start_col, end_row, capture_right});
        }
    }

    if (en_passant[0] != -1){
        int en_passant_row = en_passant[0];
        int en_passant_col = en_passant[1];
        int required_row = en_passant_row - direction;
        if(start_row == required_row && (start_col == en_passant_col - 1 || start_col == en_passant_col + 1)){
            pawn_moves.push_back({start_row, start_col, en_passant_row, en_passant_col});
        }
    }
    return pawn_moves;
}
