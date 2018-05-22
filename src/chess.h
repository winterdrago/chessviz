#ifndef CHESS_H
#define CHESS_H

extern char **board;

void init_log();
void clear_log();
void add_log(char *msg);
void print_log();
int get_line(char *buff, size_t sz) ;
void fill_board();
void clear_board();
void print_board();
void init_board();

#endif
