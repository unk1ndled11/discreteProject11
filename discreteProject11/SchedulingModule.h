#ifndef SCHEDULING_MODULE_H
#define SCHEDULING_MODULE_H

#include "Entities.h"
#include "SetsRelationsFunctions.h" // We need access to student history

class SchedulingModule {
private:
    // Stores pairs: <CourseID, PrerequisiteID>
    // Example: <102, 101> means 102 requires 101
    SimpleVector<RelationPair<int, int>> prerequisiteRules;

    SetModule* setModule;
    RelationModule* relationModule;

public:
    SchedulingModule(SetModule* sm, RelationModule* rm)
        : setModule(sm), relationModule(rm) {}

    // 1. Add a rule: courseId requires prereqId
    void addPrerequisite(int courseId, int prereqId);

    // 2. Check if a student meets prerequisites for a specific course
    bool checkPrerequisites(int studentId, int courseId);

    // 3. Suggest courses a student is eligible for next
    void suggestCoursesForStudent(int studentId);

    // 4. View all prerequisite rules
    void printPrerequisites();

    // 5. Verify chains (Recursive/Inductive check for cycles)
    bool validatePrerequisiteChain(int courseId, SimpleVector<int>& visited);
};

#endif