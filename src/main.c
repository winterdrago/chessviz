#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess.h"
#include "moves.h"

int main()
{
    system("clear");
    init_log();
    init_board();
    print_board();
    while (make_turn()) {
        system("clear");
        print_board();
        print_log();
    }
    print_log();
    print_board();
    clear_log();
    clear_board();
    return 0;
}
