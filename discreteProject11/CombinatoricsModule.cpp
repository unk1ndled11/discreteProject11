#include "CombinatoricsModule.h"
#include <iostream>
#include <iomanip>

using namespace std;

// 1. Factorial (Iterative for safety)
unsigned long long CombinatoricsModule::factorial(int n) {
    if (n < 0) return 0; // Error
    if (n == 0 || n == 1) return 1;
    if (n > 20) {
        cout << " [Warning] n is too large for standard integer math. Result may overflow.\n";
    }

    unsigned long long res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

// 2. Permutations P(n, r)
unsigned long long CombinatoricsModule::calculatePermutations(int n, int r) {
    if (r < 0 || r > n) return 0;
    // P(n,r) = n! / (n-r)!
    // Optimization: We can just multiply n * (n-1) * ... * (n-r+1)
    unsigned long long res = 1;
    for (int i = 0; i < r; i++) {
        res *= (n - i);
    }
    return res;
}

// 3. Combinations C(n, r)
unsigned long long CombinatoricsModule::calculateCombinations(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r; // Optimization: C(n, r) == C(n, n-r)

    unsigned long long res = 1;
    for (int i = 1; i <= r; i++) {
        // Multiply by (n - i + 1) and divide by i
        // Doing it in this loop prevents massive overflows of n!
        res = res * (n - i + 1) / i;
    }
    return res;
}

// 4. Recursive Generator
void CombinatoricsModule::generateCombinationRecursive(SimpleVector<Student*>& allStudents,
    SimpleVector<Student*>& currentGroup,
    int start, int r) {
    // Base Case: If currentGroup size equals 'r', we found a valid group!
    if (currentGroup.getSize() == r) {
        cout << "  Group: { ";
        for (int i = 0; i < r; i++) {
            if (i > 0) cout << ", ";
            cout << currentGroup[i]->name;
        }
        cout << " }" << endl;
        return;
    }

    // Recursive Step: Loop through remaining students
    for (int i = start; i < allStudents.getSize(); i++) {
        // 1. Add Student i to the group
        currentGroup.push_back(allStudents[i]);

        // 2. Recurse for the next student
        generateCombinationRecursive(allStudents, currentGroup, i + 1, r);

        // 3. Backtrack: Remove Student i to try the next possibility
        // (Our SimpleVector needs a pop_back or remove last logic)
        currentGroup.remove(currentGroup.getSize() - 1);
    }
}

void CombinatoricsModule::generateStudentGroups(int groupSize) {
    // 1. Get All Students
    SimpleVector<int> ids = setModule->getAllStudentIDs();
    SimpleVector<Student*> studentPtrs;

    // Convert IDs to Pointers for easier printing
    for (int i = 0; i < ids.getSize(); i++) {
        studentPtrs.push_back(setModule->findStudent(ids[i]));
    }

    int n = studentPtrs.getSize();
    int r = groupSize;

    cout << "\n=== GENERATING GROUPS (" << n << " Choose " << r << ") ===\n";
    unsigned long long totalWays = calculateCombinations(n, r);
    cout << "Total Possible Groups: " << totalWays << endl;
    cout << "Listing all possibilities:\n";

    SimpleVector<Student*> tempGroup;
    generateCombinationRecursive(studentPtrs, tempGroup, 0, r);
}