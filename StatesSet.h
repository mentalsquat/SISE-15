#ifndef FIFTEEN_STATESSET_H
#define FIFTEEN_STATESSET_H

#include "State.h"

class StatesSet {
public:
    unsigned int heuristic;
    std::shared_ptr<State> state;

    bool operator < (const StatesSet& rhs) const { return heuristic<rhs.heuristic; }
    bool operator > (const StatesSet& rhs) const { return heuristic>rhs.heuristic; }
};


#endif //FIFTEEN_STATESSET_H
