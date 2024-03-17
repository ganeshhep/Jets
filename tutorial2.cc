#include <iostream>
#include "Pythia8/Pythia.h"

int main()
{
  int nevents = 10;
  Pythia8::Pythia pythia;      //every event is a proton-proton collision. 
  pythia.readString("Beams:idA = 2212");
  pythia.readString("Beams:idB = 2212"); 
  pythia.readString("Beams:eCM = 14.e3");
  pythia.readString("SoftQCD:all = on");
  pythia.readString("HardQCD:all = on");

  Pythia8::Hist hpz("Z-momentum distribution", 100, -10, 10);
  
  pythia.init();

  for (int i = 0; i < nevents; i++)
  {
    if (!pythia.next()) continue;
 
    int entries = pythia.event.size(); //number of particles in an event
    
    std::cout << "Event: " << i << std::endl;
    std::cout << "Event size: " << entries << std::endl;

    for (int j = 0; j < entries; j++)
    {
      //a particle informations we want to get.
      int id = pythia.event[j].id();
      double m = pythia.event[j].m();
      double px = pythia.event[j].px();
      double py = pythia.event[j].py();
      double pz = pythia.event[j].pz();
      double pabs = sqrt(pow(px, 2) + pow(py, 2) + pow(pz, 2));

      hpz.fill(pz);
      
      std::cout << id << " " << m << " " << pabs << std::endl;
    }  
  }  
  
  std::cout << hpz << std::endl;
  Pythia8::HistPlot hpl("tutorial2");
  hpl.frame("output", "Momentum distribution", "z-momentum", "entries");
  hpl.add(hpz);
  hpl.plot();
  return 0;

}
