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
    std::vector<Board> successors;
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
Board find_parent(const std::vector<std::pair<Board, Board>>& parent_list, const Board& child) {
    for (const auto& pair : parent_list) {
        if (pair.first == child) {
            return pair.second;
        }
    }
    throw std::runtime_error("Parent not found");
}

// Greedy Best-First Search
std::vector<std::pair<Board, int>> greedy_search(Board& game) {

    int moves = 0;
    std::queue<Board> queue;
    std::vector<std::tuple<Board, Board, int>> parent_list; // Track child, parent, and move
    std::unordered_set<Board, BoardHash> visited; // Track visited boards
    parent_list.push_back({game, game, -1}); // Initialize with the starting board
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
                auto it = std::find_if(parent_list.begin(), parent_list.end(),
                                       [&temp](const std::tuple<Board, Board, int>& entry) {
                                           return std::get<0>(entry) == temp; // Match the child board
                                       });
                if (it == parent_list.end()) {
                    throw std::runtime_error("Parent not found");
                }
                Board parent = std::get<1>(*it);
                int move = std::get<2>(*it);
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
                parent_list.push_back({successor.first, current, successor.second}); // Track the parent of this successor
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

// A* Search
std::vector<Board> a_star(Board& game) {
    return std::vector<Board>(); // Placeholder for A* search implementation
}
