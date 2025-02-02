#include <iostream>
#include <vector>

const int E = 0;
const int P = 1;
const int N = 3;
const int B = 4;
const int R = 5;
const int Q = 9;
const int K = 1000;

const int b = -1;
const int w = 1;

const int knight_offsets[8] = {-17, -15, -10, -6, 6, 10, 15, 17};
const int rook_offsets[4] = {-8, -1, 1, 8};
const int bishop_offsets[4] = {-9, -7, 7, 9};

bool curr_turn = true;

struct Move{
    int start_square;
    int destination_square;
    int promotion;
    Move(int s, int d, int p){
        start_square = s;
        destination_square = d;
        promotion = p;
    }
};

int piece[64] = {
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

void print_board(){
    int square = 0;
    for(int rank = 8; rank >= 1; rank--){
        std::cout << rank << '|';
        for(int file = 1; file <= 8; file++){
            if(piece[square] == E){
                std::cout << ". ";
            }
            else{
                if(piece[square] == P){
                    if(color[square] == b) std::cout << 'p' << ' ';
                    else std::cout << 'P' << ' ';
                }
                else if(piece[square] == N){
                    if(color[square] == b) std::cout << 'n' << ' ';
                    else std::cout << 'N' << ' ';
                }
                else if(piece[square] == B){
                    if(color[square] == b) std::cout << 'b' << ' ';
                    else std::cout << 'B' << ' ';
                }
                else if(piece[square] == R){
                    if(color[square] == -1) std::cout << 'r' << ' ';
                    else std::cout << 'R' << ' ';
                }
                else if(piece[square] == Q){
                    if(color[square] == -1) std::cout << 'q' << ' ';
                    else std::cout << 'Q' << ' ';
                }
                else if(piece[square] == K){
                    if(color[square] == b) std::cout << 'k' << ' ';
                    else std::cout << 'K' << ' ';
                }
            }
            square++;
        }
        std::cout << std::endl;
    }
    std::cout << " +---------------" << std::endl;
    std::cout << "  a b c d e f g h" << std::endl;
}

void pawn_move_generator(int start_square, std::vector<Move> moves){
    if(start_square < 0 || start_square >= 64) return;

    int direction = (color_turn == true) ? -8 : 8;
    int start_rank = start_square / 8;
    if(piece[destination_square] == E){
        if(start_rank == 1 || start_rank == 6){
            Move m = new Move(start_square, start_square + 2 * direction, 0);
        }
        else if()
    }
}

void knight_move_generator(int start_square, std::vector<Move> moves){

}

void bishop_move_generator(int start_square, std::vector<Move> moves){

}

void rook_move_generator(int start_square, std::vector<Move> moves){

}

void queen_move_generator(int start_square, std::vector<Move> moves){

}

void king_move_generator(int start_square, std::vector<Move> moves){

}

void pseudo_legal_move_generator(int start_square, int destination_square){
    std::vector<Move> move_list;
    for(int i = 0; i < 64; i++){
        if(piece[start_square] == E) continue;
        else if((curr_turn && color[start_square] == w) || (!curr_turn && color[start_square] == b)){
            if(piece[start_square] == P){
                pawn_move_generator(start_square, move_list);
            }
            else if(piece[start_square] == N){
                knight_move_generator(start_square, move_list);
            }
            else if(piece[start_square] == B){
                bishop_move_generator(start_square, move_list);
            }
            else if(piece[start_square] == R){
                rook_move_generator(start_square, move_list);
            }
            else if(piece[start_square] == Q){
                queen_move_generator(start_square, move_list);
            }
            else if(piece[start_square] == K){
                king_move_generator(start_square, move_list);
            }
        }
    }
}

int coordinate_to_index(std::string square) {
    char file = square[0];
    int file_index = file - 'a';
    char rank = square[1];
    int rank_index = 8 - (rank - '0');
    int index = rank_index * 8 + file_index;
    return index;
}




void make_move(int start_square, int destination_square){
    if((curr_turn && color[start_square] == w) || (!curr_turn && color[start_square] == b)){
        piece[destination_square] = piece[start_square];
        color[destination_square] = color[start_square];
        piece[start_square] = E;
        color[start_square] = E;
        curr_turn = !curr_turn;
    }
}

int main(){
    std::string start_square, destination_square;
    do{
        print_board();
        std::cin >> start_square >> destination_square;
        make_move(coordinate_to_index(start_square), coordinate_to_index(destination_square));
    }while(true);

    return 0;
}
