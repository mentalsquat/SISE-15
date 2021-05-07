#ifndef FIFTEEN_SOLUTION_H
#define FIFTEEN_SOLUTION_H

typedef struct Solution {
    unsigned int lengthOfSolution = -1;
    std::string searchOrder = "";
    int numberOfVisitedStates = 0;
    int numberOfProcessedStates = 0;
    int maxRecursiveDepth = 0;
    float elapsedTime = 0.0f;
} Solution;


#endif //FIFTEEN_SOLUTION_H
