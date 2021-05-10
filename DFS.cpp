#include "DFS.h"

DFS::DFS(State *initialState, std::string neighborhoodOrder, Solution *solution) {
    this->initialState = initialState;
    this->neighborhoodOrder = neighborhoodOrder;
    this->solution = solution;
}

void DFS::FindSolution() {
    Search(initialState, 0, solution);
}

bool DFS::Search(State *state, int currentDepth, Solution *solution) {
    solution->numberOfProcessedStates++;

    if(solution->maxRecursiveDepth < currentDepth)
        solution->maxRecursiveDepth = currentDepth;

    if(state->CheckSolution()) {
        solution->lengthOfSolution = state->getMoveOrder().size();
        solution->searchOrder = state->getMoveOrder();
        //initialState->PrintFields();
        //state->PrintFields();
        return true;
    } else if(currentDepth != maxPossibleDepth) {
        visited.insert({state});

        State* newState;
        for(char i : neighborhoodOrder) {
            if(!state->CheckIfMoveIsPossible(i))
                continue;
            solution->numberOfVisitedStates++;
            newState = state->Move(i);

            if(visited.find(state) != visited.end()) {
                if(Search(newState,currentDepth + 1, solution)) {
                    return true;
                }
            }
        }
    }
    return false;
}
