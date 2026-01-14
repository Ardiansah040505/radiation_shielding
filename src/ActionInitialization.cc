#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

#include "G4RunManager.hh"

// --------------------------------------------------------------------
ActionInitialization::ActionInitialization()
: G4VUserActionInitialization()
{}

// --------------------------------------------------------------------
ActionInitialization::~ActionInitialization()
{}

// --------------------------------------------------------------------
void ActionInitialization::Build() const
{
    // Primary generator
    SetUserAction(new PrimaryGeneratorAction());

    // Run action
    auto runAction = new RunAction();
    SetUserAction(runAction);

    // Access detector
    auto detector =
        static_cast<const DetectorConstruction*>(
            G4RunManager::GetRunManager()
                ->GetUserDetectorConstruction()
        );

    // Event action
    auto eventAction =
        new EventAction(runAction, detector);
    SetUserAction(eventAction);

    // Stepping action
    SetUserAction(
        new SteppingAction(eventAction, detector)
    );
}
