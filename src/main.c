#include <stdio.h>
#include <string.h>  // for memset

#include "sudokuHeader.h"
#include "sudokuUtils.h"

int main() {
    struct Board *board = malloc(sizeof(*board) + sizeof(int) * 9 * 9);

    // Initialize the struct
    board->sideLength = 9;
    board->blockSideLength = 3;  // for a 9x9 board, typically
    // memset(board->boardValues, 0, sizeof(int) * 9 * 9);
    // for (size_t i = 0; i < board->sideLength * board->sideLength; i++) {
    //     board->boardValues[i] = i + 1;
    // }

    int tmpBoard[81] = {
        2, 9, 3, 1, 4, 5, 7, 6, 8,
        4, 8, 1, 6, 7, 3, 5, 2, 9,
        5, 6, 7, 2, 9, 8, 4, 3, 1,
        9, 3, 8, 5, 1, 2, 6, 7, 4,
        7, 2, 6, 4, 3, 9, 1, 8, 5,
        1, 5, 4, 7, 8, 6, 2, 9, 3,
        8, 7, 2, 3, 6, 1, 9, 4, 8,
        3, 4, 5, 9, 2, 7, 8, 1, 6,
        6, 1, 9, 8, 5, 4, 3, 6, 2};

    for (size_t i = 0; i < 81; i++) {
        board->boardValues[i] = tmpBoard[i];
    }

    int nRet = validateCell(board, 8);
    printf("nRet=%d ", nRet);
    if (nRet & ROW)
        printf("row ");
    if (nRet & COLUMN)
        printf("col ");
    if (nRet & BLOCK)
        printf("block ");
    printf("\n");

    nRet = validateCell(board, 79);
    printf("nRet=%d ", nRet);
    if (nRet & ROW)
        printf("row ");
    if (nRet & COLUMN)
        printf("col ");
    if (nRet & BLOCK)
        printf("block ");
    printf("\n");
    nRet = validateCell(board, 28);
    printf("nRet=%d ", nRet);
    if (nRet & ROW)
        printf("row ");
    if (nRet & COLUMN)
        printf("col ");
    if (nRet & BLOCK)
        printf("block ");
printf("\n");
    free(board);
}