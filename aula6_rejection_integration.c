#include "Riostream.h"
#include "TROOT.h"
#include "TMath.h"
#include "TRandom.h"

//Exericio 1:Evaluate the integral using both methods. int_{0}^{3} (1-x*x)*(1-x*x)dx

#define MAXEVENTS 100000

Double_t Function(Double_t n){
   return (1-n*n)*(1-n*n);
}

void aula6_rejection_integration(){
  std::cout << " Staring Monte Carlo...  " << std::endl;
 
 TCanvas *c = new TCanvas("c","Monte Carlo Integration",0,0,800,600);
 TF1 *f = new TF1("f","(1-x*x)*(1-x*x)",0,10);

 TH2F *area_in = new TH2F("area_in","Rejection Sampling Integration: f(x) = (1-x*x)**2", 100,0,3,100,0,100);

//Integration Interval
Int_t x_i = 0;
Int_t x_f = 3;
Int_t y_i = 0;
Double_t area = 192;
Int_t n_acertos = 0;
Double_t integration = 0;

  // generating sample
  for( int ievent = 0 ; ievent < MAXEVENTS ; ievent++ ){
    // generate random points
    Double_t x = gRandom->Uniform(x_i,x_f);
    Double_t y = gRandom->Uniform(0,64);
    if(y <= Function(x)){ 
     area_in->Fill(x,y); 
     n_acertos++;
    }
  }
integration = (n_acertos*area)/MAXEVENTS;

cout << "A área sob a curva é: " << integration << endl;

area_in->Draw();
f->Draw("SAME");
}
