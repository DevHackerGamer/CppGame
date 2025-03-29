#ifndef ALGS_H
#define ALGS_H

#include <vector>
#include "Objects.h"


// Function prototypes
int heuristic(const std::vector<std::vector<int>>& board);
std::vector<Board> get_successors(Board& game);
std::vector<Board> greedy_search(Board& game); // Greedy Best-First Search
std::vector<Board> randomMove(Board& game); //RandomMove 

#endif // ALGS_H