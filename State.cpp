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
    this->zeroX = state->getZeroX();
    this->zeroY = state->getZeroY();
    this->moveOrder = state->getMoveOrder();
    this->currentDepth = state->currentDepth;
}

State* State::Move(char direction) {
    auto* newState = new State(this);
    newState->move = direction;
    newState->moveOrder += direction;
    newState->currentDepth = getCurrentDepth() + 1;
    switch(direction) {
        case UP:
            Swap(newState, -1, 0);
            break;
        case DOWN:
            Swap(newState, 1, 0);
            break;
        case LEFT:
            Swap(newState, 0, -1);
            break;
        case RIGHT:
            Swap(newState, 0, 1);
        default:
            break;
    }
    return newState;
}

void State::Swap(State* state, int x, int y) const {
    unsigned int tmp = state->getFields()[zeroX][zeroY];
    state->getFields()[zeroX][zeroY] = state->getFields()[zeroX + x][zeroY + y];
    state->getFields()[zeroX + x][zeroY + y] = tmp;
    state->setZeroX(state->getZeroX() + x);
    state->setZeroY(state->getZeroY() + y);
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

std::pair<unsigned int, unsigned int> State::GetIndexOf(int value) {
    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++) {
            if(fields[i][j] == value)
                return std::make_pair(i,j);
        }
    }
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

