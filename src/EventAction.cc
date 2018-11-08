/*! @file EventAction.cc
  @brief Defines mandatory user class EventAction.
  @based on BeamTestEventAction class -> J.C. Zamora  jczamorac@gmail.com
  @modified by Flechas (D. Flechas dcflechasg@unal.edu.co)
  @date  Nov. 2018
*/
#include "EventAction.hh"

#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

EventAction::EventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event* event) 
{ }


void EventAction::EndOfEventAction(const G4Event* event)
{ }

