#ifndef COMBINATORICS_MODULE_H
#define COMBINATORICS_MODULE_H

#include "Entities.h"
#include "SetsRelationsFunctions.h" 

class CombinatoricsModule {
private:
    SetModule* setModule;

    // recursive helper
    void generateCombinationRecursive(SimpleVector<Student*>& allStudents,
        SimpleVector<Student*>& currentGroup,
        int start, int r);

public:
    CombinatoricsModule(SetModule* sm) : setModule(sm) {}

    // factorial logic
    unsigned long long factorial(int n);

    // permutation logic
    unsigned long long calculatePermutations(int n, int r);

    // combination logic
    unsigned long long calculateCombinations(int n, int r);

    // group generation
    void generateStudentGroups(int groupSize);
};

#endif