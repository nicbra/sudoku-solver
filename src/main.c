#include <stdio.h>
#include <string.h>  // for memset

#include "sudokuUtils.h"

int main() {
    struct Board *board = malloc(sizeof(*board) + sizeof(int) * 9 * 9);

    // Initialize the struct
    board->sideLength = 9;
    board->blockSideLength = 3;  // for a 9x9 board, typically
    memset(board->boardValues, 0, sizeof(int) * 9 * 9);

    validateCell(board, 0);
    validateCell(board, 9);
    validateCell(board, 34);
    validateCell(board, 80);

    free(board);
}