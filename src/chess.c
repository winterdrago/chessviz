#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **board;


typedef struct log {
    char line[16];
    struct log *next;
} log_t;

log_t *log_head;
log_t *log_curr;

void init_log() {
    log_head = malloc(sizeof(log_t));
    if (log_head == NULL) exit(1);
    log_curr = log_head;
}

void clear_log() {
    log_curr = log_head;
    log_t *log_tmp = log_curr->next;
    while (log_tmp != NULL) {
        free(log_curr);
        log_curr = NULL;
        log_curr = log_tmp;
        log_tmp = log_tmp->next;
    }
}

void add_log(char *msg) {
    log_t *log_next;
    strcpy(log_curr->line,msg);
    log_next = malloc(sizeof(log_t));
    if (log_next == NULL) exit(1);
    log_curr->next = log_next;
    log_curr = log_curr->next;
}

void print_log() {
    int i = 1;
    log_t *log_tmp = log_head;
    while (log_tmp->next != NULL) {
        printf("%d. %s\n", i, log_tmp->line);
        log_tmp = log_tmp->next;
        i++;
    }
}

int get_line(char *buff, size_t sz) {
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
        printf("\n");
    }
    print_log();
    print_board();
    clear_log();
    clear_board();
    return 0;
}
