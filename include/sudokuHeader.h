#ifndef SUDOKU_HEADER_H
#define SUDOKU_HEADER_H

#define NO_VAL -1
#define NO_POS -1
#define NO_SUCCESS -2

// Rule of evaluation
typedef enum E_EVAL_RULE
{
    NO_RULE = 0b000,
    ROW = 0b001,
    COLUMN = 0b010,
    BLOCK = 0b100,

} EVAL_RULE;

#endif // SUDOKU_HEADER_H