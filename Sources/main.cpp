#include <iostream>
#include <vector>

#include "generate_moves.h"
#include "print_board.h"
#include "make_move.h"

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
