#ifndef SUDOKU_HEADER_H
#define SUDOKU_HEADER_H

// Rule of evaluation
typedef enum E_EVAL_RULE {
    ROW     = 0b001,
    COLUMN  = 0b010,
    BLOCK   = 0b100,

} EVAL_RULE;

#endif // SUDOKU_HEADER_H