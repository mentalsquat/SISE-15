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
    Solution *solution;
    const int possibleMoves = 4;
    const char directions[4] = {'L', 'R', 'U', 'D'};
    std::vector<std::vector<unsigned int>> solutionFields;
    std::vector<std::shared_ptr<State>> closedList;
public:
    AStar(std::shared_ptr<State> initialState, std::string heuristic, Solution *solution);

    void FindSolution(std::shared_ptr<State> currentState);
    unsigned int HammingDistance(std::shared_ptr<State> state);
    unsigned int ManhattanDistance(std::shared_ptr<State> state);

    bool CheckHistory(std::shared_ptr<State> state, std::vector<std::shared_ptr<State>> visited);
};


#endif //FIFTEEN_ASTAR_H
