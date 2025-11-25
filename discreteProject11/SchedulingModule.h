#ifndef SCHEDULING_MODULE_H
#define SCHEDULING_MODULE_H

#include "Entities.h"
#include "SetsRelationsFunctions.h" 

class SchedulingModule {
private:
    // stores pairs: <course id, prereq id>
    SimpleVector<RelationPair<int, int>> prerequisiteRules;

    SetModule* setModule;
    RelationModule* relationModule;

public:
    SchedulingModule(SetModule* sm, RelationModule* rm)
        : setModule(sm), relationModule(rm) {}

    // rule add karnay wala function
    void addPrerequisite(int courseId, int prereqId);

    // check eligibility
    bool checkPrerequisites(int studentId, int courseId);

    // suggest courses
    void suggestCoursesForStudent(int studentId);

    // view rules
    void printPrerequisites();

    // verify chains
    bool validatePrerequisiteChain(int courseId, SimpleVector<int>& visited);
};

#endif