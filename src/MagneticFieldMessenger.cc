//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
// $Id: MagneticFieldMessenger.cc,v 1.3 2002/12/13 11:34:34 gunter Exp $
// --------------------------------------------------------------
//
#include "MagneticFieldMessenger.hh"
#include "MagneticField.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4ios.hh"

MagneticFieldMessenger::MagneticFieldMessenger(MagneticField * mpga)
:target(mpga)
{
  fieldCmd = new G4UIcmdWithADoubleAndUnit("/mydet/currentValue",this);
  fieldCmd->SetGuidance("solenoid current");
  fieldCmd->SetParameterName("current",true);
  fieldCmd->SetDefaultValue(22.);
  fieldCmd->SetDefaultUnit("tesla");
}

MagneticFieldMessenger::~MagneticFieldMessenger()
{
  delete fieldCmd;
}

void MagneticFieldMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if( command==fieldCmd )
  { target->SetCurrent(fieldCmd->GetNewDoubleValue(newValue)); }
}

G4String MagneticFieldMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  if( command==fieldCmd )
  { cv = fieldCmd->ConvertToString(target->GetCurrent(),""); }

  return cv;
}

