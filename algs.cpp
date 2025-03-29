#include <vector>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include "Objects.h"
#include <set>
#include <map>
#include <functional> // For std::hash
#include <unordered_map>
#include "algs.h"


struct BoardHash {
    std::size_t operator()(const Board& board) const {
        std::size_t hash = 0;
        for (const auto& row : board.board) {
            for (int cell : row) {
                hash ^= std::hash<int>()(cell) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            }
        }
        return hash;
    }
};

// Heuristic: Prefer states with more empty tiles
// int heuristic(const std::vector<std::vector<int>>& board) {
//     int empty_count = 0;
//     for (const auto& row : board) {
//         for (int cell : row) {
//             if (cell == 0) empty_count++;
//         }
//     }
//     return -empty_count; // More empty tiles is better
// }

// Heuristic: Prefer states with fewer `2`s
int heuristic(const std::vector<std::vector<int>>& board) {
    int empty_count = 0;
    int score = 0;

    // Count empty tiles and calculate a score based on tile values
    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == 0) {
                empty_count++;
            } else {
                // Add the value of the tile to the score
                score += board[i][j];
            }
        }
    }

    // Higher score for more empty tiles and higher tile values
    return -empty_count + score;
}

// Generate new possible board states
std::vector<Board> get_successors(Board& game) {
    std::vector<Board> successors;
    for (int direction = 0; direction < 4; ++direction) {
        Board newBoard = game; // Copy the current board
        newBoard.move(direction);
        if (newBoard != game) { // Only add if the board changes
            successors.push_back(newBoard);
        }
    }
    return successors;
}
Board find_parent(const std::vector<std::pair<Board, Board>>& parent_list, const Board& child) {
    for (const auto& pair : parent_list) {
        if (pair.first == child) {
            return pair.second;
        }
    }
    throw std::runtime_error("Parent not found");
}

// Greedy Best-First Search
std::vector<Board> greedy_search(Board& game) {

    int moves = 0;
    std::queue<Board> queue;
    std::vector<std::pair<Board, Board>> parent_list; // Track parent-child relationships
    std::unordered_set<Board, BoardHash> visited; // Track visited boards
    parent_list.push_back({game, game}); // Initialize with the starting board
    visited.insert(game); // Mark the initial board as visited
    queue.push(game);
    

    while(!queue.empty()) {
        Board current = queue.front();
        queue.pop();
        moves++;

        if (current.checkIfWin()) {
            std::cout << "You Win!" << std::endl;

            std::vector<Board> path;
            Board temp = current;
            while (true) {
                path.push_back(temp);
                if (temp == game) break; // Stop when we reach the starting board
                temp = find_parent(parent_list, temp); // Backtrack to find the parent
            }
            std::reverse(path.begin(), path.end()); // Reverse the path to get the correct order
            return path;
        }

        // Check if we have reached the maximum number of moves

        if (moves >= 1000) {
            std::cout << "Maximum moves reached! Lose!" << std::endl;
            break;
        }
        // Generate successors

        std::vector<Board> successors = get_successors(current);
        // if(moves<=10){
        //     std::cout << "Generated successors for current board:\n";
        //     for (auto& successor : successors) {
        //         std::cout << "Successor board:\n";
        //         successor.print_board();
        //     }
        // }

        // if moves == 10, print the path to current board
        if (moves == 10) {
            std::cout << "Path to current board:\n";
        
            // Reconstruct the path from the starting board to the current board
            std::vector<Board> path;
            Board temp = current;
            while (true) {
                path.push_back(temp);
                if (temp == game) break; // Stop when we reach the starting board
                temp = find_parent(parent_list, temp); // Backtrack to find the parent
            }
            std::reverse(path.begin(), path.end()); // Reverse the path to get the correct order
        
            // Print the reconstructed path
            for (auto& board : path) {
                board.print_board();
                std::cout << "-------------------------\n";
            }
        }


        // order the successors by heuristic
        std::sort(successors.begin(), successors.end(), [](const Board& a, const Board& b) {
            return heuristic(a.board) < heuristic(b.board);
        });
        // Add the successors to the queue
        for (const auto& successor : successors) {
            if (visited.find(successor) == visited.end()) { // Check if not visited
                parent_list.push_back({successor, current}); // Track the parent of this successor
                visited.insert(successor); // Mark as visited
            }
        }
        //add the best successor to the queue
        if (!successors.empty()) {
            queue.push(successors[0]); // Push the best successor to the queue
        }

    }
    return {};
}

// A* Search
std::vector<Board> a_star(Board& game) {
    return std::vector<Board>(); // Placeholder for A* search implementation
}
