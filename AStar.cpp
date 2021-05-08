#include <algorithm>
#include <iostream>
#include "AStar.h"

AStar::AStar(std::shared_ptr<State> initialState, std::string heuristic, Solution *solution) : initialState(initialState), heuristic(heuristic),
                                                                                               solution(solution) {
    solutionFields.resize(initialState->getHeight());
    for(size_t i = 0; i < initialState->getHeight(); i++) {
        solutionFields[i] = std::vector<unsigned int>(initialState->getWidth());
        for(size_t j = 0; j < initialState->getWidth(); j++) {
            solutionFields[i][j] = i + 1;
        }
    }
    solutionFields[initialState->getHeight() - 1][initialState->getWidth() - 1] = 0;
}

void AStar::FindSolution(std::shared_ptr<State> currentState) {
    currentState = initialState;

    openList.insert({INT_MAX, initialState});
    auto it = openList.begin();
    while(!openList.empty()) {
        it = openList.begin();
        currentState = it->state;
        openList.erase(openList.begin());

        if(!closedList.empty()) {
            while(!CheckHistory(currentState, closedList)) {
                currentState = it->state;
                openList.erase(openList.begin());
            }
        }

        if(solution->maxRecursiveDepth < currentState->getCurrentDepth())
            solution->maxRecursiveDepth = currentState->getCurrentDepth();

        if(currentState->CheckSolution()) {
//            //solution->lengthOfSolution = (int) currentState->getMoveOrder().length();
//            currentState->PrintFields();
//            std::shared_ptr<State> n = currentState;
//            return n;
            break;
        }


        std::shared_ptr<State> newState;
        for(int i = 0; i < possibleMoves; i++) {
            if(!currentState->CheckIfMoveIsPossible(directions[i]))
                continue;
            newState = currentState->Move(directions[i]);

            solution->numberOfProcessedStates++;

            unsigned int distance = (heuristic == "hamm") ? HammingDistance(newState) : ManhattanDistance(newState);
            unsigned int priority = distance * newState->getCurrentDepth();

            openList.insert({priority, newState});
        }
        closedList.push_back(currentState);
        solution->numberOfVisitedStates = closedList.size();
    }
    return ;
}

unsigned int AStar::HammingDistance(std::shared_ptr<State> state) {
    unsigned int distance = 0;
    for(size_t i = 0; i < state->getHeight(); i++)
        for(size_t j = 0; j < state->getHeight(); j++)
            if(state->getFields()[i][j] != solutionFields[i][j])
                distance++;
    return distance;
}

unsigned int AStar::ManhattanDistance(std::shared_ptr<State> state) {
    return 1;
}

bool AStar::CheckHistory(std::shared_ptr<State> state, std::vector<std::shared_ptr<State>> visited) {
    for(const auto& s : visited) {
        if(s->CompareToFields(state))
            return false;
    }
    return true;
}



