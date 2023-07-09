#include "sudokuUtils.h"

bool validateRange(int **range, size_t length) {
    // Check for duplicates
    for (size_t i = 0; i < length; i++) {
        for (size_t j = 0; j < length; j++) {
            if ((*range[i] != 0) && (i != j) && (*range[i] == *range[j])) {
                return false;
            }
        }
    }
    return true;
}

EVAL_RULE validateCell(struct Board *b, int cellPos) {
    int boardSize = b->sideLength * b->sideLength;

    int **row = malloc(b->sideLength * sizeof(int *));                              // allocate array of pointers
    int **col = malloc(b->sideLength * sizeof(int *));                              // allocate array of pointers
    int **block = malloc(b->blockSideLength * b->blockSideLength * sizeof(int *));  // allocate array of pointers

    getRow(row, b, cellPos);
    getCol(col, b, cellPos);
    getBlock(block, b, cellPos);

    // Evaluate row, column and block and store violations of these rules
    int ruleViolation = 0;
    ruleViolation |= (!validateRange(row, b->sideLength) ? ROW : 0);
    ruleViolation |= (!validateRange(col, b->sideLength) ? COLUMN : 0);
    ruleViolation |= (!validateRange(block, b->sideLength) ? BLOCK : 0);

    return ruleViolation;
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
    int startPos = (startRow * b->sideLength) + startCol;
    int endPos = ((startRow + b->blockSideLength - 1) * b->sideLength) + startCol + b->blockSideLength - 1;
    int endRow = getRow(NULL, b, endPos);
    int endCol = getCol(NULL, b, endPos);

    size_t j = 0;
    for (size_t i = 0; i < (endPos - startPos + 1); i++) {
        int currentCol = getCol(NULL, b, i + startPos);
        if ((currentCol >= startCol) && (currentCol <= endCol)) {
            array[j++] = &b->boardValues[i + startPos];
        }
    }
}