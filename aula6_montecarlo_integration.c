#include "Riostream.h"
#include "TROOT.h"
#include "TMath.h"
#include "TRandom.h"

using namespace std;

//Exericio 1:Evaluate the integral using both methods. int_{0}^{3} (1-x*x)*(1-x*x)dx

#define MAXEVENTS 100000

Double_t Function(Double_t n){
   return (1-n*n)*(1-n*n);
}

void aula6_montecarlo_integration(){
  std::cout << " Staring Monte Carlo...  " << std::endl;
 
 
//Integration Interval
Int_t x_i = 0;
Int_t x_f = 3;
Double_t total_function = 0;
Double_t integration = 0;

  // generating sample
  for( int ievent = 0 ; ievent < MAXEVENTS ; ievent++ ){
    // generate random points
    Double_t x = gRandom->Uniform(0,1);
    total_function = total_function + Function(x*3);
    total_function++;
    }

integration = (3*total_function)/MAXEVENTS;
cout << "A área sob a curva é: " << integration << endl;
}
