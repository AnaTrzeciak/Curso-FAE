#define Analyze_cxx
// The class definition in Analyze.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


//### Compilação: 
// TFile *f = new TFile("experiment.root")
//tree1->Process("Analyze.C")

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("Analyze.C")
// root> T->Process("Analyze.C","some options")
// root> T->Process("Analyze.C+")
//


#include "Analyze.h"
#include <TH2.h>
#include <TStyle.h>

TH1* chi2Hist = NULL;
TH1* ebeamHist = NULL;
TH2* scattHist = NULL;
TH1* ptHist = NULL;
TH1* thetaHist = NULL;
Int_t cont =0;  //contando o numero de eventos com pz < 145.0 GeV
void Analyze::Begin(TTree * /*tree*/)
{
   
   TString option = GetOption();

//###### Arquivo onde está sendo salvo todos os histogramas ######
   TFile *f = new TFile("histograms_cpp.root","RECREATE");


//####### Histogram chi2 ###########
  chi2Hist = new TH1D("chi2","Histogram of Chi2",100,0,2);
  chi2Hist->GetXaxis()->SetTitle("chi2");
  chi2Hist->GetYaxis()->SetTitle("number of events");
 
//####### Histogram ebeam #########
  ebeamHist = new TH1D("ebeamHist", "Histogram of ebeam",100,149.0,151.0); 
  ebeamHist->GetXaxis()->SetTitle("ebeam");
  ebeamHist->GetYaxis()->SetTitle("number of events");
 
//###### Scatterplot chi2 x ebeam  
  scattHist = new TH2F("scattHist", "Scatterplot chi2 x ebeam",100,149.0,151.0,100,0,2);
  scattHist->GetYaxis()->SetTitle("chi2");
  scattHist->GetXaxis()->SetTitle("ebeam");


//###### Histogram pt variable: pt = sqrt(px*px+py*py) ###########
  ptHist = new TH1D("pt","Histogram of pt",100,0,35);
  ptHist->GetXaxis()->SetTitle("pt (GeV)");
  ptHist->GetYaxis()->SetTitle("Number of Events");

//#### Histogram of theta: theta = artg(pt/pz) ###############
  thetaHist = new TH1D("theta", "Histogram of theta", 100, -0.4, 0.4);
  thetaHist->GetXaxis()->SetTitle("theta");
  thetaHist->GetYaxis()->SetTitle("Number of Events");

}

void Analyze::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t Analyze::Process(Long64_t entry)
{
   
   fReader.SetLocalEntry(entry);

   GetEntry(entry);
 //Fill histogram of Chi2
   chi2Hist->Fill(*chi2);

 //Fill histogram of ebeam
   ebeamHist->Fill(*ebeam);

 //Fill scatterplot 
   scattHist->Fill(*ebeam,*chi2);

 //Fill histogram of pt
   Double_t pt;
   pt = TMath::Sqrt((*px)*(*px)+(*py)*(*py));
   ptHist->Fill(pt);

 //Fill histogram of theta
   Double_t theta;
   theta = TMath::ATan2((pt),(*pz));
   thetaHist->Fill(theta);

 //Cut: pz < 145 GeV

 
 if(*pz < 145.0){
  //std:: cout << *pz << endl;
  cont++;
 } 
 
   return kTRUE;
}

void Analyze::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Analyze::Terminate()
{
   
  //chi2Hist->Draw("E");
  //ebeamHist->Fit("gaus");
  //ebeamHist->Draw("E");
  //scattHist->Draw();
  //ptHist->Draw();
  //thetaHist->Draw();
 
 std:: cout << "Number of events with  pz is less than 145 GeV: " << cont << endl; 
 
  chi2Hist->Write();
  ebeamHist->Write();
  scattHist->Write();
  ptHist->Write();
  thetaHist->Write();
  f->Write();
  f->Close();
}
