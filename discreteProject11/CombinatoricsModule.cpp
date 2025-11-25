#include "CombinatoricsModule.h"
#include <iostream>
#include <iomanip>

using namespace std;

// factorial
unsigned long long CombinatoricsModule::factorial(int n) {
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;
    if (n > 20) {
        cout << " warning: n too large.\n";
    }

    unsigned long long res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

// permutations
unsigned long long CombinatoricsModule::calculatePermutations(int n, int r) {
    if (r < 0 || r > n) return 0;
    unsigned long long res = 1;
    for (int i = 0; i < r; i++) {
        res *= (n - i);
    }
    return res;
}

// combinations
unsigned long long CombinatoricsModule::calculateCombinations(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r;

    unsigned long long res = 1;
    for (int i = 1; i <= r; i++) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

// recursive generator
void CombinatoricsModule::generateCombinationRecursive(SimpleVector<Student*>& allStudents,
    SimpleVector<Student*>& currentGroup,
    int start, int r) {

    // base case
    if (currentGroup.getSize() == r) {
        cout << "  group: { ";
        for (int i = 0; i < r; i++) {
            if (i > 0) cout << ", ";
            cout << currentGroup[i]->name;
        }
        cout << " }" << endl;
        return;
    }

    // loop
    for (int i = start; i < allStudents.getSize(); i++) {
        currentGroup.push_back(allStudents[i]);
        generateCombinationRecursive(allStudents, currentGroup, i + 1, r);
        currentGroup.remove(currentGroup.getSize() - 1);
    }
}

void CombinatoricsModule::generateStudentGroups(int groupSize) {
    SimpleVector<int> ids = setModule->getAllStudentIDs();
    SimpleVector<Student*> studentPtrs;

    for (int i = 0; i < ids.getSize(); i++) {
        studentPtrs.push_back(setModule->findStudent(ids[i]));
    }

    int n = studentPtrs.getSize();
    int r = groupSize;

    cout << "\n=== generating groups ===\n";
    unsigned long long totalWays = calculateCombinations(n, r);
    cout << "total possible groups: " << totalWays << endl;
    cout << "listing all possibilities:\n";

    SimpleVector<Student*> tempGroup;
    generateCombinationRecursive(studentPtrs, tempGroup, 0, r);
}