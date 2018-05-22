#include <stdio.h>
#include <stdlib.h>

char **board;

void fill_board()
{
    int i;
    for (i = 0; i < 8; i++){
        board[i][1] = 'P';
        board[i][6] = 'p';
    }
    board[0][0] = 'R';
    board[1][0] = 'N';
    board[2][0] = 'B';
    board[3][0] = 'Q';
    board[4][0] = 'K';
    board[5][0] = 'B';
    board[6][0] = 'N';
    board[7][0] = 'R';
    board[0][7] = 'r';
    board[1][7] = 'n';
    board[2][7] = 'b';
    board[3][7] = 'q';
    board[4][7] = 'k';
    board[5][7] = 'b';
    board[6][7] = 'n';
    board[7][7] = 'r';
}

void clear_board()
{
    int i;
    for (i = 0; i < 8; i++) {
        free(board[i]);
    }
    free(board);
    board = NULL;
}

void print_board()
{
    int i,j;
    for (i = 7; i >= -1; i--) {
        printf("  ---------------------------------\n");
        for (j = 8; j > -1; j--) {
            if (j > 7 && i < 0) {
                printf("   ");
            } else  if (j > 7) {
                printf("%d |",i + 1);
            } else if (i < 0) {
                printf(" %c  ",'H' - j);
            } else {
                printf(" %c |",board[7-j][i]);
            }
        }
        printf("\n");
    }
}

void init_board()
{
    int i,j;
    board = (char**)malloc(8 * sizeof(char*));
    for (i = 0; i < 8; i++) {
        board[i] = (char*)malloc(8 * sizeof(char));
        for (j = 0; j < 8; j++) {
            board[i][j] = ' ';
        }
    }
    fill_board();
}

int main()
{
    init_board();
    print_board();
    clear_board();
    return 0;
}
