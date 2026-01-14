#include "SteppingAction.hh"

#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4LogicalVolume.hh"

// --------------------------------------------------------------------
SteppingAction::SteppingAction(EventAction* eventAction,
                               const DetectorConstruction* detector)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fDetector(detector)
{}

// --------------------------------------------------------------------
SteppingAction::~SteppingAction()
{}

// --------------------------------------------------------------------
void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4double edep = step->GetTotalEnergyDeposit();
    if (edep <= 0.0) return;

    auto volume =
        step->GetPreStepPoint()
            ->GetTouchableHandle()
            ->GetVolume()
            ->GetLogicalVolume();

    if (volume == fDetector->GetDetectorLV()) {
        fEventAction->AddEdep(edep);
    }
}
 