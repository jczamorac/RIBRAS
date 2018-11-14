/*!
  @file MonitorHit.hh
  @based on BeamTestMonitorHit class -> J.C. Zamora  jczamorac@gmail.com
  @modified by Flechas (D. Flechas dcflechasg@unal.edu.co)
  @date  Nov. 2018
*/

#ifndef MONITORHIT_HH
#define MONITORHIT_HH

#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"
#include "G4ParticleDefinition.hh"
#include "G4VHit.hh"

class MonitorHit : public G4VHit {

public:
  
  MonitorHit();
  MonitorHit(const MonitorHit &right);
  virtual ~MonitorHit();
  const MonitorHit& operator=(const MonitorHit &right);
  G4int operator==(const MonitorHit &right) const;
  
  inline void *operator new(size_t);
  inline void operator delete(void *aHit);

  virtual void Draw();
  virtual void Print();

  inline void SetIncidenceDefinition(G4ParticleDefinition* pd) {fIPD = pd;}
  inline void SetIncidencePosition(G4ThreeVector position) {fIPosition = position;}
  inline void SetIncidenceKineticEnergy(G4double e) {fIKEnergy = e;}
  inline void SetIncidenceMomentumDirection(G4ThreeVector momentum) {fIMomentumD = momentum;}
  inline void SetIncidenceTime(G4double time) {fITime = time;}
  
  inline G4double GetIncidenceKineticEnergy()               {return fIKEnergy;}
  inline G4ParticleDefinition* GetIncidenceDefinition()     {return fIPD;}
  inline G4ThreeVector GetIncidencePosition()               {return fIPosition;}
  inline G4ThreeVector GetIncidenceMomentumDirection()      {return fIMomentumD;}
  inline G4double GetIncidenceTime()                        {return fITime;}
  
private:
  G4ParticleDefinition* fIPD;
  G4double fIKEnergy;
  G4ThreeVector fIPosition;
  G4ThreeVector fIMomentumD;
  G4double fITime;
};

typedef G4THitsCollection<MonitorHit> MonitorHitsCollection;

extern G4ThreadLocal G4Allocator<MonitorHit>* MonitorHitsAllocator;

inline void* MonitorHit::operator new(size_t)
{
  if(!MonitorHitsAllocator)
    MonitorHitsAllocator = new G4Allocator<MonitorHit>;
  return (void *) MonitorHitsAllocator->MallocSingle();
}

inline void MonitorHit::operator delete(void* aHit)
{
  MonitorHitsAllocator->FreeSingle((MonitorHit*) aHit);
}

#endif
