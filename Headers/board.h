#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "piece.h"

struct Board{
    Piece board[8][8];
    Board();
};

#endif // BOARD_H_INCLUDED
