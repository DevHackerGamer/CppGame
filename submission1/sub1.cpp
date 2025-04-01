#include <iostream>
#include <vector>
#include "Objects.h"
#include <string>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

int main(){

    std::cout << "Enter the type and size of the board (ex. 256, 4): ";
    std::string type_size;
    std::getline(std::cin, type_size);

    // Ensure input is valid
    if (type_size.find(",") == std::string::npos) {
        std::cout<< "Invalid input. Please use 'type, size' format: ";
        getline(std::cin, type_size);
    }
    std::string type = type_size.substr(0, type_size.find(","));
    std::string size = type_size.substr(type_size.find(",") + 1);

    Board board(std::stoi(type), std::stoi(size));


    board.print_board();
    std::string userInput;
    std::getline(std::cin, userInput);
    int maxMoves=0;

    while(userInput != "exit"){

        if(maxMoves==1000){
            std::cout << "Maximum moves reached! Lose!" << std::endl;
            break;
        }

        if(userInput == "left"){
            board.move(LEFT);
            board.print_board();
            maxMoves++;
        }
        else if(userInput == "right"){
            board.move(RIGHT);
            board.print_board();
            maxMoves++;
        }
        else if(userInput == "up"){
            board.move(UP);
            board.print_board();
            maxMoves++;
        }
        else if(userInput == "down"){
            board.move(DOWN);
            board.print_board();
            maxMoves++;
        }
        else{
            std::cout << "Invalid input. Please use specified format in README (ex. 'left)" << std::endl;
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