#ifndef FIFTEEN_ASTAR_H
#define FIFTEEN_ASTAR_H

#include <set>
#include <unordered_set>
#include "State.h"
#include "Solution.h"
#include "StatesSet.h"

class AStar {
private:
    State* initialState;
    std::multiset<StatesSet, std::less<>> openList;
    std::string heuristic;
    Solution *solution;
    const int possibleMoves = 4;
    const char directions[4] = {'L', 'U', 'R', 'D'};
    std::vector<std::vector<unsigned int>> solutionFields;
    std::unordered_set<State*> closedList;
    State *solutionState;
public:
    AStar(State* initialState, std::string heuristic, Solution *solution);

    void FindSolution();
    int HammingDistance(State* state);
    int ManhattanDistance(State* state);

    bool CheckHistory(State* state);
};


#endif //FIFTEEN_ASTAR_H
