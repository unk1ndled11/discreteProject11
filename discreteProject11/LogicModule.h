#ifndef LOGIC_MODULE_H
#define LOGIC_MODULE_H

#include "SimpleVector.h"
#include "Entities.h"
#include "SetsRelationsFunctions.h"

struct LogicRule {
    char condition[100];
    char result[100];

    LogicRule() { condition[0] = '\0'; result[0] = '\0'; }
    LogicRule(const char* c, const char* r) {
        int i = 0; while (c[i] && i < 99) { condition[i] = c[i]; i++; } condition[i] = '\0';
        i = 0; while (r[i] && i < 99) { result[i] = r[i]; i++; } result[i] = '\0';
    }
};

class LogicModule {
private:
    SimpleVector<LogicRule> rules;
    SimpleVector<const char*> knownFacts;

    bool isFactKnown(const char* fact);

public:
    // rule add karnay wala
    void addRule(const char* condition, const char* result);

    // fact add karnay wala
    void addFact(const char* fact);

    // inference engine
    void runInferenceEngine();

    // clear
    void clearKnowledgeBase();
};

#endif