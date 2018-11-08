/*!
  @file SiliconMonitorHit.hh
  @based on BeamTestSiliconMonitorHit class -> J.C. Zamora  jczamorac@gmail.com
  @author Flechas (D. Flechas dcflechasg@unal.edu.co)
  @date  Nov. 2018
*/

#ifndef SILICONMONITORHIT_HH
#define SILICONMONITORHIT_HH

#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"
#include "G4ParticleDefinition.hh"
#include "G4VHit.hh"

class SiliconMonitorHit : public G4VHit {

public:
  
  SiliconMonitorHit();
  SiliconMonitorHit(const SiliconMonitorHit &right);
  virtual ~SiliconMonitorHit();
  const SiliconMonitorHit& operator=(const SiliconMonitorHit &right);
  G4int operator==(const SiliconMonitorHit &right) const;
  
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

typedef G4THitsCollection<SiliconMonitorHit> SiliconMonitorHitsCollection;

extern G4ThreadLocal G4Allocator<SiliconMonitorHit>* SiliconMonitorHitsAllocator;

inline void* SiliconMonitorHit::operator new(size_t)
{
  if(!SiliconMonitorHitsAllocator)
    SiliconMonitorHitsAllocator = new G4Allocator<SiliconMonitorHit>;
  return (void *) SiliconMonitorHitsAllocator->MallocSingle();
}

inline void SiliconMonitorHit::operator delete(void* aHit)
{
  SiliconMonitorHitsAllocator->FreeSingle((SiliconMonitorHit*) aHit);
}

#endif
