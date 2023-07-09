#include "sudokuUtils.h"

bool validateRange(int *range, size_t length) {
    // Check for duplicates
    for (size_t i = 0; i < length; i++) {
        for (size_t j = 0; j < length; j++) {
            if ((range[i] != 0) && (i != j) && (range[i] == range[j])) {
                return false;
            }
        }
    }
    return true;
}

bool validateCell(struct Board *b, int cellPos) {
    int boardSize = b->sideLength * b->sideLength;
    int row = getRow(NULL, b, cellPos);
    int col = getCol(NULL, b, cellPos);

    printf("Cellpos: %d, row: %d, col: %d\n", cellPos, row, col);
}

int getRow(int **array, struct Board *b, int cellPos) {
    int row = (int)cellPos / b->sideLength;
    if (array) {
        for (size_t i = 0; i < b->sideLength; i++) {
            array[i] = &b->boardValues[row * b->sideLength + i];
        }
    }
    return row;
}

int getCol(int **array, struct Board *b, int cellPos) {
    int col = (int)cellPos % b->sideLength;
    if (array) {
        for (size_t i = 0; i < b->sideLength; i++) {
            array[i] = &b->boardValues[b->sideLength * i + col];
        }
    }
    return col;
}

void getBlock(int **array, struct Board *b, int cellPos) {
    int startRow = ((int)getRow(NULL, b, cellPos) / b->blockSideLength) * b->blockSideLength;
    int startCol = (int)getCol(NULL, b, cellPos) / b->blockSideLength * b->blockSideLength;
    int startPos = b->boardValues[(startRow * b->sideLength) + startCol];
    int endPos = b->boardValues[((startRow + b->blockSideLength) * b->sideLength) + startCol * b->blockSideLength];
    int endRow = getRow(NULL, b, endPos);
    int endCol = getCol(NULL, b, endPos);

    int j = 0;
    for (size_t i = 0; i < (endPos - startPos); i++) {
        int currentCol = getCol(NULL, b, i + startPos);
        if ((currentCol >= startCol) && (currentCol <= endCol)) {
            array[j++] = &b->boardValues[i + startPos];
        }
    }
}