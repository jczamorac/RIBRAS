#ifndef SetupConstruction_h
#define SetupConstruction_h 1

/*! @file SetupConstruction.hh
  @brief Defines mandatory user class SetupConstruction.
  @author Flechas (D. Flechas dcflechasg@unal.edu.co)
  @date  Nov. 2018
  @version 1.0
  
  In this header file, the 'physical' setup is defined: materials, geometries and positions. 
  This class defines the experimental hall used in the toolkit.
*/

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4ThreeVector.hh"

class G4Material;
class MagneticField;

/*! @brief This mandatory user class defines the geometry.
  It is responsible for
  @li Construction of geometry

  \sa Construct()
*/
class SetupConstruction : public G4VUserDetectorConstruction
{
public:
  //! Constructor
  SetupConstruction();
  //! Destructor
  ~SetupConstruction();
public:
  //! Construct geometry of the setup
  G4VPhysicalVolume* Construct();
  void ConstructSDandField(void);
  //! Update geometry
  void UpdateGeometry();

  void DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth=0);

  //! \name some simple construction functions
  void ConstructSetup(void);
  //!! Variables
private:
  G4VPhysicalVolume* physiWorld;
  //! Logical Global mother volume
  G4LogicalVolume* logicWorld;
  //! Construction flag 
  G4bool constructed;
  //! magnetic field
  MagneticField* magneticField;
};

#endif // end SetupConstruction_h
