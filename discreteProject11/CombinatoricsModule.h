#ifndef COMBINATORICS_MODULE_H
#define COMBINATORICS_MODULE_H

#include "Entities.h"
#include "SetsRelationsFunctions.h" // To access the list of students

class CombinatoricsModule {
private:
    SetModule* setModule;

    // Recursive helper to actually print the groups
    void generateCombinationRecursive(SimpleVector<Student*>& allStudents,
        SimpleVector<Student*>& currentGroup,
        int start, int r);

public:
    CombinatoricsModule(SetModule* sm) : setModule(sm) {}

    // 1. Factorial Calculation (n!)
    unsigned long long factorial(int n);

    // 2. Calculate Number of Ways (The Math Formulas)
    unsigned long long calculatePermutations(int n, int r);
    unsigned long long calculateCombinations(int n, int r);

    // 3. Generate and View Actual Groups
    void generateStudentGroups(int groupSize);
};

#endif