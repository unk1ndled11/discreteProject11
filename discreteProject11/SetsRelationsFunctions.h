#ifndef SETS_RELATIONS_FUNCTIONS_H
#define SETS_RELATIONS_FUNCTIONS_H

#include "Entities.h"

// generic pair structure for relations
template <typename A, typename B>
struct RelationPair {
    int a;
    int b;

    RelationPair() : a(-1), b(-1) {}
    RelationPair(int x, int y) : a(x), b(y) {}

    bool operator==(const RelationPair& other) {
        return a == other.a && b == other.b;
    }
};

// module 5: sets
class SetModule {
private:
    SimpleVector<Student> studentSet;
    SimpleVector<Course> courseSet;
    SimpleVector<Faculty> facultySet;
    SimpleVector<Room> roomSet;

public:
    // humaray adders
    void addStudent(const Student& s) { studentSet.push_back(s); }
    void addCourse(const Course& c) { courseSet.push_back(c); }
    void addFaculty(const Faculty& f) { facultySet.push_back(f); }
    void addRoom(const Room& r) { roomSet.push_back(r); }

    // humaray finders
    Student* findStudent(int id);
    Course* findCourse(int id);
    Faculty* findFaculty(int id);
    Room* findRoom(int id);

    // module 6 math helpers
    // extracting ids for reflexivity check
    SimpleVector<int> getAllStudentIDs();
    SimpleVector<int> getAllCourseIDs();
    SimpleVector<int> getAllFacultyIDs();
    SimpleVector<int> getAllRoomIDs();

    // module 1 helper for scheduling
    SimpleVector<Course>* getRawCourseData() { return &courseSet; }

    // printers
    void printStudentSet();
    void printCourseSet();
    void printFacultySet();
    void printRoomSet();

    // set operations
    bool isSubset(SimpleVector<int>& sub, SimpleVector<int>& sup);
    SimpleVector<int> getUnion(SimpleVector<int>& setA, SimpleVector<int>& setB);
    SimpleVector<int> getIntersection(SimpleVector<int>& setA, SimpleVector<int>& setB);
    void printCommonStudents(SimpleVector<int>& set1, SimpleVector<int>& set2);

    // counts
    int getStudentCount() const { return studentSet.getSize(); }
    int getCourseCount() const { return courseSet.getSize(); }
    int getFacultyCount() const { return facultySet.getSize(); }
    int getRoomCount() const { return roomSet.getSize(); }
};

// module 6: relations
class RelationModule {
private:
    SimpleVector<RelationPair<int, int>> studentCourseRel;
    SimpleVector<RelationPair<int, int>> facultyCourseRel;
    SimpleVector<RelationPair<int, int>> courseRoomRel;
    SimpleVector<RelationPair<int, int>> studentPeerRel;
    SetModule* setModule;

public:
    RelationModule(SetModule* sm) : setModule(sm) {}

    // adding relations
    void addStudentCourseRelation(int studentId, int courseId);
    void addFacultyCourseRelation(int facultyId, int courseId);
    void addCourseRoomRelation(int courseId, int roomId);
    void addStudentPeerRelation(int s1, int s2);

    // helper for scheduling module
    SimpleVector<RelationPair<int, int>>* getRawStudentCourseData() { return &studentCourseRel; }

    // discrete math properties
    // reflexivity check
    bool isReflexive(SimpleVector<RelationPair<int, int>>& rel, SimpleVector<int>& universe);

    // symmetry check
    bool isSymmetric(SimpleVector<RelationPair<int, int>>& rel);

    // transitivity check
    bool isTransitive(SimpleVector<RelationPair<int, int>>& rel);

    // equivalence check
    bool isEquivalence(SimpleVector<RelationPair<int, int>>& rel, SimpleVector<int>& universe);

    // operations
    SimpleVector<RelationPair<int, int>> getInverse(SimpleVector<RelationPair<int, int>>& rel);

    void composeRelations(SimpleVector<RelationPair<int, int>>& rel1,
        SimpleVector<RelationPair<int, int>>& rel2);

    // printers
    void printStudentCourses(int studentId);
    void printCourseFaculty(int courseId);
    void printCourseRooms(int courseId);
    void printAllRelations();
    int getStudentCourseRelCount() const { return studentCourseRel.getSize(); }

    SimpleVector<RelationPair<int, int>>* getRawPeerData() { return &studentPeerRel; }
};

// module 7: functions
class FunctionModule {
private:
    SimpleVector<RelationPair<int, int>> studentCourseFunc;
    SimpleVector<RelationPair<int, int>> courseFacultyFunc;
    SimpleVector<RelationPair<int, int>> facultyRoomFunc;
    SetModule* setModule;

    bool isFunctionValid(SimpleVector<RelationPair<int, int>>& func);

public:
    FunctionModule(SetModule* sm) : setModule(sm) {}

    bool addStudentCourseFunction(int studentId, int courseId);
    bool addCourseFacultyFunction(int courseId, int facultyId);
    bool addFacultyRoomFunction(int facultyId, int roomId);

    // discrete math properties for functions

    // one to one check
    bool isInjective(SimpleVector<RelationPair<int, int>>& func);

    // onto check
    bool isSurjective(SimpleVector<RelationPair<int, int>>& func, SimpleVector<int>& codomain);

    // bijective check
    bool isBijective(SimpleVector<RelationPair<int, int>>& func, SimpleVector<int>& codomain);

    // composition
    void composeFunctions(SimpleVector<RelationPair<int, int>>& f1,
        SimpleVector<RelationPair<int, int>>& f2);

    // printers with analysis
    void printAnalysis();
    void printStudentCourseAssignments();
    void printCourseFacultyAssignments();
    void printFacultyRoomAssignments();
    void printAllFunctions();

    int getStudentCourseFuncCount() const { return studentCourseFunc.getSize(); }
};

#endif