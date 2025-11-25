#include "SetsRelationsFunctions.h"
#include <iostream>
#include <cstdlib> 
#include "SchedulingModule.h"
#include "CombinatoricsModule.h"
#include "InductionModule.h"
#include "LogicModule.h"
#include "ProofModule.h"

// THE ENGINE CLASS
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

// --- UTILITY ---
void clearScreen() {
    system("cls");
}

void printHeader() {
    cout << "\n================================================================\n";
    cout << "           UNIDISC ENGINE - DISCRETE STRUCTURES SYSTEM          \n";
    cout << "                 FAST University Management                     \n";
    cout << "================================================================\n";
}

// --- MASTER TEST SUITE (MODULE 12 INTEGRATION) ---
void loadMasterTestSuite() {
    cout << "\n[INIT] Loading Module 12: Comprehensive Test Suite...\n";

    // 1. POPULATE SETS (Module 5)
    engine.setModule.addStudent(Student(1001, "Ali (High Achiever)", 7));
    engine.setModule.addStudent(Student(1002, "Bob (The Struggler)", 1));
    engine.setModule.addStudent(Student(1003, "Charlie (Transfer)", 4));
    engine.setModule.addStudent(Student(1004, "Dave (The Ghost)", 2));

    engine.setModule.addCourse(Course(101, "CS101", "Intro to Comp", 3));
    engine.setModule.addCourse(Course(102, "CS102", "Data Structures", 3));
    engine.setModule.addCourse(Course(201, "CS201", "Algorithms", 3));
    engine.setModule.addCourse(Course(301, "CS301", "Ethics", 2));
    engine.setModule.addCourse(Course(400, "CS400", "Final Year Project", 6));

    engine.setModule.addFaculty(Faculty(201, "Dr. Einstein", "CS"));
    engine.setModule.addFaculty(Faculty(202, "Dr. Turing", "CS"));
    engine.setModule.addFaculty(Faculty(203, "Dr. Lazy", "Math")); // Teaches nothing (Surjective Fail)

    engine.setModule.addRoom(Room(301, "C-101", 50));
    engine.setModule.addRoom(Room(302, "C-102", 50));
    engine.setModule.addRoom(Room(999, "Closet", 0));

    // 2. POPULATE RELATIONS (Module 6)
    // Ali's Path
    engine.relationModule.addStudentCourseRelation(1001, 101);
    engine.relationModule.addStudentCourseRelation(1001, 102);
    engine.relationModule.addStudentCourseRelation(1001, 201);
    engine.relationModule.addStudentCourseRelation(1001, 301);
    // Bob's Path
    engine.relationModule.addStudentCourseRelation(1002, 101);

    // 3. POPULATE FUNCTIONS (Module 7)
    // Injectivity Failure: Einstein teaches TWO courses
    engine.functionModule.addCourseFacultyFunction(101, 201);
    engine.functionModule.addCourseFacultyFunction(102, 201);
    engine.functionModule.addCourseFacultyFunction(201, 202);
    // Surjectivity Failure: Dr. Lazy (203) is never assigned.

    // 4. POPULATE PREREQUISITE GRAPH (Module 1)
    engine.schedulingModule.addPrerequisite(102, 101); // DS requires Intro
    engine.schedulingModule.addPrerequisite(201, 102); // Algo requires DS
    engine.schedulingModule.addPrerequisite(400, 201); // FYP requires Algo
    engine.schedulingModule.addPrerequisite(400, 301); // FYP requires Ethics (Branching)

    // 5. POPULATE LOGIC RULES (Module 4)
    engine.logicModule.addRule("Failed CS101", "Academic Probation");
    engine.logicModule.addRule("Academic Probation", "Cannot Register");
    engine.logicModule.addRule("Cannot Register", "Visa Warning");

    // 6. POPULATE PEER RELATIONS (For Module 8 Proofs)
    // We create a relation R that is BROKEN on purpose to verify the Proof Logic.

    // Reflexivity Setup:
    // Ali(1001) and Bob(1002) map to themselves.
    // Charlie(1003) DOES NOT. -> Proof should catch Charlie.
    engine.relationModule.addStudentPeerRelation(1001, 1001);
    engine.relationModule.addStudentPeerRelation(1002, 1002);

    // Symmetry Setup:
    // Ali(1001) -> Bob(1002).
    // Bob(1002) DOES NOT -> Ali(1001). -> Proof should catch (1001, 1002).
    engine.relationModule.addStudentPeerRelation(1001, 1002);

    // Transitivity Setup:
    // Bob(1002) -> Charlie(1003).
    // Charlie(1003) -> Dave(1004).
    // Bob(1002) DOES NOT -> Dave(1004). -> Proof should catch this chain.
    engine.relationModule.addStudentPeerRelation(1002, 1003);
    engine.relationModule.addStudentPeerRelation(1003, 1004);

    cout << "[SUCCESS] Master Test Suite Loaded.\n";
    cout << "   > Sets, Relations, and Functions initialized.\n";
    cout << "   > Proof Module Data: Configured to FAIL Reflexivity (Charlie) and Symmetry.\n";
    cout << "   > Logic Engine: Rules loaded.\n";
}

// --- MENUS ---

void relationMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ RELATIONS MODULE (6) ]\n";
        cout << "  1. Add Student-Course Relation\n";
        cout << "  2. Query Student Courses\n";
        cout << "  3. View All Relations\n";
        cout << "  4. Add Peer Relation (A-A for Proofs)\n";
        cout << "  5. Back\n> ";
        cin >> choice;
        if (choice == 5) return;
        int id1, id2;
        if (choice == 1) {
            cout << "Student ID: "; cin >> id1; cout << "Course ID: "; cin >> id2;
            engine.relationModule.addStudentCourseRelation(id1, id2);
        }
        else if (choice == 2) {
            cout << "Student ID: "; cin >> id1;
            engine.relationModule.printStudentCourses(id1);
        }
        else if (choice == 3) {
            engine.relationModule.printAllRelations();
        }
        else if (choice == 4) {
            cout << "Student ID 1: "; cin >> id1; cout << "Student ID 2: "; cin >> id2;
            engine.relationModule.addStudentPeerRelation(id1, id2);
        }
    }
}

void functionMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ FUNCTIONS MODULE (7) ]\n";
        cout << "  1. View All Assignments & Analysis\n";
        cout << "  2. Back\n> ";
        cin >> choice;
        if (choice == 2) return;
        if (choice == 1) engine.functionModule.printAllFunctions();
    }
}

void schedulingMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ MODULE 1: COURSE SCHEDULING ]\n";
        cout << "  1. Add Prerequisite Rule\n";
        cout << "  2. Check Eligibility\n";
        cout << "  3. Suggest Next Courses\n";
        cout << "  4. View Prereq Graph\n";
        cout << "  5. Back\n> ";
        cin >> choice;
        if (choice == 5) return;
        int id1, id2;
        if (choice == 1) {
            cout << "Target ID: "; cin >> id1; cout << "Prereq ID: "; cin >> id2;
            engine.schedulingModule.addPrerequisite(id1, id2);
        }
        else if (choice == 2) {
            cout << "Student ID: "; cin >> id1; cout << "Target Course ID: "; cin >> id2;
            if (engine.schedulingModule.checkPrerequisites(id1, id2)) cout << " [Eligible]\n"; else cout << " [Not Eligible]\n";
        }
        else if (choice == 3) {
            cout << "Student ID: "; cin >> id1;
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
        cout << "\n[ MODULE 3: INDUCTION ]\n";
        cout << "  1. Prove Course Chain (Weak Induction)\n";
        cout << "  2. Prove Eligibility (Strong Induction)\n";
        cout << "  3. Back\n> ";
        cin >> choice;
        if (choice == 3) return;
        if (choice == 1) {
            SimpleVector<int> chain;
            int count, val;
            cout << "Count: "; cin >> count;
            cout << "IDs: ";
            for (int i = 0; i < count; i++) { cin >> val; chain.push_back(val); }
            engine.inductionModule.proveCourseChain(chain);
        }
        else if (choice == 2) {
            int s, c; cout << "Student ID: "; cin >> s; cout << "Target ID: "; cin >> c;
            engine.inductionModule.provePrerequisiteSatisfaction(s, c);
        }
    }
}

void logicMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ MODULE 4: LOGIC ENGINE ]\n";
        cout << "  1. Add Fact\n";
        cout << "  2. Run Inference\n";
        cout << "  3. Back\n> ";
        cin >> choice;
        cin.ignore();
        if (choice == 3) return;
        if (choice == 1) {
            char buf[100]; cout << "Fact: "; cin.getline(buf, 100);
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
        cout << "\n[ MODULE 8: AUTOMATED PROOFS ]\n";
        cout << "  1. Prove Reflexivity\n";
        cout << "  2. Prove Symmetry\n";
        cout << "  3. Prove Transitivity\n";
        cout << "  4. Back\n> ";
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
        cout << "\n[ MODULE 2: COMBINATORICS ]\n";
        cout << "  1. Generate Groups\n";
        cout << "  2. Back\n> ";
        cin >> choice;
        if (choice == 2) return;
        if (choice == 1) {
            int r; cout << "Group Size: "; cin >> r;
            engine.combinatoricsModule.generateStudentGroups(r);
        }
    }
}

// --- MAIN LOOP ---
int main() {
    printHeader();
    cout << " Initialize System?\n";
    cout << " 1. Load Master Test Suite (Module 12) [RECOMMENDED]\n";
    cout << " 2. Start Empty\n";
    cout << "> ";

    int init; cin >> init;
    if (init == 1) loadMasterTestSuite();

    while (true) {
        clearScreen();
        printHeader();
        cout << "\n [ DATA & RELATIONS ]\n";
        cout << "  1.  Sets (View Students, etc.)\n";
        cout << "  2.  Relations (Module 6)\n";
        cout << "  3.  Functions (Module 7)\n";

        cout << "\n [ DISCRETE MATH ENGINES ]\n";
        cout << "  4.  Scheduling & Graphs (Module 1)\n";
        cout << "  5.  Combinatorics (Module 2)\n";
        cout << "  6.  Induction Proofs (Module 3)\n";
        cout << "  7.  Logic Inference (Module 4)\n";
        cout << "  8.  Automated Proof Gen (Module 8)\n";

        cout << "\n  0.  Exit\n> ";

        int choice; cin >> choice;
        switch (choice) {
        case 1: engine.setModule.printStudentSet(); engine.setModule.printCourseSet(); system("pause"); break;
        case 2: relationMenuUI(); break;
        case 3: functionMenuUI(); break;
        case 4: schedulingMenuUI(); break;
        case 5: combinatoricsMenuUI(); break;
        case 6: inductionMenuUI(); break;
        case 7: logicMenuUI(); break;
        case 8: proofMenuUI(); break;
        case 0: return 0;
        default: cout << "Invalid.\n";
        }
    }
}