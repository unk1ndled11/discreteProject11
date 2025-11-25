#include "LogicModule.h"
#include <iostream>
#include <iomanip>
#include <cstring> 

using namespace std;

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
    cout << " rule added: if (" << condition << ") then (" << result << ")\n";
}

void LogicModule::addFact(const char* fact) {
    if (!isFactKnown(fact)) {
        char* newFact = new char[100];
        int i = 0; while (fact[i] && i < 99) { newFact[i] = fact[i]; i++; } newFact[i] = '\0';

        knownFacts.push_back(newFact);
        cout << " fact added: " << fact << "\n";
    }
}

void LogicModule::runInferenceEngine() {
    cout << "\n=== running inference ===\n";

    bool newFactDerived = true;
    int pass = 1;

    while (newFactDerived) {
        newFactDerived = false;

        for (int i = 0; i < rules.getSize(); i++) {
            if (isFactKnown(rules[i].condition)) {
                if (!isFactKnown(rules[i].result)) {
                    cout << "  [pass " << pass << "] applied rule: " << rules[i].result << endl;
                    addFact(rules[i].result);
                    newFactDerived = true;
                }
            }
        }
        pass++;
    }

    cout << "\n=== final knowledge ===\n";
    for (int i = 0; i < knownFacts.getSize(); i++) {
        cout << "  - " << knownFacts[i] << endl;
    }
}

void LogicModule::clearKnowledgeBase() {
}