/*!
  @file SDMonitor.cc
  @based on BeamTestMonitor class -> J.C. Zamora  jczamorac@gmail.com
  @modified by Flechas (D. Flechas dcflechasg@unal.edu.co)
  @date  Nov. 2018
*/

#include "SDMonitor.hh"
#include "MonitorHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"    
#include "G4TouchableHistory.hh"
#include "G4Track.hh"

SDMonitor::SDMonitor(const G4String& name)
   :G4VSensitiveDetector(name)
{
   collectionName.insert( "siliconMonitorHCollection" );
   fHitsCollectionID = -1;
}

SDMonitor::~SDMonitor() {}

void SDMonitor::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent)
{
   fHitsCollection =
      new MonitorHitsCollection(SensitiveDetectorName, collectionName[0]);
 
  if ( fHitsCollectionID < 0 )
       fHitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
 
  // Add collection to the event
  hitsCollectionOfThisEvent->AddHitsCollection(fHitsCollectionID, fHitsCollection);
 
}

G4bool SDMonitor::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{

// Limited by Geom Boundary?
   if ( aStep->GetPreStepPoint()->GetStepStatus() == fGeomBoundary )
   {
      // Create Hit 
      MonitorHit* aHit = new MonitorHit();
      fHitsCollection->insert( aHit );

      // Get Transportaion Matrix
      G4TouchableHistory* theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
      G4AffineTransform aTrans = theTouchable->GetHistory()->GetTopTransform();

      G4ThreeVector position = aTrans.NetRotation() * ( aTrans.NetTranslation() + aStep->GetPreStepPoint()->GetPosition() ); 
      G4ThreeVector momentumD = aTrans.NetRotation() * aStep->GetPreStepPoint()->GetMomentumDirection();

      G4ParticleDefinition* pd = aStep->GetTrack()->GetDefinition(); 
      G4double ke = aStep->GetPreStepPoint()->GetKineticEnergy();
      G4double ti = aStep->GetPreStepPoint()->GetGlobalTime();

      aHit->SetIncidenceDefinition(pd);
      aHit->SetIncidenceKineticEnergy(ke);
      aHit->SetIncidencePosition(position);
      aHit->SetIncidenceMomentumDirection(momentumD);
      aHit->SetIncidenceTime(ti);
   }
   else 
   {
      return true;
   }
   
   return true;
}

void SDMonitor::EndOfEvent(G4HCofThisEvent*) {}
