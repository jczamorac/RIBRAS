/*! @file SetupConstruction.cc
  @brief Defines mandatory user class SetupConstruction.
  @author Flechas (D. Flechas dcflechasg@unal.edu.co)
  @author Andre (andreserra@ymail.com)
  @based on A01DetectorConstruction class -> J. Zamora  ---
  @date  Oct. 2018
  In this source file, the 'physical' setup is defined: materials, geometries and positions. 
  This class defines the experimental hall used in the toolkit.
*/

/* no-geant4 classes*/
#include "SetupConstruction.hh"
#include "MagneticField.hh"

/*  units  */
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

/* geometric objects */
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

/* geant4 materials */
#include "G4NistManager.hh"

/* solid volumes */
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4UnionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4AssemblyVolume.hh"

/* logic and physical volume */
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4UserLimits.hh"

/* Sensitive volumes*/
#include "G4SDManager.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
//#include "G4PSEnergyDeposit3D.hh"

/* EM fields */
#include "G4UniformElectricField.hh"
#include "G4UniformMagField.hh"
#include "G4MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4EquationOfMotion.hh"
#include "G4EqMagElectricField.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4ChordFinder.hh"

#include "G4ExplicitEuler.hh"
#include "G4ImplicitEuler.hh"
#include "G4SimpleRunge.hh"
#include "G4SimpleHeum.hh"
#include "G4ClassicalRK4.hh"
#include "G4HelixExplicitEuler.hh"
#include "G4HelixImplicitEuler.hh"
#include "G4HelixSimpleRunge.hh"
#include "G4CashKarpRKF45.hh"
#include "G4RKG3_Stepper.hh"
/* for UpdateGeometry */

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else

#include "G4RunManager.hh"
#endif

/* visualization */
#include "G4VisAttributes.hh"


SetupConstruction::SetupConstruction()
{
  magneticField = new MagneticField();
}

SetupConstruction::~SetupConstruction()
{
}

/*!
  This function is called by G4 when the detector has to be created\n
  Definitions of Solids, Logical Volumes and Physical Volumes comes here.
  //! \sa ConstructEnclosure(), ConstructIMPLANT(), ConstructSiDetectors(), ConstructGeDetectors() and Sensibilize()
  */

G4VPhysicalVolume* SetupConstruction::Construct()
{ 
  //------------------------------
  // World
  //------------------------------
  G4double halfWorldLength = 10.0* m;

  G4Box * solidWorld= new G4Box("world",halfWorldLength,halfWorldLength,halfWorldLength);
  logicWorld = new G4LogicalVolume(solidWorld,
				   //G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"),
				   G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic"),
				   "World", 0, 0, 0);
  logicWorld -> SetVisAttributes(G4VisAttributes::GetInvisible()); //never show

  //! \li Must place the \ref logicWorld "World" physical volume unrotated at \f$(0,0,0)\f$.
  physiWorld = new G4PVPlacement(0,               // no rotation
				 G4ThreeVector(), // at (0,0,0)
				 logicWorld,      // its logical volume
				 "World",         // its name
				 0,               // its mother  volume
				 false,           // no boolean operations
				 0);              // copy number

  /*************************************/
  /*****   REAL DEAL FROM HERE ON  *****/
  /*************************************/
  ConstructSetup();
  /** In this routine the logical volumes to score get register with
      the SDmanager **/
  constructed = true;
    //! \li Always return the physical World
  return physiWorld;
}

void SetupConstruction::ConstructSetup(void)
{
  ////////////////////////////
  ////// Beam - monitor //////
  ////////////////////////////
  G4double monitor_length = 50.0*cm;
  G4double monitor_thick = 10.0*um;
  G4ThreeVector Pos_BeamMonitor = G4ThreeVector(0.,0.,150.*cm);
  
  G4VSolid* Sol_BeamMonitor = new G4Box("S_BeamMonitor", // Name
                                         monitor_length/2.0,                // x half length
                                         monitor_length/2.0,                // y half length
                                         monitor_thick) ;             // z half length
  G4LogicalVolume* Log_BeamMonitor =
    new G4LogicalVolume(Sol_BeamMonitor,       // Solid
                        G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic"),// Material
                        "L_BeamMonitor"); // Name
  G4VPhysicalVolume* Phy_BeamMonitor = new G4PVPlacement(0,                          // Rotation matrix pointer
							 Pos_BeamMonitor, // Translation vector
							 Log_BeamMonitor,         // Logical volume
							 "P_BeamMonitor",   // Name
							 logicWorld,        // Mother volume
							 false,             // Unused boolean
							 0,                 // Copy number     
							 true);
  ////////////////
  /// Solenoid ///
  ////////////////

  G4double Solenoid_length = 100.0*cm;
  G4double Solenoid_diameter_inner = 30.0*cm;
  G4double Solenoid_diameter_outer = 100.0*cm;

  G4ThreeVector Pos_Solenoid = G4ThreeVector();
   
  G4VSolid* Sol_Solenoid = new G4Tubs("magneticexterior",
				      Solenoid_diameter_inner/2.0,
				      Solenoid_diameter_outer/2.0,
				      Solenoid_length/2.0,0.,360.*deg);
  
  G4LogicalVolume* Log_Solenoid
    = new G4LogicalVolume(Sol_Solenoid,
			  G4NistManager::Instance()->FindOrBuildMaterial("G4_Fe"),
			  "Log_Solenoid");
 
  G4VPhysicalVolume* Phy_Solenoid = new G4PVPlacement(0,
						      Pos_Solenoid,
						      Log_Solenoid,
						      "P_Solenoid",
						      logicWorld,
						      false,
						      0,
						      true);

  /////////////////////////////
  /// magnetic field region ///
  /////////////////////////////
  G4double Mag_diameter = Solenoid_diameter_inner;
  G4double Mag_length = 68.0*cm;
 
  
  G4VSolid* Sol_Magnet = new G4Tubs("S_Magnet",0.,Mag_diameter/2.0,Mag_length/2.0,0.,360.*deg);
  
  G4LogicalVolume* Log_Magnet  = new G4LogicalVolume(Sol_Magnet,
						     G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic"),// Material
						     "Log_Magent",0,0,0);
  
  G4VPhysicalVolume* Phy_Magnet = new G4PVPlacement(0,
						    Pos_Solenoid,
						    Log_Magnet,
						    "P_Magnet",
						    logicWorld,
						    false,
						    0,
						    true);
  // set "user limits" for drawing smooth curve
  G4UserLimits* userLimits = new G4UserLimits(1.e-5*mm);
  Log_Magnet->SetUserLimits(userLimits);

}

//! from the detector messenger you can force a geometry re-computation
void SetupConstruction::UpdateGeometry()
{
  if(physiWorld) 
    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}

//!  Sensitive detectors : MultiFunctionalDetector
void SetupConstruction::ConstructSDandField()
{
  // G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  // MultiFunctionalDetector
  // Define MultiFunctionalDetector with name.
  G4MultiFunctionalDetector* mFDet = new G4MultiFunctionalDetector("DetectorsVol1");
  G4SDManager::GetSDMpointer()->AddNewDetector(mFDet);
  // PS : Primitive Scorers
  G4VPrimitiveScorer* scorer0 = new G4PSEnergyDeposit("Edep");
  //  Register primitive scorers to MultiFunctionalDetector
  mFDet->RegisterPrimitive(scorer0);
  //  SetSensitiveDetector("cyl_log",mFDet);


  ////////////////////
  // Magnetic field //
  ////////////////////
  G4bool fieldIsInitialized = false;
  if(!fieldIsInitialized)
  {
    G4MagIntegratorStepper* fStepper;

    G4FieldManager* fieldMgr
      = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    fieldMgr->SetDetectorField(magneticField);
    fieldMgr->CreateChordFinder(magneticField);
 
    G4double minEps= 1.0e-9;  //   Minimum & value for smallest steps
    G4double maxEps= 1.0e-8;  //   Maximum & value for largest steps

    fieldMgr->SetMinimumEpsilonStep( minEps );
    fieldMgr->SetMaximumEpsilonStep( maxEps );


    //fieldMgr->GetChordFinder()->SetDeltaChord( 0.0000001*cm);
    G4Mag_UsualEqRhs* 
      fEquation = new G4Mag_UsualEqRhs(magneticField); 
    //fStepper = new G4HelixImplicitEuler( fEquation ); 

    // Note that for magnetic field that do not vary with time,
    //  the default number of variables suffices.
 
    // or ..
    //fStepper = new G4HelixExplicitEuler( fEquation ); 
    //fStepper = new G4HelixSimpleRunge( fEquation );   
    fStepper = new G4CashKarpRKF45( fEquation );   
    fieldMgr->SetDeltaOneStep( 0.5e-3 * mm );  // 0.5 micrometer

    //G4ChordFinder( G4MagneticField* itsMagField,
    //             G4double         stepMinimum = 1.0e-2 * mm,
    //           G4MagIntegratorStepper* pItsStepper = 0 );


    fieldIsInitialized = true;
  }


  
}
