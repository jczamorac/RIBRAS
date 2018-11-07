/**
 * @file
 * @brief implements mandatory user class PrimaryGeneratorAction
 */

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4RandomDirection.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"
#include <cmath>
using namespace CLHEP;

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);
  gun = new  G4GeneralParticleSource();
  fposition = G4ThreeVector(0.*mm,0.*mm,-115.*cm);
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="alpha");
  
  particleGun->SetParticleDefinition(particle);

  //particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.5,0.5));
    
  particleGun->SetParticlePosition(fposition);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete gun;
  delete particleGun;
}

////////////////////////////////////////////
///// ********  Particle Gun  ******** /////
////////////////////////////////////////////

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4IonTable* ionTable =  G4IonTable::GetIonTable();
  
  G4ParticleDefinition* part = 0;
  G4int j = 0; //(int)(5*G4UniformRand());
  switch(j)
    {
    case 0:
      part = ionTable->GetIon(4,7,0.);
      particleGun->SetParticleDefinition(part);
      particleGun->SetParticleEnergy(19.8*MeV);
      break;
   
    case 1:
      part = ionTable->GetIon(3,6,0.);
      particleGun->SetParticleDefinition(part);
      particleGun->SetParticleEnergy(24.0*MeV);
      break;

    case 3:
      part = ionTable->GetIon(5,8,0.);
      particleGun->SetParticleDefinition(part);
      particleGun->SetParticleEnergy(24.*MeV);
      break;

    case 4:
      part = ionTable->GetIon(3,7,0.);
      particleGun->SetParticleDefinition(part);
      particleGun->SetParticleEnergy(24.*MeV);
      break;

    case 5:
      part = ionTable->GetIon(2,4,0.);
      particleGun->SetParticleDefinition(part);
      particleGun->SetParticleEnergy(24.*MeV);
      break;

  
    }
  	
  double a = G4UniformRand();
  G4double phi = 2*pi*(a);
  G4double theta = 0.066667*pi*(G4UniformRand()-0.5);
  //G4double theta = 0.066667*pi*(G4UniformRand());	
  //G4double theta = 0.0111*pi;
  if( abs(theta) < 0.0349  ){ 
    theta = 0.07; 	 	
  }
 	
  //G4cout<<"angulo aleatotio  "<<angle<<G4endl;
  //particleGun->SetParticleEnergy(12.9*MeV);	
  particleGun->SetParticleMomentumDirection(G4ThreeVector(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta)));
  particleGun->GeneratePrimaryVertex(anEvent);

 
}


///////////////////////////////////////////////////////
///// ********  General Particle Source  ******** /////
///////////////////////////////////////////////////////
/*
  void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
  {
  gun->GeneratePrimaryVertex(anEvent);
  }
*/
