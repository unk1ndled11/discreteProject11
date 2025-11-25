#ifndef INDUCTION_MODULE_H
#define INDUCTION_MODULE_H

#include "Entities.h"
#include "SetsRelationsFunctions.h"

class InductionModule {
private:
    SetModule* setModule;
    RelationModule* relationModule;

public:
    InductionModule(SetModule* sm, RelationModule* rm) : setModule(sm), relationModule(rm) {}

    // 1. Weak Induction: Verify a linear chain (A -> B -> C -> D)
    // Proofs that if you start at A, you can legally reach D.
    bool proveCourseChain(SimpleVector<int>& courseChain);

    // 2. Strong Induction: Verify eligibility for a target based on COMPLETE history.
    // Proves: (Has taken 1..k) -> Can take k+1
    bool provePrerequisiteSatisfaction(int studentId, int targetCourseId);

    // Helper to print the "Proof Steps"
    void printProofStep(int step, const char* logic);
};

#endif