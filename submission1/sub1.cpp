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

    std::cout << "Enter the type and size of the board (ex. 256, 4): ";
    std::string type_size;
    std::getline(std::cin, type_size);
    std::string type = type_size.substr(0, type_size.find(","));
    std::string size = type_size.substr(type_size.find(",") + 1);

    Board board(std::stoi(type), std::stoi(size));


    board.print_board();
    std::string userInput;
    std::getline(std::cin, userInput);
    while(userInput != "exit"){

        if(userInput == "left"){
            board.move(LEFT);
            board.print_board();
        }
        else if(userInput == "right"){
            board.move(RIGHT);
            board.print_board();
        }
        else if(userInput == "up"){
            board.move(UP);
            board.print_board();
        }
        else if(userInput == "down"){
            board.move(DOWN);
            board.print_board();
        }
        else{
            std::cout << "Invalid input" << std::endl;
        }
        if(board.checkIfWin()){
            std::cout << "You Win!" << std::endl;
            board.print_board();
            break;
        }
        std::getline(std::cin, userInput);
    } // end

    return 0;
}