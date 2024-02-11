#include <stdio.h>
#include <string.h> // for memset
#include <time.h>

#include "cli.h"
#include "sudokuHeader.h"
#include "sudokuUtils.h"

void fillUnambigousVals(struct Board* b)
{
    /*
     * First we will find all unambigous values.
     * I.e. values that can't be places anywhere else.
     */
    bool newRound = false;
    do {
        newRound = false;
        for (size_t cell = 0; cell < 9 * 9; cell++) {
            for (size_t val = 1; val < 10; val++) {
                int unambPos = findUnambPos(ROW, cell, b, val);
                if (unambPos != NO_POS) {
                    b->boardValues[unambPos] = val;
                    newRound = true;
                }
                unambPos = findUnambPos(COLUMN, cell, b, val);
                if (unambPos != NO_POS) {
                    b->boardValues[unambPos] = val;
                    newRound = true;
                }
            }
        }
    } while (newRound);
    return;
}

bool DFS_method(struct Board* b, int depth)
{
    // Copy to a new board to preserve the original
    struct Board* b_copy = malloc(sizeof(*b));
    memcpy(b_copy, b, sizeof(*b));

    bool tryNextValue = false;

    int cell = 0;
    for (; cell < 9 * 9; cell++) {
        if (b_copy->boardValues[cell] == 0) {
            tryNextValue = true;
            break;
        }
    }

    int tryVal = 1;
    int nRet;
    if (tryNextValue) {
    tryvalue_label:
        memcpy(b_copy, b, sizeof(*b));
        do {
            nRet = tryCellValue(b_copy, cell, tryVal);
            if (nRet == NO_RULE) {
                b_copy->boardValues[cell] = tryVal;
                // fillUnambigousVals(b_copy);
            }
            if (tryVal < 9) {
                tryVal++;
            }
            else {
                break;
            }

        } while ((tryVal <= 9) && nRet != NO_RULE);
    }
    else {
        free(b_copy);
        return true;
    }

    if (nRet == NO_RULE) {
        if (!DFS_method(b_copy, depth + 1)) {
            if (tryVal >= 9) {
                free(b_copy);
                return false;
            }
            else {
                goto tryvalue_label;
            }
        }
        else {
            memcpy(b, b_copy, sizeof(*b));
            free(b_copy);
            return true;
        }
    }
    else {
        free(b_copy);
        return false;
    }
}

int main()
{

    initScreen();

    clock_t start_t, end_t;
    start_t = clock();
    struct Board* board = malloc(sizeof(*board));

    // Initialize the struct
    board->sideLength = 9;
    board->blockSideLength = 3; // for a 9x9 board, typically

    // clang-format off
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
    // clang-format on

    int j = 0;
    for (size_t i = 0; i < 81; i++) {
        board->boardValues[i] = tmpBoard[i];
        if (tmpBoard[i] != 0) {
            board->clues[j++] = &board->boardValues[i];
        }
    }

    fillUnambigousVals(board);

    DFS_method(board, 0);

    printf("\n\n");
    printBoard(board);

    free(board);

    end_t = clock();

    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total ms taken by CPU: %f\n", total_t * 1000);
}
