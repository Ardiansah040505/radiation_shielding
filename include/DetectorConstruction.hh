#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4String.hh"
#include "globals.hh"

class G4LogicalVolume;
class DetectorMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    // akses logical volume detector (untuk scoring)\

    void SetPumiceType(const G4String& name);

    G4LogicalVolume* GetDetectorLV() const;

private:
    enum class PumiceType {
        Ijobalit,
        Setangi,
        Lingsar
    };

    PumiceType fPumiceType;

    DetectorMessenger* fMessenger;


    G4LogicalVolume* fDetectorLV;
};

#endif
