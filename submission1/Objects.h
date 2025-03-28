#ifndef OBJECTS_H
#define OBJECTS_H

#include <vector>
#include <iostream>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

class Board
{
public:
    std::vector<std::vector<int>> board;
    int board_type;
    Board(int max, size_t size);
    void print_board();
    bool canDo(int obj, int obj2);
    void slide(std::vector<int> &list, int direction);
    void elevate(std::vector<std::vector<int>> &board, int direction);
    void check_for_merges(std::vector<std::vector<int>> &board, int direction);
    void checkIfWin(std::vector<std::vector<int>> &board);
    bool checkIfWin();
    void move(int direction);
    void update_board();
    ~Board();
};

#endif // OBJECTS_H