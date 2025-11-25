#include "LogicModule.h"
#include <iostream>
#include <iomanip>
#include <cstring> // For strcmp

using namespace std;

// Helper: Check if strings match
bool stringsMatch(const char* s1, const char* s2) {
    return strcmp(s1, s2) == 0;
}

bool LogicModule::isFactKnown(const char* fact) {
    for (int i = 0; i < knownFacts.getSize(); i++) {
        if (stringsMatch(knownFacts[i], fact)) return true;
    }
    return false;
}

void LogicModule::addRule(const char* condition, const char* result) {
    rules.push_back(LogicRule(condition, result));
    cout << " [Rule Added] IF (" << condition << ") THEN (" << result << ")\n";
}

void LogicModule::addFact(const char* fact) {
    if (!isFactKnown(fact)) {
        // We need to store a persistent copy of the string
        char* newFact = new char[100];
        int i = 0; while (fact[i] && i < 99) { newFact[i] = fact[i]; i++; } newFact[i] = '\0';

        knownFacts.push_back(newFact);
        cout << " [Fact Added] " << fact << "\n";
    }
}

// === THE INFERENCE ENGINE (MODUS PONENS) ===
// It keeps looping through rules until no NEW facts can be derived.
void LogicModule::runInferenceEngine() {
    cout << "\n=== RUNNING LOGIC INFERENCE ===\n";

    bool newFactDerived = true;
    int pass = 1;

    while (newFactDerived) {
        newFactDerived = false;

        // Check every rule
        for (int i = 0; i < rules.getSize(); i++) {
            // Rule: P -> Q
            // Do we know P is true?
            if (isFactKnown(rules[i].condition)) {
                // Yes! P is true.
                // Do we already know Q?
                if (!isFactKnown(rules[i].result)) {
                    // No! We just discovered a NEW TRUTH.
                    cout << "  [Inference Pass " << pass << "] Applied Rule: IF "
                        << rules[i].condition << " THEN " << rules[i].result << endl;
                    cout << "  >>> Derived New Fact: " << rules[i].result << endl;

                    addFact(rules[i].result); // Add Q to known facts
                    newFactDerived = true;    // Flag to run loop again
                }
            }
        }
        pass++;
    }

    cout << "\n=== FINAL KNOWLEDGE BASE ===\n";
    for (int i = 0; i < knownFacts.getSize(); i++) {
        cout << "  - " << knownFacts[i] << endl;
    }
}

void LogicModule::clearKnowledgeBase() {
    //not really needed here
}