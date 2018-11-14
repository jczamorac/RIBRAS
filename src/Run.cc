/// \file include/Run.hh
/// \brief Definition of the Run class
/// @Date Nov. 2018
/// @Author DFlechas, dcflechasg@unal.edu.co

#include "Analysis.hh"
#include "Run.hh"
#include "MonitorHit.hh"

#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
//  Constructor. 
//   (The vector of MultiFunctionalDetector name has to given.)
Run::Run()
  : G4Run(),
    hitsCollID(-1),
    hitsCollName("siliconMonitorHCollection")
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Destructor
//    clear all data members.
Run::~Run()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Run::RecordEvent(const G4Event* aEvent)
{
  auto RootManager = G4RootAnalysisManager::Instance();
  
  G4int evtNb = aEvent->GetEventID();
  //Hits collections
  //
  G4HCofThisEvent* HCE = aEvent->GetHCofThisEvent();
  if(!HCE) return;
 
  /////////////////////////////////////////////////
  // **** Selsitive detector (user-defined) **** //
  /////////////////////////////////////////////////
  
  // ***************************************************** //
  // **** Analysis and Historam fill**** //
  // ***************************************************** //

  if ( hitsCollID == -1 )
    hitsCollID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollName);
  
  const  MonitorHitsCollection* fHCMonitor = static_cast<const MonitorHitsCollection*>(HCE->GetHC(hitsCollID));

  // Reading info
  G4int nMonitorHits = fHCMonitor->entries();

  if( nMonitorHits > 0 )
    {
      G4double a1=0*mm, a2=0*mm, a3=0*mm;
      G4double r=0*mm;
      for ( G4int d = 0 ; d< nMonitorHits ; d++ )
	{
	  MonitorHit* aHit = static_cast<MonitorHit*>( fHCMonitor->GetHit( d ) );
	  //hit->Print();
	  a1=0*mm; a2=0*mm; a3=0*mm; r= 0*mm;
	  G4ThreeVector pos =aHit->GetIncidencePosition()/mm;
	  G4double time = aHit->GetIncidenceTime()/ns;
   
	  a1=pos.x(); a2=pos.y(); a3=pos.z();
	  r = sqrt(a1*a1+a2*a2);

	  
	  RootManager->FillNtupleDColumn(0,0,aHit->GetIncidenceKineticEnergy()/MeV);
	  RootManager->FillNtupleDColumn(0,1,a1);
	  RootManager->FillNtupleDColumn(0,2,a2);
	  RootManager->FillNtupleDColumn(0,3,r);
	  RootManager->FillNtupleDColumn(0,4,time);
	  
	  RootManager->FillH2(0,a1,a2);
	  RootManager->FillH2(1,r,time);
	  
	  RootManager->AddNtupleRow(0);
	}
      RootManager->AddNtupleRow(0);
    }
    
  //////////////////
  // Record event //
  //////////////////
  G4Run::RecordEvent(aEvent);
  
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void Run::Merge(const G4Run * aRun) {
  const Run * localRun = static_cast<const Run *>(aRun);
  
  //=======================================================
  
  G4Run::Merge(aRun);
}

