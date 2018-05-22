#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess.h"

int in_bounds(char ch, char b1, char b2) {
    return (ch >= b1 && ch <= b2);
}

int check_syntax(char *str,int b,int p) {
    return ((in_bounds(str[b],'A','Z') || p) &&
            in_bounds(str[b+1-p],'a','h') &&
            in_bounds(str[b+2-p],'1','8') &&
            (str[b+3-p] == '-' || str[b+3-p] == 'x') &&
            in_bounds(str[b+4-p],'a','h') &&
            in_bounds(str[b+5-p],'1','8'));
}

int make_move(char *move, int m1, int pawn) {
    int l1 = (int)(move[m1+1-pawn] - 'a');
    int l2 = (int)(move[m1+4-pawn] - 'a');
    int d1 = (int)(move[m1+2-pawn] - '1');
    int d2 = (int)(move[m1+5-pawn] - '1');
    if (check_syntax(move,m1,pawn) && ((pawn && (board[l1][d1]=='P' || board[l1][d1]=='p')) ||
            (board[l1][d1]==move[m1]||board[l1][d1]==move[m1]+32)) && board[l2][d2]==' ') {
        board[l2][d2] = board[l1][d1];
        board[l1][d1] = ' ';
    } else {
        return 0;
    }
    return 1;
}

int make_kill(char *move, int m1, int pawn) {
    int l1 = (int)(move[m1+1-pawn] - 'a');
    int l2 = (int)(move[m1+4-pawn] - 'a');
    int d1 = (int)(move[m1+2-pawn] - '1');
    int d2 = (int)(move[m1+5-pawn] - '1');
    if (check_syntax(move,m1,pawn) && ((pawn && (board[l1][d1]=='P' || board[l1][d1]=='p')) ||
            (board[l1][d1]==move[m1]||board[l1][d1]==move[m1]+32)) && board[l2][d2]!=' ') {
        board[l2][d2] = board[l1][d1];
        board[l1][d1] = ' ';
    } else {
        return 0;
    }
    return 1;
}

int make_castling(int w,int l) {
    if (l) {
        if (board['b'-'a'][7-7*w]==' ' && board['c'-'a'][7-7*w]==' ' && board['d'-'a'][7-7*w]==' ' &&
                board['a'-'a'][7-7*w]=='r'-(char)(32*w) && board['e'-'a'][7-7*w]=='k'-(char)(32*w)) {
            board['c'-'a'][7-7*w]=board['e'-'a'][7-7*w];
            board['d'-'a'][7-7*w]=board['a'-'a'][7-7*w];
            board['e'-'a'][7-7*w]=' ';
            board['a'-'a'][7-7*w]=' ';
        } else {
            return 0;
        }
    } else {
        if (board['f'-'a'][7-7*w]==' ' && board['g'-'a'][7-7*w]==' ' &&
                board['h'-'a'][7-7*w]=='r'-(char)(32*w) && board['e'-'a'][7-7*w]=='k'-(char)(32*w)) {
            board['g'-'a'][7-7*w]=board['e'-'a'][7-7*w];
            board['f'-'a'][7-7*w]=board['h'-'a'][7-7*w];
            board['e'-'a'][7-7*w]=' ';
            board['h'-'a'][7-7*w]=' ';
        } else {
            return 0;
        }
    }
    return 1;
}

int make_turn() {
    int i,sp;
    char turn[16];
    int correct_input = 0;
    get_line(turn, sizeof(turn));
    sp=-1;
    for (i = 0; i < strlen(turn); i++){
        if (turn[i] == ' ' || turn[i] == '#') {
            sp = i;
            break;
        }
    }
    if (sp<0) {
        add_log("Wrong input.");
        return 1;
    }
    for (i = 0; i < strlen(turn); i++){
        if (turn[i] == '-') {
            if (i < sp) {
                if (turn[0]=='0' && turn[2]=='0') {
                    correct_input = make_castling(1,(turn[3]=='-' && turn[4]=='0'));
                    i+=3*(turn[3]=='-' && turn[4]=='0');
                } else {
                    correct_input = make_move(turn, 0, (i == 2));
                }
            } else {
                if (turn[sp+1]=='0' && turn[sp+3]=='0') {
                    correct_input = make_castling(0,(turn[sp+4]=='-' && turn[sp+5]=='0'));
                    i+=3*(turn[sp+4]=='-' && turn[sp+5]=='0');
                } else {
                    correct_input = make_move(turn, sp+1, (i == sp+3));
                }
            }
        } else if (turn[i] == 'x') {
            if (i < sp) {
                correct_input = make_kill(turn, 0, (i == 2));
            } else {
                correct_input = make_kill(turn, sp+1, (i == sp+3));
            }
        } else if (turn[i]=='#') {
            add_log(turn);
            return 0;
        }
    }
    if (correct_input) add_log(turn); else add_log("Wrong input.");
    return 1;
}

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
