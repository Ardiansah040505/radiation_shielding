#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Gamma.hh"
#include "G4Event.hh"

#include "G4SystemOfUnits.hh"

// --------------------------------------------------------------------
PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(nullptr)
{
    // ================================================================
    // Particle gun: 1 particle per event
    // ================================================================
    fParticleGun = new G4ParticleGun(1);

    // ================================================================
    // Particle definition: gamma
    // ================================================================
    fParticleGun->SetParticleDefinition(G4Gamma::Gamma());

    // ================================================================
    // Default energy (akan dioverride oleh macro)
    // ================================================================
    fParticleGun->SetParticleEnergy(0.662 * MeV);

    // ================================================================
    // Direction: along +Z (source -> pumice -> detector)
    // ================================================================
    fParticleGun->SetParticleMomentumDirection(
        G4ThreeVector(0.0, 0.0, 1.0)
    );

    // ================================================================
    // Position: 15 cm in front of detector
    // Detector at z = 0 → source at z = -15 cm
    // ================================================================
    fParticleGun->SetParticlePosition(
        G4ThreeVector(0.0, 0.0, -15.0 * cm)
    );
}

// --------------------------------------------------------------------
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

// --------------------------------------------------------------------
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    fParticleGun->GeneratePrimaryVertex(event);
}
