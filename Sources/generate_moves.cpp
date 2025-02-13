#include <vector>

#include "generate_moves.h"

std::vector<Move> generate_moves(Board& b, int turn){
    std::vector<Move> possible_moves;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(b.board[i][j].color == turn){
                if(b.board[i][j].piece == Pawn){
                    std::vector<Move> pawn_moves = generate_pawn_moves(b, i, j, turn);
                    possible_moves.insert(possible_moves.end(), pawn_moves.begin(), pawn_moves.end());
                }
                else if(b.board[i][j].piece == Knight){
                    std::vector<Move> knight_moves = generate_knight_moves(b, i, j, turn);
                    possible_moves.insert(possible_moves.end(), knight_moves.begin(), knight_moves.end());
                }
                else if(b.board[i][j].piece == Bishop){
                    std::vector<Move> bishop_moves = generate_bishop_moves(b, i, j, turn);
                    possible_moves.insert(possible_moves.end(), bishop_moves.begin(), bishop_moves.end());

                }
                else if(b.board[i][j].piece == Rook){
                    std::vector<Move> rook_moves = generate_rook_moves(b, i, j, turn);
                    possible_moves.insert(possible_moves.end(), rook_moves.begin(), rook_moves.end());

                }
                else if(b.board[i][j].piece == Queen){
                    std::vector<Move> queen_moves = generate_queen_moves(b, i, j, turn);
                    possible_moves.insert(possible_moves.end(), queen_moves.begin(), queen_moves.end());
                }
                else if(b.board[i][j].piece == King){
                    std::vector<Move> king_moves = generate_king_moves(b, i, j, turn);
                    possible_moves.insert(possible_moves.end(), king_moves.begin(), king_moves.end());
                }
            }
        }
    }
    return possible_moves;
}
