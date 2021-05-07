#ifndef FIFTEEN_STATE_H
#define FIFTEEN_STATE_H

#include <vector>
#include <string>
#include <memory>

#define LEFT 'L'
#define RIGHT 'R'
#define UP 'U'
#define DOWN 'D'

class State {
private:
    std::shared_ptr<State> previousState;
    std::vector<std::shared_ptr<State>> nextStates;

    unsigned int **fields;
    unsigned int height;
    unsigned int width;
    unsigned int zeroX;
    unsigned int zeroY;
    unsigned int currentDepth;

    char move;
    std::string moveOrder;
public:
    State(unsigned int **arr, unsigned int x, unsigned int y, unsigned int height, unsigned int width);
    explicit State(std::shared_ptr<State> state);
    virtual ~State() = default;

    std::shared_ptr<State> Move(char direction);
    void Swap(const std::shared_ptr<State>& state, unsigned int x, unsigned int y) const;

    bool CheckSolution() const;

    const std::shared_ptr<State> &getPreviousState() const;
    const std::vector<std::shared_ptr<State>> &getNextStates() const;
    unsigned int **getFields() const;
    unsigned int getHeight() const;
    unsigned int getWidth() const;
    unsigned int getZeroX() const;
    unsigned int getZeroY() const;
    unsigned int getCurrentDepth() const;
    char getMove() const;
    const std::string &getMoveOrder() const;

    void setZeroX(unsigned int zeroX);
    void setZeroY(unsigned int zeroY);
};


#endif //FIFTEEN_STATE_H
