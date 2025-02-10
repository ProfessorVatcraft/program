#include <iostream>
#include <vector>

#include "Print_board.h"
#include "Board.h"
#include "Piece.h"

void print_board(Board& b){
    std::cout << "  0  1  2  3  4  5  6  7" << std::endl;
    for(int i = 0; i < 8; i++){
        std::cout << i << ' ';
        for(int j = 0; j < 8; j++){
            if(b.board[i][j].piece == Empty){
                std::cout << ".  ";
            }
            else{
                char color = (b.board[i][j].color == White) ? 'w' : 'b';
                std::cout << color;
                if(b.board[i][j].piece == Pawn) std::cout << 'P';
                else if(b.board[i][j].piece == Knight) std::cout << 'N';
                else if(b.board[i][j].piece == Bishop) std::cout << 'B';
                else if(b.board[i][j].piece == Rook) std::cout << 'R';
                else if(b.board[i][j].piece == Queen) std::cout << 'Q';
                else if(b.board[i][j].piece == King) std::cout << 'K';
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
}
