#include "Riostream.h"
#include "TROOT.h"
#include "TMath.h"
#include "TRandom.h"

//Exericio 1:Escreva um código que estime a área de um disco unitário usando o método Monte Carlo de acerto ou erro. 
//Círculo raio 1
//Inscrito num quadrado de lado 2

#define MAXEVENTS 10000

void montecarlo_area_circulo(){
  std::cout << " Staring Monte Carlo...  " << std::endl;
 
 TCanvas *c = new TCanvas("c","Monte Carlo - Circle Area",0,0,800,600);
 TH2F *MC = new TH2F("MC","Monte Carlo - Circle Area", 100,-1,1,100,-1,1);

  
  // generating sample
  for( int ievent = 0 ; ievent < MAXEVENTS ; ievent++ ){
    // generate random points
    Double_t x = gRandom->Uniform(-1.0,1.0);
    Double_t y = gRandom->Uniform(-1.0,1.0);
   
    if (x*x + y*y <= 1){
    MC->Fill(x,y);
     }
  }
 
 MC->SetMarkerStyle(8);
 MC->SetMarkerColor(2);
 MC->Draw();

}
