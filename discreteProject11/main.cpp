#include "SetsRelationsFunctions.h"
#include <iostream>
#include <cstdlib> 
#include "SchedulingModule.h"
#include "CombinatoricsModule.h"
#include "InductionModule.h"
#include "LogicModule.h"
#include "ProofModule.h"

class DiscreteMathModule {
public:
    SetModule setModule;
    RelationModule relationModule;
    FunctionModule functionModule;
    SchedulingModule schedulingModule;
    CombinatoricsModule combinatoricsModule;
    InductionModule inductionModule;
    LogicModule logicModule;
    ProofModule proofModule;

    DiscreteMathModule()
        : relationModule(&setModule),
        functionModule(&setModule),
        schedulingModule(&setModule, &relationModule),
        combinatoricsModule(&setModule),
        inductionModule(&setModule, &relationModule),
        proofModule(&setModule, &relationModule)
    {}
};

using namespace std;
DiscreteMathModule engine;

void clearScreen() {
    system("cls");
}

void printHeader() {
    cout << "\n================================================================\n";
    cout << "           unidisc engine - discrete structures system          \n";
    cout << "                 fast university management                     \n";
    cout << "================================================================\n";
}

// humara master test suite (module 12 integration)
void loadMasterTestSuite() {
    cout << "\n[init] loading test suite...\n";

    // 1. populate sets
    engine.setModule.addStudent(Student(1001, "ali (high achiever)", 7));
    engine.setModule.addStudent(Student(1002, "bob (struggler)", 1));
    engine.setModule.addStudent(Student(1003, "charlie (transfer)", 4));
    engine.setModule.addStudent(Student(1004, "dave (ghost)", 2));

    engine.setModule.addCourse(Course(101, "CS101", "intro to comp", 3));
    engine.setModule.addCourse(Course(102, "CS102", "data structures", 3));
    engine.setModule.addCourse(Course(201, "CS201", "algorithms", 3));
    engine.setModule.addCourse(Course(301, "CS301", "ethics", 2));
    engine.setModule.addCourse(Course(400, "CS400", "final year project", 6));

    engine.setModule.addFaculty(Faculty(201, "dr. einstein", "cs"));
    engine.setModule.addFaculty(Faculty(202, "dr. turing", "cs"));
    engine.setModule.addFaculty(Faculty(203, "dr. lazy", "math"));

    engine.setModule.addRoom(Room(301, "C-101", 50));
    engine.setModule.addRoom(Room(302, "C-102", 50));
    engine.setModule.addRoom(Room(999, "closet", 0));

    // 2. populate relations
    // ali path
    engine.relationModule.addStudentCourseRelation(1001, 101);
    engine.relationModule.addStudentCourseRelation(1001, 102);
    engine.relationModule.addStudentCourseRelation(1001, 201);
    engine.relationModule.addStudentCourseRelation(1001, 301);
    // bob path
    engine.relationModule.addStudentCourseRelation(1002, 101);

    // 3. populate functions
    // injectivity failure: einstein teaches two
    engine.functionModule.addCourseFacultyFunction(101, 201);
    engine.functionModule.addCourseFacultyFunction(102, 201);
    engine.functionModule.addCourseFacultyFunction(201, 202);
    // surjectivity failure: lazy is never assigned

    // 4. populate prereq graph
    engine.schedulingModule.addPrerequisite(102, 101);
    engine.schedulingModule.addPrerequisite(201, 102);
    engine.schedulingModule.addPrerequisite(400, 201);
    engine.schedulingModule.addPrerequisite(400, 301);

    // 5. populate logic rules
    engine.logicModule.addRule("failed cs101", "academic probation");
    engine.logicModule.addRule("academic probation", "cannot register");
    engine.logicModule.addRule("cannot register", "visa warning");

    // 6. populate peer relations for proofs
    // reflexivity setup
    engine.relationModule.addStudentPeerRelation(1001, 1001);
    engine.relationModule.addStudentPeerRelation(1002, 1002);

    // symmetry setup
    engine.relationModule.addStudentPeerRelation(1001, 1002);

    // transitivity setup
    engine.relationModule.addStudentPeerRelation(1002, 1003);
    engine.relationModule.addStudentPeerRelation(1003, 1004);

    cout << "[success] master test suite loaded.\n";
}

// menus

void relationMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ relations module ]\n";
        cout << "  1. add student-course relation\n";
        cout << "  2. query student courses\n";
        cout << "  3. view all relations\n";
        cout << "  4. add peer relation\n";
        cout << "  5. back\n> ";
        cin >> choice;
        if (choice == 5) return;
        int id1, id2;
        if (choice == 1) {
            cout << "student id: "; cin >> id1; cout << "course id: "; cin >> id2;
            engine.relationModule.addStudentCourseRelation(id1, id2);
        }
        else if (choice == 2) {
            cout << "student id: "; cin >> id1;
            engine.relationModule.printStudentCourses(id1);
        }
        else if (choice == 3) {
            engine.relationModule.printAllRelations();
        }
        else if (choice == 4) {
            cout << "student id 1: "; cin >> id1; cout << "student id 2: "; cin >> id2;
            engine.relationModule.addStudentPeerRelation(id1, id2);
        }
    }
}

void functionMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ functions module ]\n";
        cout << "  1. view all assignments & analysis\n";
        cout << "  2. back\n> ";
        cin >> choice;
        if (choice == 2) return;
        if (choice == 1) engine.functionModule.printAllFunctions();
    }
}

void schedulingMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ module 1: course scheduling ]\n";
        cout << "  1. add prerequisite rule\n";
        cout << "  2. check eligibility\n";
        cout << "  3. suggest next courses\n";
        cout << "  4. view prereq graph\n";
        cout << "  5. back\n> ";
        cin >> choice;
        if (choice == 5) return;
        int id1, id2;
        if (choice == 1) {
            cout << "target id: "; cin >> id1; cout << "prereq id: "; cin >> id2;
            engine.schedulingModule.addPrerequisite(id1, id2);
        }
        else if (choice == 2) {
            cout << "student id: "; cin >> id1; cout << "target course id: "; cin >> id2;
            if (engine.schedulingModule.checkPrerequisites(id1, id2)) {
                cout << " [eligible]\n";
            }
            else {
                cout << " [not eligible]\n";
            }
        }
        else if (choice == 3) {
            cout << "student id: "; cin >> id1;
            engine.schedulingModule.suggestCoursesForStudent(id1);
        }
        else if (choice == 4) {
            engine.schedulingModule.printPrerequisites();
        }
    }
}

void inductionMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ module 3: induction ]\n";
        cout << "  1. prove course chain\n";
        cout << "  2. prove eligibility\n";
        cout << "  3. back\n> ";
        cin >> choice;
        if (choice == 3) return;
        if (choice == 1) {
            SimpleVector<int> chain;
            int count, val;
            cout << "count: "; cin >> count;
            cout << "ids: ";
            for (int i = 0; i < count; i++) { cin >> val; chain.push_back(val); }
            engine.inductionModule.proveCourseChain(chain);
        }
        else if (choice == 2) {
            int s, c; cout << "student id: "; cin >> s; cout << "target id: "; cin >> c;
            engine.inductionModule.provePrerequisiteSatisfaction(s, c);
        }
    }
}

void logicMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ module 4: logic engine ]\n";
        cout << "  1. add fact\n";
        cout << "  2. run inference\n";
        cout << "  3. back\n> ";
        cin >> choice;
        cin.ignore();
        if (choice == 3) return;
        if (choice == 1) {
            char buf[100]; cout << "fact: "; cin.getline(buf, 100);
            engine.logicModule.addFact(buf);
        }
        else if (choice == 2) {
            engine.logicModule.runInferenceEngine();
        }
    }
}

void proofMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ module 8: automated proofs ]\n";
        cout << "  1. prove reflexivity\n";
        cout << "  2. prove symmetry\n";
        cout << "  3. prove transitivity\n";
        cout << "  4. back\n> ";
        cin >> choice;
        if (choice == 4) return;
        if (choice == 1) engine.proofModule.proveReflexivity();
        else if (choice == 2) engine.proofModule.proveSymmetry();
        else if (choice == 3) engine.proofModule.proveTransitivity();
    }
}

void combinatoricsMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ module 2: combinatorics ]\n";
        cout << "  1. generate groups\n";
        cout << "  2. back\n> ";
        cin >> choice;
        if (choice == 2) return;
        if (choice == 1) {
            int r; cout << "group size: "; cin >> r;
            engine.combinatoricsModule.generateStudentGroups(r);
        }
    }
}

void addStudentUI() {
    int id, sem;
    char name[100];
    cout << "enter student id: "; cin >> id; cin.ignore(1000, '\n');
    cout << "enter student name: "; cin.getline(name, 100);
    cout << "enter semester: "; cin >> sem;
    engine.setModule.addStudent(Student(id, name, sem));
    cout << " student added.\n";
}

void addCourseUI() {
    int id, credits;
    char code[50], title[100];
    cout << "enter course id: "; cin >> id; cin.ignore(1000, '\n');
    cout << "enter course code: "; cin.getline(code, 50);
    cout << "enter course title: "; cin.getline(title, 100);
    cout << "enter credits: "; cin >> credits;
    engine.setModule.addCourse(Course(id, code, title, credits));
    cout << " course added.\n";
}

void addFacultyUI() {
    int id;
    char name[100], dept[50];
    cout << "enter faculty id: "; cin >> id; cin.ignore(1000, '\n');
    cout << "enter faculty name: "; cin.getline(name, 100);
    cout << "enter department: "; cin.getline(dept, 50);
    engine.setModule.addFaculty(Faculty(id, name, dept));
    cout << " faculty added.\n";
}

void addRoomUI() {
    int id, cap;
    char code[50];
    cout << "enter room id: "; cin >> id; cin.ignore(1000, '\n');
    cout << "enter room code: "; cin.getline(code, 50);
    cout << "enter capacity: "; cin >> cap;
    engine.setModule.addRoom(Room(id, code, cap));
    cout << " room added.\n";
}

void consistencyCheckUI() {
    cout << "\n[ checking consistency ]\n";
    cout << "  - students: " << engine.setModule.getStudentCount() << endl;
    cout << "  - courses:  " << engine.setModule.getCourseCount() << endl;
    cout << "  - faculty:  " << engine.setModule.getFacultyCount() << endl;
    cout << "  - rooms:    " << engine.setModule.getRoomCount() << endl;
    cout << "  - relations: " << engine.relationModule.getStudentCourseRelCount() << endl;
    cout << "  all good.\n";
}

int main() {
    printHeader();
    cout << " initialize system?\n";
    cout << " 1. load master test suite\n";
    cout << " 2. start empty\n";
    cout << "> ";

    int init; cin >> init;
    if (init == 1) loadMasterTestSuite();

    while (true) {
        clearScreen();
        printHeader();
        cout << "\n [ data & relations ]\n";
        cout << "  1.  sets (view students, etc.)\n";
        cout << "  2.  relations (module 6)\n";
        cout << "  3.  functions (module 7)\n";

        cout << "\n [ discrete math engines ]\n";
        cout << "  4.  scheduling & graphs (module 1)\n";
        cout << "  5.  combinatorics (module 2)\n";
        cout << "  6.  induction proofs (module 3)\n";
        cout << "  7.  logic inference (module 4)\n";
        cout << "  8.  automated proof gen (module 8)\n";

        cout << "\n  0.  exit\n> ";

        int choice; cin >> choice;
        if (choice == 1) {
            clearScreen();
            cout << "1. add student | 2. add course | 3. add faculty | 4. add room | 5. view students | 6. back\n> ";
            int sub; cin >> sub;
            if (sub == 1) addStudentUI();
            else if (sub == 2) addCourseUI();
            else if (sub == 3) addFacultyUI();
            else if (sub == 4) addRoomUI();
            else if (sub == 5) engine.setModule.printStudentSet();
        }
        else if (choice == 2) relationMenuUI();
        else if (choice == 3) functionMenuUI();
        else if (choice == 4) schedulingMenuUI();
        else if (choice == 5) combinatoricsMenuUI();
        else if (choice == 6) inductionMenuUI();
        else if (choice == 7) logicMenuUI();
        else if (choice == 8) proofMenuUI();
        else if (choice == 0) return 0;
        else cout << "invalid.\n";
    }
}