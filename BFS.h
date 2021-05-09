#ifndef FIFTEEN_BFS_H
#define FIFTEEN_BFS_H

#include <string>
#include "Solution.h"
#include "State.h"

class BFS {
private:
    Solution *solution;
    State *initialState;
    std::string neighborhoodOrder;
    const int possibleMoves = 4;
public:
    BFS(State *initialState, std::string neighborhoodOrder, Solution *solution);

    void FindSolution();
    //bool CheckHistory(State* state, std::vector<State*> visited);
};


#endif //FIFTEEN_BFS_H
