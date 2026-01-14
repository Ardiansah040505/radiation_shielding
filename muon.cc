#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

int main(int argc, char** argv)
{
    // ================================================================
    // UI
    // ================================================================
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // ================================================================
    // Run manager
    // ================================================================
    auto runManager = new G4RunManager();

    // ================================================================
    // Mandatory initializations
    // ================================================================
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new ActionInitialization());

    // ================================================================
    // Initialize kernel
    // ================================================================
    runManager->Initialize();

    // ================================================================
    // Visualization
    // ================================================================
    auto visManager = new G4VisExecutive();
    visManager->Initialize();

    auto UImanager = G4UImanager::GetUIpointer();

    // ================================================================
    // Batch or interactive
    // ================================================================
    if (!ui) {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {
        // interactive mode
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    }

    // ================================================================
    // Cleanup
    // ================================================================
    delete visManager;
    delete runManager;

    return 0;
}
