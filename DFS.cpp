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
    solution->numberOfVisitedStates++;

    if(solution->maxRecursiveDepth < currentDepth)
        solution->maxRecursiveDepth = currentDepth;

    if(state->CheckSolution()) {
        solution->lengthOfSolution = state->getMoveOrder().size();
        solution->searchOrder = state->getMoveOrder();
        //initialState->PrintFields();
        //state->PrintFields();
        return true;
    } else if(currentDepth != maxPossibleDepth) {
        visited.insert({state, currentDepth});

        State* newState;
        for(char i : neighborhoodOrder) {
            if(!state->CheckIfMoveIsPossible(i))
                continue;
            solution->numberOfProcessedStates++;
            newState = state->Move(i);

            if(!CheckHistory(newState)) {
                if(Search(newState,currentDepth + 1, solution)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool DFS::CheckHistory(State *state) {
    auto it = visited.find(state);
    if (it == visited.end()) {
        return false;
    } else if (it->second > state->getCurrentDepth()) {
        it->second = state->getCurrentDepth();
        return false;
    } else {
        return true;
    }
}