#include "State.h"
#include <iostream>

State::State(unsigned int **arr, unsigned int x, unsigned int y, unsigned int height, unsigned int width) {
    this->fields = arr;
    this->height = height;
    this->width = width;
    this->zeroX = x;
    this->zeroY = y;
    this->moveOrder = "";
    this->currentDepth = 0;
}

State::State(std::shared_ptr<State> state) {
    this->fields = state->getFields();
    this->previousState = state->getPreviousState();
    this->zeroX = state->getZeroX();
    this->zeroY = state->getZeroY();
    this->moveOrder = state->getMoveOrder();
}

std::shared_ptr<State> State::Move(char direction) {
    std::shared_ptr<State> newState = std::make_shared<State>(static_cast<const std::shared_ptr<State>>(this));
    newState->move = direction;
    newState->moveOrder += direction;
    newState->previousState = static_cast<const std::shared_ptr<State>>(this);
    newState->currentDepth = ++currentDepth;
    switch(direction) {
        case UP:
            if((zeroY == 0) && (move == 'D')) {
                newState = nullptr;
                break;
            }
            Swap(newState, -1, 0);
            newState->setZeroX(newState->getZeroX() - 1);
            break;
        case DOWN:
            if((zeroY == height - 1) && (move == 'U')) {
                newState = nullptr;
                break;
            }
            Swap(newState, 1, 0);
            newState->setZeroX(newState->getZeroX() + 1);
            break;
        case LEFT:
            if((zeroX == 0) && (move == 'R')) {
                newState = nullptr;
                break;
            }
            Swap(newState, 0, -1);
            newState->setZeroY(newState->getZeroY() - 1);
            break;
        case RIGHT:
            if((zeroX == width - 1) && (move == 'L')) {
                newState = nullptr;
                break;
            }
            Swap(newState, 0, 1);
            newState->setZeroY(newState->getZeroY() + 1);
        default:
            break;
    }
    return newState;
}

void State::Swap(const std::shared_ptr<State>& state, unsigned int x, unsigned int y) const {
    unsigned int tmp = state->getFields()[zeroX][zeroY];
    state->getFields()[zeroX][zeroY] = state->getFields()[zeroX + x][zeroY + y];
    state->getFields()[zeroX + x][zeroY + y] = tmp;
}

bool State::CheckSolution() const {
    for (size_t i = 0; i < height * width - 1; i++)
        if (fields[i / width][i % width] != (i + 1))
            return false;
    return true;
}
const std::shared_ptr<State> &State::getPreviousState() const {
    return previousState;
}

const std::vector<std::shared_ptr<State>> &State::getNextStates() const {
    return nextStates;
}

unsigned int **State::getFields() const {
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

const std::string &State::getMoveOrder() const {
    return moveOrder;
}

void State::setZeroX(unsigned int zeroX) {
    State::zeroX = zeroX;
}

void State::setZeroY(unsigned int zeroY) {
    State::zeroY = zeroY;
}

