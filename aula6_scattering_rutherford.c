#include "Riostream.h"
#include "TROOT.h"
#include "TMath.h"
#include "TRandom.h"
#include <math.h>

//Exericio 3:Write a code to calculate the differential cross section of the Rutherford scattering

#define MAXEVENTS 3000

void aula6_scattering_rutherford(){
  std::cout << " Staring Code...  " << std::endl;
 
//Constants
Double_t mass_alpha = 6.644e-27;  //kg
Double_t velocity_alpha = 2e7;    //m/s
Double_t charge_alpha = 2*1.602e-19;   //C
Double_t permittivity = 8.854e-12; //kg^-1 m^-3 s^4 A^2 


//Range theta
Double_t theta_i = 0.1*TMath::Pi();
Double_t theta_f = 0.9*TMath::Pi(); 

// open out file
TString file = "aula6_scattering_rutherford-output.txt";
ofstream outfile;
outfile.open(file);
 
 Double_t numerical = (pow(charge_alpha*charge_alpha,2))/(pow(8*TMath::Pi()*permittivity*mass_alpha*velocity_alpha*velocity_alpha,2)); 

 cout << numerical << endl;
 // generating sample
  for( int ievent = 0 ; ievent < MAXEVENTS ; ievent++ ){
    // generate random points
  Double_t theta = gRandom->Uniform(theta_i,theta_f);
 
  Double_t diff_section = numerical*(1/(pow(TMath::Sin(theta/2),4)));

  outfile << theta << " " << diff_section << endl;
  }

}
