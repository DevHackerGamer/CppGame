#include <iostream>
#include <vector>
#include "Objects.cpp"

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

int main(){

    Board board;
    board.print_board();

    board.move(LEFT);
    board.print_board();

    board.move(RIGHT);
    board.print_board();

    board.move(UP);
    board.print_board();

    board.move(DOWN);
    board.print_board();

    return 0;
}