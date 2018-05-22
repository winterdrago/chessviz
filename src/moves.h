#ifndef MOVES_H
#define MOVES_H

int in_bounds(char ch, char b1, char b2);
int check_syntax(char *str,int b,int p);
int make_move(char *move, int m1, int pawn);
int make_kill(char *move, int m1, int pawn);
int make_castling(int w,int l);
int make_turn();

#endif
