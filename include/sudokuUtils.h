#ifndef SUDOKU_UTILS_H
#define SUDOKU_UTILS_H

#define MAX_SIDE_LENGTH 25

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudokuHeader.h"

/**
 * @brief Struct holding information about the sudoku board.
 * For now, it will only work with square boards with square sub-blocks
 */
struct Board {
    int sideLength;                                      // Side length of board (e.g. 9x9 board have side length 9)
    int blockSideLength;                                 // Side length of block
    int *clues[MAX_SIDE_LENGTH * MAX_SIDE_LENGTH];       // Pointer to initial values on the board
    int boardValues[MAX_SIDE_LENGTH * MAX_SIDE_LENGTH];  // The values on the board. Zeroes are empty cells
};

/**
 * @brief Checks if numbers in the passed array is unike.
 *
 * @param range Pointer to an array of of numbers. Either a row, column or a block.
 * @param length Length of the passed array
 * @return true if ok
 * @return false if not valid
 */
bool validateRange(int **range, size_t length);

/**
 * @brief Check if the cell has a valid value on the board
 *
 * @param board pointer to the board struct
 * @param cellPos position of the cell on the board
 * @return The rules that are violated
 */
EVAL_RULE validateCell(struct Board *b, int cellPos);


/**
 * @brief Try a value in a cell, to see if that doesn't breake any rules
 * 
 * @param b The board
 * @param cellPos Position to try the value
 * @param tryVal The value to try
 * @return EVAL_RULE Which rules are broken
 */
EVAL_RULE tryCellValue(struct Board *b, int cellPos, int tryVal);
/**
 * @brief Get the values of the row where cell are located
 * Fills the array with pointers each cells in the row where the reference cell is located.
 *
 * @param array the array to fill with pointers to the row cells
 * @param b structure of the board
 * @param cellPos position of the reference cell
 * @return int The number of the row (zero indexed)
 */
int getRow(int **array, struct Board *b, int cellPos);

/**
 * @brief Get the values of the column where cell are located
 * Fills the array with pointers each cells in the column where the reference cell is located.
 *
 * @param array the array to fill with pointers to the column cells
 * @param b structure of the board
 * @param cellPos position of the reference cell
 * @return int The number of the column (zero indexed)
 */
int getCol(int **array, struct Board *b, int cellPos);

/**
 * @brief Get the values of the subblock where the cell are located
 * Fills the passed array with pointers to each cells in the subblock where the reference cell is located
 *
 * @param parray Pointer to array to fill with pointers to values of subblock. Will be filled by the function.
 * @param narray Pointer to array to fill with values of positions in the board. Will be filled by the function.
 * @param b structure of the board
 * @param cellPos position of the reference cell
 */
void getBlock(int **parray, int *narray, struct Board *b, int cellPos);

/**
 * @brief Find unambigious position of a value
 * Say you want to put the value 3 somewhere in a row. The row is base in this case.
 * The function tells you where to put it, if it's ambigious.
 * If it's possible to put it several places, the function returns NO_POS
 *
 * @param base Where to put it with respect to basePos (block/row/col)
 * @param basePos From witch cell to try from (the same row, col or block).
 * @param b The board
 * @param value The value to find unambigious position
 * @return The position to put the value. If several positions are possible, NO_POS is returned.
 */
int findUnambPos(EVAL_RULE base, int basePos, struct Board *b, int value);

/**
 * @brief Print the board to terminal
 * 
 * @param b the board
 */
void printBoard (struct Board *b);

#endif  // SUDOKU_UTILS_H