#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UImanager.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* detector)
:fDetector(detector)
{
    fDetectorDir = new G4UIdirectory("/detector/");
    fDetectorDir->SetGuidance("Detector Control Command");

    fPumiceCmd = new G4UIcmdWithAString("/detector/setPumice", this);
    fPumiceCmd->SetGuidance("Set the pumice material");
    fPumiceCmd->SetCandidates("Ijobalit Setangi Lingsar");
    fPumiceCmd->SetParameterName("pumice", false);
}

DetectorMessenger::~DetectorMessenger()
{
    delete fPumiceCmd;
    delete fDetectorDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if (command == fPumiceCmd) {
        fDetector->SetPumiceType(newValue);
    }
}