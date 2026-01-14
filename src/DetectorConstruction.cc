#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"


DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction(),
    fDetectorLV(nullptr)
    {}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // ================================================================
    // 1. NIST MANAGER
    // ================================================================
    auto nist = G4NistManager::Instance();

    // ================================================================
    // 2. ELEMENTS (for pumice)
    // ================================================================
    G4Element* elO  = nist->FindOrBuildElement("O");
    G4Element* elSi = nist->FindOrBuildElement("Si");
    G4Element* elAl = nist->FindOrBuildElement("Al");
    G4Element* elNa = nist->FindOrBuildElement("Na");
    G4Element* elK  = nist->FindOrBuildElement("K");
    G4Element* elFe = nist->FindOrBuildElement("Fe");

    // ================================================================
    // 3. MATERIALS
    // ================================================================

    // ---- World material
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

    // ---- NaI(Tl) detector material
    G4Material* NaI = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");

    // ---- Pumice material (Ijobalit sample)
    // Density and mass fraction from paper (Table 1 & 2)
    G4Material* pumice = new G4Material(
        "IjobalitPumice",
        2.48583 * g/cm3,
        6
    );

    pumice->AddElement(elO,  50.59 * perCent);
    pumice->AddElement(elSi, 31.63 * perCent);
    pumice->AddElement(elAl, 8.70  * perCent);
    pumice->AddElement(elNa, 3.24  * perCent);
    pumice->AddElement(elK,  3.33  * perCent);
    pumice->AddElement(elFe, 2.51  * perCent);

    // ================================================================
    // 4. WORLD VOLUME
    // ================================================================
    G4double worldSize = 1.0 * m;

    auto solidWorld =
        new G4Box("World",
                  worldSize/2,
                  worldSize/2,
                  worldSize/2);

    auto logicWorld =
        new G4LogicalVolume(
            solidWorld,
            air,
            "World"
        );

    auto physWorld =
        new G4PVPlacement(
            nullptr,
            G4ThreeVector(),
            logicWorld,
            "World",
            nullptr,
            false,
            0,
            true
        );

    // ================================================================
    // 5. PUMICE SLAB (SHIELD)
    // ================================================================
    // Thickness r used in Beer–Lambert equation
    G4double pumiceThickness = 2.0 * cm;
    G4double pumiceXY        = 10.0 * cm;

    auto solidPumice =
        new G4Box("Pumice",
                  pumiceXY/2,
                  pumiceXY/2,
                  pumiceThickness/2);

    auto logicPumice =
        new G4LogicalVolume(
            solidPumice,
            pumice,
            "Pumice"
        );

    // Pumice placed 10 cm in front of detector
    new G4PVPlacement(
        nullptr,
        G4ThreeVector(0, 0, -10.0 * cm),
        logicPumice,
        "Pumice",
        logicWorld,
        false,
        0,
        true
    );

    auto pumiceVis = new G4VisAttributes(G4Color::White()); // Brownish color
    pumiceVis->SetForceSolid(true);
    logicPumice->SetVisAttributes(pumiceVis);



    // ================================================================
    // 6. NaI(Tl) DETECTOR (3 inch × 3 inch)
    // ================================================================
    G4double detRadius = 3.81 * cm;   // 3 inch / 2
    G4double detLength = 7.62 * cm;   // 3 inch

    auto solidDetector =
        new G4Tubs("NaIDetector",
                   0.0,
                   detRadius,
                   detLength/2,
                   0.0,
                   twopi);

    fDetectorLV =
        new G4LogicalVolume(
            solidDetector,
            NaI,
            "NaIDetector"
        );

    auto detVis = new G4VisAttributes(G4Colour(1.0, 0.6, 0.2));
    detVis->SetForceSolid(true);
    fDetectorLV->SetVisAttributes(detVis);

    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

    new G4PVPlacement(
        nullptr,
        G4ThreeVector(0, 0, 0),
        fDetectorLV,
        "NaIDetector",
        logicWorld,
        false,
        0,
        true
    );

    // ================================================================
    // 7. RETURN WORLD
    // ================================================================
    return physWorld;
}

G4LogicalVolume* DetectorConstruction::GetDetectorLV() const
{
    return fDetectorLV;
}