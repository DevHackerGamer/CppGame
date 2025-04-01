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
std::vector<std::pair<Board, int>> get_successors(Board& game) {
    std::vector<std::pair<Board, int>> successors_direction;
    for (int direction = 0; direction < 4; ++direction) {
        Board newBoard = game; // Copy the current board
        newBoard.move(direction);
        if (newBoard != game) {
            std::pair<Board, int> tmp = {newBoard, direction}; // Only add if the board changes
            successors_direction.push_back(tmp);
        }
    }
    return successors_direction;
}

// Greedy Best-First Search
std::vector<std::pair<Board, int>> greedy_search(Board& game) {

    int moves = 0;
    std::queue<Board> queue;
    std::map<Board, std::pair<Board, int>> parent_list; // Track child, parent, and move
    std::set<Board> visited; // Track visited boards
    parent_list[game]={game, -1}; // Initialize with the starting board
    visited.insert(game); // Mark the initial board as visited
    queue.push(game);
    

    while(!queue.empty()) {
        Board current = queue.front();
        queue.pop();
        moves++;

        if (current.checkIfWin()) {
            std::vector<std::pair<Board, int>> path;
            Board temp = current;
            while (true) {

                // Find the parent and the move that led to this board

                auto it = parent_list.find(temp);
                if (it == parent_list.end()) {
                    throw std::runtime_error("Parent not found");
                }

                auto& [parent, move] = it->second;
                path.push_back({temp, move}); // Add the current board to the path
                if (temp == game) break; // Stop when we reach the starting board
                temp = parent; // Backtrack to find the parent
            }
            std::reverse(path.begin(), path.end()); // Reverse the path to get the correct order
            return path; // Return the path
        }

        // Check if we have reached the maximum number of moves

        if (moves >= 1000) {
            throw std::runtime_error("Maximum moves reached");
        }
        // Generate successors

        std::vector<std::pair<Board, int>> successors = get_successors(current);
        
        // order the successors by heuristic
        std::sort(successors.begin(), successors.end(), [](const std::pair<Board, int>& a, const std::pair<Board, int>& b) {
            return heuristic(a.first.board) < heuristic(b.first.board);
        });
        // Add the successors to the queue
        for (const auto& successor : successors) {
            if (visited.find(successor.first) == visited.end()) { // Check if not visited
                parent_list[successor.first]= {current, successor.second}; // Track the parent of this successor
                visited.insert(successor.first); // Mark as visited
            }
        }
        //add the best successor to the queue
        if (!successors.empty()) {
            queue.push(successors[0].first); // Push the best successor to the queue
        }

    }
    return {};
}

// randomMove Search
std::vector<std::pair<Board, int>> randomMove(Board& game) {
    std::vector<std::pair<Board, int>> path;
    try {
        int moves=0;
        while (moves<=1000) {
            int direction = rand() % 4; // Random direction: 0 (LEFT), 1 (RIGHT), 2 (UP), 3 (DOWN)
            game.move(direction);
            path.push_back({game, direction}); // Add the current board state and move to the path
            if(game.checkIfWin())
            {
                return path;
            }
            moves++;
        }
        if(moves==1000) return path;

    } catch (const std::runtime_error& e) {
        if (std::string(e.what()) == "Game Over") {
            // Game over, return the path generated so far
            return path;
        } else {
            // Re-throw other exceptions
            throw;
        }
    }
    return path;
}
