/// \file include/Run.hh
/// \brief Definition of the Run class
/// @Date Nov. 2018
/// @Author DFlechas, dcflechasg@unal.edu.co

#ifndef Run_h
#define Run_h 1

#include "G4Run.hh"
#include "G4Event.hh"

#include "G4THitsMap.hh"
#include <vector>

class Run : public G4Run {

public:
  // constructor and destructor.
  //  vector of multifunctionaldetector name has to given to constructor.
  Run(void);
  virtual ~Run(void);

  virtual void RecordEvent(const G4Event*);
  virtual void Merge(const G4Run*);
  
private:
  G4int hitsCollID;
  G4String hitsCollName;
};

//

#endif
