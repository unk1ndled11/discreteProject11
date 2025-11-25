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

    // weak induction logic
    bool proveCourseChain(SimpleVector<int>& courseChain);

    // strong induction logic
    bool provePrerequisiteSatisfaction(int studentId, int targetCourseId);

    // helper
    void printProofStep(int step, const char* logic);
};

#endif