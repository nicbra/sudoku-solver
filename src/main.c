#include <stdio.h>
#include <string.h>  // for memset

#include "sudokuHeader.h"
#include "sudokuUtils.h"

int main() {
    struct Board *board = malloc(sizeof(*board));

    // Initialize the struct
    board->sideLength = 9;
    board->blockSideLength = 3;  // for a 9x9 board, typically

    int tmpBoard[] = {
        0, 0, 3, 0, 4, 0, 0, 0, 8,
        0, 0, 1, 6, 7, 0, 0, 2, 0,
        0, 0, 0, 0, 0, 8, 4, 3, 0,
        0, 0, 0, 5, 1, 0, 6, 7, 0,
        7, 0, 6, 0, 3, 0, 1, 0, 0,
        0, 5, 0, 0, 0, 0, 2, 0, 0,
        8, 7, 0, 0, 0, 0, 0, 4, 0,
        0, 0, 0, 0, 2, 0, 0, 0, 0,
        0, 1, 0, 8, 0, 0, 0, 0, 0};
    int j = 0;
    for (size_t i = 0; i < 81; i++) {
        board->boardValues[i] = tmpBoard[i];
        if (tmpBoard[i] != 0) {
            board->clues[j++] = &board->boardValues[i];
        }
    }

    printBoard(board);

    /*
     * First we will find all unambigous values.
     * I.e. values that can't be places anywhere else.
     */
    bool newRound = false;
    do {
        printf("--\n");
        newRound = false;
        for (size_t cell = 0; cell < 9 * 9; cell++) {
            for (size_t val = 1; val < 10; val++) {
                int unambPos = findUnambPos(ROW, cell, board, val);
                if (unambPos != NO_POS) {
                    printf("Val %ld at pos %d\n", val, unambPos);
                    board->boardValues[unambPos] = val;
                    newRound = true;
                }
                unambPos = findUnambPos(BLOCK, cell, board, val);
                if (unambPos != NO_POS) {
                    printf("Val %ld at pos %d\n", val, unambPos);
                    board->boardValues[unambPos] = val;
                    newRound = true;
                }
                unambPos = findUnambPos(COLUMN, cell, board, val);
                if (unambPos != NO_POS) {
                    printf("Val %ld at pos %d\n", val, unambPos);
                    board->boardValues[unambPos] = val;
                    newRound = true;
                }
            }
        }
    } while (newRound);

    printf("\n\n");
    printBoard(board);

    free(board);
}