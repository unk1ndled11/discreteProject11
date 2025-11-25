#include "SetsRelationsFunctions.h"
#include <iostream>
#include <iomanip>

using namespace std;

// set module implementation

// finders
Student* SetModule::findStudent(int id) {
    for (int i = 0; i < studentSet.getSize(); i++) if (studentSet[i].id == id) return &studentSet[i];
    return nullptr;
}
Course* SetModule::findCourse(int id) {
    for (int i = 0; i < courseSet.getSize(); i++) if (courseSet[i].id == id) return &courseSet[i];
    return nullptr;
}
Faculty* SetModule::findFaculty(int id) {
    for (int i = 0; i < facultySet.getSize(); i++) if (facultySet[i].id == id) return &facultySet[i];
    return nullptr;
}
Room* SetModule::findRoom(int id) {
    for (int i = 0; i < roomSet.getSize(); i++) if (roomSet[i].id == id) return &roomSet[i];
    return nullptr;
}

// math helpers
SimpleVector<int> SetModule::getAllStudentIDs() {
    SimpleVector<int> ids;
    for (int i = 0; i < studentSet.getSize(); i++) ids.push_back(studentSet[i].id);
    return ids;
}
SimpleVector<int> SetModule::getAllCourseIDs() {
    SimpleVector<int> ids;
    for (int i = 0; i < courseSet.getSize(); i++) ids.push_back(courseSet[i].id);
    return ids;
}
SimpleVector<int> SetModule::getAllFacultyIDs() {
    SimpleVector<int> ids;
    for (int i = 0; i < facultySet.getSize(); i++) ids.push_back(facultySet[i].id);
    return ids;
}
SimpleVector<int> SetModule::getAllRoomIDs() {
    SimpleVector<int> ids;
    for (int i = 0; i < roomSet.getSize(); i++) ids.push_back(roomSet[i].id);
    return ids;
}

// set operations
SimpleVector<int> SetModule::getUnion(SimpleVector<int>& setA, SimpleVector<int>& setB) {
    SimpleVector<int> result;
    for (int i = 0; i < setA.getSize(); i++) result.push_back(setA[i]);
    for (int i = 0; i < setB.getSize(); i++) {
        bool exists = false;
        for (int j = 0; j < setA.getSize(); j++) {
            if (setB[i] == setA[j]) { exists = true; break; }
        }
        if (!exists) result.push_back(setB[i]);
    }
    return result;
}

SimpleVector<int> SetModule::getIntersection(SimpleVector<int>& setA, SimpleVector<int>& setB) {
    SimpleVector<int> result;
    for (int i = 0; i < setA.getSize(); i++) {
        for (int j = 0; j < setB.getSize(); j++) {
            if (setA[i] == setB[j]) {
                result.push_back(setA[i]);
                break;
            }
        }
    }
    return result;
}

bool SetModule::isSubset(SimpleVector<int>& sub, SimpleVector<int>& sup) {
    for (int i = 0; i < sub.getSize(); i++) {
        bool found = false;
        for (int j = 0; j < sup.getSize(); j++) {
            if (sub[i] == sup[j]) { found = true; break; }
        }
        if (!found) return false;
    }
    return true;
}

// printers
void SetModule::printStudentSet() {
    cout << "\n=== student set ===\n";
    cout << left << setw(5) << "id" << " | " << setw(20) << "name" << " | " << setw(10) << "semester" << endl;
    cout << "-----+----------------------+----------" << endl;
    for (int i = 0; i < studentSet.getSize(); i++) {
        cout << left << setw(5) << studentSet[i].id << " | " << setw(20) << studentSet[i].name << " | " << setw(10) << studentSet[i].semester << endl;
    }
}
void SetModule::printCourseSet() {
    cout << "\n=== course set ===\n";
    cout << left << setw(5) << "id" << " | " << setw(10) << "code" << " | " << setw(30) << "title" << " | " << setw(7) << "credits" << endl;
    cout << "-----+----------+------------------------------+-------" << endl;
    for (int i = 0; i < courseSet.getSize(); i++) {
        cout << left << setw(5) << courseSet[i].id << " | " << setw(10) << courseSet[i].code << " | " << setw(30) << courseSet[i].title << " | " << setw(7) << courseSet[i].credits << endl;
    }
}
void SetModule::printFacultySet() {
    cout << "\n=== faculty set ===\n";
    cout << left << setw(5) << "id" << " | " << setw(20) << "name" << " | " << setw(20) << "department" << endl;
    cout << "-----+---------------------+---------------------" << endl;
    for (int i = 0; i < facultySet.getSize(); i++) {
        cout << left << setw(5) << facultySet[i].id << " | " << setw(20) << facultySet[i].name << " | " << setw(20) << facultySet[i].department << endl;
    }
}
void SetModule::printRoomSet() {
    cout << "\n=== room set ===\n";
    cout << left << setw(5) << "id" << " | " << setw(10) << "code" << " | " << setw(10) << "capacity" << endl;
    cout << "-----+----------+----------" << endl;
    for (int i = 0; i < roomSet.getSize(); i++) {
        cout << left << setw(5) << roomSet[i].id << " | " << setw(10) << roomSet[i].code << " | " << setw(10) << roomSet[i].capacity << endl;
    }
}
void SetModule::printCommonStudents(SimpleVector<int>& set1, SimpleVector<int>& set2) {
    cout << "\ncommon students: ";
    SimpleVector<int> common = getIntersection(set1, set2);
    if (common.getSize() == 0) cout << "none";
    else {
        for (int i = 0; i < common.getSize(); i++) {
            if (i > 0) cout << ", ";
            cout << common[i];
        }
    }
    cout << endl;
}

// relation module implementation

void RelationModule::addStudentCourseRelation(int s, int c) {
    if (setModule->findStudent(s) && setModule->findCourse(c)) {
        studentCourseRel.push_back(RelationPair<int, int>(s, c));
        cout << " ok: relation added.\n";
    }
    else cout << " error: invalid id.\n";
}
void RelationModule::addFacultyCourseRelation(int f, int c) {
    if (setModule->findFaculty(f) && setModule->findCourse(c)) {
        facultyCourseRel.push_back(RelationPair<int, int>(f, c));
        cout << " ok: relation added.\n";
    }
    else cout << " error: invalid id.\n";
}
void RelationModule::addCourseRoomRelation(int c, int r) {
    if (setModule->findCourse(c) && setModule->findRoom(r)) {
        courseRoomRel.push_back(RelationPair<int, int>(c, r));
        cout << " ok: relation added.\n";
    }
    else cout << " error: invalid id.\n";
}

// discrete math properties

// reflexive check
bool RelationModule::isReflexive(SimpleVector<RelationPair<int, int>>& rel, SimpleVector<int>& universe) {
    for (int i = 0; i < universe.getSize(); i++) {
        int val = universe[i];
        bool foundSelfLoop = false;
        for (int j = 0; j < rel.getSize(); j++) {
            if (rel[j].a == val && rel[j].b == val) {
                foundSelfLoop = true;
                break;
            }
        }
        if (!foundSelfLoop) return false;
    }
    return true;
}

// symmetric check
bool RelationModule::isSymmetric(SimpleVector<RelationPair<int, int>>& rel) {
    for (int i = 0; i < rel.getSize(); i++) {
        int a = rel[i].a;
        int b = rel[i].b;
        bool foundInverse = false;
        for (int j = 0; j < rel.getSize(); j++) {
            if (rel[j].a == b && rel[j].b == a) {
                foundInverse = true;
                break;
            }
        }
        if (!foundInverse) return false;
    }
    return true;
}

// transitive check
bool RelationModule::isTransitive(SimpleVector<RelationPair<int, int>>& rel) {
    for (int i = 0; i < rel.getSize(); i++) {
        for (int j = 0; j < rel.getSize(); j++) {
            if (rel[i].b == rel[j].a) { // chain found
                int a = rel[i].a;
                int c = rel[j].b;

                // must find a->c
                bool foundShortcut = false;
                for (int k = 0; k < rel.getSize(); k++) {
                    if (rel[k].a == a && rel[k].b == c) {
                        foundShortcut = true;
                        break;
                    }
                }
                if (!foundShortcut) return false;
            }
        }
    }
    return true;
}

bool RelationModule::isEquivalence(SimpleVector<RelationPair<int, int>>& rel, SimpleVector<int>& universe) {
    return isReflexive(rel, universe) && isSymmetric(rel) && isTransitive(rel);
}

SimpleVector<RelationPair<int, int>> RelationModule::getInverse(SimpleVector<RelationPair<int, int>>& rel) {
    SimpleVector<RelationPair<int, int>> inv;
    for (int i = 0; i < rel.getSize(); i++) {
        inv.push_back(RelationPair<int, int>(rel[i].b, rel[i].a));
    }
    return inv;
}

void RelationModule::composeRelations(SimpleVector<RelationPair<int, int>>& r1, SimpleVector<RelationPair<int, int>>& r2) {
    cout << "\ncomposed relations:\n";
    cout << left << setw(10) << "from" << " | " << setw(10) << "to" << endl;
    cout << "-----------+-----------" << endl;
    for (int i = 0; i < r1.getSize(); i++) {
        for (int j = 0; j < r2.getSize(); j++) {
            if (r1[i].b == r2[j].a) {
                cout << left << setw(10) << r1[i].a << " | " << setw(10) << r2[j].b << endl;
            }
        }
    }
}
void RelationModule::addStudentPeerRelation(int s1, int s2) {
    if (setModule->findStudent(s1) && setModule->findStudent(s2)) {
        studentPeerRel.push_back(RelationPair<int, int>(s1, s2));
        cout << " ok: peer relation added: " << s1 << " <-> " << s2 << "\n";
    }
    else {
        cout << " error: invalid student id.\n";
    }
}

void RelationModule::printStudentCourses(int id) {
    cout << "\ncourses for student " << id << ":\n";
    bool found = false;
    for (int i = 0; i < studentCourseRel.getSize(); i++) {
        if (studentCourseRel[i].a == id) {
            Course* c = setModule->findCourse(studentCourseRel[i].b);
            if (c) {
                cout << "  - " << c->code << " (" << c->title << ")" << endl;
                found = true;
            }
        }
    }
    if (!found) cout << "  no courses found.\n";
}

void RelationModule::printCourseFaculty(int id) {
    cout << "\nfaculty for course " << id << ":\n";
    bool found = false;
    for (int i = 0; i < facultyCourseRel.getSize(); i++) {
        if (facultyCourseRel[i].b == id) {
            Faculty* f = setModule->findFaculty(facultyCourseRel[i].a);
            if (f) {
                cout << "  - " << f->name << " (" << f->department << ")" << endl;
                found = true;
            }
        }
    }
    if (!found) cout << "  no faculty found.\n";
}

void RelationModule::printCourseRooms(int id) {
    cout << "\nrooms for course " << id << ":\n";
    bool found = false;
    for (int i = 0; i < courseRoomRel.getSize(); i++) {
        if (courseRoomRel[i].a == id) {
            Room* r = setModule->findRoom(courseRoomRel[i].b);
            if (r) {
                cout << "  - " << r->code << " (cap: " << r->capacity << ")" << endl;
                found = true;
            }
        }
    }
    if (!found) cout << "  no rooms found.\n";
}

void RelationModule::printAllRelations() {
    cout << "\n=== all relations ===\n";
    cout << "\nstudent-course relations:\n";
    cout << left << setw(12) << "student id" << " | " << setw(12) << "course id" << endl;
    cout << "--------------+--------------" << endl;
    for (int i = 0; i < studentCourseRel.getSize(); i++) {
        cout << left << setw(12) << studentCourseRel[i].a << " | " << setw(12) << studentCourseRel[i].b << endl;
    }
}


// function module implementation

bool FunctionModule::isFunctionValid(SimpleVector<RelationPair<int, int>>& func) {
    for (int i = 0; i < func.getSize(); i++) {
        for (int j = i + 1; j < func.getSize(); j++) {
            if (func[i].a == func[j].a && func[i].b != func[j].b) return false;
        }
    }
    return true;
}

bool FunctionModule::addStudentCourseFunction(int s, int c) {
    studentCourseFunc.push_back(RelationPair<int, int>(s, c));
    if (isFunctionValid(studentCourseFunc)) {
        cout << " ok: function added.\n"; return true;
    }
    else {
        studentCourseFunc.remove(studentCourseFunc.getSize() - 1);
        cout << " error: invalid: multiple mappings.\n"; return false;
    }
}

bool FunctionModule::addCourseFacultyFunction(int c, int f) {
    courseFacultyFunc.push_back(RelationPair<int, int>(c, f));
    if (isFunctionValid(courseFacultyFunc)) {
        cout << " ok: function added.\n"; return true;
    }
    else {
        courseFacultyFunc.remove(courseFacultyFunc.getSize() - 1);
        cout << " error: invalid: multiple mappings.\n"; return false;
    }
}

bool FunctionModule::addFacultyRoomFunction(int f, int r) {
    facultyRoomFunc.push_back(RelationPair<int, int>(f, r));
    if (isFunctionValid(facultyRoomFunc)) {
        cout << " ok: function added.\n"; return true;
    }
    else {
        facultyRoomFunc.remove(facultyRoomFunc.getSize() - 1);
        cout << " error: invalid: multiple mappings.\n"; return false;
    }
}

// discrete math properties for functions

bool FunctionModule::isInjective(SimpleVector<RelationPair<int, int>>& func) {
    for (int i = 0; i < func.getSize(); i++) {
        for (int j = i + 1; j < func.getSize(); j++) {
            if (func[i].b == func[j].b) return false;
        }
    }
    return true;
}

bool FunctionModule::isSurjective(SimpleVector<RelationPair<int, int>>& func, SimpleVector<int>& codomain) {
    for (int i = 0; i < codomain.getSize(); i++) {
        int target = codomain[i];
        bool covered = false;
        for (int j = 0; j < func.getSize(); j++) {
            if (func[j].b == target) {
                covered = true;
                break;
            }
        }
        if (!covered) return false;
    }
    return true;
}

bool FunctionModule::isBijective(SimpleVector<RelationPair<int, int>>& func, SimpleVector<int>& codomain) {
    return isInjective(func) && isSurjective(func, codomain);
}

void FunctionModule::composeFunctions(SimpleVector<RelationPair<int, int>>& f1, SimpleVector<RelationPair<int, int>>& f2) {
    cout << "\ncomposed functions:\n";
    cout << left << setw(10) << "input" << " | " << setw(10) << "middle" << " | " << setw(10) << "output" << endl;
    cout << "-----------+-----------+-----------" << endl;
    for (int i = 0; i < f1.getSize(); i++) {
        for (int j = 0; j < f2.getSize(); j++) {
            if (f1[i].b == f2[j].a) {
                cout << left << setw(10) << f1[i].a << " | " << setw(10) << f1[i].b << " | " << setw(10) << f2[j].b << endl;
            }
        }
    }
}

void FunctionModule::printAnalysis() {
    cout << "\n=== discrete function analysis ===\n";

    SimpleVector<int> allCourses = setModule->getAllCourseIDs();
    SimpleVector<int> allFaculty = setModule->getAllFacultyIDs();
    SimpleVector<int> allRooms = setModule->getAllRoomIDs();

    cout << "1. course -> faculty assignment:\n";
    cout << "   - injective (one-to-one)? ";
    if (isInjective(courseFacultyFunc)) cout << "yes"; else cout << "no";
    cout << endl;

    cout << "   - surjective (onto)?      ";
    if (isSurjective(courseFacultyFunc, allFaculty)) cout << "yes"; else cout << "no";
    cout << endl;

    cout << "   - bijective?              ";
    if (isBijective(courseFacultyFunc, allFaculty)) cout << "yes"; else cout << "no";
    cout << endl;

    cout << "\n2. faculty -> room assignment:\n";
    cout << "   - injective (one-to-one)? ";
    if (isInjective(facultyRoomFunc)) cout << "yes"; else cout << "no";
    cout << endl;

    cout << "   - surjective (onto)?      ";
    if (isSurjective(facultyRoomFunc, allRooms)) cout << "yes"; else cout << "no";
    cout << endl;
}

void FunctionModule::printStudentCourseAssignments() {
    cout << "\n=== student -> course assignments ===\n";
    cout << left << setw(12) << "student id" << " | " << setw(12) << "course id" << endl;
    cout << "--------------+--------------" << endl;
    for (int i = 0; i < studentCourseFunc.getSize(); i++) {
        cout << left << setw(12) << studentCourseFunc[i].a << " | " << setw(12) << studentCourseFunc[i].b << endl;
    }
}

void FunctionModule::printCourseFacultyAssignments() {
    cout << "\n=== course -> faculty assignments ===\n";
    cout << left << setw(12) << "course id" << " | " << setw(12) << "faculty id" << endl;
    cout << "--------------+--------------" << endl;
    for (int i = 0; i < courseFacultyFunc.getSize(); i++) {
        cout << left << setw(12) << courseFacultyFunc[i].a << " | " << setw(12) << courseFacultyFunc[i].b << endl;
    }
}

void FunctionModule::printFacultyRoomAssignments() {
    cout << "\n=== faculty -> room assignments ===\n";
    cout << left << setw(12) << "faculty id" << " | " << setw(12) << "room id" << endl;
    cout << "--------------+--------------" << endl;
    for (int i = 0; i < facultyRoomFunc.getSize(); i++) {
        cout << left << setw(12) << facultyRoomFunc[i].a << " | " << setw(12) << facultyRoomFunc[i].b << endl;
    }
}

void FunctionModule::printAllFunctions() {
    printAnalysis();
    cout << endl;
    printStudentCourseAssignments();
    cout << endl;
    printCourseFacultyAssignments();
    cout << endl;
    printFacultyRoomAssignments();
}