#ifndef ALGS_H
#define ALGS_H

#include <vector>
#include "Objects.h"


// Function prototypes
int heuristic(const std::vector<std::vector<int>>& board);
std::vector<std::pair<Board, int>> get_successors(Board& game);
std::vector<std::pair<Board, int>> greedy_search(Board& game); // Greedy Best-First Search
std::vector<std::pair<Board, int>> randomMove(Board& game);

#endif // ALGS_H