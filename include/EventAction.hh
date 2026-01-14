#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;
class DetectorConstruction;

class EventAction : public G4UserEventAction
{
    public:
        EventAction(RunAction* runAction, const DetectorConstruction* detConstruction);
        virtual ~EventAction();

        virtual void BeginOfEventAction(const G4Event* event) ;
        virtual void EndOfEventAction(const G4Event* event);

        void AddEdep(G4double edep);
    
    private:
        G4double fEdepEvent;

        RunAction* fRunAction;
        const DetectorConstruction* fDetConstruction;
};
#endif