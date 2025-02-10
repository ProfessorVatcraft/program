#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "Piece.h"

struct Board{
    Piece board[8][8];
    Board(){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                board[i][j] = {Empty, 0};
            }
        }
        board[0][0] = {Rook, Black};
        board[0][1] = {Knight, Black};
        board[0][2] = {Bishop, Black};
        board[0][3] = {Queen, Black};
        board[0][4] = {King, Black};
        board[0][5] = {Bishop, Black};
        board[0][6] = {Knight, Black};
        board[0][7] = {Rook, Black};
        board[1][0] = {Pawn, Black};
        board[1][1] = {Pawn, Black};
        board[1][2] = {Pawn, Black};
        board[1][3] = {Pawn, Black};
        board[1][4] = {Pawn, Black};
        board[1][5] = {Pawn, Black};
        board[1][6] = {Pawn, Black};
        board[1][7] = {Pawn, Black};

        board[6][0] = {Pawn, White};
        board[6][1] = {Pawn, White};
        board[6][2] = {Pawn, White};
        board[6][3] = {Pawn, White};
        board[6][4] = {Pawn, White};
        board[6][5] = {Pawn, White};
        board[6][6] = {Pawn, White};
        board[6][7] = {Pawn, White};
        board[7][0] = {Rook, White};
        board[7][1] = {Knight, White};
        board[7][2] = {Bishop, White};
        board[7][3] = {Queen, White};
        board[7][4] = {King, White};
        board[7][5] = {Bishop, White};
        board[7][6] = {Knight, White};
        board[7][7] = {Rook, White};

    }
};

#endif //BOARD_H_INCLUDED
