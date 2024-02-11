#include "cli.h"

int initScreen()
{
    initscr(); /* Start curses mode */
    printw(
        "Welcome to the sudo solver\n"
        "Please select mode:\n\n"
        "1) 4x4\n"
        "2) 9x9\n"
        "3) 16x16\n"
        "4) 25x25\n"
        "\n"
        "q) Quit");
    refresh();          /* Print it on to the real screen */
    auto cmd = getch(); /* Wait for user input */

    printw("Hei");
    refresh();
    switch (cmd) {
    default:
        printw((char)1);
        refresh();
        break;
    }
    getch();
    endwin(); /* End curses mode */

    return 0;
}