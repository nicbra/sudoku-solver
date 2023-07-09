#ifndef SUDOKU_UTILS_H
#define SUDOKU_UTILS_H

#define MAX_SIDE_LENGTH 25

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Struct holding information about the sudoku board.
 * For now, it will only work with square boards with square sub-blocks
 */
struct Board {
    int sideLength;       // Side length of board (e.g. 9x9 board have side length 9)
    int blockSideLength;  // Side length of block
    int boardValues[];    // The values on the board. Zeroes are empty cells
};

/**
 * @brief Checks if numbers in the passed array is unike.
 *
 * @param range Pointer to an array of of numbers. Either a row, column or a block.
 * @param length Length of the passed array
 * @return true if ok
 * @return false if not valid
 */
bool validateRange(int *range, size_t length);

/**
 * @brief Check if the cell has a valid value on the board
 * 
 * @param board pointer to the board struct
 * @param cellPos position of the cell on the board
 * @return true if valid
 * @return false if invalid
 */
bool validateCell(struct Board *b, int cellPos);

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
 * @param array the array to fill with pointers to the subblock
 * @param b structure of the board
 * @param cellPos position of the reference cell
 */
void getBlock(int **array, struct Board *b, int cellPos);

#endif  // SUDOKU_UTILS_H