#ifndef FIFTEEN_ASTAR_H
#define FIFTEEN_ASTAR_H

#include <set>
#include "State.h"
#include "Solution.h"
#include "StatesSet.h"

class AStar {
private:
    std::shared_ptr<State> initialState;
    std::multiset<StatesSet, std::less<>> openList;
    std::string heuristic;
    Solution solution;
public:
    AStar(std::shared_ptr<State> initialState, std::string heuristic, Solution &solution);

    std::shared_ptr<State> FindSolution();
    unsigned int HammingDistance(std::shared_ptr<State> state);
};


#endif //FIFTEEN_ASTAR_H
