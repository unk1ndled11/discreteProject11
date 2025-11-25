#include "InductionModule.h"
#include <iostream>
#include <iomanip>

using namespace std;

void InductionModule::printProofStep(int step, const char* logic) {
    cout << "  [Step " << step << "] " << logic << endl;
}

// === WEAK INDUCTION ===
// Scenario: A student wants to take a chain of courses in order: [101, 102, 103]
// We prove P(n) is valid for all n in the chain.
bool InductionModule::proveCourseChain(SimpleVector<int>& courseChain) {
    if (courseChain.getSize() == 0) return false;

    cout << "\n=== INDUCTIVE PROOF OF COURSE CHAIN ===\n";
    cout << "Hypothesis: The sequence of courses is a valid progression.\n";

    // 1. BASE CASE: Can we start?
    // The first course must have NO prerequisites, or prerequisites must be assumed 'met' for the chain to start.
    // For this module, we assume the Base Case is the first course itself exists.
    int firstId = courseChain[0];
    Course* first = setModule->findCourse(firstId);
    if (!first) {
        printProofStep(1, "Base Case FAILED: First course does not exist.");
        return false;
    }
    cout << "  [Base Case] Course " << first->code << " exists and starts the chain. (True)\n";

    // 2. INDUCTIVE STEP: P(k) -> P(k+1)
    // Does Course K actually satisfy the requirements for Course K+1?
    for (int k = 0; k < courseChain.getSize() - 1; k++) {
        int currentId = courseChain[k];
        int nextId = courseChain[k + 1];

        Course* curr = setModule->findCourse(currentId);
        Course* next = setModule->findCourse(nextId);

        // Check if 'next' actually lists 'curr' as a prerequisite
        // We look inside the 'next' course's adjacency list
        bool linkFound = false;
        SimpleVector<int>& prereqs = next->prerequisiteIDs;
        for (int i = 0; i < prereqs.getSize(); i++) {
            if (prereqs[i] == currentId) {
                linkFound = true;
                break;
            }
        }

        if (linkFound) {
            cout << "  [Inductive Step " << k + 1 << "] " << curr->code
                << " implies eligibility for " << next->code << ". (True)\n";
        }
        else {
            cout << "  [Inductive Step " << k + 1 << "] FAILED: " << curr->code
                << " is NOT a prerequisite for " << next->code << ".\n";
            cout << "  [Conclusion] The chain is broken.\n";
            return false;
        }
    }

    cout << "  [Conclusion] By Mathematical Induction, the entire chain is valid.\n";
    return true;
}

// === STRONG INDUCTION ===
// Scenario: Proving a student is ready for a course by checking ALL history.
// P(n) is true if P(1) AND P(2) AND ... P(n-1) are true.
bool InductionModule::provePrerequisiteSatisfaction(int studentId, int targetCourseId) {
    cout << "\n=== STRONG INDUCTION PROOF FOR ELIGIBILITY ===\n";

    Course* target = setModule->findCourse(targetCourseId);
    if (!target) { cout << "  [Error] Invalid Course.\n"; return false; }

    SimpleVector<int>& requiredIds = target->prerequisiteIDs;

    // Base Case: If there are no prerequisites, it's vacuously true.
    if (requiredIds.getSize() == 0) {
        cout << "  [Base Case] " << target->code << " has no prerequisites. Eligibility is TRUE.\n";
        return true;
    }

    cout << "  Goal: Prove Student " << studentId << " satisfies ALL prerequisites for " << target->code << ".\n";

    // Access student history
    SimpleVector<RelationPair<int, int>>* history = relationModule->getRawStudentCourseData();
    bool allMet = true;

    // Strong Induction Loop
    for (int i = 0; i < requiredIds.getSize(); i++) {
        int reqId = requiredIds[i];
        Course* reqCourse = setModule->findCourse(reqId);

        // Search history for this specific requirement
        bool found = false;
        for (int j = 0; j < history->getSize(); j++) {
            if ((*history)[j].a == studentId && (*history)[j].b == reqId) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << "  [Step " << i + 1 << "] Prerequisite " << (reqCourse ? reqCourse->code : "Unknown")
                << " found in history. (True)\n";
        }
        else {
            cout << "  [Step " << i + 1 << "] FAILED: Missing Prerequisite "
                << (reqCourse ? reqCourse->code : "Unknown") << ".\n";
            allMet = false;
        }
    }

    if (allMet) {
        cout << "  [Conclusion] By Strong Induction (All P(k) met), student is eligible.\n";
        return true;
    }
    else {
        cout << "  [Conclusion] Proof Failed. Eligibility denied.\n";
        return false;
    }
}