#include "SchedulingModule.h"
#include <iostream>
#include <iomanip>

using namespace std;

void SchedulingModule::addPrerequisite(int courseId, int prereqId) {
    Course* target = setModule->findCourse(courseId);
    Course* required = setModule->findCourse(prereqId);

    if (target && required) {
        // graph edge addition
        target->prerequisiteIDs.push_back(prereqId);

        // local list tracking
        prerequisiteRules.push_back(RelationPair<int, int>(courseId, prereqId));

        cout << " ok: rule added: " << target->code << " requires " << required->code << endl;
    }
    else {
        cout << " error: invalid course ids." << endl;
    }
}

bool SchedulingModule::checkPrerequisites(int studentId, int courseId) {
    Course* target = setModule->findCourse(courseId);
    if (!target) {
        cout << " error: course not found." << endl;
        return false;
    }

    bool allMet = true;

    // graph traversal
    SimpleVector<int>& prereqs = target->prerequisiteIDs;

    for (int i = 0; i < prereqs.getSize(); i++) {
        int requiredId = prereqs[i];

        // check history
        bool taken = false;
        SimpleVector<RelationPair<int, int>>* history = relationModule->getRawStudentCourseData();

        for (int j = 0; j < history->getSize(); j++) {
            if ((*history)[j].a == studentId && (*history)[j].b == requiredId) {
                taken = true;
                break;
            }
        }

        if (!taken) {
            Course* c = setModule->findCourse(requiredId);
            cout << " missing prereq: ";
            if (c) {
                cout << c->code;
            }
            else {
                cout << "unknown";
            }
            cout << endl;
            allMet = false;
        }
    }
    return allMet;
}

void SchedulingModule::suggestCoursesForStudent(int studentId) {
    cout << "\n=== suggested courses for student " << studentId << " ===\n";

    SimpleVector<Course>* allCourses = setModule->getRawCourseData();
    SimpleVector<RelationPair<int, int>>* history = relationModule->getRawStudentCourseData();

    bool suggestionsFound = false;

    for (int i = 0; i < allCourses->getSize(); i++) {
        Course* currentCourse = &(*allCourses)[i];
        int cId = currentCourse->id;

        // 1. check if already taken
        bool alreadyTaken = false;
        for (int j = 0; j < history->getSize(); j++) {
            if ((*history)[j].a == studentId && (*history)[j].b == cId) {
                alreadyTaken = true;
                break;
            }
        }
        if (alreadyTaken) continue;

        // 2. check prerequisites
        bool eligible = true;
        SimpleVector<int>& prereqs = currentCourse->prerequisiteIDs;

        for (int k = 0; k < prereqs.getSize(); k++) {
            int reqId = prereqs[k];
            bool reqMet = false;
            for (int m = 0; m < history->getSize(); m++) {
                if ((*history)[m].a == studentId && (*history)[m].b == reqId) {
                    reqMet = true;
                    break;
                }
            }
            if (!reqMet) { eligible = false; break; }
        }

        if (eligible) {
            cout << "  - [ ] " << currentCourse->code << ": " << currentCourse->title << endl;
            suggestionsFound = true;
        }
    }

    if (!suggestionsFound) cout << "  no eligible courses found.\n";
}

void SchedulingModule::printPrerequisites() {
    cout << "\n=== prerequisite graph ===\n";
    cout << left << setw(15) << "course" << " | " << "requires" << endl;
    cout << "----------------+---------------------" << endl;

    SimpleVector<Course>* allCourses = setModule->getRawCourseData();
    for (int i = 0; i < allCourses->getSize(); i++) {
        Course* c = &(*allCourses)[i];
        if (c->prerequisiteIDs.getSize() > 0) {
            cout << left << setw(15) << c->code << " | ";
            for (int j = 0; j < c->prerequisiteIDs.getSize(); j++) {
                if (j > 0) cout << ", ";
                Course* p = setModule->findCourse(c->prerequisiteIDs[j]);
                if (p) {
                    cout << p->code;
                }
                else {
                    cout << "unknown";
                }
            }
            cout << endl;
        }
    }
}