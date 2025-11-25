#include "InductionModule.h"
#include <iostream>
#include <iomanip>

using namespace std;

void InductionModule::printProofStep(int step, const char* logic) {
    cout << "  [step " << step << "] " << logic << endl;
}

// weak induction
bool InductionModule::proveCourseChain(SimpleVector<int>& courseChain) {
    if (courseChain.getSize() == 0) return false;

    cout << "\n=== inductive proof of chain ===\n";
    cout << "hypothesis: valid progression.\n";

    // base case
    int firstId = courseChain[0];
    Course* first = setModule->findCourse(firstId);
    if (!first) {
        printProofStep(1, "base case failed: course missing.");
        return false;
    }
    cout << "  [base case] course " << first->code << " starts chain. (true)\n";

    // inductive step
    for (int k = 0; k < courseChain.getSize() - 1; k++) {
        int currentId = courseChain[k];
        int nextId = courseChain[k + 1];

        Course* curr = setModule->findCourse(currentId);
        Course* next = setModule->findCourse(nextId);

        bool linkFound = false;
        SimpleVector<int>& prereqs = next->prerequisiteIDs;
        for (int i = 0; i < prereqs.getSize(); i++) {
            if (prereqs[i] == currentId) {
                linkFound = true;
                break;
            }
        }

        if (linkFound) {
            cout << "  [step " << k + 1 << "] " << curr->code
                << " implies " << next->code << ". (true)\n";
        }
        else {
            cout << "  [step " << k + 1 << "] failed: " << curr->code
                << " is not prereq for " << next->code << ".\n";
            cout << "  [conclusion] broken chain.\n";
            return false;
        }
    }

    cout << "  [conclusion] chain is valid.\n";
    return true;
}

// strong induction
bool InductionModule::provePrerequisiteSatisfaction(int studentId, int targetCourseId) {
    cout << "\n=== strong induction proof ===\n";

    Course* target = setModule->findCourse(targetCourseId);
    if (!target) { cout << "  error: invalid course.\n"; return false; }

    SimpleVector<int>& requiredIds = target->prerequisiteIDs;

    // base case
    if (requiredIds.getSize() == 0) {
        cout << "  [base case] " << target->code << " has no prereqs. eligible.\n";
        return true;
    }

    cout << "  goal: prove student " << studentId << " has all prereqs for " << target->code << ".\n";

    SimpleVector<RelationPair<int, int>>* history = relationModule->getRawStudentCourseData();
    bool allMet = true;

    // loop
    for (int i = 0; i < requiredIds.getSize(); i++) {
        int reqId = requiredIds[i];
        Course* reqCourse = setModule->findCourse(reqId);

        bool found = false;
        for (int j = 0; j < history->getSize(); j++) {
            if ((*history)[j].a == studentId && (*history)[j].b == reqId) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << "  [step " << i + 1 << "] prereq ";
            if (reqCourse) cout << reqCourse->code; else cout << "unknown";
            cout << " found. (true)\n";
        }
        else {
            cout << "  [step " << i + 1 << "] failed: missing prereq ";
            if (reqCourse) cout << reqCourse->code; else cout << "unknown";
            cout << ".\n";
            allMet = false;
        }
    }

    if (allMet) {
        cout << "  [conclusion] eligible.\n";
        return true;
    }
    else {
        cout << "  [conclusion] eligibility denied.\n";
        return false;
    }
}