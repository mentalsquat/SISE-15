#include <algorithm>
#include <iostream>
#include "AStar.h"

AStar::AStar(State* initialState, std::string heuristic, Solution *solution) : initialState(initialState), heuristic(heuristic),
                                                                                               solution(solution) {
    solutionFields.resize(initialState->getHeight());
    for(size_t i = 0; i < initialState->getHeight(); i++) {
        solutionFields[i] = std::vector<unsigned int>(initialState->getWidth());
        for(size_t j = 0; j < initialState->getWidth(); j++) {
            solutionFields[i][j] = i * initialState->getHeight() + j + 1;
        }
    }
    solutionFields[initialState->getHeight() - 1][initialState->getWidth() - 1] = 0;
    solutionState = new State(solutionFields,initialState->getHeight(), initialState->getWidth(),initialState->getHeight(), initialState->getWidth());
}

void AStar::FindSolution() {
    State *currentState;
    openList.insert({(float) INT_MAX, initialState});

    while(!openList.empty()) {
        currentState = openList.begin()->state;
        openList.erase(openList.begin());

        if(!closedList.empty()) {
            while(closedList.count(currentState) != 0) {
                currentState = openList.begin()->state;
                openList.erase(openList.begin());
            }
        }

        if(solution->maxRecursiveDepth < currentState->getCurrentDepth())
            solution->maxRecursiveDepth = currentState->getCurrentDepth();

        if(currentState->CheckSolution()) {
            solution->lengthOfSolution = (int) currentState->getMoveOrder().length();
            solution->searchOrder = currentState->getMoveOrder();
            //initialState->PrintFields();
            //currentState->PrintFields();
            break;
        }

        State* newState;
        for(int i = 0; i < possibleMoves; i++) {
            if(!currentState->CheckIfMoveIsPossible(directions[i]))
                continue;
            newState = currentState->Move(directions[i]);

            solution->numberOfVisitedStates++;

            int distance = (heuristic == "hamm") ? HammingDistance(newState) : ManhattanDistance(newState);
            float priority = distance * (1.0 + 1/10.0) + newState->getCurrentDepth();

            openList.insert({priority, newState});
        }
        closedList.insert(currentState);
        solution->numberOfProcessedStates++;
    }
}

int AStar::HammingDistance(State* state) {
    int distance = 0;
    for(size_t i = 0; i < state->getHeight(); i++)
        for(size_t j = 0; j < state->getWidth(); j++)
            if(state->getFields()[i][j] != solutionFields[i][j])
                distance++;
    return distance;
}

int AStar::ManhattanDistance(State* state) {
    int distance = 0;
    for(size_t i = 0; i < state->getHeight() ; i++) {
        for(size_t j = 0; j < state->getWidth(); j++) {
            unsigned int temp = state->getFields()[i][j];
            if(temp != 0 && temp != solutionFields[i][j]) {
                auto node = state->GetIndexOf(temp);
                auto goal = solutionState->GetIndexOf(temp);

                distance += abs(node.first - goal.first) + abs(node.second - goal.second);
            }
        }
    }
    return distance;
}
