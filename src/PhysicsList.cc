#include "PhysicsList.hh"

#include "G4EmPenelopePhysics.hh"
#include "G4SystemOfUnits.hh"

// --------------------------------------------------------------------
PhysicsList::PhysicsList()
: G4VModularPhysicsList()
{
    // ================================================================
    // EM PHYSICS: PENELOPE (sesuai paper)
    // ================================================================
    RegisterPhysics(new G4EmPenelopePhysics());

    // ================================================================
    // Default cut value
    // ================================================================
    SetDefaultCutValue(0.1 * mm);
}

// --------------------------------------------------------------------
PhysicsList::~PhysicsList()
{}
