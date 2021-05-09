#ifndef FIFTEEN_DFS_H
#define FIFTEEN_DFS_H

#include <unordered_map>
#include "State.h"
#include "Solution.h"

class DFS {
private:
    std::unordered_map<State*, int> visited;
    Solution *solution;
    State *initialState;
    std::string neighborhoodOrder;
    const int maxPossibleDepth = 20;
public:
    DFS(State *initialState, std::string neighborhoodOrder, Solution *solution);
    ~DFS() = default;

    void FindSolution();
    bool Search(State *state, int currentDepth, Solution *solution);

    bool CheckHistory(State *state);
};


#endif //FIFTEEN_DFS_H
