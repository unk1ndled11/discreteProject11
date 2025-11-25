#ifndef LOGIC_MODULE_H
#define LOGIC_MODULE_H

#include "SimpleVector.h"
#include "Entities.h"
#include "SetsRelationsFunctions.h"

struct LogicRule {
    char condition[100]; // The "If" part (P)
    char result[100];    // The "Then" part (Q)

    LogicRule() { condition[0] = '\0'; result[0] = '\0'; }
    LogicRule(const char* c, const char* r) {
        // Simple string copy
        int i = 0; while (c[i] && i < 99) { condition[i] = c[i]; i++; } condition[i] = '\0';
        i = 0; while (r[i] && i < 99) { result[i] = r[i]; i++; } result[i] = '\0';
    }
};

class LogicModule {
private:
    SimpleVector<LogicRule> rules;       // Knowledge Base (P -> Q)
    SimpleVector<const char*> knownFacts; // Things we know are TRUE

    // Helper to check if a fact is already known
    bool isFactKnown(const char* fact);

public:
    // 1. Add a Logic Rule (If P -> Q)
    void addRule(const char* condition, const char* result);

    // 2. Add a Fact (P is True)
    void addFact(const char* fact);

    // 3. Run Inference (Apply Modus Ponens to find ALL truths)
    void runInferenceEngine();

    // 4. Clear memory for a new scenario
    void clearKnowledgeBase();
};

#endif