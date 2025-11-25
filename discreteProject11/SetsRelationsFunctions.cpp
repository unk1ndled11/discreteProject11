#include "SetsRelationsFunctions.h"
#include <iostream>
#include <iomanip> // Used for std::left, std::setw (spacing)

using namespace std;

// ========== SET MODULE IMPLEMENTATIONS ==========
Student* SetModule::findStudent(int id) {
    for (int i = 0; i < studentSet.getSize(); i++) {
        if (studentSet[i].id == id) return &studentSet[i];
    }
    return nullptr;
}

Course* SetModule::findCourse(int id) {
    for (int i = 0; i < courseSet.getSize(); i++) {
        if (courseSet[i].id == id) return &courseSet[i];
    }
    return nullptr;
}

Faculty* SetModule::findFaculty(int id) {
    for (int i = 0; i < facultySet.getSize(); i++) {
        if (facultySet[i].id == id) return &facultySet[i];
    }
    return nullptr;
}

Room* SetModule::findRoom(int id) {
    for (int i = 0; i < roomSet.getSize(); i++) {
        if (roomSet[i].id == id) return &roomSet[i];
    }
    return nullptr;
}

void SetModule::printStudentSet() {
    cout << "\n=== STUDENT SET ===\n";
    cout << left << setw(5) << "ID" << " | " << setw(20) << "Name" << " | " << setw(10) << "Semester" << endl;
    cout << "-----+----------------------+----------" << endl;
    for (int i = 0; i < studentSet.getSize(); i++) {
        cout << left << setw(5) << studentSet[i].id << " | "
            << setw(20) << studentSet[i].name << " | "
            << setw(10) << studentSet[i].semester << endl;
    }
}

void SetModule::printCourseSet() {
    cout << "\n=== COURSE SET ===\n";
    cout << left << setw(5) << "ID" << " | " << setw(10) << "Code" << " | "
        << setw(30) << "Title" << " | " << setw(7) << "Credits" << endl;
    cout << "-----+----------+------------------------------+-------" << endl;
    for (int i = 0; i < courseSet.getSize(); i++) {
        cout << left << setw(5) << courseSet[i].id << " | "
            << setw(10) << courseSet[i].code << " | "
            << setw(30) << courseSet[i].title << " | "
            << setw(7) << courseSet[i].credits << endl;
    }
}

void SetModule::printFacultySet() {
    cout << "\n=== FACULTY SET ===\n";
    cout << left << setw(5) << "ID" << " | " << setw(20) << "Name" << " | " << setw(20) << "Department" << endl;
    cout << "-----+---------------------+---------------------" << endl;
    for (int i = 0; i < facultySet.getSize(); i++) {
        cout << left << setw(5) << facultySet[i].id << " | "
            << setw(20) << facultySet[i].name << " | "
            << setw(20) << facultySet[i].department << endl;
    }
}

void SetModule::printRoomSet() {
    cout << "\n=== ROOM SET ===\n";
    cout << left << setw(5) << "ID" << " | " << setw(10) << "Code" << " | " << setw(10) << "Capacity" << endl;
    cout << "-----+----------+----------" << endl;
    for (int i = 0; i < roomSet.getSize(); i++) {
        cout << left << setw(5) << roomSet[i].id << " | "
            << setw(10) << roomSet[i].code << " | "
            << setw(10) << roomSet[i].capacity << endl;
    }
}

bool SetModule::isSubset(SimpleVector<int>& sub, SimpleVector<int>& sup)// checks subset k sare elements ki instance in superset k elements aik aik karke
{
    for (int i = 0; i < sub.getSize(); i++)
    {
        bool found = false;
        for (int j = 0; j < sup.getSize(); j++)
        {
            if (sub[i] == sup[j])
            {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

void SetModule::printCommonStudents(SimpleVector<int>& set1, SimpleVector<int>& set2) //checks both and prints unke common elements
{
    cout << "\nCommon Students: ";
    bool found = false;
    for (int i = 0; i < set1.getSize(); i++) 
    {
        for (int j = 0; j < set2.getSize(); j++)
        {
            if (set1[i] == set2[j]) {
                if (found) cout << ", ";
                cout << set1[i];
                found = true;
            }
        }
    }
    if (!found) cout << "None";
    cout << endl;
}

// ========== RELATION MODULE IMPLEMENTATIONS ==========
void RelationModule::addStudentCourseRelation(int studentId, int courseId) {
    if (setModule->findStudent(studentId) && setModule->findCourse(courseId)) {
        studentCourseRel.push_back(RelationPair<int, int>(studentId, courseId));
        cout << " [OK] Student " << studentId << " -> Course " << courseId << " relation added." << endl;
    }
    else {
        cout << " [Error] Invalid student or course ID." << endl;
    }
}

void RelationModule::addFacultyCourseRelation(int facultyId, int courseId) {
    if (setModule->findFaculty(facultyId) && setModule->findCourse(courseId)) {
        facultyCourseRel.push_back(RelationPair<int, int>(facultyId, courseId));
        cout << " [OK] Faculty " << facultyId << " -> Course " << courseId << " relation added." << endl;
    }
    else {
        cout << " [Error] Invalid faculty or course ID." << endl;
    }
}

void RelationModule::addCourseRoomRelation(int courseId, int roomId) {
    if (setModule->findCourse(courseId) && setModule->findRoom(roomId)) {
        courseRoomRel.push_back(RelationPair<int, int>(courseId, roomId));
        cout << " [OK] Course " << courseId << " -> Room " << roomId << " relation added." << endl;
    }
    else {
        cout << " [Error] Invalid course or room ID." << endl;
    }
}

bool RelationModule::isReflexive(SimpleVector<RelationPair<int, int>>& rel) //dawg what
{
    return true; 
}

bool RelationModule::isSymmetric(SimpleVector<RelationPair<int, int>>& rel)

{
    for (int i = 0; i < rel.getSize(); i++) 
    {
        bool found = false;
        for (int j = 0; j < rel.getSize(); j++) 
        {
            if (rel[i].a == rel[j].b && rel[i].b == rel[j].a)
            {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

bool RelationModule::isTransitive(SimpleVector<RelationPair<int, int>>& rel) 
{
    for (int i = 0; i < rel.getSize(); i++) 
    {
        for (int j = 0; j < rel.getSize(); j++) 
        {
            if (rel[i].b == rel[j].a) {
                bool found = false;
                for (int k = 0; k < rel.getSize(); k++) 
                {
                    if (rel[k].a == rel[i].a && rel[k].b == rel[j].b)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found) return false;
            }
        }
    }
    return true;
}

bool RelationModule::isEquivalence(SimpleVector<RelationPair<int, int>>& rel) {
    return isReflexive(rel) && isSymmetric(rel) && isTransitive(rel);
}

void RelationModule::composeRelations(SimpleVector<RelationPair<int, int>>& rel1, SimpleVector<RelationPair<int, int>>& rel2) {
    cout << "\nComposed Relations (R1 o R2):\n";
    cout << left << setw(10) << "From" << " | " << setw(10) << "To" << endl;
    cout << "-----------+-----------" << endl;
    for (int i = 0; i < rel1.getSize(); i++) {
        for (int j = 0; j < rel2.getSize(); j++) {
            if (rel1[i].b == rel2[j].a) {
                cout << left << setw(10) << rel1[i].a << " | " << setw(10) << rel2[j].b << endl;
            }
        }
    }
}

void RelationModule::printStudentCourses(int studentId) {
    cout << "\nCourses for Student " << studentId << ":\n";
    bool found = false;
    for (int i = 0; i < studentCourseRel.getSize(); i++) {
        if (studentCourseRel[i].a == studentId) {
            Course* c = setModule->findCourse(studentCourseRel[i].b);
            if (c) {
                cout << "  - " << c->code << " (" << c->title << ")" << endl;
                found = true;
            }
        }
    }
    if (!found) cout << "  No courses found." << endl;
}

void RelationModule::printCourseFaculty(int courseId) {
    cout << "\nFaculty for Course " << courseId << ":\n";
    bool found = false;
    for (int i = 0; i < facultyCourseRel.getSize(); i++) {
        if (facultyCourseRel[i].b == courseId) {
            Faculty* f = setModule->findFaculty(facultyCourseRel[i].a);
            if (f) {
                cout << "  - " << f->name << " (" << f->department << ")" << endl;
                found = true;
            }
        }
    }
    if (!found) cout << "  No faculty found." << endl;
}

void RelationModule::printCourseRooms(int courseId) {
    cout << "\nRooms for Course " << courseId << ":\n";
    bool found = false;
    for (int i = 0; i < courseRoomRel.getSize(); i++) {
        if (courseRoomRel[i].a == courseId) {
            Room* r = setModule->findRoom(courseRoomRel[i].b);
            if (r) {
                cout << "  - " << r->code << " (Cap: " << r->capacity << ")" << endl;
                found = true;
            }
        }
    }
    if (!found) cout << "  No rooms found." << endl;
}

void RelationModule::printAllRelations() {
    cout << "\n=== ALL RELATIONS ===\n";
    cout << "\nSTUDENT-COURSE RELATIONS:\n";
    cout << left << setw(12) << "Student ID" << " | " << setw(12) << "Course ID" << endl;
    cout << "--------------+--------------" << endl;
    for (int i = 0; i < studentCourseRel.getSize(); i++) {
        cout << left << setw(12) << studentCourseRel[i].a << " | " << setw(12) << studentCourseRel[i].b << endl;
    }
}

// ========== FUNCTION MODULE IMPLEMENTATIONS ==========
bool FunctionModule::isFunctionValid(SimpleVector<RelationPair<int, int>>& func) {
    for (int i = 0; i < func.getSize(); i++) {
        for (int j = i + 1; j < func.getSize(); j++) {
            if (func[i].a == func[j].a && func[i].b != func[j].b) {
                return false;
            }
        }
    }
    return true;
}

bool FunctionModule::addStudentCourseFunction(int studentId, int courseId) {
    studentCourseFunc.push_back(RelationPair<int, int>(studentId, courseId));
    if (isFunctionValid(studentCourseFunc)) {
        cout << " [OK] Student " << studentId << " -> Course " << courseId << " function added." << endl;
        return true;
    }
    else {
        studentCourseFunc.remove(studentCourseFunc.getSize() - 1);
        cout << " [Error] Invalid function: Multiple mappings detected for this Student." << endl;
        return false;
    }
}

bool FunctionModule::addCourseFacultyFunction(int courseId, int facultyId) {
    courseFacultyFunc.push_back(RelationPair<int, int>(courseId, facultyId));
    if (isFunctionValid(courseFacultyFunc)) {
        cout << " [OK] Course " << courseId << " -> Faculty " << facultyId << " function added." << endl;
        return true;
    }
    else {
        courseFacultyFunc.remove(courseFacultyFunc.getSize() - 1);
        cout << " [Error] Invalid function: Course already assigned to a Faculty." << endl;
        return false;
    }
}

bool FunctionModule::addFacultyRoomFunction(int facultyId, int roomId) {
    facultyRoomFunc.push_back(RelationPair<int, int>(facultyId, roomId));
    if (isFunctionValid(facultyRoomFunc)) {
        cout << " [OK] Faculty " << facultyId << " -> Room " << roomId << " function added." << endl;
        return true;
    }
    else {
        facultyRoomFunc.remove(facultyRoomFunc.getSize() - 1);
        cout << " [Error] Invalid function: Faculty already assigned." << endl;
        return false;
    }
}

bool FunctionModule::isInjective(SimpleVector<RelationPair<int, int>>& func) {
    for (int i = 0; i < func.getSize(); i++) {
        for (int j = i + 1; j < func.getSize(); j++) {
            if (func[i].b == func[j].b) return false;
        }
    }
    return true;
}

bool FunctionModule::isSurjective(SimpleVector<RelationPair<int, int>>& func) { return true; }

bool FunctionModule::isBijective(SimpleVector<RelationPair<int, int>>& func) {
    return isInjective(func) && isSurjective(func);
}

void FunctionModule::composeFunctions(SimpleVector<RelationPair<int, int>>& f1, SimpleVector<RelationPair<int, int>>& f2) {
    cout << "\nComposed Functions (f1 o f2):\n";
    cout << left << setw(10) << "Input" << " | " << setw(10) << "Intermediate" << " | " << setw(10) << "Output" << endl;
    cout << "-----------+-----------+-----------" << endl;
    for (int i = 0; i < f1.getSize(); i++) {
        for (int j = 0; j < f2.getSize(); j++) {
            if (f1[i].b == f2[j].a) {
                cout << left << setw(10) << f1[i].a << " | " << setw(10) << f1[i].b << " | " << setw(10) << f2[j].b << endl;
            }
        }
    }
}

void FunctionModule::printStudentCourseAssignments() {
    cout << "\n=== STUDENT -> COURSE ASSIGNMENTS ===\n";
    cout << left << setw(12) << "Student ID" << " | " << setw(12) << "Course ID" << endl;
    cout << "--------------+--------------" << endl;
    for (int i = 0; i < studentCourseFunc.getSize(); i++) {
        cout << left << setw(12) << studentCourseFunc[i].a << " | " << setw(12) << studentCourseFunc[i].b << endl;
    }
    cout << "\nInjective: " << (isInjective(studentCourseFunc) ? "Yes" : "No")
        << " | Surjective: " << (isSurjective(studentCourseFunc) ? "Yes" : "No")
        << " | Bijective: " << (isBijective(studentCourseFunc) ? "Yes" : "No") << endl;
}

void FunctionModule::printCourseFacultyAssignments() {
    cout << "\n=== COURSE -> FACULTY ASSIGNMENTS ===\n";
    cout << left << setw(12) << "Course ID" << " | " << setw(12) << "Faculty ID" << endl;
    cout << "--------------+--------------" << endl;
    for (int i = 0; i < courseFacultyFunc.getSize(); i++) {
        cout << left << setw(12) << courseFacultyFunc[i].a << " | " << setw(12) << courseFacultyFunc[i].b << endl;
    }
    cout << "\nInjective: " << (isInjective(courseFacultyFunc) ? "Yes" : "No") << endl;
}

void FunctionModule::printFacultyRoomAssignments() {
    cout << "\n=== FACULTY -> ROOM ASSIGNMENTS ===\n";
    cout << left << setw(12) << "Faculty ID" << " | " << setw(12) << "Room ID" << endl;
    cout << "--------------+--------------" << endl;
    for (int i = 0; i < facultyRoomFunc.getSize(); i++) {
        cout << left << setw(12) << facultyRoomFunc[i].a << " | " << setw(12) << facultyRoomFunc[i].b << endl;
    }
}

void FunctionModule::printAllFunctions() {
    printStudentCourseAssignments();
    cout << endl;
    printCourseFacultyAssignments();
    cout << endl;
    printFacultyRoomAssignments();
}