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
    Board(size_t size);
    void print_board();
    bool canDo(int obj, int obj2);
    void slide(std::vector<int> &list, int direction);
    void elevate(std::vector<std::vector<int>> &board, int direction);
    void check_for_merges(std::vector<std::vector<int>> &board, int direction);
    void move(int direction);
    void update_board();
    ~Board();
};

// Constructor
Board::Board(size_t size)
{
    srand(time(0)); // Seed the random number generator
    std::vector<std::vector<int>> board(size, std::vector<int>(size, 0));
    this->board = board;
    
    // set two values (adjacent) in the middle of the board to 256 for init state
    int middle_row = this->board.size() / 2;
    int middle_col = this->board[0].size() / 2;
    this->board[middle_row][middle_col] = 512;
    this->board[middle_row+1][middle_col] = 512;
}

// Print board for debug

void Board::print_board()
{

    std::cout << "Board: " << std::endl;
    std::cout << "-------------------------" << std::endl;

    for (int i = 0; i < this->board.size(); i++)
    {
        for (int j = 0; j < this->board[0].size(); j++)
        {
            if(this->board[i][j] == 0){
                std::cout << "-\t";
            }
            else{
                std::cout << this->board[i][j] << "\t";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "-------------------------" << std::endl;
}

// Check if the move is valid

bool Board::canDo(int obj, int obj2){
    return (obj == obj2 && obj != 0);
}

void Board::slide(std::vector<int> &list, int direction) {
    if (direction == LEFT) {
        // Move all non-zero elements to the front
        int index = 0; // Index to place the next non-zero element
        for (int i = 0; i < list.size(); i++) {
            if (list[i] != 0) {
                list[index++] = list[i];
            }
        }
        // Fill the remaining positions with zeros
        while (index < list.size()) {
            list[index++] = 0;
        }
    }
    

    if (direction == RIGHT) {
        // Move all non-zero elements to the end
        int index = list.size() - 1; // Index to place the next non-zero element
        for (int i = list.size() - 1; i >= 0; i--) {
            if (list[i] != 0) {
                list[index--] = list[i];
            }
        }
        // Fill the remaining positions with zeros
        while (index >= 0) {
            list[index--] = 0;
        }
    }
}

// slide all elements up or down

void Board::elevate(std::vector<std::vector<int>> &board, int direction) {
    if (direction == UP) {
        // Move all non-zero elements to the top
        for (int j = 0; j < board[0].size(); j++) {
            std::vector<int> column;
            for (int i = 0; i < board.size(); i++) {
                column.push_back(board[i][j]);
            }
            slide(column, LEFT);
            for (int i = 0; i < board.size(); i++) {
                board[i][j] = column[i];
            }
        }
    }
    if (direction == DOWN) {
        // Move all non-zero elements to the bottom
        for (int j = 0; j < board[0].size(); j++) {
            std::vector<int> column;
            for (int i = 0; i < board.size(); i++) {
                column.push_back(board[i][j]);
            }
            slide(column, RIGHT);
            for (int i = 0; i < board.size(); i++) {
                board[i][j] = column[i];
            }
        }
    }
}

void Board::check_for_merges(std::vector<std::vector<int>> &board, int direction) {
    // Check for merges (if two adjacent elements are equal, then divide the first element by 2)
    if (direction == LEFT) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size() - 1; j++) {
                if (canDo(board[i][j], board[i][j + 1])) {
                    board[i][j] /= 2;
                    board[i][j + 1] = 0;
                }
            }
        }
    }
    if (direction == RIGHT) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = board[0].size() - 1; j > 0; j--) {
                if (canDo(board[i][j], board[i][j - 1])) {
                    board[i][j] /= 2;
                    board[i][j - 1] = 0;
                }
            }
        }
    }
    if (direction == UP) {
        for (int j = 0; j < board[0].size(); j++) {
            for (int i = 0; i < board.size() - 1; i++) {
                if (canDo(board[i][j], board[i + 1][j])) {
                    board[i][j] /= 2;
                    board[i + 1][j] = 0;
                }
            }
        }
    }
    if (direction == DOWN) {
        for (int j = 0; j < board[0].size(); j++) {
            for (int i = board.size() - 1; i > 0; i--) {
                if (canDo(board[i][j], board[i - 1][j])) {
                    board[i][j] /= 2;
                    board[i - 1][j] = 0;
                }
            }
        }
    }
}

// Move everything to the (arg) direction

void Board::move(int direction)
{
    switch (direction)
    {
    case LEFT:
        // move everything ALL THE WAY to the left 
        for(auto& row : this->board){
            slide(row, LEFT);
        }

        // check for merges
        check_for_merges(this->board, LEFT);

        for(auto& row : this->board){
            slide(row, LEFT);
        }

        update_board();
        break;
    case RIGHT:
    // same for right moves:

        for(auto& row : this->board){
            slide(row, RIGHT);
        }

        // check for merges
        check_for_merges(this->board, RIGHT);

        for(auto& row : this->board){
            slide(row, RIGHT);
        }

        update_board();
        break;
    case UP:
        // move everything ALL THE WAY to the top
        elevate(this->board, UP);

        // check for merges 
        check_for_merges(this->board, UP);

        elevate(this->board, UP);


        update_board();
        break;
    case DOWN:

        // move everything ALL THE WAY to the bottom
        elevate(this->board, DOWN);

        // check for merges 
        check_for_merges(this->board, DOWN);

        elevate(this->board, DOWN);


        update_board();
        break;

    default:
        break;
    }
}

// After a move is made, update a random square with value 256/128/64 or 32..

void Board::update_board()
{
    // check if there is an empty square
    bool hasEmpty = false;
    for (const auto& row : this->board)
    {
        for (int cell : row)
        {
            if (cell == 0)
            {
                hasEmpty = true;
                break;
            }
        }
        if (hasEmpty) break;
    }
    // if theres no empty square, the game ends player loses
    if (!hasEmpty) {
        std::cout << "Game Over" << std::endl;
        // Set a flag or return a value to indicate the game has ended
        throw std::runtime_error("Game Over");
    }


    // find a random empty square
    int row = rand() % this->board.size();
    int col = rand() % this->board[0].size();
    while (this->board[row][col] != 0)
    {
        row = rand() % this->board.size();
        col = rand() % this->board[0].size();
    }

    // set the value
    std::vector<int> values = {256, 128, 64, 32};
    int value = values[rand() % values.size()];
    this->board[row][col] = value;
}

// Destructor

Board::~Board()
{

}





