#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"
#include "G4UIcmdWithAString.hh"

class DetectorMessenger : public G4UImessenger
{
    public :
        DetectorMessenger(DetectorConstruction* detector);
        virtual ~DetectorMessenger();

        virtual void SetNewValue(G4UIcommand* command, G4String newValue);

    private :
        DetectorConstruction* fDetector;

        G4UIdirectory* fDetectorDir;
        G4UIcmdWithAString* fPumiceCmd;
};





#endif