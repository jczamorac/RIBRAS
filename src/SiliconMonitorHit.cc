/*!
  @file SiliconMonitorHit.cc
  @based on BeamTestSiliconMonitorHit class -> J.C. Zamora  jczamorac@gmail.com
  @author Flechas (D. Flechas dcflechasg@unal.edu.co)
  @date  Nov. 2018
*/
#include "SiliconMonitorHit.hh"

#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

G4ThreadLocal G4Allocator<SiliconMonitorHit>* SiliconMonitorHitsAllocator = nullptr;

SiliconMonitorHit::SiliconMonitorHit()
  : fIPD(0), fIKEnergy(0.0), fIPosition(0), fIMomentumD(0), fITime(0.0)
{ }

SiliconMonitorHit::~SiliconMonitorHit() {}

void SiliconMonitorHit::Draw() {}

SiliconMonitorHit::SiliconMonitorHit(const SiliconMonitorHit &right)
  : G4VHit()
{
  fIPD = right.fIPD;
  fIKEnergy = right.fIKEnergy;
  fIPosition = right.fIPosition;
  fITime = right.fITime;
}

const SiliconMonitorHit& SiliconMonitorHit::operator=(const SiliconMonitorHit &right)
{
  fIPD = right.fIPD;
  fIKEnergy = right.fIKEnergy;
  fIPosition = right.fIPosition;
  fITime = right.fITime;
  return *this;
}

G4int SiliconMonitorHit::operator==(const SiliconMonitorHit&) const{
  return false;
  //returns false because there currently isnt need to check for equality yet
}

void SiliconMonitorHit::Print()
{
   if( fIPD->GetParticleName()=="Li6[0.0]" || fIPD->GetParticleName()=="e-"){ }
   else{	
   G4cout << "Incidence Particle Name and Kinetic Energy " << fIPD->GetParticleName() 
          << " " << fIKEnergy/MeV << " MeV" << G4endl; 
   G4cout << "Insidence position in silicon monitor " << fIPosition/mm << " in mm" << G4endl; 
   G4cout << "Incidence Direction " << fIMomentumD << G4endl; G4cout << "Tiempo " << fITime/ns << G4endl;}
}
