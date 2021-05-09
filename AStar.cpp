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
}

void AStar::FindSolution() {
    State *currentState = initialState;
    openList.insert({INT_MAX, initialState});

    std::multiset<StatesSet, std::less<>>::iterator it;

    while(!openList.empty()) {
        unsigned int oldPriority;
        currentState = GetLowestPriorityAndDepthState();

        if(!closedList.empty()) {
            //while(CheckHistory(currentState)) {
            while(closedList.count(currentState) != 0) {
                currentState = GetLowestPriorityAndDepthState();
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

            solution->numberOfProcessedStates++;

            unsigned int distance = (heuristic == "hamm") ? HammingDistance(newState) : ManhattanDistance(newState);
            unsigned int priority = distance + newState->getCurrentDepth();

            openList.insert({priority, newState});
        }
        closedList.insert(currentState);
        solution->numberOfVisitedStates = closedList.size();
    }
}


State * AStar::GetLowestPriorityAndDepthState() {
   std::multiset<StatesSet, std::less<>>::iterator it;
   std::multiset<StatesSet, std::less<>>::iterator tmp;
   State *state;

   unsigned int min = openList.begin()->heuristic;
   tmp = openList.begin();
   for(it = openList.begin(); it != openList.end(); it++) {
       if(it->heuristic > min)
           break;
       if(it->heuristic == min && (it->state->getCurrentDepth() < tmp->state->getCurrentDepth())) {
           tmp = it;
       }
   }

   state = tmp->state;
   openList.erase(tmp);
   return state;
}

unsigned int AStar::HammingDistance(State* state) {
    unsigned int distance = 0;
    for(size_t i = 0; i < state->getHeight(); i++)
        for(size_t j = 0; j < state->getHeight(); j++)
            if(state->getFields()[i][j] != solutionFields[i][j])
                distance++;
    return distance;
}

unsigned int AStar::ManhattanDistance(State* state) {
    unsigned int distance = 0;
    for (size_t i = 0; i < state->getHeight() * state->getHeight(); i++)
        for (size_t j = 0; j < state->getHeight() * state->getHeight(); j++)
            if(state->getFields()[i / state->getWidth()][i % state->getWidth()] == solutionFields[j / state->getWidth()][j % state->getWidth()]) {
                unsigned int ax = i % state->getWidth();
                unsigned int ay = i / state->getHeight();
                unsigned int bx = j % state->getWidth();
                unsigned int by = j / state->getHeight();
                distance += (abs(ax - bx) + abs(ay - by));
            }
    return distance;
}

bool AStar::CheckHistory(State *state) {
    for(const auto& s : closedList) {
        if(s->CompareToFields(state))
            return true;
    }
    return false;
}

