#include "sudokuUtils.h"

bool validateRange(int** range, size_t length)
{
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

EVAL_RULE validateCell(struct Board* b, int cellPos)
{
    int boardSize = b->sideLength * b->sideLength;

    int** row = malloc(b->sideLength * sizeof(int*));                             // allocate array of pointers
    int** col = malloc(b->sideLength * sizeof(int*));                             // allocate array of pointers
    int** block = malloc(b->blockSideLength * b->blockSideLength * sizeof(int*)); // allocate array of pointers

    getRow(row, b, cellPos);
    getCol(col, b, cellPos);
    getBlock(block, NULL, b, cellPos);

    // Evaluate row, column and block and store violations of these rules
    int ruleViolation = NO_RULE;
    ruleViolation |= (!validateRange(row, b->sideLength) ? ROW : 0);
    ruleViolation |= (!validateRange(col, b->sideLength) ? COLUMN : 0);
    ruleViolation |= (!validateRange(block, b->sideLength) ? BLOCK : 0);

    return ruleViolation;
}

EVAL_RULE tryCellValue(struct Board* b, int cellPos, int tryVal)
{
    struct Board* tmpBoard = malloc(sizeof(struct Board));
    memcpy(tmpBoard, b, sizeof(struct Board));

    tmpBoard->boardValues[cellPos] = tryVal;
    EVAL_RULE nRet = validateCell(tmpBoard, cellPos);
    free(tmpBoard);
    return nRet;
}

int getRow(int** array, struct Board* b, int cellPos)
{
    int row = (int)cellPos / b->sideLength;
    if (array) {
        for (size_t i = 0; i < b->sideLength; i++) {
            array[i] = &b->boardValues[row * b->sideLength + i];
        }
    }
    return row;
}

int getCol(int** array, struct Board* b, int cellPos)
{
    int col = (int)cellPos % b->sideLength;
    if (array) {
        for (size_t i = 0; i < b->sideLength; i++) {
            array[i] = &b->boardValues[b->sideLength * i + col];
        }
    }
    return col;
}

void getBlock(int** parray, int* narray, struct Board* b, int cellPos)
{
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
            if (parray)
                parray[j] = &b->boardValues[i + startPos];
            if (narray)
                narray[j] = i + startPos;
            j++;
        }
    }
}

int findUnambPos(EVAL_RULE base, int basePos, struct Board* b, int value)
{
    int arraySize;

    size_t i = 0;
    int validPositions = 0;
    int cellPos = 0;
    switch (base) {
    case BLOCK: {
        arraySize = b->blockSideLength * b->blockSideLength;

        // Iterate over block
        int block[arraySize]; //= malloc(b->blockSideLength * b->blockSideLength * sizeof(int *));  // allocate array
        getBlock(NULL, block, b, basePos);

        for (; i < arraySize; i++) {
            if (b->boardValues[block[i]] == 0) {
                if (tryCellValue(b, block[i], value) == NO_RULE) {
                    validPositions++;
                    cellPos = block[i];
                }
            }
        }
        if (validPositions == 1)
            return cellPos;
        else
            return NO_POS;

        break;
    }
    case ROW: {
        int row = getRow(NULL, b, basePos);
        int startPos = row * b->sideLength;

        // Iterate over row
        for (; i < b->sideLength; i++) {
            if (b->boardValues[startPos + i] == 0) {
                if (tryCellValue(b, startPos + i, value) == NO_RULE) {
                    validPositions++;
                    cellPos = startPos + i;
                }
            }
        }
        if (validPositions == 1)
            return cellPos;
        else
            return NO_POS;
        break;
    }
    case COLUMN: {
        int column = getCol(NULL, b, basePos);
        int cell;

        // Iterate over column
        for (; i < b->sideLength; i++) {
            cell = column + (i * b->sideLength);
            if (b->boardValues[cell] == 0) {
                if (tryCellValue(b, cell, value) == NO_RULE) {
                    validPositions++;
                    cellPos = cell;
                }
            }
        }
        if (validPositions == 1)
            return cellPos;
        else
            return NO_POS;
        break;
    }
    default:
        return NO_SUCCESS;
    }
}

void printBoard(struct Board* b)
{
    int cell = 0;
    for (size_t i = 0; i < b->sideLength; i++) {
        if ((i % b->blockSideLength == 0) && i > 0) {
            int nDivisions = (b->sideLength / b->blockSideLength) - 1;
            printf("%c", ' ');
            for (size_t j = 0; j < b->sideLength * 2 + nDivisions * 2 - 1; j++) {
                printf("%c", '-');
            }
            printf("%c", '\n');
        }

        for (size_t j = 0; j < b->sideLength; j++) {
            if (b->boardValues[cell] == 0)
                printf(" %c", '.');
            else
                printf(" %d", b->boardValues[cell]);
            cell++;
            if (((j + 1) % b->blockSideLength == 0) && j < b->sideLength - 1)
                printf(" |"); // Print a divider

            else if (j == b->sideLength - 1)
                printf("%c", '\n'); // Print a new line
        }
    }
}