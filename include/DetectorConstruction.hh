 // $Id: DetectorConstruction.hh 33 2010-01-14 17:08:18Z adotti $
 #ifndef DetectorConstruction_h
 #define DetectorConstruction_h 1

 /**
  * @file
  * @brief Defines mandatory user class DetectorConstruction.
  */

 #include "globals.hh"
 #include "G4VUserDetectorConstruction.hh"
 #include "G4ThreeVector.hh"

 class MagneticField;
 class MagneticField2;
 class G4LogicalVolume;
 class G4VPhysicalVolume;
 class G4Material;
 class DetectorMessenger;

 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

 /*!
 \brief This mandatory user class defines the geometry.

 It is responsible for
  - Definition of material, and
  - Construction of geometry

 \sa Construct()
  */
 class DetectorConstruction : public G4VUserDetectorConstruction
 {
 public:
   //! Constructor
   DetectorConstruction();
   //! Destructor
   ~DetectorConstruction();
 public:
   //! Construct geometry of the setup
   G4VPhysicalVolume* Construct();

   //! Update geometry
   void UpdateGeometry();

   //! \name some simple set & get functions
   //@{
   G4ThreeVector FirstSensorPosition() const  { return vector_D_0_0; }
   G4ThreeVector SecondSensorPosition() const { return vector_D_0_1; }
   //G4ThreeVector ThirdSensorPosition() const { return vector_D_0_2; }
   //G4ThreeVector CuartoSensorPosition() const { return posCuartoSensor; }

   G4ThreeVector SetFirstSensorPosition(const G4ThreeVector & pos) { return vector_D_0_0=pos; }
   G4ThreeVector SetSecondSensorPosition(const G4ThreeVector & pos) { return vector_D_0_1=pos; }
   // G4ThreeVector SetThirdSensorPosition(const G4ThreeVector & pos) { return vector_D_0_2=pos; }
   //G4ThreeVector SetCuartoSensorPosition(const G4ThreeVector & pos) { return posCuartoSensor=pos; }



//-------------------------algunos mensajes------------------------------
   G4double GetSlit_z() const { return slit_z; }
   G4double SetSlit_z(const G4double el_z)  { return slit_z=el_z; }

   G4double GetSlit_x() const { return slit_x; }
   G4double SetSlit_x(const G4double el_x)  { return slit_x=el_x; }

   G4double GetPocket1_x() const { return pocket_x; }
   G4double SetPocket1_x(const G4double el_x_pocket)  { return pocket_x=el_x_pocket; }
//-----------------------------------------------------------------------


   //@}
 private:
   //! define needed materials
   void DefineMaterials();
   //! initialize geometry parameters
   void ComputeParameters();
   //! Construct geometry of the Beam Telescope
   G4VPhysicalVolume* ConstructDetectors();
   //! Construct geometry of the Device-under-test
   void ConstructSetup(void);


   //G4VPhysicalVolume* ConstructRings();
   //! Construct geometry of the Device-under-test
   G4VPhysicalVolume* ConstructRing_D_0_0();
   //! Construct geometry of the 2Pocket
   G4VPhysicalVolume* ConstructRing_D_0_1();

  /* G4VPhysicalVolume* ConstructRing_D_0_2(); */

   G4double* rotacion(G4double dx , G4double dy, G4double dz, G4double angulo);

 private:

   //! \name Materials
   //@{
   G4Material* air;
   G4Material* silicon;
   G4Material* vacuum;
   G4Material* H2;
   G4Material* AlN;
   G4Material* steel;
   G4Material* tungsten;
   G4Material* lead;
   G4Material* tantalum;
   G4Material* sio2;
   G4Material* CH4;

   //@}

   //! \name Geometry
   //@{

   //! global mother volume
   G4LogicalVolume * logicWorld;


   MagneticField* magneticField;
   MagneticField2* magneticField2;


   //G4VPhysicalVolume * physiSensorslit;

   G4VPhysicalVolume * physiTarget;
   G4VPhysicalVolume * physiCilindro;
   G4VPhysicalVolume* solenoidef;
   G4VPhysicalVolume* Phy_Solenoid;

   //  Região do campo magnético


   //G4VPhysicalVolume* Phy_Magnet;
   //G4VPhysicalVolume* magneticof;




   //@}

   //! \name Parameters
   //@{
   G4double halfWorldLength;

   G4int noOfSensorStrips;
   G4double Lengthy_sili;
   G4double Thickness_sili;

   G4double Lengthx_sili;

   G4double Lengthy_dssd;
   G4double Thickness_dssd;
   G4double Thickness_dssd_gr;
   G4double Lengthx_dssd;

   G4ThreeVector posFirstSensor;
   G4ThreeVector posSecondSensor;
   G4ThreeVector posSecondSensor1a;
   G4ThreeVector posThirdSensor;

   G4double slit_x;
   G4double slit_z;
   G4double pocket_x;

   G4double fwhm_beam;
   G4double fwhm_target;
   //@}

//------------ring D_0_0
     G4VPhysicalVolume * physiSensorStripD_0_0;
     G4VPhysicalVolume* detector1phys;
     G4ThreeVector vector_D_0_0;
     G4double phi_D_0_0;
     G4double coorx_D_0_0;
     G4double coory_D_0_0;
     G4double coorz_D_0_0;
     G4double coorx_D_0_0_e;
     G4double coory_D_0_0_e;
     G4double coorz_D_0_0_e;
     G4double theta_D_0_0;


   //------------ring D_0_1
     G4VPhysicalVolume* physiSensorStripD_0_1;
     G4VPhysicalVolume* physiSensorRing_D_0_1;
     G4ThreeVector vector_D_0_1;
     G4double phi_D_0_1;
     G4double coorx_D_0_1;
     G4double coory_D_0_1;
     G4double coorz_D_0_1;
     G4double coorx_D_0_1_e;
     G4double coory_D_0_1_e;
     G4double coorz_D_0_1_e;
     G4double theta_D_0_1;


    //------------ring D_0_2
     /*G4VPhysicalVolume* physiSensorStripD_0_2;
     G4VPhysicalVolume* physiSensorRing_D_0_2;
     G4ThreeVector vector_D_0_2;
     G4double phi_D_0_2;
     G4double coorx_D_0_2;
     G4double coory_D_0_2;
     G4double coorz_D_0_2;
     G4double coorx_D_0_2_e;
     G4double coory_D_0_2_e;
     G4double coorz_D_0_2_e;
     G4double theta_D_0_2;*/


   G4double Lengthy_dssd_t1;
   G4double Thickness_dssd_t1;
   G4double Lengthx_dssd_t1;

   //! \name UI Messenger
   //@{
   DetectorMessenger * messenger;
   //@}
 };

 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

 #endif
