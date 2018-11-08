#ifndef EVENTACTION_HH
#define EVENTACTION_HH

/*! @file EventAction.cc
  @brief Defines mandatory user class EventAction.
  @based on BeamTestEventAction class -> J.C. Zamora  jczamorac@gmail.com
  @modified by Flechas (D. Flechas dcflechasg@unal.edu.co)
  @date  Nov. 2018
*/

#include "G4UserEventAction.hh"
#include "globals.hh"

class EventAction : public G4UserEventAction {

public:

  // Constructor
  EventAction();

  // Destructor
  ~EventAction();

  // Metohds
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  
private:

  // Data member
  G4int fHitsCollectionID;
  G4int HCID;
  G4int fHitsCollectionID_monitor;	
  
};

#endif

    
