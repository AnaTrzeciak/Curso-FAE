#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooGaussian.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "TFile.h"
#include "RooPolynomial.h"

#include<iostream>
#include<cmath>

using namespace RooFit;
using namespace std;

//Exercise 2 (RooFit): Construct J/Psi + Psi(2S) + Background PDF.
//J/Psi as a Crystall Ball Function
//Psi(2S) as a similar Crystall Ball (Gaussian)
//Background as a polynomial function

void RooFit_Exercise2(){


//Reading input file
TFile *f = new TFile("DataSet_lowstat.root");
RooDataSet *dataset = (RooDataSet*)f->Get("data");

//Observable
RooRealVar mass("mass", "#mu^{+}#mu^{-} invariant mass", 2.,6., "GeV");

//Build a Crystal Ball PDF for J/Psi
RooRealVar meanJpsi("meanJpsi", "Mean of the Crystal Ball",3.1,2.8,3.2);
RooRealVar sigmaJpsi("sigmaJpsi", "The width of the Crystal ball", 0.3,0.0001,1.);
RooRealVar alphaJpsi("alphaJpsi", "Parameter Alpha", 1.5,-5,5);
RooRealVar nJpsi("nJpsi","Parameter n", 1.5,0.5,5);
RooCBShape CBJpsi("CBJpsi","The Crystal Ball Function", mass, meanJpsi, sigmaJpsi, alphaJpsi, nJpsi);

//Build a Gaussian PDF for Psi(2S)
RooRealVar meanPsi2s("meanPsi2s", "Mean of the Crystal Ball",3.7,3.6,3.8);
RooGaussian gaussPsi2s("gaussPsi2s", "Gaussian Distribution for Psi2s", mass, meanPsi2s, sigmaJpsi);

//Build a polynomial function for background
RooRealVar a1("a1", "Parameter a1 background", -0.7,-2.,2.);
RooRealVar a2("a2", "Parameter a2 background", 0.3,-2.,2.);
RooRealVar a3("a3", "Parameter a3 background", -0.03,-2.,2.);
RooPolynomial bkgPDF("bkgPDF", "Background function polynomial", mass, {a1,a2,a3});

//Construct a signal and background PDF
RooRealVar Njpsi("Njpsi","Jpsi signal events", 1500,0.1,10000);
RooRealVar Npsi("Npsi","Psi signal events", 100,0.1,5000);
RooRealVar Nbkg("Nbkg","Nbkg signal events", 5000,0.1,50000);
RooAddPdf model("model", "signal + background",RooArgList(CBJpsi,gaussPsi2s,bkgPDF),RooArgList(Njpsi,Npsi,Nbkg));


//Fit of model
model.fitTo(*dataset);

meanPsi2s.Print();
Njpsi.Print();
Npsi.Print();

//Plotting
RooPlot* xframe = mass.frame(Title("Mass Invariant #mu^{+} #mu^{-}"));
dataset->plotOn(xframe);
model.plotOn(xframe);
model.plotOn(xframe, LineStyle(ELineStyle::kDashed));
xframe->Draw();
}
