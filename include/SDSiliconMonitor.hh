/*!
  @file SDSiliconMonitor.hh
  @based on BeamTestSiliconMonitor class -> J.C. Zamora  jczamorac@gmail.com
  @author Flechas (D. Flechas dcflechasg@unal.edu.co)
  @date  Nov. 2018
*/
#ifndef SDSILICONMONITOR_HH
#define SDSILICONMONITOR_HH

#include "G4VSensitiveDetector.hh"
#include "SiliconMonitorHit.hh"

class G4HCofThisEvent;
class G4TouchableHistory;
class G4Step;

class SDSiliconMonitor : public G4VSensitiveDetector {

public:

  // Constructor
  SDSiliconMonitor(const G4String& name);

  // Destructor
  virtual ~SDSiliconMonitor();
  
  // Methods
  virtual void Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent);
  
  virtual G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* history);

  virtual void EndOfEvent(G4HCofThisEvent* hitsCollectionOfThisEvent);
  
private:
  
  // Data members
  SiliconMonitorHitsCollection* fHitsCollection;
  G4int fHitsCollectionID;
};



#endif

