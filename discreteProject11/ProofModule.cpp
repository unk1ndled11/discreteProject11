#include "ProofModule.h"
#include <iostream>
#include <iomanip>

using namespace std;

void ProofModule::proveReflexivity() {
    cout << "\n=== proof: reflexivity ===\n";
    cout << "target: 'study partner'\n";
    cout << "--------------------------------------------------------\n";

    SimpleVector<int> universe = setModule->getAllStudentIDs();
    SimpleVector<RelationPair<int, int>>* rel = relationModule->getRawPeerData();

    bool isReflexive = true;
    int counterExample = -1;

    cout << "[log]\n";
    for (int i = 0; i < universe.getSize(); i++) {
        int x = universe[i];
        bool found = false;

        for (int j = 0; j < rel->getSize(); j++) {
            if ((*rel)[j].a == x && (*rel)[j].b == x) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << "  [pass] student " << x << " has self-loop.\n";
        }
        else {
            cout << "  [fail] student " << x << " missing self-loop.\n";
            isReflexive = false;
            counterExample = x;
            break;
        }
    }

    cout << "\n--------------------------------------------------------\n";
    if (isReflexive) {
        cout << "conclusion: reflexive. q.e.d.\n";
    }
    else {
        cout << "proof by counterexample:\n";
        cout << "1. x = " << counterExample << ".\n";
        cout << "2. (x,x) not in r.\n";
        cout << "3. not reflexive. q.e.d.\n";
    }
}

void ProofModule::proveSymmetry() {
    cout << "\n=== proof: symmetry ===\n";
    cout << "target: 'study partner'\n";
    cout << "--------------------------------------------------------\n";

    SimpleVector<RelationPair<int, int>>* rel = relationModule->getRawPeerData();
    bool isSymmetric = true;
    RelationPair<int, int> badPair;

    if (rel->getSize() == 0) {
        cout << "relation empty.\n";
        return;
    }

    cout << "[log]\n";
    for (int i = 0; i < rel->getSize(); i++) {
        int a = (*rel)[i].a;
        int b = (*rel)[i].b;

        if (a == b) continue;

        bool inverseFound = false;
        for (int j = 0; j < rel->getSize(); j++) {
            if ((*rel)[j].a == b && (*rel)[j].b == a) {
                inverseFound = true;
                break;
            }
        }

        if (inverseFound) {
            cout << "  [pass] pair (" << a << "," << b << ") has inverse.\n";
        }
        else {
            cout << "  [fail] pair (" << a << "," << b << ") has no inverse.\n";
            isSymmetric = false;
            badPair.a = a; badPair.b = b;
            break;
        }
    }

    cout << "\n--------------------------------------------------------\n";
    if (isSymmetric) {
        cout << "conclusion: symmetric. q.e.d.\n";
    }
    else {
        cout << "proof by counterexample:\n";
        cout << "1. pair (" << badPair.a << ", " << badPair.b << ") exists.\n";
        cout << "2. inverse missing.\n";
        cout << "3. not symmetric. q.e.d.\n";
    }
}

void ProofModule::proveTransitivity() {
    cout << "\n=== proof: transitivity ===\n";
    cout << "target: 'study partner'\n";
    cout << "--------------------------------------------------------\n";

    SimpleVector<RelationPair<int, int>>* rel = relationModule->getRawPeerData();
    bool isTransitive = true;
    int v1 = -1, v2 = -1, v3 = -1;

    cout << "[log]\n";
    for (int i = 0; i < rel->getSize(); i++) {
        int a = (*rel)[i].a;
        int b = (*rel)[i].b;

        for (int j = 0; j < rel->getSize(); j++) {
            if ((*rel)[j].a == b) {
                int c = (*rel)[j].b;

                bool shortcutFound = false;
                for (int k = 0; k < rel->getSize(); k++) {
                    if ((*rel)[k].a == a && (*rel)[k].b == c) {
                        shortcutFound = true;
                        break;
                    }
                }

                if (shortcutFound) {
                    cout << "  [pass] chain (" << a << "," << b << ")->(" << b << "," << c
                        << ") satisfied.\n";
                }
                else {
                    cout << "  [fail] chain (" << a << "," << b << ")->(" << b << "," << c
                        << ") broken.\n";
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
        cout << "conclusion: transitive. q.e.d.\n";
    }
    else {
        cout << "proof by counterexample:\n";
        cout << "1. found chain: (" << v1 << "," << v2 << ") and (" << v2 << "," << v3 << ").\n";
        cout << "2. (" << v1 << "," << v3 << ") missing.\n";
        cout << "3. not transitive. q.e.d.\n";
    }
}