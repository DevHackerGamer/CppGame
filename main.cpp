#include <iostream>
#include <vector>
#include "Objects.h"
#include <string>
#include "algs.h"

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

int main(){

    std::cout << "Enter the size of the board: ";
    std::string size;

    std::getline(std::cin, size);
    std::cout << "Enter type of game (2048/1024): ";
    std::string type;
    std::getline(std::cin, type);

    Board board(std::stoi(type), std::stoi(size));


    try {
        std::vector<Board> path = greedy_search(board);
        std::cout << "Path found with " << path.size() << " moves." << std::endl;
        for (auto& board : path) {
            board.print_board();
            std::cout << "-----------------" << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }


    // board.print_board();
    // std::string userInput;
    // std::getline(std::cin, userInput);
    // while(userInput != "exit"){
    //     if(userInput == "left"){
    //         board.move(LEFT);
    //         board.print_board();
    //     }
    //     else if(userInput == "right"){
    //         board.move(RIGHT);
    //         board.print_board();
    //     }
    //     else if(userInput == "up"){
    //         board.move(UP);
    //         board.print_board();
    //     }
    //     else if(userInput == "down"){
    //         board.move(DOWN);
    //         board.print_board();
    //     }
    //     else{
    //         std::cout << "Invalid input" << std::endl;
    //     }
    //     std::getline(std::cin, userInput);
    // } // end

    return 0;
}