// $Id: RunAction.cc 102 2010-01-26 16:45:56Z adotti $
/*! @file Analysis.hh
  @based on RunAction and Analysis classes -> J.C. Zamora jczamorac@gmail.com
  @author Flechas (D. Flechas dcflechasg@unal.edu.co)
  @date Nov. 2018
  @brief Defines user class RunAction.
*/
 
#ifndef RUNACTION_HH_
#define RUNACTION_HH_

#include "G4UserRunAction.hh"
 
class G4Run;
 
class RunAction : public G4UserRunAction
{
public:
  RunAction(void);
  virtual ~RunAction();
public:
  virtual G4Run* GenerateRun(void);
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);
private:
  
};
 
#endif /* RUNACTION_HH_ */
