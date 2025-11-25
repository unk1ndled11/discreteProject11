#include "ProofModule.h"
#include <iostream>
#include <iomanip>

using namespace std;

// 1. REFLEXIVITY PROOF
// Definition: For EVERY student 'x', (x, x) must exist in the relation.
void ProofModule::proveReflexivity() {
    cout << "\n=== FORMAL PROOF: REFLEXIVITY ===\n";
    cout << "Target Relation: 'Study Partner' (Student x Student)\n";
    cout << "Definition: For all x in Set A, (x,x) must be in R.\n";
    cout << "--------------------------------------------------------\n";

    SimpleVector<int> universe = setModule->getAllStudentIDs();
    SimpleVector<RelationPair<int, int>>* rel = relationModule->getRawPeerData();

    bool isReflexive = true;
    int counterExample = -1;

    cout << "[Analysis Log]\n";
    for (int i = 0; i < universe.getSize(); i++) {
        int x = universe[i];
        bool found = false;

        // Search for self-loop
        for (int j = 0; j < rel->getSize(); j++) {
            if ((*rel)[j].a == x && (*rel)[j].b == x) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << "  [Pass] Student " << x << " has self-loop (x,x).\n";
        }
        else {
            cout << "  [FAIL] Student " << x << " is MISSING self-loop (x,x).\n";
            isReflexive = false;
            counterExample = x;
            break; // Stop at first failure
        }
    }

    cout << "\n--------------------------------------------------------\n";
    if (isReflexive) {
        cout << "MATHEMATICAL CONCLUSION:\n";
        cout << "1. The Set A contains " << universe.getSize() << " elements.\n";
        cout << "2. We verified (x,x) exists for every x in A.\n";
        cout << "3. Therefore, R IS REFLEXIVE. Q.E.D.\n";
    }
    else {
        cout << "PROOF BY COUNTEREXAMPLE:\n";
        cout << "1. Let x = " << counterExample << ".\n";
        cout << "2. x is an element of the Set of Students.\n";
        cout << "3. However, the pair (" << counterExample << ", " << counterExample << ") is NOT in R.\n";
        cout << "4. Therefore, R is NOT REFLEXIVE. Q.E.D.\n";
    }
}

// 2. SYMMETRY PROOF
// Definition: If (a,b) exists, (b,a) must exist.
void ProofModule::proveSymmetry() {
    cout << "\n=== FORMAL PROOF: SYMMETRY ===\n";
    cout << "Target Relation: 'Study Partner' (Student x Student)\n";
    cout << "Definition: For all (a,b) in R, (b,a) must also be in R.\n";
    cout << "--------------------------------------------------------\n";

    SimpleVector<RelationPair<int, int>>* rel = relationModule->getRawPeerData();
    bool isSymmetric = true;
    RelationPair<int, int> badPair;

    if (rel->getSize() == 0) {
        cout << "[Note] Relation is empty. Vacuously Symmetric.\n";
        return;
    }

    cout << "[Analysis Log]\n";
    for (int i = 0; i < rel->getSize(); i++) {
        int a = (*rel)[i].a;
        int b = (*rel)[i].b;

        if (a == b) continue; // (x,x) is trivially symmetric

        bool inverseFound = false;
        for (int j = 0; j < rel->getSize(); j++) {
            if ((*rel)[j].a == b && (*rel)[j].b == a) {
                inverseFound = true;
                break;
            }
        }

        if (inverseFound) {
            cout << "  [Pass] Pair (" << a << "," << b << ") has inverse (" << b << "," << a << ").\n";
        }
        else {
            cout << "  [FAIL] Pair (" << a << "," << b << ") has NO inverse.\n";
            isSymmetric = false;
            badPair.a = a; badPair.b = b;
            break;
        }
    }

    cout << "\n--------------------------------------------------------\n";
    if (isSymmetric) {
        cout << "MATHEMATICAL CONCLUSION:\n";
        cout << "1. We inspected all pairs in R.\n";
        cout << "2. For every (a,b), the inverse (b,a) was found.\n";
        cout << "3. Therefore, R IS SYMMETRIC. Q.E.D.\n";
    }
    else {
        cout << "PROOF BY COUNTEREXAMPLE:\n";
        cout << "1. The pair (" << badPair.a << ", " << badPair.b << ") exists in R.\n";
        cout << "2. However, (" << badPair.b << ", " << badPair.a << ") does NOT exist in R.\n";
        cout << "3. Therefore, R is NOT SYMMETRIC. Q.E.D.\n";
    }
}

// 3. TRANSITIVITY PROOF
// Definition: If (a,b) and (b,c) exist, (a,c) must exist.
void ProofModule::proveTransitivity() {
    cout << "\n=== FORMAL PROOF: TRANSITIVITY ===\n";
    cout << "Target Relation: 'Study Partner' (Student x Student)\n";
    cout << "Definition: If (a,b) and (b,c) are in R, then (a,c) must be in R.\n";
    cout << "--------------------------------------------------------\n";

    SimpleVector<RelationPair<int, int>>* rel = relationModule->getRawPeerData();
    bool isTransitive = true;
    int v1 = -1, v2 = -1, v3 = -1;

    cout << "[Analysis Log]\n";
    // Loop 1: Find (a,b)
    for (int i = 0; i < rel->getSize(); i++) {
        int a = (*rel)[i].a;
        int b = (*rel)[i].b;

        // Loop 2: Find (b,c)
        for (int j = 0; j < rel->getSize(); j++) {
            if ((*rel)[j].a == b) {
                int c = (*rel)[j].b;

                // We found a chain: a -> b -> c. 
                // Now checking for a -> c
                bool shortcutFound = false;
                for (int k = 0; k < rel->getSize(); k++) {
                    if ((*rel)[k].a == a && (*rel)[k].b == c) {
                        shortcutFound = true;
                        break;
                    }
                }

                if (shortcutFound) {
                    cout << "  [Pass] Chain (" << a << "," << b << ")->(" << b << "," << c
                        << ") satisfied by (" << a << "," << c << ").\n";
                }
                else {
                    cout << "  [FAIL] Chain (" << a << "," << b << ")->(" << b << "," << c
                        << ") BROKEN. (" << a << "," << c << ") missing.\n";
                    isTransitive = false;
                    v1 = a; v2 = b; v3 = c;
                    break;
                }
            }
        }
        if (!isTransitive) break;
    }

    cout << "\n--------------------------------------------------------\n";
    if (isTransitive) {
        cout << "MATHEMATICAL CONCLUSION:\n";
        cout << "1. We examined all transitive chains in R.\n";
        cout << "2. All chains were closed (a->c exists).\n";
        cout << "3. Therefore, R IS TRANSITIVE. Q.E.D.\n";
    }
    else {
        cout << "PROOF BY COUNTEREXAMPLE:\n";
        cout << "1. Found chain: (" << v1 << "," << v2 << ") and (" << v2 << "," << v3 << ").\n";
        cout << "2. This implies (" << v1 << "," << v3 << ") must exist.\n";
        cout << "3. The pair (" << v1 << "," << v3 << ") is NOT in R.\n";
        cout << "4. Therefore, R is NOT TRANSITIVE. Q.E.D.\n";
    }
}