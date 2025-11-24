#ifndef SETS_RELATIONS_FUNCTIONS_H
#define SETS_RELATIONS_FUNCTIONS_H

#include "Entities.h"

template <typename A, typename B>
struct RelationPair {
    int a;
    int b;

    RelationPair() : a(-1), b(-1) {}
    RelationPair(int x, int y) : a(x), b(y) {}
};

// ============== SET OPERATIONS MODULE (Module 5) ==============
class SetModule {
private:
    SimpleVector<Student> studentSet;
    SimpleVector<Course> courseSet;
    SimpleVector<Faculty> facultySet;
    SimpleVector<Room> roomSet;

public:
    // NEW: Allow other modules to see the list of courses
    SimpleVector<Course>* getRawCourseData() { return &courseSet; }
    void addStudent(const Student& s) { studentSet.push_back(s); }
    void addCourse(const Course& c) { courseSet.push_back(c); }
    void addFaculty(const Faculty& f) { facultySet.push_back(f); }
    void addRoom(const Room& r) { roomSet.push_back(r); }

    Student* findStudent(int id);
    Course* findCourse(int id);
    Faculty* findFaculty(int id);
    Room* findRoom(int id);

    void printStudentSet();
    void printCourseSet();
    void printFacultySet();
    void printRoomSet();

    bool isSubset(SimpleVector<int>& sub, SimpleVector<int>& sup);
    void printCommonStudents(SimpleVector<int>& set1, SimpleVector<int>& set2);

    int getStudentCount() const { return studentSet.getSize(); }
    int getCourseCount() const { return courseSet.getSize(); }
    int getFacultyCount() const { return facultySet.getSize(); }
    int getRoomCount() const { return roomSet.getSize(); }

    Student* getStudent(int idx) { return &studentSet[idx]; }
    Course* getCourse(int idx) { return &courseSet[idx]; }
    Faculty* getFaculty(int idx) { return &facultySet[idx]; }
    Room* getRoom(int idx) { return &roomSet[idx]; }
};

// ============== RELATIONS MODULE (Module 6) ==============
class RelationModule {
private:
    SimpleVector<RelationPair<int, int>> studentCourseRel;
    SimpleVector<RelationPair<int, int>> facultyCourseRel;
    SimpleVector<RelationPair<int, int>> courseRoomRel;
    SetModule* setModule;

public:
    // NEW: Allow other modules to see student history
    SimpleVector<RelationPair<int, int>>* getRawStudentCourseData() { return &studentCourseRel; }
    RelationModule(SetModule* sm) : setModule(sm) {}

    void addStudentCourseRelation(int studentId, int courseId);
    void addFacultyCourseRelation(int facultyId, int courseId);
    void addCourseRoomRelation(int courseId, int roomId);

    bool isReflexive(SimpleVector<RelationPair<int, int>>& rel);
    bool isSymmetric(SimpleVector<RelationPair<int, int>>& rel);
    bool isTransitive(SimpleVector<RelationPair<int, int>>& rel);
    bool isEquivalence(SimpleVector<RelationPair<int, int>>& rel);

    void composeRelations(SimpleVector<RelationPair<int, int>>& rel1,
        SimpleVector<RelationPair<int, int>>& rel2);

    void printStudentCourses(int studentId);
    void printCourseFaculty(int courseId);
    void printCourseRooms(int courseId);
    void printAllRelations();

    int getStudentCourseRelCount() const { return studentCourseRel.getSize(); }
    RelationPair<int, int>* getStudentCourseRel(int idx) {
        return &studentCourseRel[idx];
    }
};

// ============== FUNCTIONS MODULE (Module 7) ==============
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

    bool isInjective(SimpleVector<RelationPair<int, int>>& func);
    bool isSurjective(SimpleVector<RelationPair<int, int>>& func);
    bool isBijective(SimpleVector<RelationPair<int, int>>& func);

    void composeFunctions(SimpleVector<RelationPair<int, int>>& f1,
        SimpleVector<RelationPair<int, int>>& f2);

    void printStudentCourseAssignments();
    void printCourseFacultyAssignments();
    void printFacultyRoomAssignments();
    void printAllFunctions();

    int getStudentCourseFuncCount() const { return studentCourseFunc.getSize(); }
};



#endif