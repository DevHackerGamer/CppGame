#include <iostream>
#include <vector>
#include "Objects.h"
#include <string>
#include "algs.h"
#include <fstream>
#include <iomanip>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

std::vector<std::pair<Board, int>> Alg_1(Board& game) {
    std::vector<std::pair<Board, int>> path = greedy_search(game);
    return path;
}

std::vector<std::pair<Board, int>> Alg_2(Board& game) {
    std::vector<std::pair<Board, int>> path = randomMove(game);
    return path;
}

void printingMoves(std::vector<std::pair<Board, int>>& alg_1, std::vector<std::pair<Board, int>>& alg_2, std::ofstream& outputFile) {
    if (alg_1.empty() && alg_2.empty()) {
        outputFile << "Both algorithms have no solution." << std::endl;
        return;
    }

    int useSize = std::max(alg_1.size(), alg_2.size());
    if ((alg_1.size() == 0 && !alg_2[alg_2.size() - 1].first.checkIfWin()) || useSize == 0) {
        return;
    }

    if (alg_1.size() > 0) {
        alg_1.erase(alg_1.begin());
    }

    for (int i = 0; i < useSize; i++) {
        outputFile << "Move " << i + 1 << ": ";

        if (i < alg_1.size()) {
            outputFile << "Alg_1: ";
            switch (alg_1[i].second) {
                case LEFT: outputFile << "L"; break;
                case RIGHT: outputFile << "R"; break;
                case UP: outputFile << "U"; break;
                case DOWN: outputFile << "D"; break;
                default: outputFile << "-"; break;
            }
            outputFile << " \t\t | ";
        } else {
            outputFile << "Alg_1: (no move) \t\t| ";
        }

        if (i < alg_2.size()) {
            outputFile << "Alg_2: ";
            switch (alg_2[i].second) {
                case LEFT: outputFile << "L"; break;
                case RIGHT: outputFile << "R"; break;
                case UP: outputFile << "U"; break;
                case DOWN: outputFile << "D"; break;
                default: outputFile << "-"; break;
            }
            outputFile << std::endl;
        } else {
            outputFile << "Alg_2: (no move)" << std::endl;
        }

        outputFile << "---------------------------------------------------------------------------------------------------" << std::endl;

        int rows1 = (i < alg_1.size()) ? alg_1[i].first.board.size() : 0;
        int rows2 = (i < alg_2.size()) ? alg_2[i].first.board.size() : 0;
        int maxRows = std::max(rows1, rows2);

        for (int row = 0; row < maxRows; row++) {
            if (i < alg_1.size() && row < rows1) {
                outputFile << "| ";
                for (int col = 0; col < alg_1[i].first.board[row].size(); col++) {
                    if (alg_1[i].first.board[row][col] == 0) {
                        outputFile << std::setw(4) << "-";
                    } else {
                        outputFile << std::setw(4) << alg_1[i].first.board[row][col];
                    }
                }
            } else {
                outputFile << "|\t\t(empty)";
            }

            outputFile <<"\t\t|"<<std::setw(4);

            if (i < alg_2.size() && row < rows2) {
                for (int col = 0; col < alg_2[i].first.board[row].size(); col++) {
                    if (alg_2[i].first.board[row][col] == 0) {
                        outputFile << std::setw(4) << "-";
                    } else {
                        outputFile << std::setw(4) << alg_2[i].first.board[row][col];
                    }
                }
            } else {
                outputFile <<"\t\t(empty)";
            }

            outputFile <<"\t\t|" << std::endl;
        }
        outputFile << "---------------------------------------------------------------------------------------------------" << std::endl;

        if (i < alg_1.size() && alg_1[i].first.checkIfWin()) {
            break;
        }
        if (i < alg_2.size() && alg_2[i].first.checkIfWin()) {
            break;
        }
    }
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }

    std::ofstream outputFile("output.txt");
    if (!outputFile) {
        std::cerr << "Error: Could not open output.txt" << std::endl;
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
        Board board2 = board;

        try {
            std::string error1, error2;
            int size1, size2 = INT16_MAX;
            std::vector<std::pair<Board, int>> alg_1, alg_2;

            try {
                alg_1 = Alg_1(board);
                size1 = alg_1.size();
            } catch (const std::runtime_error& e) {
                if (e.what() == std::string("You Win!")) {
                    error1 = "Alg_1: You Win!";
                } else if (e.what() == std::string("Maximum moves reached")) {
                    error1 = "Alg_1: 1000 moves";
                } else if (e.what() == std::string("Game Over")) {
                    size1 = alg_1.size();
                    error1 = "Alg_1: Board is full";
                }
            }

            try {
                alg_2 = Alg_2(board2);
                size2 = alg_2.size();
            } catch (const std::runtime_error& e) {
                if (e.what() == std::string("You Win!")) {
                    error2 = "Alg_2 wins?";
                } else if (e.what() == std::string("Maximum moves reached_alg2")) {
                    error2 = "Alg_2: 1000 moves";
                } else if (e.what() == std::string("Game Over")) {
                    size2 = alg_2.size();
                    error2 = "Alg_2: Board is full";
                }
            }

            outputFile << "===================================================================================================" << std::endl;
            outputFile << "Game " << gameCount << ": " << "reverse " << type << " (" << size << " x " << size << " )";

            // Only print the initial board if at least one algorithm solves the game (algo_2 is only ever an error if its a win)
            if (error1.empty() && error2.empty()) {
                outputFile << " - Initial Board" << std::endl;
                outputFile << "---------------------------------------------------------------------------------------------------" << std::endl;
                for (int i = 0; i < board.board.size(); i++) {
                    outputFile << "|  ";
                    for (int j = 0; j < board.board[0].size(); j++) {
                        if (board.board[i][j] == 0) {
                            outputFile << "-\t";
                        } else {
                            outputFile << board.board[i][j] << "\t";
                        }
                    }
                    outputFile << "|" << std::endl;
                }
                outputFile << "---------------------------------------------------------------------------------------------------" << std::endl;
            }

            printingMoves(alg_1, alg_2, outputFile);
            if (error2=="Alg_2 wins?" && size2 < size1) {
                outputFile << "Winner: Alg_2, total moves: "<<size2 << std::endl;
            }
            else if (error1 == "Alg_1: Board is full" && error2 == "Alg_2: Board is full") {
                outputFile << ", draw: Both boards are full" << std::endl;
            } else if (error1 == "Alg_1: 1000 moves" && error2 == "Alg_2: 1000 moves") {
                outputFile << "Draw: Both algorithms reached 1000 moves" << std::endl;
            } else if (!error1.empty() && !error2.empty()) {
                outputFile << "Error: " << error1 << ", " << error2 << std::endl;
            } else if (!error1.empty()) {
                // Check if Alg_2 is actually a win
                if (!alg_2.empty() && alg_2.back().first.checkIfWin() && size2 < size1) {
                    outputFile << "Winner: Alg_2, total moves: " << size2 << "("<< error1<<")" << std::endl;
                } else {
                    outputFile << ", draw ("<< error1<< "| "<< (!error2.empty() ? error2 : "Alg_2: Board is full") <<") " << std::endl;
                }
            }  else {
                if (size1 < size2 && alg_1[alg_1.size() - 1].first.checkIfWin()) {
                    outputFile << "Winner: Alg_1, total moves: " << size1-1  <<" ("<<(!error2.empty() ? error2 : "Alg_2: Board is full") <<")"<< std::endl;
                } else if (size2 < size1 && alg_2[alg_2.size() - 1].first.checkIfWin()) {
                    outputFile << "Winner: Alg_2, total moves: " << size2 << std::endl;
                } else {
                    outputFile << "Winner: Alg_1, total moves: " << size1-1 <<" ("<<(!error2.empty() ? error2 : "Alg_2: Board is full") <<") "<< std::endl;
                }
            }

            outputFile << "---------------------------------------------------------------------------------------------------" << std::endl;
            outputFile << std::endl;

        } catch (const std::exception& e) {
            outputFile << "Unexpected error: " << e.what() << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();
    return 0;
}

