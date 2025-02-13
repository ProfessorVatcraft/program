#include <vector>
#include <iostream>

#include "make_move.h"

void make_move(Board& b, int start_row, int start_col, int end_row, int end_col, int turn){
    if(b.board[start_row][start_col].piece != Empty && b.board[start_row][start_col].color != 0){
        std::vector<Move> moves = generate_moves(b, turn);
        for(int i = 0; i < moves.size() ; i++){

            if(start_row == moves[i].start_row && start_col == moves[i].start_col && end_row == moves[i].end_row && end_col == moves[i].end_col){
                b.board[end_row][end_col] = b.board[start_row][start_col];
                b.board[start_row][start_col] = {Empty, 0};

                bool is_en_passant = false;

                if(b.board[end_row][end_col].piece == Pawn){
                    if(end_row == 0 || end_row == 7){
                        int promoted_piece;
                        std::cout << "Promote to Queen(9), Knight(3), Rook(5), Bishop(4): ";
                        std::cin >> promoted_piece;
                        if(promoted_piece == Knight || promoted_piece == Rook || promoted_piece == Bishop){
                            b.board[end_row][end_col].piece = promoted_piece;
                        }
                        else{
                            b.board[end_row][end_col].piece = Queen;
                        }
                    }
                    else if((start_row == 1 && end_row == 3) || (start_row == 6 && end_row == 4)){
                        int en_passant_direction = (b.board[end_row][end_col].color == White) ? 1 : -1;
                        en_passant[0] = end_row + en_passant_direction;
                        en_passant[1] = start_col;
                        is_en_passant = true;
                    }
                    else if(end_row == en_passant[0] && end_col == en_passant[1]){
                        int en_passant_row = end_row + ((b.board[end_row][end_col].color == White) ? 1 : -1);
                        b.board[en_passant_row][end_col] = {Empty, 0};
                    }
                }

                if(b.board[end_row][end_col].piece == Rook && b.board[end_row][end_col].color == White){
                    if(start_row == 7 && start_col == 7){
                        castling_kingside_white = false;
                    }
                    else if(start_row == 7 && start_col == 0){
                        castling_queenside_white = false;
                    }
                }
                else if(b.board[end_row][end_col].piece == Rook && b.board[end_row][end_col].color == Black){
                    if(start_row == 0 && start_col == 7){
                        castling_kingside_black = false;
                    }
                    else if(start_row == 0 && start_col == 0){
                        castling_queenside_black = false;
                    }
                }
                else if(b.board[end_row][end_col].piece == King && b.board[end_row][end_col].color == White){
                    if(start_row == 7 && start_col == 4){
                        if(end_row == 7 && end_col == 6){
                            b.board[7][5] = b.board[7][7];
                            b.board[7][7] = {Empty, 0};
                        }
                        else if(end_row == 7 && end_col == 2){
                            b.board[7][3] = b.board[7][0];
                            b.board[7][0] = {Empty, 0};
                        }
                    }
                    castling_kingside_white = false;
                    castling_queenside_white = false;
                }
                else if(b.board[end_row][end_col].piece == King && b.board[end_row][end_col].color == Black){
                    if(start_row == 0 && start_col == 4){
                        if(end_row == 0 && end_col == 6){
                            b.board[0][5] = b.board[0][7];
                            b.board[0][7] = {Empty, 0};
                        }
                        else if(end_row == 0 && end_col == 2){
                            b.board[0][3] = b.board[0][0];
                            b.board[0][0] = {Empty, 0};
                        }
                    }
                    castling_kingside_black = false;
                    castling_queenside_black = false;
                }

                if(is_en_passant == false){
                    en_passant[0] = -1;
                    en_passant[1] = -1;
                }

                break;
            }
        }
    }
}
