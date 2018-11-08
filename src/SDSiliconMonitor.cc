/*!
  @file SDSiliconMonitor.cc
  @based on BeamTestSiliconMonitor class -> J.C. Zamora  jczamorac@gmail.com
  @author Flechas (D. Flechas dcflechasg@unal.edu.co)
  @date  Nov. 2018
*/

#include "SDSiliconMonitor.hh"
#include "SiliconMonitorHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"    
#include "G4TouchableHistory.hh"
#include "G4Track.hh"

SDSiliconMonitor::SDSiliconMonitor(const G4String& name)
   :G4VSensitiveDetector(name)
{
   collectionName.insert( "siliconMonitorHCollection" );
   fHitsCollectionID = -1;
}

SDSiliconMonitor::~SDSiliconMonitor() {}

void SDSiliconMonitor::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent)
{
   fHitsCollection =
      new SiliconMonitorHitsCollection(SensitiveDetectorName, collectionName[0]);
 
  if ( fHitsCollectionID < 0 )
       fHitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
 
  // Add collection to the event
  hitsCollectionOfThisEvent->AddHitsCollection(fHitsCollectionID, fHitsCollection);
 
}

G4bool SDSiliconMonitor::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{

// Limited by Geom Boundary?
   if ( aStep->GetPreStepPoint()->GetStepStatus() == fGeomBoundary )
   {
      // Create Hit 
      SiliconMonitorHit* aHit = new SiliconMonitorHit();
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

void SDSiliconMonitor::EndOfEvent(G4HCofThisEvent*) {}
