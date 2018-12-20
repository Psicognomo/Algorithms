
#include "iostream"
#include "../pkg/particle.h"
#include "../pkg/particleSimulation.h"

#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TPad.h"
TApplication Runner("gui",0,NULL);

int main() {
  particleSimulation simulator( 20,1,1 );
  double dT = simulator.timeAtNextCollision();
  std::cout<<"Time : "<<dT<<std::endl;

  TCanvas *c0 = new TCanvas();
  c0->Draw();
  
  simulator.move( dT );
  simulator.draw( *c0 );

  Runner.Run(true);
}
