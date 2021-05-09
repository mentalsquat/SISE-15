#include "State.h"
#include <iostream>

State::State(std::vector<std::vector<unsigned int>> arr, unsigned int x, unsigned int y, unsigned int height, unsigned int width) {
    this->fields = arr;
    this->height = height;
    this->width = width;
    this->zeroX = x;
    this->zeroY = y;
    this->moveOrder = "";
    this->currentDepth = 0;
}

State::State(State *state) {
    this->fields = state->getFields();
    this->height = state->getHeight();
    this->width = state->getWidth();
    //this->previousState = state->getPreviousState();
    this->zeroX = state->getZeroX();
    this->zeroY = state->getZeroY();
    this->moveOrder = state->getMoveOrder();
    this->currentDepth = state->currentDepth;
}

State* State::Move(char direction) {
    auto* newState = new State(this);
    newState->move = direction;
    newState->moveOrder += direction;
    newState->previousState = (this);
    newState->currentDepth = getCurrentDepth() + 1;
    switch(direction) {
        case UP:
            Swap(newState, -1, 0);
            newState->setZeroX(newState->getZeroX() - 1);
            break;
        case DOWN:
            Swap(newState, 1, 0);
            newState->setZeroX(newState->getZeroX() + 1);
            break;
        case LEFT:
            Swap(newState, 0, -1);
            newState->setZeroY(newState->getZeroY() - 1);
            break;
        case RIGHT:
            Swap(newState, 0, 1);
            newState->setZeroY(newState->getZeroY() + 1);
        default:
            break;
    }
    return newState;
}

void State::Swap(State* state, int x, int y) const {
    unsigned int tmp = state->getFields()[zeroX][zeroY];
    state->getFields()[zeroX][zeroY] = state->getFields()[zeroX + x][zeroY + y];
    state->getFields()[zeroX + x][zeroY + y] = tmp;
}

bool State::CheckIfMoveIsPossible(char d) {
    bool backFlag = true;
    bool forwardFlag = true;

    if((zeroX == 0 && d == 'U') ||
        (zeroX == height - 1 && d == 'D') ||
        (zeroY == 0 && d == 'L') ||
        (zeroY == width - 1 && d == 'R'))
        forwardFlag = false;

    if((move == 'U' && d == 'D') ||
       (move == 'D' && d == 'U') ||
       (move == 'L' && d == 'R') ||
       (move == 'R' && d == 'L'))
        backFlag = false;

    return forwardFlag == backFlag;
}

bool State::CheckSolution() const {
    for (size_t i = 0; i < height * width - 1; i++)
        if (fields[i / width][i % width] != (i + 1))
            return false;
    return true;
}

bool State::CompareToFields(State* state) {
    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++) {
            if(fields[i][j] != state->getFields()[i][j])
                return false;
        }
    }
    return true;
}

void State::PrintFields() {
    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++)
            std::cout << fields[i][j] << " ";
        std::cout << std::endl;
    }
}

void State::CopyFields(State* other) {
    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++)
            this->fields[i][j] = other->getFields()[i][j];
    }
}

void State::CopyFields(unsigned int **arr) {
    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++)
            this->fields[i][j] = arr[i][j];
    }
}

State* State::getPreviousState(){
    return previousState;
}

const std::vector<State*> &State::getNextStates() const {
    return nextStates;
}

std::vector<std::vector<unsigned int>> &State::getFields() {
    return fields;
}

unsigned int State::getHeight() const {
    return height;
}

unsigned int State::getWidth() const {
    return width;
}

unsigned int State::getZeroX() const {
    return zeroX;
}

unsigned int State::getZeroY() const {
    return zeroY;
}

unsigned int State::getCurrentDepth() const {
    return currentDepth;
}

char State::getMove() const {
    return move;
}

std::string State::getMoveOrder() {
    return moveOrder;
}

void State::setZeroX(unsigned int zeroX) {
    State::zeroX = zeroX;
}

void State::setZeroY(unsigned int zeroY) {
    State::zeroY = zeroY;
}

