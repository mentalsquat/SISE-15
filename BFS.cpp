#include <deque>
#include <iostream>
#include <unordered_set>
#include "BFS.h"


BFS::BFS(State *initialState, std::string neighborhoodOrder, Solution *solution) {
    this->initialState = initialState;
    this->neighborhoodOrder = neighborhoodOrder;
    this->solution = solution;
}

void BFS::FindSolution() {
    std::deque<State*> frontier;
    //std::vector<State*> visited;
    std::unordered_set<State*> visited;

    frontier.push_back(initialState);
    while(!frontier.empty()) {
        State *currentState = frontier.front();
        visited.insert(currentState);
        frontier.pop_front();

        if(solution->maxRecursiveDepth < currentState->getCurrentDepth())
            solution->maxRecursiveDepth = currentState->getCurrentDepth();

        if(currentState->CheckSolution()) {
            solution->lengthOfSolution = currentState->getMoveOrder().size();
            solution->searchOrder = currentState->getMoveOrder();
            solution->numberOfProcessedStates = visited.size();
            solution->numberOfVisitedStates = visited.size() + frontier.size();
            break;
        }

        State* newState;
        for(char i : neighborhoodOrder) {
            if(!currentState->CheckIfMoveIsPossible(i))
                continue;
            newState = currentState->Move(i);

            if(visited.count(currentState) != 0)
                frontier.push_back(newState);
        }

    }
}

//bool BFS::CheckHistory(State* state, std::vector<State*> visited) {
//    for(const auto& s : visited) {
//        if(s->CompareToFields(state))
//            return true;
//    }
//    return false;
//}

