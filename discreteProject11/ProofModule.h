#ifndef PROOF_MODULE_H
#define PROOF_MODULE_H

#include "SetsRelationsFunctions.h"
#include <iostream>

class ProofModule {
private:
    SetModule* setModule;
    RelationModule* relationModule;

public:
    ProofModule(SetModule* sm, RelationModule* rm) : setModule(sm), relationModule(rm) {}

    // 1. Generate Formal Proof for Reflexivity
    // Prints a step-by-step mathematical argument.
    void proveReflexivity();

    // 2. Generate Formal Proof for Transitivity
    // Shows the logic chain for every connection.
    void proveTransitivity();

    // 3. Generate Formal Proof for Symmetry
    void proveSymmetry();
};

#endif