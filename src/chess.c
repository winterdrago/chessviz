#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess.h"

char **board;


typedef struct log 
{
    char line[16];
    struct log *next;
} log_t;

log_t *log_head;
log_t *log_curr;

void init_log() 
{
    log_head = malloc(sizeof(log_t));
    if (log_head == NULL) exit(1);
    log_curr = log_head;
}

void clear_log() 
{
    log_curr = log_head;
    log_t *log_tmp = log_curr->next;
    while (log_tmp != NULL) {
        free(log_curr);
        log_curr = NULL;
        log_curr = log_tmp;
        log_tmp = log_tmp->next;
    }
}

void add_log(char *msg) 
{
    log_t *log_next;
    strcpy(log_curr->line,msg);
    log_next = malloc(sizeof(log_t));
    if (log_next == NULL) exit(1);
    log_curr->next = log_next;
    log_curr = log_curr->next;
}

void print_log() 
{
    int i = 1;
    log_t *log_tmp = log_head;
    while (log_tmp->next != NULL) {
        printf("%d. %s\n", i, log_tmp->line);
        log_tmp = log_tmp->next;
        i++;
    }
    printf("%d.",i);
}

int get_line(char *buff, size_t sz) 
{
    int ch, extra;
    if (fgets (buff, sz, stdin) == NULL) {
        return 1;
    }
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? 1 : 0;
    }
    buff[strlen(buff)-1] = '\0';
    return 0;
}

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

