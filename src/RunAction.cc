#include "RunAction.hh"

#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

// --------------------------------------------------------------------
RunAction::RunAction()
: G4UserRunAction(),
  fEventID(0)
{}

// --------------------------------------------------------------------
RunAction::~RunAction()
{
    if (fOutFile.is_open()) {
        fOutFile.close();
    }
}

// --------------------------------------------------------------------
void RunAction::BeginOfRunAction(const G4Run*)
{
    fEventID = 0;

    // buka file CSV
    fOutFile.open("energy_spectrum.csv");

    // header
    fOutFile << "event_id,edep_MeV\n";
}

// --------------------------------------------------------------------
void RunAction::EndOfRunAction(const G4Run*)
{
    if (fOutFile.is_open()) {
        fOutFile.close();
    }
}

// --------------------------------------------------------------------
void RunAction::AddEventEnergy(G4double edep)
{
    // simpan per event (konversi ke MeV)
    fOutFile
        << fEventID << ","
        << edep / MeV << "\n";

    fEventID++;
}
