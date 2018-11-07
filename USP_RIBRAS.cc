//
// $Id: GFNUNdetMTtest.cc June 2016 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "Randomize.hh"

#include "G4EventManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "G4VUserActionInitialization.hh"

#include "SetupConstruction.hh"
#include "ActionInitialization.hh"
//#include "PhysicsList.hh"
//#include "PhysicsListMessenger.hh"
//#include "G4EmUserPhysics.hh" // No Geant4 class, own defined

//#include "SteppingAction.hh"*/

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
int main(int argc,char** argv) {
 
  //choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  //set random seed with system time
  G4long seed = time(NULL);
  G4Random::setTheSeed(seed);
  
  // Construct the default run manager
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(3); // Is equal to 2 by default
#else
  G4RunManager* runManager = new G4RunManager;
#endif
  
  // set mandatory initialization classes
  //PrimaryGeneratorAction* prim;

  runManager->SetUserInitialization(new SetupConstruction);

  G4PhysListFactory factory;
  //G4VModularPhysicsList* physlist = 0;
  G4VModularPhysicsList* physlist = factory.GetReferencePhysList("Shielding");
  /*
  PhysicsListMessenger* mess = 0;
  G4String physName = "";

  // Physics List name defined via 3nd argument
  if (argc==3) { physName = argv[2]; }

  // Physics List name defined via environment variable
  if("" == physName) {
    char* path = getenv("PHYSLIST");
    if (path) { physName = G4String(path); }
  }

  // reference PhysicsList via its name
  if("" != physName && factory.IsReferencePhysList(physName)) {
    physlist = factory.GetReferencePhysList(physName);

    // added extra EM options
    physlist->RegisterPhysics(new G4EmUserPhysics(1));

    // instantiated messenger
    mess = new PhysicsListMessenger();
  } 

  // local Physics List
  if(!physlist) { physlist = new PhysicsList(); }
  */
  // define physics
  runManager->SetUserInitialization(physlist);
  // define primary generator action
  runManager->SetUserInitialization(new ActionInitialization());

  //runManager->SetUserInitialization(new PhysicsList);
  
  // get the pointer to the User Interface manager
  G4UImanager* UI = G4UImanager::GetUIpointer();  
  // Initialize G4 kernel
  //runManager->Initialize();
#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif
  if (argc!=1)   // batch mode  
    {
  G4String command = "/control/execute ";
  G4String fileName = argv[1];
  UI->ApplyCommand(command+fileName);
}
    
  else  //define visualization and UI terminal for interactive mode
    {/*
       #ifdef _WIN32
       G4UIsession * session;
       session = new G4UIterminal();
       #else
       G4UIsession * session;
       session = new G4UIterminal(new G4UItcsh);
       #endif
     */
  UI->ApplyCommand("/run/initialize");
  UI->ApplyCommand("/control/execute macros/vis.mac");
#ifdef G4UI_USE
  G4UIExecutive * ui = new G4UIExecutive(argc,argv);
  ui->SessionStart();
  delete ui;
#endif
}

#ifdef G4VIS_USE
  delete visManager;
#endif     
  //! @attention Free the store: user actions, physics_list and detector_description are
  //!                 owned and deleted by the run manager, so they should not
  //!                 be deleted in the main() program !
  delete runManager;
  return 0;
}

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
