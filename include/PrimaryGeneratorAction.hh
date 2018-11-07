#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

/**
 * @file
 *
 * @date   01 July, 2010
 * @author Pico
 *
 * @brief Defines mandatory user class PrimaryGeneratorAction.
 */

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include <fstream>
#include "G4ThreeVector.hh"

class G4VPrimaryGenerator;
class G4GeneralParticleSource;
/*!
\brief This mandatory user class provides the primary particle generator

Geant4 provides a number of predefined primary particle generator, to be utilised by the user.
 - G4ParticleGun
 - G4GeneralParticleSource

\sa GeneratePrimaries()
*/

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  //! constructor
  PrimaryGeneratorAction();
  //! destructor
  ~PrimaryGeneratorAction();
  //! defines primary particles (mandatory)
  void GeneratePrimaries(G4Event*);

  void SetPosition(G4ThreeVector pos){fposition = pos;};
  void SetTilting(G4double tilt){CameraTilting = tilt;};

private:
  G4GeneralParticleSource* gun;
  G4ParticleGun* particleGun;
  G4ThreeVector fposition;
  G4double CameraTilting;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
