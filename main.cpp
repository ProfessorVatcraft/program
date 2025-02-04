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

// Castling check
bool can_castle_kingside_w = true, can_castle_queenside_w = true;
bool can_castle_kingside_b = true, can_castle_queenside_b = true;

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
    bool en_passan;
    bool castling;
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
            pawn_moves.push_back({square, move_one_square, Q, false, false});
            pawn_moves.push_back({square, move_one_square, R, false, false});
            pawn_moves.push_back({square, move_one_square, B, false, false});
            pawn_moves.push_back({square, move_one_square, N, false, false});
        } else {
            pawn_moves.push_back({square, move_one_square, E, false, false});

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
                pawn_moves.push_back({square, move_diag_left, Q, false, false});
                pawn_moves.push_back({square, move_diag_left, R, false, false});
                pawn_moves.push_back({square, move_diag_left, B, false, false});
                pawn_moves.push_back({square, move_diag_left, N, false, false});
            } else {
                pawn_moves.push_back({square, move_diag_left, E, false, false});
            }
        }
    }

    // Diagonal capture right.
    int move_diag_right = square + direction + 1;
    if (col < 7 && move_diag_right >= 0 && move_diag_right < 64) {
        if (color[move_diag_right] == -turn) {
            if (move_diag_right / 8 == promotion_rank) {
                pawn_moves.push_back({square, move_diag_right, Q, false, false});
                pawn_moves.push_back({square, move_diag_right, R, false, false});
                pawn_moves.push_back({square, move_diag_right, B, false, false});
                pawn_moves.push_back({square, move_diag_right, N, false, false});
            } else {
                pawn_moves.push_back({square, move_diag_right, E, false, false});
            }
        }
    }
    if (square / 8 == enpassant_row && en_passant_check(square, turn)) {
        pawn_moves.push_back({square, en_passant_square, E, true, false});
    }
    return pawn_moves;
}

// Check en_passant
bool en_passant_check(int square, int turn){
    int left = square - 1;
    int right = square + 1;
    if (en_passant_square != -1 &&
        ((left >= 0 && color[left] == -turn && piece[left] == P) ||
         (right < 64 && color[right] == -turn && piece[right] == P))) {
        return true;
    }
    return false;
}

// Knight moves
std::vector<Move> knight_move_generation(int square, int turn) {
    std::vector<Move> knight_moves;

    // Knight offsets
    const int knight_offsets[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };

    int row = square / 8;
    int col = square % 8;

    for (int i = 0; i < 8; i++) {
        int new_square = square + knight_offsets[i];

        // Ensure the move is within board bounds
        if (new_square >= 0 && new_square < 64) {
            int new_row = new_square / 8;
            int new_col = new_square % 8;

            // Ensure the move does not wrap around the board
            if (abs(new_row - row) == 2 && abs(new_col - col) == 1 ||
                abs(new_row - row) == 1 && abs(new_col - col) == 2) {

                // Check if the destination square is empty or has an enemy piece
                if (color[new_square] != turn) {
                    knight_moves.push_back({square, new_square, E, false, false});
                }
            }
        }
    }

    return knight_moves;
}


// Bishop moves
std::vector<Move> bishop_move_generation(int square, int turn){
    std::vector<Move> bishop_moves;

    // Bishop offsets
    const int bishop_offsets[4] = { -9, -7, 7, 9 };

    int row = square / 8;
    int col = square % 8;
    for(int i = 0; i < 4; i++){
        int new_square = square;
        while(true){
            new_square += bishop_offsets[i];
            if(new_square < 0 || new_square >= 64) break;

            // Ensure the move is within board bounds
            int new_row = new_square / 8;
            int new_col = new_square % 8;

            // Add move if square is empty
            if(piece[new_square] == E){
                bishop_moves.push_back({square, new_square, E, false, false});
            }
            // Capture opponent's piece
            else if(color[new_square] == -turn){
                bishop_moves.push_back({square, new_square, E, false, false});
                break;
            }
            // Friendly piece
            else{
                break;
            }
        }
    }
    return bishop_moves;
}

// Rook moves
std::vector<Move> rook_move_generation(int square, int turn){
    std::vector<Move> rook_moves;

    // Rook offsets
    const int rook_offsets[4] = { -8, 8, -1, 1 };

    int row = square / 8;
    int col = square % 8;

    for(int i = 0; i < 4; i++){
        int new_square = square;
        while(true){
            new_square += rook_offsets[i];
            if(new_square < 0 || new_square >= 64) break;
            int new_row = new_square / 8;
            int new_col = new_square % 8;

            // Check warpping
            if((i == 2 || i == 3) && (new_row != row)) break;

            // Add move if square is empty
            if(piece[new_square] == E){
                rook_moves.push_back({square, new_square, E, false, false});
            }

            // Capture opponent's piece
            else if(color[new_square] == -turn){
                rook_moves.push_back({square, new_square, E, false, false});
                break;
            }
            // Friendly piece
            else{
                break;
            }
        }
    }
    return rook_moves;
}

// Queen moves
std::vector<Move> queen_move_generation(int square, int turn){
    bishop_move_generation(square, turn);
    rook_move_generation(square, turn);
}

// King moves
std::vector<Move> king_move_generation(int square, int turn){
    std::vector<Move> king_moves;

    // King offsets
    const int king_offsets[8] = { -8, 8, -1, 1, -9, -7, 7, 9 };

    int row = square / 8;
    int col = square % 8;

    for(int i = 0; i < 8; i++){
        int new_square = square + king_offsets[i];
        if(new_square < 0 || new_square >= 64) break;

        int new_row = new_square / 8;
        int new_col = new_square % 8;

        // Wrapping
        if((king_offsets[i] == -1 || king_offsets[i] == 1) && (abs(new_col - col) != 1)) continue;

        // Empty square or square containing opponent's piece
        if(color[new_square] != turn){
            king_moves.pushback({square, new_square, E, false, false});
        }
    }
    return king_moves;
}

// Castling
bool castling_check(int turn, bool kingside){
    if(turn == w){
        if(kingside && can_castle_kingside_w && piece[5] == E && piece[6] == E) return true;
        if(!kingside && can_castle_queenside_w && piece[1] == E && piece[2] == E && piece[3] == E) return true;
    }
    else{
        if(kingside && can_castle_kingside_b && piece[61] == E && piece[62] == E) return true;
        if(!kingside && can_castle_queenside_b && piece[57] == E && piece[58] == E && piece[59] == E) return true;
    }
    return false;
}


int main(){

}
