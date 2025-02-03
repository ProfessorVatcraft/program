#include <iostream>
#include <vector>

/* Piece values, necessary constants and board representation using mail box */
const int P = 1;
const int N = 3;
const int B = 4;
const int R = 5;
const int Q = 9;
const int K = 100;
const int E = 0;

const int b = -1;
const int w = 1;

int en_passant_square = -1; // -1 = no en passant square

int piece[64]{
    R, N, B, Q, K, B, N, R,
    P, P, P, P, P, P, P, P,
    E, E, E, E, E, E, E, E,
    E, E, E, E, E, E, E, E,
    E, E, E, E, E, E, E, E,
    E, E, E, E, E, E, E, E,
    P, P, P, P, P, P, P, P,
    R, N, B, Q, K, B, N, R
};

int color[64]{
    b, b, b, b, b, b, b, b,
    b, b, b, b, b, b, b, b,
    E, E, E, E, E, E, E, E,
    E, E, E, E, E, E, E, E,
    E, E, E, E, E, E, E, E,
    E, E, E, E, E, E, E, E,
    w, w, w, w, w, w, w, w,
    w, w, w, w, w, w, w, w
};

/* Move generation */

// Move structure
struct Move{
    int start_square;
    int end_square;
    int promotion;
    bool en_passant;
};

// pseudo-legal move generation
std::vector<Move> pseudo_legal_move_generation (int turn) {
    std::vector<Move> pseudo_legal_move_list;
    for (int i = 0; i < 64; i++) {
        if (color[i] == turn) {
            std::vector<Move> moves;
            if (piece[i] == P) {
                moves = pawn_move_generation(i, turn);
            }
            else if (piece[i] == N) {
                moves = knight_move_generation(i, turn);
            }
            else if (piece[i] == B) {
                moves = bishop_move_generation(i, turn);
            }
            else if (piece[i] == R) {
                moves = rook_move_generation(i, turn);
            }
            else if (piece[i] == Q) {
                moves = queen_move_generation(i, turn);
            }
            else if (piece[i] == K) {
                moves = king_move_generation(i, turn);
            }
            pseudo_legal_move_list.insert(pseudo_legal_move_list.end(), moves.begin(), moves.end());
        }
    }
    return pseudo_legal_move_list;
}

// Helper functions for pseudo_legal_move_generation function (piece movement functions)

// Pawn moves
std::vector<Move> pawn_move_generation(int square, int turn) {
    std::vector<Move> pawn_moves;

    int direction = (turn == w) ? -8 : 8;
    int start_rank = (turn == w) ? 6 : 1;
    int promotion_rank = (turn == w) ? 0 : 7;

    int row = square / 8;
    int col = square % 8;

    // One-square forward move.
    int move_one_square = square + direction;
    if (move_one_square >= 0 && move_one_square < 64 && piece[move_one_square] == E) {
        if (move_one_square / 8 == promotion_rank) {
            pawn_moves.push_back({square, move_one_square, Q, false});
            pawn_moves.push_back({square, move_one_square, R, false});
            pawn_moves.push_back({square, move_one_square, B, false});
            pawn_moves.push_back({square, move_one_square, N, false});
        } else {
            pawn_moves.push_back({square, move_one_square, E, false});

            // Two-square forward move if on the starting rank and path is clear.
            if (row == start_rank) {
                int move_two_square = square + 2 * direction;
                if (move_two_square >= 0 && move_two_square < 64 && piece[move_two_square] == E) {
                    pawn_moves.push_back({square, move_two_square, E, false});
                }
            }
        }
    }

    // Diagonal capture left.
    int move_diag_left = square + direction - 1;
    if (col > 0 && move_diag_left >= 0 && move_diag_left < 64) {
        // Regular capture.
        if (color[move_diag_left] == -turn) {
            if (move_diag_left / 8 == promotion_rank) {
                pawn_moves.push_back({square, move_diag_left, Q, false});
                pawn_moves.push_back({square, move_diag_left, R, false});
                pawn_moves.push_back({square, move_diag_left, B, false});
                pawn_moves.push_back({square, move_diag_left, N, false});
            } else {
                pawn_moves.push_back({square, move_diag_left, E, false});
            }
        }
    }

    // Diagonal capture right.
    int move_diag_right = square + direction + 1;
    if (col < 7 && move_diag_right >= 0 && move_diag_right < 64) {
        if (color[move_diag_right] == -turn) {
            if (move_diag_right / 8 == promotion_rank) {
                pawn_moves.push_back({square, move_diag_right, Q, false});
                pawn_moves.push_back({square, move_diag_right, R, false});
                pawn_moves.push_back({square, move_diag_right, B, false});
                pawn_moves.push_back({square, move_diag_right, N, false});
            } else {
                pawn_moves.push_back({square, move_diag_right, E, false});
            }
        }
    }

    // En Passant:
    // En passant capture is only possible when:
    // - There is a valid en passant square (enpassantSquare != -1).
    // - The pawn is on the correct row (row 3 for white, row 4 for black).
    int enpassant_row = (turn == w) ? 3 : 4;
    if (row == enpassant_row && enpassantSquare != -1) {
        // If the en passant square is diagonally adjacent to the pawn.
        if (enpassantSquare == square + direction - 1 || enpassantSquare == square + direction + 1) {
            pawn_moves.push_back({square, enpassantSquare, E, true});
        }
    }

    return pawn_moves;
}

// Knight moves
std::vector<Move> knight_move_generation(int square, int turn){

}

// Bishop moves
std::vector<Move> bishop_move_generation(int square, int turn){

}

// Rook moves
std::vector<Move> rook_move_generation(int square, int turn){

}

// Queen moves
std::vector<Move> queen_move_generation(int square, int turn){

}

// King moves
std::vector<Move> king_move_generation(int square, int turn){

}

int main(){

}
