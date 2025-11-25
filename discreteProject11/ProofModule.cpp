#include "ProofModule.h"
#include <iostream>
#include <iomanip>

using namespace std;

// 1. REFLEXIVITY PROOF
// Definition: For EVERY student 'x', is 'x' partners with themselves? (x, x)
void ProofModule::proveReflexivity() {
    cout << "\n=== FORMAL PROOF: REFLEXIVITY ===\n";
    cout << "Relation: 'Study Partner' (Student x Student)\n";
    cout << "Definition: A relation R on set A is reflexive if for all x in A, (x,x) is in R.\n";
    cout << "--------------------------------------------------------\n";

    SimpleVector<int> universe = setModule->getAllStudentIDs();
    SimpleVector<RelationPair<int, int>>* rel = relationModule->getRawPeerData();

    int counterExample = -1;
    bool isReflexive = true;

    // Logic Loop
    for (int i = 0; i < universe.getSize(); i++) {
        int x = universe[i];
        bool selfLoopFound = false;

        // Scan relation for (x, x)
        for (int j = 0; j < rel->getSize(); j++) {
            if ((*rel)[j].a == x && (*rel)[j].b == x) {
                selfLoopFound = true;
                break;
            }
        }

        if (!selfLoopFound) {
            isReflexive = false;
            counterExample = x;
            break; // Stop looking, we found a flaw
        }
    }

    // Generate Text
    if (isReflexive) {
        cout << "Proof Steps:\n";
        cout << "1. The Set A (Students) contains " << universe.getSize() << " elements.\n";
        cout << "2. We inspected every student x in A.\n";
        cout << "3. For every x, the pair (x, x) was found in R.\n";
        cout << "CONCLUSION: Since the definition is satisfied for all x, R IS Reflexive. Q.E.D.\n";
    }
    else {
        cout << "Proof by Counterexample:\n";
        cout << "1. Let x = " << counterExample << ".\n";
        cout << "2. x is an element of Set A.\n";
        cout << "3. However, the pair (" << counterExample << ", " << counterExample << ") is NOT in R.\n";
        cout << "CONCLUSION: Since there exists an x such that (x,x) is not in R, R is NOT Reflexive. Q.E.D.\n";
    }
}

// 2. SYMMETRY PROOF
// Definition: If Ali partners Bob, Bob MUST partner Ali.
void ProofModule::proveSymmetry() {
    cout << "\n=== FORMAL PROOF: SYMMETRY ===\n";
    cout << "Definition: R is symmetric if for all (a,b) in R, (b,a) is also in R.\n";
    cout << "--------------------------------------------------------\n";

    SimpleVector<RelationPair<int, int>>* rel = relationModule->getRawPeerData();
    bool isSymmetric = true;
    RelationPair<int, int> badPair;

    // Loop through every pair in the relation
    for (int i = 0; i < rel->getSize(); i++) {
        int a = (*rel)[i].a;
        int b = (*rel)[i].b;

        // Skip (a,a) pairs, they are trivially symmetric
        if (a == b) continue;

        // Check if inverse (b,a) exists
        bool foundInverse = false;
        for (int j = 0; j < rel->getSize(); j++) {
            if ((*rel)[j].a == b && (*rel)[j].b == a) {
                foundInverse = true;
                break;
            }
        }

        if (!foundInverse) {
            isSymmetric = false;
            badPair.a = a;
            badPair.b = b;
            break;
        }
    }

    // Generate Text
    if (isSymmetric) {
        cout << "Proof Steps:\n";
        cout << "1. Checked all " << rel->getSize() << " pairs in R.\n";
        cout << "2. For every pair (a,b), the inverse (b,a) was found.\n";
        cout << "CONCLUSION: R IS Symmetric. Q.E.D.\n";
    }
    else {
        cout << "Proof by Counterexample:\n";
        cout << "1. Found pair (" << badPair.a << ", " << badPair.b << ") in R.\n";
        cout << "2. Searched for inverse pair (" << badPair.b << ", " << badPair.a << ").\n";
        cout << "3. Inverse pair was NOT found.\n";
        cout << "CONCLUSION: R is NOT Symmetric. Q.E.D.\n";
    }
}

// 3. TRANSITIVITY PROOF
// Definition: If A->B and B->C, then A->C must exist.
void ProofModule::proveTransitivity() {
    cout << "\n=== FORMAL PROOF: TRANSITIVITY ===\n";
    cout << "Definition: R is transitive if ((a,b) in R ^ (b,c) in R) -> (a,c) in R.\n";
    cout << "--------------------------------------------------------\n";

    SimpleVector<RelationPair<int, int>>* rel = relationModule->getRawPeerData();
    bool isTransitive = true;
    int v1 = -1, v2 = -1, v3 = -1;

    // Loop 1: Find (a, b)
    for (int i = 0; i < rel->getSize(); i++) {
        int a = (*rel)[i].a;
        int b = (*rel)[i].b;

        // Loop 2: Find (b, c)
        for (int j = 0; j < rel->getSize(); j++) {
            if ((*rel)[j].a == b) { // Connection found!
                int c = (*rel)[j].b;

                // We have a chain: a -> b -> c
                // Now we MUST find a -> c
                bool foundShortcut = false;
                for (int k = 0; k < rel->getSize(); k++) {
                    if ((*rel)[k].a == a && (*rel)[k].b == c) {
                        foundShortcut = true;
                        break;
                    }
                }

                if (!foundShortcut) {
                    isTransitive = false;
                    v1 = a; v2 = b; v3 = c;
                    break; // Break Loop 2
                }
            }
        }
        if (!isTransitive) break; // Break Loop 1
    }

    // Generate Text
    if (isTransitive) {
        cout << "Proof Steps:\n";
        cout << "1. Examined all transitive chains ((a,b), (b,c)).\n";
        cout << "2. For each chain, verified (a,c) exists.\n";
        cout << "CONCLUSION: R IS Transitive. Q.E.D.\n";
    }
    else {
        cout << "Proof by Counterexample:\n";
        cout << "1. Found chain: (" << v1 << "," << v2 << ") and (" << v2 << "," << v3 << ").\n";
        cout << "2. This implies (" << v1 << "," << v3 << ") must exist.\n";
        cout << "3. However, (" << v1 << "," << v3 << ") is NOT in R.\n";
        cout << "CONCLUSION: R is NOT Transitive. Q.E.D.\n";
    }
}