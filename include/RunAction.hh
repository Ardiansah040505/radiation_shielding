#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <fstream>

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    // dipanggil dari EventAction
    void AddEventEnergy(G4double edep);

private:
    std::ofstream fOutFile;
    G4int fEventID;
};

#endif
