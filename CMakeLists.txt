cmake_minimum_required(VERSION 3.0.0)
project(sudoku-solver VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(sudoku-solver
    src/main.c
    src/cli.c
    src/sudokuUtils.c
)

include_directories(include)
link_directories(include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(sudoku-solver m ncurses)