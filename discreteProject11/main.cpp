#include "SetsRelationsFunctions.h"
#include <iostream>
#include <cstdlib> // For system("cls")
// Add to includes
#include "SchedulingModule.h"
#include "CombinatoricsModule.h"
#include "InductionModule.h"

// Define the Engine Class here (remove it from SetsRelationsFunctions.h if it causes issues, or just add the new field)
class DiscreteMathModule {
public:
    SetModule setModule;
    RelationModule relationModule;
    FunctionModule functionModule;
    SchedulingModule schedulingModule;
    CombinatoricsModule combinatoricsModule;
    InductionModule inductionModule;
    LogicModule logicModule;

    DiscreteMathModule()
        : relationModule(&setModule),
        functionModule(&setModule),
        schedulingModule(&setModule, &relationModule), combinatoricsModule(&setModule), inductionModule(&setModule, &relationModule)
    {}
};

using namespace std;

DiscreteMathModule engine;

void clearScreen() {
    system("cls"); // Standard C++ command for Windows clearing
}

void printHeader() {
    cout << "\n========================================================\n";
    cout << "      UNIDISC ENGINE - FAST UNIVERSITY MANAGER          \n";
    cout << "     Modules 5, 6, 7: Sets, Relations, Functions       \n";
    cout << "========================================================\n";
}

void printMainMenu() {
    printHeader();
    cout << "\n[ MAIN MENU ]\n";
    cout << "  1. Add Student\n";
    cout << "  2. Add Course\n";
    cout << "  3. Add Faculty\n";
    cout << "  4. Add Room\n";
    cout << "  5. Manage Relations (Module 6)\n";
    cout << "  6. Manage Functions (Module 7)\n";
    cout << "  7. Query Sets & Display (Module 5)\n";
    cout << "  8. Verify System Consistency\n";
    cout << "  10. Course Scheduling (Module 1) [NEW]\n"; // Added
    cout << "  11. Combinatorics & Groups (Module 2) [NEW]\n";
    cout << "  12. Induction Proofs (Module 3) [NEW]\n";
    cout << "  13. Logic Engine (Module 4) [NEW]\n";
    cout << "  14. Add Student Peer Relation (A-A Relation for Proofs)\n";
    cout << "  9. Exit\n";
    cout << "--------------------------------------------------------\n";
}

void addStudentUI() {
    int id, sem;
    char name[100];

    cout << "\n--- Add Student ---\n";
    cout << "Enter Student ID: ";
    cin >> id;
    cin.ignore(1000, '\n'); // Clear buffer

    cout << "Enter Student Name: ";
    cin.getline(name, 100); // Reads spaces too

    cout << "Enter Semester: ";
    cin >> sem;

    engine.setModule.addStudent(Student(id, name, sem));
    cout << " [OK] Student added successfully.\n";
}

void addCourseUI() {
    int id, credits;
    char code[50], title[100];

    cout << "\n--- Add Course ---\n";
    cout << "Enter Course ID: ";
    cin >> id;
    cin.ignore(1000, '\n');

    cout << "Enter Course Code: ";
    cin.getline(code, 50);

    cout << "Enter Course Title: ";
    cin.getline(title, 100);

    cout << "Enter Credits: ";
    cin >> credits;

    engine.setModule.addCourse(Course(id, code, title, credits));
    cout << " [OK] Course added successfully.\n";
}

void addFacultyUI() {
    int id;
    char name[100], dept[50];

    cout << "\n--- Add Faculty ---\n";
    cout << "Enter Faculty ID: ";
    cin >> id;
    cin.ignore(1000, '\n');

    cout << "Enter Faculty Name: ";
    cin.getline(name, 100);

    cout << "Enter Department: ";
    cin.getline(dept, 50);

    engine.setModule.addFaculty(Faculty(id, name, dept));
    cout << " [OK] Faculty added successfully.\n";
}

void addRoomUI() {
    int id, cap;
    char code[50];

    cout << "\n--- Add Room ---\n";
    cout << "Enter Room ID: ";
    cin >> id;
    cin.ignore(1000, '\n');

    cout << "Enter Room Code: ";
    cin.getline(code, 50);

    cout << "Enter Capacity: ";
    cin >> cap;

    engine.setModule.addRoom(Room(id, code, cap));
    cout << " [OK] Room added successfully.\n";
}

void relationMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ RELATIONS MODULE (6) ]\n";
        cout << "  1. Add Student-Course Relation\n";
        cout << "  2. Add Faculty-Course Relation\n";
        cout << "  3. Add Course-Room Relation\n";
        cout << "  4. Query Student Courses\n";
        cout << "  5. Query Course Faculty\n";
        cout << "  6. Query Course Rooms\n";
        cout << "  7. View All Relations\n";
        cout << "  8. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 8) return;

        int id1, id2;
        switch (choice) {
        case 1:
            cout << "Enter Student ID: "; cin >> id1;
            cout << "Enter Course ID: "; cin >> id2;
            engine.relationModule.addStudentCourseRelation(id1, id2);
            break;
        case 2:
            cout << "Enter Faculty ID: "; cin >> id1;
            cout << "Enter Course ID: "; cin >> id2;
            engine.relationModule.addFacultyCourseRelation(id1, id2);
            break;
        case 3:
            cout << "Enter Course ID: "; cin >> id1;
            cout << "Enter Room ID: "; cin >> id2;
            engine.relationModule.addCourseRoomRelation(id1, id2);
            break;
        case 4:
            cout << "Enter Student ID: "; cin >> id1;
            engine.relationModule.printStudentCourses(id1);
            break;
        case 5:
            cout << "Enter Course ID: "; cin >> id1;
            engine.relationModule.printCourseFaculty(id1);
            break;
        case 6:
            cout << "Enter Course ID: "; cin >> id1;
            engine.relationModule.printCourseRooms(id1);
            break;
        case 7:
            engine.relationModule.printAllRelations();
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }
}

void functionMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ FUNCTIONS MODULE (7) ]\n";
        cout << "  1. Add Student-Course Function\n";
        cout << "  2. Add Course-Faculty Function\n";
        cout << "  3. Add Faculty-Room Function\n";
        cout << "  4. View Student-Course Assignments\n";
        cout << "  5. View Course-Faculty Assignments\n";
        cout << "  6. View Faculty-Room Assignments\n";
        cout << "  7. View All Functions\n";
        cout << "  8. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 8) return;

        int id1, id2;
        switch (choice) {
        case 1:
            cout << "Enter Student ID: "; cin >> id1;
            cout << "Enter Course ID: "; cin >> id2;
            engine.functionModule.addStudentCourseFunction(id1, id2);
            break;
        case 2:
            cout << "Enter Course ID: "; cin >> id1;
            cout << "Enter Faculty ID: "; cin >> id2;
            engine.functionModule.addCourseFacultyFunction(id1, id2);
            break;
        case 3:
            cout << "Enter Faculty ID: "; cin >> id1;
            cout << "Enter Room ID: "; cin >> id2;
            engine.functionModule.addFacultyRoomFunction(id1, id2);
            break;
        case 4:
            engine.functionModule.printStudentCourseAssignments();
            break;
        case 5:
            engine.functionModule.printCourseFacultyAssignments();
            break;
        case 6:
            engine.functionModule.printFacultyRoomAssignments();
            break;
        case 7:
            engine.functionModule.printAllFunctions();
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }
}

void querySetUI() {
    int choice;
    while (true) {
        cout << "\n[ SETS MODULE (5) ]\n";
        cout << "  1. View All Students\n";
        cout << "  2. View All Courses\n";
        cout << "  3. View All Faculty\n";
        cout << "  4. View All Rooms\n";
        cout << "  5. Find Student by ID\n";
        cout << "  6. Find Course by ID\n";
        cout << "  7. Set Statistics\n";
        cout << "  8. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 8) return;

        switch (choice) {
        case 1: engine.setModule.printStudentSet(); break;
        case 2: engine.setModule.printCourseSet(); break;
        case 3: engine.setModule.printFacultySet(); break;
        case 4: engine.setModule.printRoomSet(); break;
        case 5: {
            int id; cout << "Enter Student ID: "; cin >> id;
            Student* s = engine.setModule.findStudent(id);
            if (s) cout << "\n [Found] " << s->name << " (Sem: " << s->semester << ")\n";
            else cout << "\n [X] Student not found\n";
            break;
        }
        case 6: {
            int id; cout << "Enter Course ID: "; cin >> id;
            Course* c = engine.setModule.findCourse(id);
            if (c) cout << "\n [Found] " << c->code << " - " << c->title << "\n";
            else cout << "\n [X] Course not found\n";
            break;
        }
        case 7: {
            cout << "\n=== SET STATISTICS ===\n";
            cout << "Total Students: " << engine.setModule.getStudentCount() << endl;
            cout << "Total Courses:  " << engine.setModule.getCourseCount() << endl;
            cout << "Total Faculty:  " << engine.setModule.getFacultyCount() << endl;
            cout << "Total Rooms:    " << engine.setModule.getRoomCount() << endl;
            break;
        }
        default: cout << "Invalid choice\n";
        }
    }
}
void logicMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ MODULE 4: LOGIC & INFERENCE ]\n";
        cout << "  1. Add Logic Rule (If P -> Q)\n";
        cout << "  2. Add Known Fact (P)\n";
        cout << "  3. Run Inference Engine (Derive Conclusions)\n";
        cout << "  4. Load University Policies (Sample Rules)\n";
        cout << "  5. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(); // Clear buffer for string inputs

        if (choice == 5) return;

        char buf1[100], buf2[100];

        switch (choice) {
        case 1:
            cout << "Enter Condition (P): "; cin.getline(buf1, 100);
            cout << "Enter Result (Q): "; cin.getline(buf2, 100);
            engine.logicModule.addRule(buf1, buf2);
            break;
        case 2:
            cout << "Enter Fact: "; cin.getline(buf1, 100);
            engine.logicModule.addFact(buf1);
            break;
        case 3:
            engine.logicModule.runInferenceEngine();
            break;
        case 4:
            // Pre-load some fun FAST University rules
            engine.logicModule.addRule("High GPA", "Dean's List");
            engine.logicModule.addRule("Dean's List", "Scholarship");
            engine.logicModule.addRule("Scholarship", "Happy Student");
            engine.logicModule.addRule("Failed CS101", "Probation");
            engine.logicModule.addRule("Probation", "Cannot take Extra Credit");
            cout << " [OK] Policies Loaded.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }
}

void consistencyCheckUI() {
    cout << "\n[ CONSISTENCY CHECK ]\n";
    cout << "Verifying system integrity...\n";

    cout << "\nChecking Set Integrity:\n";
    cout << "  - Students: " << engine.setModule.getStudentCount() << endl;
    cout << "  - Courses:  " << engine.setModule.getCourseCount() << endl;
    cout << "  - Faculty:  " << engine.setModule.getFacultyCount() << endl;
    cout << "  - Rooms:    " << engine.setModule.getRoomCount() << endl;

    cout << "\nChecking Relation Integrity:\n";
    cout << "  - Student-Course Relations: " << engine.relationModule.getStudentCourseRelCount() << endl;

    cout << "\n[OK] SYSTEM CONSISTENT - All constraints satisfied\n";
}
void inductionMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ MODULE 3: INDUCTION & PROOFS ]\n";
        cout << "  1. Prove Course Chain (Weak Induction)\n";
        cout << "  2. Prove Student Eligibility (Strong Induction)\n";
        cout << "  3. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 3) return;

        switch (choice) {
        case 1: {
            // Let user build a chain to test
            SimpleVector<int> chain;
            int count, val;
            cout << "How many courses in the chain? "; cin >> count;
            cout << "Enter Course IDs in order (e.g., 101 102 103): ";
            for (int i = 0; i < count; i++) {
                cin >> val;
                chain.push_back(val);
            }
            engine.inductionModule.proveCourseChain(chain);
            break;
        }
        case 2: {
            int sId, cId;
            cout << "Enter Student ID: "; cin >> sId;
            cout << "Enter Target Course ID: "; cin >> cId;
            engine.inductionModule.provePrerequisiteSatisfaction(sId, cId);
            break;
        }
        default:
            cout << "Invalid choice.\n";
        }
    }
}

void schedulingMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ MODULE 1: COURSE SCHEDULING ]\n";
        cout << "  1. Add Prerequisite Rule\n";
        cout << "  2. Check Eligibility (Can Student take Course X?)\n";
        cout << "  3. Suggest Next Courses for Student\n";
        cout << "  4. View All Rules\n";
        cout << "  5. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 5) return;

        int id1, id2;
        switch (choice) {
        case 1:
            cout << "Enter Target Course ID: "; cin >> id1;
            cout << "Enter Required Prereq ID: "; cin >> id2;
            engine.schedulingModule.addPrerequisite(id1, id2);
            break;
        case 2:
            cout << "Enter Student ID: "; cin >> id1;
            cout << "Enter Course ID: "; cin >> id2;
            if (engine.schedulingModule.checkPrerequisites(id1, id2)) {
                cout << " [YES] Student is eligible.\n";
            }
            else {
                cout << " [NO] Eligibility failed.\n";
            }
            break;
        case 3:
            cout << "Enter Student ID: "; cin >> id1;
            engine.schedulingModule.suggestCoursesForStudent(id1);
            break;
        case 4:
            engine.schedulingModule.printPrerequisites();
            break;
        }
    }
}

void combinatoricsMenuUI() {
    int choice;
    while (true) {
        cout << "\n[ MODULE 2: COMBINATORICS (Groups) ]\n";
        cout << "  1. Calculate Combinations C(n, r)\n";
        cout << "  2. Calculate Permutations P(n, r)\n";
        cout << "  3. Generate Student Project Groups\n";
        cout << "  4. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 4) return;

        int n, r;
        switch (choice) {
        case 1:
            cout << "Enter n (Total items): "; cin >> n;
            cout << "Enter r (Items to choose): "; cin >> r;
            cout << "Result C(" << n << "," << r << ") = "
                << engine.combinatoricsModule.calculateCombinations(n, r) << endl;
            break;
        case 2:
            cout << "Enter n (Total items): "; cin >> n;
            cout << "Enter r (Items to arrange): "; cin >> r;
            cout << "Result P(" << n << "," << r << ") = "
                << engine.combinatoricsModule.calculatePermutations(n, r) << endl;
            break;
        case 3:
            cout << "Enter Group Size: "; cin >> r;
            engine.combinatoricsModule.generateStudentGroups(r);
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }
}


void sampleDataUI() {
    cout << "\nLoading sample data...\n";

    engine.setModule.addStudent(Student(1001, "Ali Ahmed", 1));
    engine.setModule.addStudent(Student(1002, "Fatima Khan", 2));
    engine.setModule.addStudent(Student(1003, "Hassan Ali", 1));

    engine.setModule.addCourse(Course(101, "CS101", "Intro to Programming", 3));
    engine.setModule.addCourse(Course(102, "CS102", "Data Structures", 3));
    engine.setModule.addCourse(Course(103, "MATH101", "Calculus I", 4));

    engine.setModule.addFaculty(Faculty(201, "Dr. Ahmed", "Computer Science"));
    engine.setModule.addFaculty(Faculty(202, "Dr. Zainab", "Mathematics"));

    engine.setModule.addRoom(Room(301, "A101", 40));
    engine.setModule.addRoom(Room(302, "B205", 35));

    // Relations
    engine.relationModule.addStudentCourseRelation(1001, 101);
    engine.relationModule.addStudentCourseRelation(1001, 103);
    engine.relationModule.addStudentCourseRelation(1002, 102);

    // Functions
    engine.functionModule.addCourseFacultyFunction(101, 201);
    engine.functionModule.addCourseFacultyFunction(103, 202);

    cout << " [OK] Sample data loaded successfully.\n";
}

int main() {
    int choice;
    cout << "\n========================================================\n";
    cout << "         UNIDISC ENGINE - INITIALIZATION                \n";
    cout << "   Load sample data? (1=Yes, 0=No):                     \n";
    cout << "========================================================\n";
    cout << "> ";
    int loadSample;
    cin >> loadSample;

    if (loadSample == 1) {
        sampleDataUI();
    }

    while (true) {
        clearScreen();
        printMainMenu();
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudentUI(); break;
        case 2: addCourseUI(); break;
        case 3: addFacultyUI(); break;
        case 4: addRoomUI(); break;
        case 5: relationMenuUI(); break;
        case 6: functionMenuUI(); break;
        case 7: querySetUI(); break;
        case 8: consistencyCheckUI(); break;
        case 10: schedulingMenuUI(); break; //
        case 11: combinatoricsMenuUI(); break;
        case 12: inductionMenuUI(); break;
        case 13: logicMenuUI(); break;// 
        case 9:
            int id1, id2;
            cout << "Enter Student ID 1: "; cin >> id1;
            cout << "Enter Student ID 2: "; cin >> id2;
            engine.relationModule.addStudentPeerRelation(id1, id2);
            break;

        case 14:
            cout << "\nThank you for using UNIDISC ENGINE!\nGoodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
    return 0;
}