/*!
  @file SDMonitor.hh
  @based on BeamTestMonitor class -> J.C. Zamora  jczamorac@gmail.com
  @modified by Flechas (D. Flechas dcflechasg@unal.edu.co)
  @date  Nov. 2018
*/
#ifndef SDSILICONMONITOR_HH
#define SDSILICONMONITOR_HH

#include "G4VSensitiveDetector.hh"
#include "MonitorHit.hh"

class G4HCofThisEvent;
class G4TouchableHistory;
class G4Step;

class SDMonitor : public G4VSensitiveDetector {

public:

  // Constructor
  SDMonitor(const G4String& name);

  // Destructor
  virtual ~SDMonitor();
  
  // Methods
  virtual void Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent);
  
  virtual G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* history);

  virtual void EndOfEvent(G4HCofThisEvent* hitsCollectionOfThisEvent);
  
private:
  
  // Data members
  MonitorHitsCollection* fHitsCollection;
  G4int fHitsCollectionID;
};



#endif

