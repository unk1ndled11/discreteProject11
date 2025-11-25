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

    // reflexivity proof
    void proveReflexivity();

    // transitivity proof
    void proveTransitivity();

    // symmetry proof
    void proveSymmetry();
};

#endif