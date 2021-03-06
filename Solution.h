#ifndef FIFTEEN_SOLUTION_H
#define FIFTEEN_SOLUTION_H

typedef struct Solution {
    int lengthOfSolution = -1;
    std::string searchOrder;
    unsigned int numberOfVisitedStates = 0;
    unsigned int numberOfProcessedStates = 0;
    unsigned int maxRecursiveDepth = 0;
    double elapsedTime = 0.0;
} Solution;


#endif //FIFTEEN_SOLUTION_H
