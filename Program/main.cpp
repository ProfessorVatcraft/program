#include <iostream>
#include <vector>

#include "Piece_values.h"
#include "Castling_checks.h"
#include "Board.h"
#include "Piece.h"
#include "En_passant_check.h"
#include "Move.h"
#include "Print_board.h"
#include "Generate_pawn_moves.h"

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

std::vector<Move> generate_queen_moves(Board& b, int start_row, int start_col, int turn){
    std::vector<Move> queen_diag_moves = generate_bishop_moves(b, start_row, start_col, turn);
    std::vector<Move> queen_hor_moves = generate_rook_moves(b, start_row, start_col, turn);
    std::vector<Move> queen_moves;
    queen_moves.insert(queen_moves.end(), queen_diag_moves.begin(), queen_diag_moves.end());
    queen_moves.insert(queen_moves.end(), queen_hor_moves.begin(), queen_hor_moves.end());
    return queen_moves;
}

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

int main(){
    Board b;
    int start_row, start_col, end_row, end_col;
    print_board(b);
    int turn = White;

    while(turn == White || turn == Black){
        std::cout << "square coordinate" << std::endl;
        std::cout << "start row: ";
        std::cin >> start_row;
        std::cout << "start col: ";
        std::cin >> start_col;
        std::cout << "end row: ";
        std::cin >> end_row;
        std::cout << "end col: ";
        std::cin >> end_col;
        make_move(b, start_row, start_col, end_row, end_col, turn);
        print_board(b);
        std::cout << "Turn: ";
        std::cin >> turn;
    }
}
