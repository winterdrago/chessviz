#define CTEST_MAIN

#include <stdlib.h>
#include <chess.h>
#include <moves.h>
#include <ctest.h>

CTEST(Syntax, CorrectSyntaxCheck) {
    int result = check_syntax("e2-e4",0,1);
    int expected = 1;
    ASSERT_EQUAL(expected,result);
}

CTEST(Syntax, IncorrectSyntaxCheck) {
    int result = check_syntax("nb1-a3",0,0);
    int expected = 0;
    ASSERT_EQUAL(expected,result);
}

CTEST(PawnMove, Correct) {
    int result = make_move("d2-d3",0,1);
    int expected = 1;
    ASSERT_EQUAL(expected,result);
}

CTEST(PawnMove, Incorrect) {
    int result = make_move("Pb2-b3",0,1);
    int expected = 0;
    ASSERT_EQUAL(expected,result);
}

int main(int argc, const char** argv) {
    init_board();
    int test_res = ctest_main(argc, argv);
    clear_board();
    return test_res;
}
