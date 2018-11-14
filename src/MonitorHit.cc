/*!
  @file MonitorHit.cc
  @based on BeamTestMonitorHit class -> J.C. Zamora  jczamorac@gmail.com
  @modified by Flechas (D. Flechas dcflechasg@unal.edu.co)
  @date  Nov. 2018
*/
#include "MonitorHit.hh"

#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

G4ThreadLocal G4Allocator<MonitorHit>* MonitorHitsAllocator = nullptr;

MonitorHit::MonitorHit()
  : fIPD(0), fIKEnergy(0.0), fIPosition(0), fIMomentumD(0), fITime(0.0)
{ }

MonitorHit::~MonitorHit() {}

void MonitorHit::Draw() {}

MonitorHit::MonitorHit(const MonitorHit &right)
  : G4VHit()
{
  fIPD = right.fIPD;
  fIKEnergy = right.fIKEnergy;
  fIPosition = right.fIPosition;
  fITime = right.fITime;
}

const MonitorHit& MonitorHit::operator=(const MonitorHit &right)
{
  fIPD = right.fIPD;
  fIKEnergy = right.fIKEnergy;
  fIPosition = right.fIPosition;
  fITime = right.fITime;
  return *this;
}

G4int MonitorHit::operator==(const MonitorHit&) const{
  return false;
  //returns false because there currently isnt need to check for equality yet
}

void MonitorHit::Print()
{
   if( fIPD->GetParticleName()=="Li6[0.0]" || fIPD->GetParticleName()=="e-"){ }
   else{	
   G4cout << "Incidence Particle Name and Kinetic Energy " << fIPD->GetParticleName() 
          << " " << fIKEnergy/MeV << " MeV" << G4endl; 
   G4cout << "Insidence position in silicon monitor " << fIPosition/mm << " in mm" << G4endl; 
   G4cout << "Incidence Direction " << fIMomentumD << G4endl; G4cout << "Tiempo " << fITime/ns << G4endl;}
}
