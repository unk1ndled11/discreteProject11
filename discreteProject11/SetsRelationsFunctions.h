#ifndef SETS_RELATIONS_FUNCTIONS_H
#define SETS_RELATIONS_FUNCTIONS_H

#include "Entities.h"

// A Generic Pair to represent (a, b) in a relation
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

// ============== SET OPERATIONS MODULE (Module 5) ==============
class SetModule {
private:
    SimpleVector<Student> studentSet;
    SimpleVector<Course> courseSet;
    SimpleVector<Faculty> facultySet;
    SimpleVector<Room> roomSet;

public:
    // Basic Adders
    void addStudent(const Student& s) { studentSet.push_back(s); }
    void addCourse(const Course& c) { courseSet.push_back(c); }
    void addFaculty(const Faculty& f) { facultySet.push_back(f); }
    void addRoom(const Room& r) { roomSet.push_back(r); }

    // Finders
    Student* findStudent(int id);
    Course* findCourse(int id);
    Faculty* findFaculty(int id);
    Room* findRoom(int id);

    // === HELPERS FOR MODULE 6 (MATH) ===
    // These extract just the IDs so we can pass "The Set of All Students" 
    // to a function like isReflexive().
    SimpleVector<int> getAllStudentIDs();
    SimpleVector<int> getAllCourseIDs();
    SimpleVector<int> getAllFacultyIDs();
    SimpleVector<int> getAllRoomIDs();

    // === HELPERS FOR MODULE 1 (SCHEDULING) ===
    // CRITICAL: Scheduling Module needs raw pointers to traverse the Graph.
    SimpleVector<Course>* getRawCourseData() { return &courseSet; }

    // Printers
    void printStudentSet();
    void printCourseSet();
    void printFacultySet();
    void printRoomSet();

    // Set Theory Operations
    bool isSubset(SimpleVector<int>& sub, SimpleVector<int>& sup);
    SimpleVector<int> getUnion(SimpleVector<int>& setA, SimpleVector<int>& setB);
    SimpleVector<int> getIntersection(SimpleVector<int>& setA, SimpleVector<int>& setB);
    void printCommonStudents(SimpleVector<int>& set1, SimpleVector<int>& set2);

    // Counts
    int getStudentCount() const { return studentSet.getSize(); }
    int getCourseCount() const { return courseSet.getSize(); }
    int getFacultyCount() const { return facultySet.getSize(); }
    int getRoomCount() const { return roomSet.getSize(); }
};

// ============== RELATIONS MODULE (Module 6) ==============
class RelationModule {
private:
    SimpleVector<RelationPair<int, int>> studentCourseRel;
    SimpleVector<RelationPair<int, int>> facultyCourseRel;
    SimpleVector<RelationPair<int, int>> courseRoomRel;
    SetModule* setModule;

public:
    RelationModule(SetModule* sm) : setModule(sm) {}

    // Adding Relations
    void addStudentCourseRelation(int studentId, int courseId);
    void addFacultyCourseRelation(int facultyId, int courseId);
    void addCourseRoomRelation(int courseId, int roomId);

    // === HELPER FOR MODULE 1 (SCHEDULING) ===
    // CRITICAL: Scheduling Module needs to check student history.
    SimpleVector<RelationPair<int, int>>* getRawStudentCourseData() { return &studentCourseRel; }

    // === DISCRETE MATH PROPERTIES (STRICT) ===
    // Reflexive: forall a in A, (a,a) in R
    // We MUST pass the 'universe' (Set A) to check this strictly.
    bool isReflexive(SimpleVector<RelationPair<int, int>>& rel, SimpleVector<int>& universe);

    // Symmetric: (a,b) in R -> (b,a) in R
    bool isSymmetric(SimpleVector<RelationPair<int, int>>& rel);

    // Transitive: (a,b) in R ^ (b,c) in R -> (a,c) in R
    bool isTransitive(SimpleVector<RelationPair<int, int>>& rel);

    // Equivalence: Reflexive + Symmetric + Transitive
    bool isEquivalence(SimpleVector<RelationPair<int, int>>& rel, SimpleVector<int>& universe);

    // Operations
    SimpleVector<RelationPair<int, int>> getInverse(SimpleVector<RelationPair<int, int>>& rel);

    void composeRelations(SimpleVector<RelationPair<int, int>>& rel1,
        SimpleVector<RelationPair<int, int>>& rel2);

    // Printers
    void printStudentCourses(int studentId);
    void printCourseFaculty(int courseId);
    void printCourseRooms(int courseId);
    void printAllRelations();
    int getStudentCourseRelCount() const { return studentCourseRel.getSize(); }
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

    // === DISCRETE MATH PROPERTIES (STRICT) ===

    // Injective (One-to-One): f(a) = f(b) -> a = b
    bool isInjective(SimpleVector<RelationPair<int, int>>& func);

    // Surjective (Onto): Range == Codomain
    // We MUST pass the Codomain (Target Set) to check this strictly.
    bool isSurjective(SimpleVector<RelationPair<int, int>>& func, SimpleVector<int>& codomain);

    // Bijective: Injective + Surjective
    bool isBijective(SimpleVector<RelationPair<int, int>>& func, SimpleVector<int>& codomain);

    // Composition
    void composeFunctions(SimpleVector<RelationPair<int, int>>& f1,
        SimpleVector<RelationPair<int, int>>& f2);

    // Printers with Analysis
    void printAnalysis();
    void printStudentCourseAssignments();
    void printCourseFacultyAssignments();
    void printFacultyRoomAssignments();
    void printAllFunctions();

    int getStudentCourseFuncCount() const { return studentCourseFunc.getSize(); }
};

#endif