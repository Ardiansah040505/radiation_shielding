#include "EventAction.hh"
#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "G4Event.hh"
#include "G4Step.hh"
#include "G4LogicalVolume.hh"

EventAction::EventAction(RunAction* runAction, const DetectorConstruction* detConstruction)
    : G4UserEventAction(),
    fEdepEvent(0.0),
    fRunAction(runAction),
    fDetConstruction(detConstruction)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* event)
{
    fEdepEvent = 0.0;
}

void EventAction::AddEdep(G4double edep)
{
    fEdepEvent += edep;
}

void EventAction::EndOfEventAction(const G4Event*)
{
    fRunAction->AddEventEnergy(fEdepEvent);
}
