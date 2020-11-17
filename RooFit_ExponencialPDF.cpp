#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooGaussian.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooPlot.h"

//Exercise 1-a: Play with some other p.d.f.
//Exponential PDF

using namespace RooFit;

void RooFit_ExponencialPDF(){


//Observable
RooRealVar x("x","x", 0,5);

//Parameters
//RooRealVar lambda("lambda", "Parameter",-0.1,-5.,0.);
RooRealVar lambda("lambda", "Parameter",0.5);

//PDF Object
RooExponential expo("Exponential Distribution", "Exponential Distribution", x, lambda);

//Generate Events
RooDataSet* data = expo.generate(x,10000);

//Fit
expo.fitTo(*data);

//Plot PDF
RooPlot* xframe = x.frame();
data->plotOn(xframe);
expo.plotOn(xframe);
xframe->Draw();
}
