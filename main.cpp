#include <iostream>
#include <vector>
#include "Objects.h"
#include <string>
#include "algs.h"
#include <fstream>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3



int Alg_1(Board& game) {

    std::vector<std::pair<Board, int>> path = greedy_search(game);
    int moveNo = 0;
    for (auto& board : path) {
        std::cout << "------------------------------------------------------"<<std::endl;
        std::cout << "Move "<< moveNo++ << ": " <<"Alg_1: ";
        switch (board.second) {
        case LEFT:
            std::cout << "L" << std::endl;
            break;
        case RIGHT:
            std::cout << "R" << std::endl;
            break;
        case UP:
            std::cout << "U" << std::endl;
            break;
        case DOWN:
            std::cout << "D" << std::endl;
            break;
        default:
            std::cout << "No Move" << std::endl;
            break;
        }
        std::cout << "------------------------------------------------------"<<std::endl;
        board.first.print_board();
    }

    return path.size();
}


int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    int gameCount = 0;
    while (std::getline(inputFile, line)) {
        gameCount++;
        size_t commaPos = line.find(',');
        std::string type = line.substr(0, commaPos);
        std::string size = line.substr(commaPos + 1);
        Board board(std::stoi(type), std::stoi(size));
        std::cout<< "======================================================"<<std::endl;
        std::cout << "Game "<< gameCount << ": " << "reverse " << type<< " ("<<size<<" x " << size<< " ) - Initial Board"<< std::endl; 
        std::cout << "------------------------------------------------------"<<std::endl;
        board.print_board();
        std::cout << "------------------------------------------------------"<<std::endl;
        try {
            int size = Alg_1(board);
            int size2 = INT16_MAX;
            std::cout << "Winner: " << (size <= size2 ? "Alg_1, ":"Alg_2, " )<<"total moves "<<(size <= size2 ? size:size2 ) << std::endl;
        } catch (const std::runtime_error& e) {
            
            if(e.what() == std::string("You Win!")){
                std::cout << "Test!" << std::endl;
            }
            else if(e.what() == std::string("Maximum moves reached")){
                std::cout << "Maximum moves reached! Lose!" << std::endl;
            }
            else if(e.what() == std::string("Game Over")){
                std::cout << "Game Over" << std::endl;
            }
        }

    }
    inputFile.close();
    return 0;
}

