#ifndef FIFTEEN_STATESSET_H
#define FIFTEEN_STATESSET_H

#include "State.h"

class StatesSet {
public:
    float heuristic;
    State* state;

    bool operator < (const StatesSet& rhs) const { return heuristic<rhs.heuristic; }
    bool operator > (const StatesSet& rhs) const { return heuristic>rhs.heuristic; }
};


#endif //FIFTEEN_STATESSET_H
