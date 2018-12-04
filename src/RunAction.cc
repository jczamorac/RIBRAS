// $Id: RunAction.cc 102 2010-01-26 16:45:56Z adotti $
/*! @file Analysis.hh
  @based on RunAction and Analysis classes -> J.C. Zamora  jczamorac@gmail.com
  @author Flechas (D. Flechas dcflechasg@unal.edu.co)
  @date  Nov. 2018
  @brief  Implements user class RunAction.
*/

#include "Analysis.hh"
#include "RunAction.hh"
#include "Run.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
 
RunAction::RunAction()
  : G4UserRunAction()
  
{
  auto RootManager = G4RootAnalysisManager::Instance();
  RootManager->SetNtupleMerging(true);
  RootManager->SetVerboseLevel(1);
  

  RootManager->CreateH2("X-Y","X (mm) - Y (mm)",500,-100,100,500,-100,100); // Id =0
  RootManager->CreateH2("R-TOF","R (mm) - TOF (s)",100,-1,100,100,50,300); // Id =1

  // *** Creating ntuple: Calorimeter Id = 0
  RootManager->SetFirstNtupleId(0);
  RootManager->CreateNtuple("TelDet", "Telescope Detector"); // Id = 0
  RootManager->CreateNtupleDColumn(0,"K"); // Id = 0
  RootManager->CreateNtupleDColumn(0,"X"); // Id = 1
  RootManager->CreateNtupleDColumn(0,"Y"); // Id = 2
  RootManager->CreateNtupleDColumn(0,"dist"); // Id = 3
  RootManager->CreateNtupleDColumn(0,"time"); // Id = 4
  
  RootManager->FinishNtuple(0);
}

RunAction::~RunAction()
{
  //fSDName.clear();
  delete G4RootAnalysisManager::Instance();
}

G4Run* RunAction::GenerateRun()
{
  // Generate new RUN object, which is specially
  // dedicated for MultiFunctionalDetector scheme.
  //  Detail description can be found in Run.hh/cc.
  return new Run();
}

void RunAction::BeginOfRunAction(const G4Run* aRun )
{
  G4cout<<"### Starting Run: "<<aRun->GetRunID()<<G4endl;
  auto RootManager = G4RootAnalysisManager::Instance();
  std::ostringstream fn;
  //fn <<"Run_"<<runcounter++ ;
  fn <<"Run_"<< aRun->GetRunID();
  RootManager->SetFileName(fn.str().data()); // outRoot
  RootManager->OpenFile();
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}
 
void RunAction::EndOfRunAction( const G4Run* aRun )
{
  //if(!IsMaster()) return;
  G4int nofEvents = aRun->GetNumberOfEvent();
  if (nofEvents == 0) return;
  
  G4cout
    << G4endl
    << "--------------------End of Run-----------------------"
    << G4endl
    << "  The run was " << nofEvents << " events ";
  
  auto RootManager = G4RootAnalysisManager::Instance();
  RootManager->Write();
  RootManager->CloseFile();
  
}
