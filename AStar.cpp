#include "AStar.h"

AStar::AStar(std::shared_ptr<State> initialState, std::string heuristic, Solution &solution) : initialState(initialState), heuristic(heuristic),
                                                                                              solution(solution) {}

std::shared_ptr<State> AStar::FindSolution() {
    std::vector<std::shared_ptr<State>> closedList;
    std::shared_ptr<State> currentState;

    openList.insert({INT_MAX, initialState});
    while(!openList.empty()) {

    }
}